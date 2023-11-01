// setup

void setup() {
  // Initializing the ports needed for all modules
  Serial.begin(9600);                         // Serial0 and Serial3 must have same baud
  Serial1.begin(9600);                        // Serial1 (piny 19, 18) połączenie z nano (kompas)
  Serial2.begin(9600);                        // Serial2 will print on Bluetooth app terminal
  Serial3.begin(9600);                        // Serial3 (piny 14, 15) połączenie z GPS
  HoverSerial.begin(HOVER_SERIAL_BAUD);
  
  Serial2.println("Konfiguracja");

  // Initializing the interrupt variables
  pinMode(interruptPinTwo, OUTPUT);     // Set pin mode of pin 2 to output
  digitalWrite(interruptPinTwo, LOW);   // Set LED in pin 2 to LOW to start
  objectDetected = false;               // initialize this bool for the interrupt

  /*
    We want to make an interrupt service routine that toggles bool objectDetected

    To avoid "polling" for obstacle avoidance, we only do so when it is necessary
    to "interrupt" the default path of our car from point A to point B

    When the ultrasonic sensors detect an object near it with one of its sensors
    we want it to quickly change the output of digital pin 2 (shown as an LED)
    and in turn trigger the bool objectDetected to change to true.

    When objectDetected changes to true, we break out of the while loop of automation
    program and go to objectAvoid() operations which will do the actual object
    avoidance functions.

    Once objectAvoid() operations are over, the pin should reset to LOW, the bool
    objectDetected should reset to false and we go back to the main while loop
    program which controls the main operations of the car within automation()

    Remember: the default of our program is to go from point A to point B. If there's
    no objects in its path, it should go in a relatively straight line (with some
    corrections to the steering every now and then due to imperfect motors and friction)

    Object avoidance should only be triggered when necessary
  */

  // Car setup
  pinMode(frontSent, OUTPUT);        // front_Trig arduino signal output
  pinMode(frontReceive, INPUT);         // front_Echo arduino signal input

  pinMode(leftSent, OUTPUT);         // left_Trig arduino signal output
  pinMode(leftReceive, INPUT);          // left_Echo arduino signal input

  pinMode(rightSent, OUTPUT);        // right_Trig arduino signal output
  pinMode(rightReceive, INPUT);         // right_Echo arduino signal input

  pinMode(L_motors_speed, OUTPUT);    // left engine speed arduino signal output
  pinMode(R_motors_speed, OUTPUT);    // Arduino signal output of right engine speed

  pinMode(L1, OUTPUT);  // Arduino signal output from left motor rotation direction control
  pinMode(L2, OUTPUT);  // Arduino signal output from left motor rotation direction control
  pinMode(R1, OUTPUT);  // Arduino signaould not find a valid HMC5883L sensor, check wiring!l output from the right engine rotation direction control
  pinMode(R2, OUTPUT);  // Arduino signal output from the right engine rotation direction control

  // Compass Setup
 

  // GPS Coordinates Setup
  /*
    GPS takes a few minutes to power on when powering vehicle for 1st time
    It has no coordinates saved until GPS turns on
    Therefore, we must wait in a while loop until GPS turns on
    and records our current location for the 1st time

    This is essential because otherwise, the vehicle could not have
    initial GPS coordinates to do the proper calculations
  */
  while (latitA == 0.00 && lonA == 0.00) {
    GPSTelemetry();
  }
  //latitB;                 // latitB, lonB are your destination coordinates
  //lonB;                   // They will be inputted from the inputDestination() function

  // Pick RISING for now so that green LED in pin 2 turns on during object avoidance and turns off when done
  // attach the ISR to the changes in pin 2 (shown through a green LED)                 // RISING: LOW to HIGH
  attachInterrupt(digitalPinToInterrupt(interruptPinTwo), activateObjectAvoid, RISING); // RISING, FALLING, CHANGE
  
  inputDestination();       // Go to function to input your destination coordinates
  
  Serial2.println("Konfiguracja ukończona. Start za 5 sekund");
  delay(5000);             // 10 seconds - To give us time to prepare the car

}
