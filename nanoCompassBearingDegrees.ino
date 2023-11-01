#include <QMC5883LCompass.h>

// ustawienia QMC5883L
#define MODE 0x01    //0x00 - uśpienie, 0x01 - ciągły pomiar
#define ODR 0x00     //0x00 - 10Hz, 0x04 - 50Hz, 0x08 - 100Hz, 0x0C - 200Hz
#define RNG 0x00     //0x00 - 2G, 0x10 - 8G
#define OSR 0xC0     //0xC0 - 64próbki, 0x80 - 128, 0x40 - 256, 0x00 - 512

// Wygładzanie
// Wykorzystuje funkcję średniej kroczącej do przechowywania (n) odczytów czujników 
//  i zwracania średnią dla każdej osi.
#define STEPS 10        //1 - 10 int, Liczba kroków, według których należy wygładzić wyniki.
#define ADVANCED true   //bool, True usunie wartości maksymalne i minimalne z każdego kroku

// Kalibracja
#define CALIBRATE true   //Kalibracja włączona
#define X_OFFSET 0
#define X_SCALE 0
#define Y_OFFSET 0
#define Y_SCALE 0
#define Z_OFFSET 0
#define Z_SCALE 0


QMC5883LCompass compass;

void setup(){
  Serial.begin(9600);
  
  compass.init();

  if (CALIBRATE){
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
    compass.setCalibrationOffsets(X_OFFSET, Y_OFFSET, Z_OFFSET);
    compass.setCalibrationScales(X_SCALE, Y_SCALE, Z_SCALE);
    compass.setMode(MODE, ODR, RNG, OSR);
    compass.setSmoothing(STEPS, ADVANCED);
  }
}

void loop() {

  int x, y;

  compass.read();
  
  float heading = atan2f(compass.getX(), compass.getY());




void compassBearingDegrees() {  // The function that updates our current compass bearing

  Vector norm = compass.readNormalize();
   // Calculate heading // atan2
  /*
    You can find declination on: http://magnetic-declination.com/
    (+) Positive or (-) for negative
      For Bytom / Poland declination angle is 4'26E (positive); + 4 = deg, 26 = min
      Formula: (deg + (min / 60.0)) / (180 / M_PI);
      For Los Angeles / USA declination angle is + 11 = deg, 38 = min
  */
  float declinationAngle = (11.0 + (38.0 / 60.0)) / (180 / M_PI);
  heading += declinationAngle;

  if (heading < 0) { // Correct for heading < 0 deg and heading > 360 deg
    heading += 2 * PI;
  }
  if (heading > 2 * PI) {
    heading -= 2 * PI;
  }
  // headingDegrees is now a global so you can use it to compare to gpsAngleDegrees
  headingDegrees = heading * 180 / M_PI; // Convert to degrees

  Serial2.print("Aktualne wskazanie kompasu = ");
  Serial2.println(headingDegrees);

}
