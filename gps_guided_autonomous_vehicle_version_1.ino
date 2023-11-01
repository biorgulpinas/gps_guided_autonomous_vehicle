// Initialization of globals and functions
#include "TinyGPS++.h"
#include <Wire.h>
#include <math.h>
#include <SoftwareSerial.h>

// ########################## DEFINES ##########################

//########## Sterownik silnika ###########
#define HOVER_SERIAL_BAUD   115200      // [-] Baud rate for HoverSerial (used to communicate with the hoverboard)
#define START_FRAME         0xABCD     	// [-] Start frme definition for reliable serial communication
#define TIME_SEND           100         // [ms] Sending time interval
#define SPEED_MAX_TEST      300         // [-] Maximum speed for testing
#define SPEED_STEP          20          // [-] Speed step

SoftwareSerial HoverSerial(2,3);        // RX, TX

// Initializing GPS
TinyGPSPlus gps;                        // GPS object "gps" that takes in NMEA data


//----------------------------- Global Variables -----------------------------//
//----- Sterownik silnika ---------//
uint8_t idx = 0;                        // Index for new data pointer
uint16_t bufStartFrame;                 // Buffer Start Frame
byte *p;                                // Pointer declaration for the new received data
byte incomingByte;
byte incomingBytePrev;

typedef struct{
   uint16_t start;
   int16_t  steer;
   int16_t  speed;
   uint16_t checksum;
} SerialCommand;
SerialCommand Command;

typedef struct{
   uint16_t start;
   int16_t  cmd1;
   int16_t  cmd2;
   int16_t  speedR_meas;
   int16_t  speedL_meas;
   int16_t  batVoltage;
   int16_t  boardTemp;
   uint16_t cmdLed;
   uint16_t checksum;
} SerialFeedback;
SerialFeedback Feedback;
SerialFeedback NewFeedback;

//----- GPS related variables -----//
bool stopTelemetry;               // Used in gpsTelemetry() functions. Breaks the infinite while loop
float latitA, lonA;               // Current Latitude/Longitude (point A)
float latitB, lonB;               // Destination Latitude/Longitude (point B)
float latitC, lonC, latitD, lonD; // Multiple destination coordinates (To be used in later versions)
float gpsAngleDegrees;            // Angle to destination B from current location // float or long
float headingDegrees;             // Compass heading angle in degrees
bool carArrived;                  // for function that checks if we've arrived at destination

//----- Infrared variables -----//
int frontSent = A4;       // controls the impulse sent from the front sensor
int frontReceive = A5;    // controls the impulse received from the front sensor
int leftSent = A2;        // controls the impulse sent from the left sensor
int leftReceive = A3;     // controls the impulse received from the left sensor
int rightSent = A0;       // controls the impulse sent from the right sensor
int rightReceive = A1;    // controls the impulse received from the right sensor

//----- ultrasonic variables -----//
long frontTime, leftTime, rightTime, frontSensor, leftSensor, rightSensor;

//----- Interrupt variables. Const and volatile must be used for ISR -----//
const uint8_t interruptPinTwo = 2;  // Digital pin 2 has an LED that will trigger ISR
volatile bool objectDetected;       // For our ISR interruptLoop() which is for objectAvoid()

//---------------------------- General Functions ----------------------------//

//---------- Menu Functions ----------//
void MenuFunction();			        // The main menu in loop()
void inputDestination();		      // The menu used to input GPS coordinates manually
void multipleDestinations();      // The menu used to input multiple GPS destinations manually
float stringToFloatConversion();  // Returns float int from inputted string text

void automation(float lat1, float long1, float lat2, float long2);			          // The main automation procedures of the vehicle
void obstacleAvoid(float lat1, float long1, float lat2, float long2);			        // The obstacle avoidance procedures of the vehicle
void activateObjectAvoid();		                                                    // The ISR that will allow us to go to objectAvoid()

//---------- GPS Functions ----------//
void GPSTelemetry();			                                              // The function that updates current GPS coordinates
void GPSBearingAngle(float lat1, float long1, float lat2, float long2);	// Calculates bearing angle to destination from current GPS coordinates
float GPSDistance(float lat1, float long1, float lat2, float long2);    // returns distance between destination and current location

//---------- Compass ----------//
void compassBearingDegrees();		    // The function that updates current compass bearing

//--------- Ultrasonic ---------//
void ultrasonicCheck();			        // Stores ultrasonic data (distance) in three globals

//--------- Check functions ---------//
void IsCarFacingDestination();		        // Checks if vehicle is facing destination
bool checkIfWeArrived();		              // Checks if vehicle has arrived at destination

//------------------------ Turning / Movement ------------------------//
void correctBearingTurn();		                  // Corrects vehicle bearing
void DCMotorZero();				                      // Turns off left and right motors
void goStraightShortDistance( int duration );	  // Go straight for a duration input of milliseconds
void goReverseShortDistance( int duration );	  // Go reverse for a duration input of milliseconds
void goStraightAfterObstacle( int duration ); 	// Same as first go straight function
void leftTurnTimed( int duration );		          // Turn left for a duration input of milliseconds
void rightTurnTimed( int duration );		        // Turn right for a duration input of milliseconds
void stopCar();					                        // Stops car for 100 seconds
void stopCarTimed( int duration );		          // Stops car for a duration input of milliseconds
//--------------------------------------------------------------------//
