Laia Bombi
Nerea González 

*Grup 13*

### Projecte final
## SONIACE
___
L'objectiu del projecte és aplicar els coneixements obtinguts al llarg de les classes de laboratori de l'assignatura de Processadors Digitals.
El nostre projecte utilitza una sèrie de dispositius i perifèrics que pretenen simular una espècie de Smartwatch. Hem utilitzat una pantalla LED com a display per mostrar les dades que recullen dos sensors: el primer és un dispositiu I2C MPU6050 que té la funció de acceleròmetre, giroscòpi i sensor de temperatura; el segon és un sensor d'ultrasons. 
___
#### Fotos del montatge
![](smartwatch.jpeg )

![](smartwatch_2.jpeg)

![](smartwatch_3.jpeg )
___
#### Connexions dispositius amb ESP32
Pantalla LED:
![](connexio_pantalla.png )

MPU-5060:
![](connexio_mpu.png )

Ultrasons:
![](connexio_ultras.png )
___

#### Explicació del codi
Primer de tot incluim totes les llibreries necessàries. Per la pantalla es necessita la *Arduino_GFX_Library.h*, per el sensor d'ultrasons es necessita la *NewPing.h* i per l'acceleròmetre, giroscopi i sensor de temperatura es necessiten les llibreries *Adafruit_MPU6050.h*, *Adafruit_Sensor.h* i *Wire.h*.
```
#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include "NewPing.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
```
Ara definim les constants per asignar els pins de cada dispositiu i els objectes necessaris per controlar els sensors
```
// PANTALLA
#define TFT_SCK 18
#define TFT_MOSI 23
#define TFT_MISO 19
#define TFT_CS 22 
#define TFT_DC 21 
#define TFT_RESET 17

Arduino_ESP32SPI bus = Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO);
Arduino_ILI9341 display = Arduino_ILI9341(&bus, TFT_RESET);

//ULTRASONS
int trigPin = 4; 
int echoPin = 2;
NewPing sonar(trigPin, echoPin);

//ACCEL, GIRO, TEMP
Adafruit_MPU6050 mpu;
```

```
void setup() { 
```
Comencem configurant la inicialització de la pantalla.
Després configurem el fons de la pantalla al color blanc pero poder comensar a escriure a la pantalla cridant al mètode **fillScreen**. Després crdidem el mètode **setCursor** per establir la posició del cursor, que determinarà on s'escriurà el text.
Ara establim el tamany del text cridant al mètode **setTextSize** i el color amb **setTextColor**
Per imprimir text per pantalla cridarem al mètode **print**.
```   
//INCIAR PANTALLA
    Serial.begin(9600);
    
    display.begin();
    display.fillScreen(WHITE);
    display.setCursor(20, 20);
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.println("¡Bienvenido/a!");
    
```
Inicialitzem el sensor MPU-6050.
```
//ACCEL, GIRO, TEMP
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
```
Configurem el rang de medició de l'acceleròmetre, després el del giroscopi i per últim el de la temperatura.
```
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
 ```
 Utilitzem la funció **ping_median** per obtenir la distància (en cm) de l'objecte detectat i registrar la distància en una nova variable.
 El que li diem es que si la ditancia és menor a 2 cm i major a 400 cm està fora de rang i, si no és així i es troba dins del rang doncs que registri la distància i la imprimeixi per la pantalla.
 ```  
 // ULTRASONIDO  
    display.println("");
    display.println("MEDIDAS ULTRASONIDO");
    display.println("");
    delay(50);
    Serial.println("");
    delay(100);
  
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
```
Per l'obtenció de les dades el MPU-6050 primer necessitem obtenir nous events de sensor amb les lectures actuals amb la funció **sensors_event_t** i **getEvent**.
Després imprimim per pantalla les mesures dels tres sensors.
```

//ACCEL, GIRO, TEMP
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
```
No posem res al void loop perque si no a la pantalla sortirien dades sense parar.
```
void loop () {}
```







