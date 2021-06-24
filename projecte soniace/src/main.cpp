#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include "NewPing.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// PANTALLA
#define TFT_SCK 18
#define TFT_MOSI 23
#define TFT_MISO 19
#define TFT_CS 22 
#define TFT_DC 21 
#define TFT_RESET 17

//ULTRASONS
int trigPin = 4; 
int echoPin = 2;
NewPing sonar(trigPin, echoPin);

//ACCELEROMETRE
Adafruit_MPU6050 mpu;
Arduino_ESP32SPI bus = Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO);
    Arduino_ILI9341 display = Arduino_ILI9341(&bus, TFT_RESET);
void setup() { 
//INCIAR PANTALLA
    Serial.begin(9600);
    
    display.begin();
    display.fillScreen(WHITE);
    display.setCursor(20, 20);
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.println("¡Bienvenido/a!");
    
/*
    while (!Serial){
        delay(10); 
    }    
    Serial.println("Adafruit MPU6050 test!");

       if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        while (1) {
            delay(10);
        }
    }
    Serial.println("MPU6050 Found!");
*/


   mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    switch (mpu.getAccelerometerRange()) {
        case MPU6050_RANGE_2_G:
        break;
        case MPU6050_RANGE_4_G:
        break;
        case MPU6050_RANGE_8_G:
        break;
        case MPU6050_RANGE_16_G:
        break;
    }
   
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    switch (mpu.getGyroRange()) {
        case MPU6050_RANGE_250_DEG:
        break;
        case MPU6050_RANGE_500_DEG:
        break;
        case MPU6050_RANGE_1000_DEG:
        break;
        case MPU6050_RANGE_2000_DEG:
        break;
    }
    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
    switch (mpu.getFilterBandwidth()) {
        case MPU6050_BAND_260_HZ:
        break;
        case MPU6050_BAND_184_HZ:
        break;
        case MPU6050_BAND_94_HZ:
        break;
        case MPU6050_BAND_44_HZ:
        break;
        case MPU6050_BAND_21_HZ:
        break;
        case MPU6050_BAND_10_HZ:
        break;
        case MPU6050_BAND_5_HZ:
        break;
    }
     
    display.println("");
    display.println("MEDIDAS ULTRASONIDO");
    display.println("");
    


    delay(50);
    Serial.println("");
    delay(100);
  
// ULTRASONIDO

  float distance = sonar.ping_median(5);
    if(distance>400 || distance<2) {
        display.println("Out of range");
    } 
    else {
        int cont = 0;
        while(cont<=5){ 
        display.print("Distancia: ");
        display.print(distance, 2); display.println(" cm");
        display.println("");
        cont++; }
        }

// ACELERÓMETRO
int cont2=0;
while(cont2<=5){
sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    display.println("MEDIDAS ACCELEROMETRO");
    display.print("X: ");
    display.print(a.acceleration.x);
    display.print(", Y: ");
    display.print(a.acceleration.y);
    display.print(", Z: ");
    display.print(a.acceleration.z);
    display.println(" m/s^2");
    display.println("");
    display.println("MEDIDAS ROTACION");
    display.print("X: ");
    display.print(g.gyro.x);
    display.print(", Y: ");
    display.print(g.gyro.y);
    display.print(", Z: ");
    display.print(g.gyro.z);
    display.println(" rad/s");
    display.println("");
    display.println("MEDIDAS TEMPERATURA");
    display.print("Temperatura: ");
    display.print(temp.temperature);
    display.println(" grados");
    display.println("");

    display.println("");
    delay(500);
    cont2++;
}


}

void loop () {}


  /*  float distance = sonar.ping_median(5);
    if(distance>400 || distance<2) {
        display.println("Out of range");
    } 
    else {
        int cont = 0;
        while(cont<=5){ 
        display.print("Distancia: ");
        display.print(distance, 2); display.println(" cm");
        display.println("");
        cont++; }
        }*/

        // iniciar=false;}}}

       
     
    /*
    // Acc.
    delay(500);
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    display.print("kk"); */
    

/*
//ACCELEROMETRE
    Serial.begin(115200);
    while (!Serial){
        delay(10); 
    }    
    Serial.println("Adafruit MPU6050 test!");

    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        while (1) {
            delay(10);
        }
    }
    Serial.println("MPU6050 Found!");

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    switch (mpu.getAccelerometerRange()) {
        case MPU6050_RANGE_2_G:
        break;
        case MPU6050_RANGE_4_G:
        break;
        case MPU6050_RANGE_8_G:
        break;
        case MPU6050_RANGE_16_G:
        break;
    }
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    switch (mpu.getGyroRange()) {
        case MPU6050_RANGE_250_DEG:
        break;
        case MPU6050_RANGE_500_DEG:
        break;
        case MPU6050_RANGE_1000_DEG:
        break;
        case MPU6050_RANGE_2000_DEG:
        break;
    }
    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
    switch (mpu.getFilterBandwidth()) {
        case MPU6050_BAND_260_HZ:
        break;
        case MPU6050_BAND_184_HZ:
        break;
        case MPU6050_BAND_94_HZ:
        break;
        case MPU6050_BAND_44_HZ:
        break;
        case MPU6050_BAND_21_HZ:
        break;
        case MPU6050_BAND_10_HZ:
        break;
        case MPU6050_BAND_5_HZ:
        break;
    }
    Serial.println("");
    delay(100);
}

void loop() {
    Arduino_ESP32SPI bus = Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO);
    Arduino_ILI9341 display = Arduino_ILI9341(&bus, TFT_RESET);
    display.begin();
//ULTRASONS
    display.println("MEDIDAS ULTRASONIDO");
    
    
//ACCELEROMETRE

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    display.println("MEDIDAS ACCELERÓMETRO");
    display.print("X: ");
    display.print(a.acceleration.x);
    display.print(", Y: ");
    display.print(a.acceleration.y);
    display.print(", Z: ");
    display.print(a.acceleration.z);
    display.println(" m/s^2");

    display.println("MEDIDAS ROTACIÓN");
    display.print("X: ");
    display.print(g.gyro.x);
    display.print(", Y: ");
    display.print(g.gyro.y);
    display.print(", Z: ");
    display.print(g.gyro.z);
    display.println(" rad/s");

    display.println("MEDIDAS TEMPERATURA");
    display.print("Temperature: ");
    display.print(temp.temperature);
    display.println(" ºC");

    display.println("");
    delay(500);


}

*/