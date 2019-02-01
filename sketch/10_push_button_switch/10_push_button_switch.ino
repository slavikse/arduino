#define BUTTON_PIN 3
#define LED_PIN 13

bool buttonWasUp = true;
bool ledEnabled = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  bool buttonIsUp = digitalRead(BUTTON_PIN);

  if (buttonWasUp && !buttonIsUp) {
    Serial.println(buttonIsUp);
    delay(10);
    buttonIsUp = digitalRead(BUTTON_PIN);

    if (!buttonIsUp) {
      ledEnabled = !ledEnabled;
      digitalWrite(LED_PIN, ledEnabled);
    }
  }

  buttonWasUp = buttonIsUp;
}
