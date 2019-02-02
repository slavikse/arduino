#include <math.h>

int minute = 1;

void setup()
{
  Serial.begin(9600);
  Serial.println("Minute\tTemperature");
}

void loop()
{
  float v = analogRead(A0) * 5.0 / 1024.0;
  float temperature = -14.46 * log(10000.0 * v / (5.0 - v) / 27074.0);

  Serial.print(minute);
  Serial.print("\t");
  Serial.print(temperature);

  delay(60000);
  minute += 1;
}
