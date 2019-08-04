#include <dht11.h>
 
dht11 DHT11;
#define PIN_DHT11 2
 
void setup()
{
  Serial.begin(9600);
}
 
void loop()
{
  DHT11.read(PIN_DHT11);
  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);
  Serial.print("Temperature (oC): ");
  Serial.println((float)DHT11.temperature, 2);
  delay(500);
}
