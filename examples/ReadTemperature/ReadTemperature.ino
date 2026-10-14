/*
  Reading Ambient and Object temperatures 
  Author: Bonezegei (Jofel Batutay)
  Date: October 14, 2026
*/

#include <Bonezegei_MLX90614.h>

Bonezegei_MLX90614 mlx(0x5A);

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Initializing MLX90614 Sensor...");

  if (!mlx.begin()) {
    Serial.println("Error: MLX90614 not detected. Check I2C wiring!");
    while (1);
  }

  Serial.println("MLX90614 Initialized Successfully.\n");
}

void loop() {
  float ambC = mlx.getAmbientC();
  float ambF = mlx.getAmbientF();
  float objC = mlx.getObjectC();
  float objF = mlx.getObjectF();

  Serial.print("Ambient Temp: ");
  Serial.print(ambC, 2);
  Serial.print(" C  |  ");
  Serial.print(ambF, 2);
  Serial.println(" F");

  Serial.print("Object  Temp: ");
  Serial.print(objC, 2);
  Serial.print(" C  |  ");
  Serial.print(objF, 2);
  Serial.println(" F");

  Serial.println("------------------------------------");
  delay(1000);
}