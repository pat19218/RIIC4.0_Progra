#include <Adafruit_SHT31.h>
#include <Wire.h>

Adafruit_SHT31 sensor = Adafruit_SHT31();

void setup() {
  Serial.begin(115200);
  if (sensor.begin(0x44)) {
    Serial.println("Sensor encontrado");
  } else {
    Serial.println("Sensor NO encontrado");
    while (1) {
      delay(10);
    }
  }

}

void loop() {
  float temp = sensor.readTemperature();
  float hume = sensor.readHumidity();

  //isnan -> no hay numero
  if (isnan(temp)){
    Serial.println("Error al obtener temperatura");
  }else{
    Serial.print("Temperatura = ");
    Serial.print(temp);
    Serial.println("°C");
  }

  if (isnan(hume)){
    Serial.println("Error al obtener humedad");
  }else{
    Serial.print("Humedad = ");
    Serial.print(hume);
    Serial.print("%");
  }

  Serial.println();
  delay(1000);
}
