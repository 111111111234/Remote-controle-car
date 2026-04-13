#include <WiFi.h>
#include <esp_now.h>

// DIRECTION PINS
#define A_1A 27
#define A_2A 33
#define B_1A 26
#define B_2A 25

// PWM PINS
#define ENA 32
#define ENB 14

typedef struct {
  int x;
  int y;
  int button;
} JoystickData;

JoystickData data;

// PWM channels
const int freq = 1000;
const int resolution = 8;

void setupPWM() {
  ledcAttach(ENA, freq, resolution);
  ledcAttach(ENB, freq, resolution);
}

// MOTOR CONTROL
void setMotor(int leftSpeed, int rightSpeed) {

  // direction LEFT
  if(leftSpeed > 0){
    digitalWrite(A_1A, HIGH);
    digitalWrite(A_2A, LOW);
  }else if(leftSpeed < 0){
    digitalWrite(A_1A, LOW);
    digitalWrite(A_2A, HIGH);
  }else{
    digitalWrite(A_1A, LOW);
    digitalWrite(A_2A, LOW);
  }

  // direction RIGHT
  if(rightSpeed > 0){
    digitalWrite(B_1A, HIGH);
    digitalWrite(B_2A, LOW);
  }else if(rightSpeed < 0){
    digitalWrite(B_1A, LOW);
    digitalWrite(B_2A, HIGH);
  }else{
    digitalWrite(B_1A, LOW);
    digitalWrite(B_2A, LOW);
  }

  // PWM speed (0–255)
  ledcWrite(ENA, abs(leftSpeed));
  ledcWrite(ENB, abs(rightSpeed));
}

// STOP
void stopMotors() {
  ledcWrite(ENA, 0);
  ledcWrite(ENB, 0);

  digitalWrite(A_1A, LOW);
  digitalWrite(A_2A, LOW);
  digitalWrite(B_1A, LOW);
  digitalWrite(B_2A, LOW);
}

// ESP-NOW receive
void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
  memcpy(&data, incomingData, sizeof(data));

  int y = data.x - 2048;
  int x = 2048 - data.y;

  int leftMotor  = (y + x * 0.7)/4;
  int rightMotor = (y - x * 0.7)/4;

  leftMotor  = constrain(leftMotor,  -255, 255);
  rightMotor = constrain(rightMotor, -255, 255);

  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.println(y);
  Serial.print(" L: ");
  Serial.print(leftMotor);
  Serial.print(" R: ");
  Serial.println(rightMotor);

  if (abs(x) < 200 and abs(y) < 200){
    stopMotors();
    return;
  }


  setMotor(leftMotor, rightMotor);
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);

  pinMode(A_1A, OUTPUT);
  pinMode(A_2A, OUTPUT);
  pinMode(B_1A, OUTPUT);
  pinMode(B_2A, OUTPUT);

  setupPWM();

  stopMotors();
}

void loop() {}
