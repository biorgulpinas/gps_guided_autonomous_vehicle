void Send(int16_t uSteer, int16_t uSpeed)
{
  // Create command
  Command.start    = (uint16_t)START_FRAME;
  Command.steer    = (int16_t)uSteer;
  Command.speed    = (int16_t)uSpeed;
  Command.checksum = (uint16_t)(Command.start ^ Command.steer ^ Command.speed);

  // Write to Serial
  HoverSerial.write((uint8_t *) &Command, sizeof(Command)); 
}

// ########################## RECEIVE ##########################
void Receive()
{
    // Check for new data availability in the Serial buffer
    if (HoverSerial.available()) {
        incomingByte 	  = HoverSerial.read();                                   // Read the incoming byte
        bufStartFrame	= ((uint16_t)(incomingByte) << 8) | incomingBytePrev;       // Construct the start frame
    }
    else {
        return;
    }

  // If DEBUG_RX is defined print all incoming bytes
  #ifdef DEBUG_RX
        Serial.print(incomingByte);
        return;
    #endif

    // Copy received data
    if (bufStartFrame == START_FRAME) {	                    // Initialize if new data is detected
        p       = (byte *)&NewFeedback;
        *p++    = incomingBytePrev;
        *p++    = incomingByte;
        idx     = 2;	
    } else if (idx >= 2 && idx < sizeof(SerialFeedback)) {  // Save the new received data
        *p++    = incomingByte; 
        idx++;
    }	
    
    // Check if we reached the end of the package
    if (idx == sizeof(SerialFeedback)) {
        uint16_t checksum;
        checksum = (uint16_t)(NewFeedback.start ^ NewFeedback.cmd1 ^ NewFeedback.cmd2 ^ NewFeedback.speedR_meas ^ NewFeedback.speedL_meas
                            ^ NewFeedback.batVoltage ^ NewFeedback.boardTemp ^ NewFeedback.cmdLed);

        // Check validity of the new data
        if (NewFeedback.start == START_FRAME && checksum == NewFeedback.checksum) {
            // Copy the new data
            memcpy(&Feedback, &NewFeedback, sizeof(SerialFeedback));

            // Print data to built-in Serial
            Serial.print("1: ");   Serial.print(Feedback.cmd1);
            Serial.print(" 2: ");  Serial.print(Feedback.cmd2);
            Serial.print(" 3: ");  Serial.print(Feedback.speedR_meas);
            Serial.print(" 4: ");  Serial.print(Feedback.speedL_meas);
            Serial.print(" 5: ");  Serial.print(Feedback.batVoltage);
            Serial.print(" 6: ");  Serial.print(Feedback.boardTemp);
            Serial.print(" 7: ");  Serial.println(Feedback.cmdLed);
        } else {
          Serial.println("Non-valid data skipped");
        }
        idx = 0;    // Reset the index (it prevents to enter in this if condition in the next cycle)
    }

    // Update previous states
    incomingBytePrev = incomingByte;
}

void DCMotorZero() {            // The function that turns off the motors. dcmotoZero() must go after ultrasonicCheck()
  analogWrite(L_motors_speed, 0);
  analogWrite(R_motors_speed, 0);

  analogWrite(L1, 0);
  analogWrite(L2, 0);
  analogWrite(R1, 0);
  analogWrite(R2, 0);
}

void goReverseShortDistance( int duration ) {   // The function that makes us go in reverse for specified duration

  analogWrite(L_motors_speed, 153); // 60, 100
  analogWrite(R_motors_speed, 153);

  analogWrite(L1, 0);
  analogWrite(L2, 255);
  analogWrite(R1, 255);
  analogWrite(R2, 0);
  delay(duration);

}

void goStraightShortDistance( int duration ) {  // The function that makes us go straight for specified duration

  analogWrite(L_motors_speed, 153); // 60, 100 // THESE COMMANDS MAKE ROBOT GO STRAIGHT
  analogWrite(R_motors_speed, 153); // 153    // RIGHT HAS MORE TORQUE THAN LEFT

  analogWrite(L1, 255); // 204
  analogWrite(L2, 0);
  analogWrite(R1, 0);
  analogWrite(R2, 255); // 255 // 204
  delay(duration);

}

void goStraightAfterObstacle( int duration ) {  // The function that makes us go straight after turning away from obstacle

  analogWrite(L_motors_speed, 220); // 51, 102
  analogWrite(R_motors_speed, 220);

  analogWrite(L1, 255); // 204
  analogWrite(L2, 0);
  analogWrite(R1, 0);
  analogWrite(R2, 255); // 255 // 204
  delay(duration);

}

void leftTurnTimed( int duration ) {              // The function to make the robot turn left for specified duration

  analogWrite(L_motors_speed, 220);  // 120 // 204
  analogWrite(R_motors_speed, 220); // 120

  analogWrite(L1, 0);     // 0
  analogWrite(L2, 255);   // 255
  analogWrite(R1, 0);     // 0
  analogWrite(R2, 255);   // 255
  delay(duration);        // 700

}

void rightTurnTimed( int duration ) {             // The function to make the robot turn right for specified duration

  analogWrite(L_motors_speed, 220);  // 120 // 204
  analogWrite(R_motors_speed, 220); // 120

  analogWrite(L1, 255); // 255
  analogWrite(L2, 0);   // 0
  analogWrite(R1, 255); // 255
  analogWrite(R2, 0);   // 0
  delay(duration);      // 800

}

void stopCar() {                                // The function that stops car for a long delay (100 seconds)

  analogWrite(L_motors_speed, 0);
  analogWrite(R_motors_speed, 0);

  analogWrite(L1, 0); // 0
  analogWrite(L2, 0); // 0
  analogWrite(R1, 0); // 0
  analogWrite(R2, 0); // 0
  delay(100000); // Stop car for one hundred seconds
  // WE ARE DONE IF WE REACH THIS POINT!!!

}

void stopCarTimed( int duration ) {             // Stop the car for a specified duration. Useful for delays

  analogWrite(L_motors_speed, 0);
  analogWrite(R_motors_speed, 0);

  analogWrite(L1, 0);
  analogWrite(L2, 0);
  analogWrite(R1, 0);
  analogWrite(R2, 0);
  delay(duration);                              // Stop car for amount of duration

}
