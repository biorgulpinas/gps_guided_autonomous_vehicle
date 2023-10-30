// Main menu in loop()

void MenuFunction() {           // The menu that will run infinitely in the loop()

  char b, c;
  bool Quit = false;
  // Print statements to show available character options
  Serial2.println("Menu główne");
  Serial2.println("'o': opcje");
  Serial2.println("'u': automatyzacja");
  Serial2.println("'w': do przodu");
  Serial2.println("'s': do tyłu");
  Serial2.println("'a': skręć w lewo");
  Serial2.println("'d': skręć w prawo");
  Serial2.println("'x': stop");
  Serial2.println("'e': wyjdź z menu");
  Serial2.println("'i': ustaw współżędne celu");
  Serial2.println("'m': ustaw współżędne wielu celów");
  delay(50);

  while (!Quit) {                   // As long as Quit isn't true, this switch/case menu will run infinitely
    DCMotorZero();                  // For the car, you need the stop function in place while it awaits commands
    if (Serial2.available() > 0) {
      b = Serial2.read();
      switch (b) {
        case 'u':     // Letter u
          Serial2.println("Rozpoczęcie procedury automatyzacji");
          automation(latitA, lonA, latitB, lonB);                     // The function that activates the car's automation functions
          if (latitC == 0.00 && lonC == 0.00) {
            Serial2.println("Niema więcej celów.");
            delay(3000);
            break;
          }
          GPSTelemetry();
          automation(latitA, lonA, latitC, lonC);
          if (latitD == 0.00 && lonD == 0.00) {
            Serial2.println("Niema więcej celów.");
            delay(3000);
            break;
          }
          GPSTelemetry();
          automation(latitA, lonA, latitD, lonD);
          Serial2.println("MISJA ZAKOŃCZONA");
          break;
        case 'w':     // Letter w
          Serial2.println("Do przodu");
          goStraightShortDistance( 1200 );  // Make car go forward for 1200 milliseconds (manual control)
          break;
        case 's':     // Letter s
          Serial2.println("Do tyłu");
          goReverseShortDistance( 1200 );   // Make care go reverse for 1200 milliseconds (manual control)
          break;
        case 'a':     // Letter a
          Serial2.println("W lewo");
          leftTurnTimed( 1300 );              // Turn left for 1200 milliseconds (manual control)
          break;
        case 'd':     // Letter d
          Serial2.println("W prawo");
          rightTurnTimed( 1200 );             // Turn right for 1200 milliseconds (manual control)
          break;
        case 'x':     // Letter x
          Serial2.println("Stop na 10s ");
          stopCarTimed(10000);              // Stop car for 10 seconds
          delay(1000);                      // This is helpful for inputting multiple commands at once
          break;
        case 'i':     // Letter i
          Serial2.println("Współrzędne celu");
          inputDestination();              // Go to function to input new destination
          break;                           // This only works for ONE destination
        case 'm':     // Letter m
          Serial2.println("Współrzędne wielu celów");
          multipleDestinations();               // Go to function to input THREE destinations
          break;                                // This only works for MULTIPLE destination
        case 'e':     // Letter e
          Serial2.println("Wyjście z menu.");   // Quit the menu
          Quit = true;                            // This wont do anything because there's nothing after
          break;                                  // MenuFunction() in loop. It'll just go back to MenuFunction()
        case 'o':     // Letter o
            Serial2.println("'o': opcje");
            Serial2.println("'u': automatyzacja");
            Serial2.println("'w': do przodu"");
            Serial2.println("'s': do tyłu");
            Serial2.println("'a': skręć w lewo");
            Serial2.println("'d': skręć w prawo");
            Serial2.println("'x': stop");
            Serial2.println("'e': wyjdź z menu");
            Serial2.println("'i': ustaw współżędne celu");
            Serial2.println("'m': ustaw współżędne wielu celów");
          break;
      }
      delay(50);
    }
  }
}
