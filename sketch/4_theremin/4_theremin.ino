#define BUZZER_PIN 3
#define LDR_PIN A0

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  int val;
  int frequency;

  val = analogRead(LDR_PIN);
  frequency = map(val, 0, 1023, 0, 10000);

  tone(BUZZER_PIN, frequency, 10);
}
