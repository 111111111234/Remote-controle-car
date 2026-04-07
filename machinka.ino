#define A_2A 7 // назад
#define A_1A 6 // вперед
#define B_1A 4 // вперед
#define B_2A 5 // назад

void setup() {
   pinMode(A_2A, OUTPUT);
   pinMode(A_1A, OUTPUT);
   pinMode(B_2A, OUTPUT);
   pinMode(B_1A, OUTPUT);

   digitalWrite(A_2A, LOW);
   digitalWrite(A_1A, LOW);
   digitalWrite(B_2A, LOW);
   digitalWrite(B_1A, LOW);
}

void loop() {
   digitalWrite(B_2A, HIGH); 
}
