#include <QMC5883LCompass.h>


//#### ustawienia QMC5883L ####
//
#define MODE 0x01    //0x00 - uśpienie, 0x01 - ciągły pomiar
#define ODR 0x00     //0x00 - 10Hz, 0x04 - 50Hz, 0x08 - 100Hz, 0x0C - 200Hz
#define RNG 0x00     //0x00 - 2G, 0x10 - 8G
#define OSR 0xC0     //0xC0 - 64próbki, 0x80 - 128, 0x40 - 256, 0x00 - 512
//#############################


// ####### Wygładzanie ########
//
//*****************************
// Wykorzystuje funkcję średniej kroczącej do przechowywania (n) odczytów czujników 
//  i zwracania średnią dla każdej osi.
//*****************************
#define STEPS 10        //1 - 10 int, Liczba kroków, według których należy wygładzić wyniki.
#define ADVANCED true   //bool, True usunie wartości maksymalne i minimalne z każdego kroku
//#############################

// ######## Opuznienie ########
//
#define DELAY 500   //Opuznienie w ms należy ustawić zależnie od poziomu wygładzania i próbkowania
//#############################

//######## Kalibracja #########
//
#define CALIBRATE true   //Kalibracja włączona
#define X_OFFSET 0
#define X_SCALE 0
#define Y_OFFSET 0
#define Y_SCALE 0
#define Z_OFFSET 0
#define Z_SCALE 0
//#############################

//
QMC5883LCompass compass;
//*****************************

//########## SETUP ############
void setup(){
  Serial.begin(9600);

  // incjowanie komunikacji z czujnikiem
  compass.init();
  compass.setMode(MODE, ODR, RNG, OSR); //ustawienie parametrów czujnika
  compass.setSmoothing(STEPS, ADVANCED); //ustawienie parametrów funkcji wygładzającej

  // Czy aktywowana kalibracja
  if (CALIBRATE){
    // Proces kalibracji
    Serial.println("Kalibracja rospocznie się za 5s...");
    delay(5000);
    Serial.println("Kalibracja! Poruszaj czujnikiem...");
    compass.calibrate();
    Serial.println("Zrobione. Skopiuj wyniki kalibracji");
    Serial.println();
    Serial.print("OFSET");
    Serial.print(compass.getCalibrationOffset(0));
    Serial.print(", ");
    Serial.print(compass.getCalibrationOffset(1));
    Serial.print(", ");
    Serial.print(compass.getCalibrationOffset(2));
    Serial.println();
    Serial.print("SKALA");
    Serial.print(compass.getCalibrationScale(0));
    Serial.print(", ");
    Serial.print(compass.getCalibrationScale(1));
    Serial.print(", ");
    Serial.print(compass.getCalibrationScale(2));
    Serial.println();
  }
  else{
    // Kalibracja nieaktywna ustawiane są stałe kalibracji
    compass.setCalibrationOffsets(X_OFFSET, Y_OFFSET, Z_OFFSET);
    compass.setCalibrationScales(X_SCALE, Y_SCALE, Z_SCALE);
    
  }
}

void loop() {

  int x, y;
  float heading = 0;
  float headinfDegrees = 0;

  compass.read();
  heading = atan2f(compass.getX(), compass.getY());

  // headingDegrees is now a global so you can use it to compare to gpsAngleDegrees
  headingDegrees = heading * 180 / M_PI; // Convert to degrees

  Serial.println(headingDegrees);
 
  delay(DELAY);
}
