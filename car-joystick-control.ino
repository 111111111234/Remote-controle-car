#include <WiFi.h>
#include <esp_now.h>

#define X 34
#define Y 35
#define BUTTON 25

// Data packet sent via ESP-NOW (joystick state)
typedef struct{
  int x;
  int y;
  int button;
}JoystickData;
JoystickData data;

//mac address
uint8_t receivMac[] = {0x14, 0x33, 0x5C, 0x09, 0x22, 0x50};

// Configuration of ESP-NOW receiver (peer device)
esp_now_peer_info_t peerInfo;

//settings
void setup() {
  Serial.begin(115200);
  pinMode(BUTTON, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  memset(&peerInfo, 0, sizeof(peerInfo));
  memcpy(peerInfo.peer_addr, receivMac, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

//data send
void loop() {
  data.x = analogRead(X);
  data.y = analogRead(Y);
  data.button = digitalRead(BUTTON);

  esp_now_send(receivMac, (uint8_t *) &data, sizeof(data));
  delay(50);
}
