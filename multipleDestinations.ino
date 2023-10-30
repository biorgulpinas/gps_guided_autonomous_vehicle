void multipleDestinations() {           // The menu that will run infinitely in the loop()

  char g;
  bool Quit = false;

  Serial2.println("Menu wielu celów");
  Serial2.println("Możesz wyznaczyć trzy kolejne cele");
  delay(1000);
  Serial2.println("Wprowadź odpowiedni znak, żeby uzyskać dostęp do wybranej opcji.");
  Serial2.println("'1': Cel 1   '2': Cel 2   '3': Cel 3   ");
  Serial2.println("'e': Wyjdź z menu  's': Pokaż cele  'd': Wyświetl opcje");
  delay(50);

  while (!Quit) {                   // As long as Quit isn't true, this switch/case menu will run infinitely
    if (Serial2.available() > 0) {
      g = Serial2.read();
      switch (g) {
        case '1':     // Destination 1
          Serial2.println("Wprowadź współrzędną szerokości geograficznej pierwszego miejsca docelowego:");
          latitB = stringToFloatConversion();
          Serial2.println("Wprowadź współrzędną długości graficznej pierwszego miejsca docelowego:");
          lonB = stringToFloatConversion();
          delay(50);
          Serial2.println("Współrzędne pierwszego celu:");
          Serial2.println(latitB, 6);
          Serial2.println(lonB, 6);
          break;
        case '2':     // Destination 2
          Serial2.println("Wprowadź współrzędną szerokości geograficznej drugiego miejsca docelowego:");
          latitC = stringToFloatConversion();
          Serial2.println("Wprowadź współrzędną długości graficznej drugiego miejsca docelowego:");
          lonC = stringToFloatConversion();
          delay(50);
          Serial2.println("Współrzędne drugiego celu:");
          Serial2.println(latitC, 6);
          Serial2.println(lonC, 6);
          break;
        case '3':     // Destination 3
          Serial2.println("Wprowadź współrzędną szerokości geograficznej trzeciego miejsca docelowego:");
          latitD = stringToFloatConversion();
          Serial2.println("Wprowadź współrzędną długości graficznej trzeciego miejsca docelowego:");
          lonD = stringToFloatConversion();
          delay(50);
          Serial2.println("Współrzędne trzeciego celu:");
          Serial2.println(latitD, 6);
          Serial2.println(lonD, 6);
          break;
        case 'e':     // Letter e
          Serial2.println("Wychodzenie z menu wielu celów.");   // Quit the menu
          Quit = true;
          break;
        case 's':     // Letter s
          Serial2.println("Aktualne cele");
          Serial2.println("Cel 1: ");
          Serial2.println(latitB, 6);
          Serial2.println(lonB, 6);
          delay(50);
          Serial2.println("Cel 2: ");
          Serial2.println(latitC, 6);
          Serial2.println(lonC, 6);
          delay(50);
          Serial2.println("Cel 3: ");
          Serial2.println(latitD, 6);
          Serial2.println(lonD, 6);
          break;
        case 'd':     // Letter d
          Serial2.println("Opcje menu wielu celów");
          delay(1000);
          Serial2.println("Wprowadź odpowiedni znak, żeby uzyskać dostęp do wybranej opcji.");
          Serial2.println("'1': Cel 1   '2': Cel 2   '3': Cel 3   ");
          Serial2.println("'e': Wyjdź z menu  's': Pokaż cele  'd': Wyświetl opcje");
          delay(50);
          break;
      }
      delay(50);
    }
  }
}

/*
  void multipleDestinations() {
  char f;
  bool Quit = true;

  while ( Quit == true ) {
    Serial2.println("Multiple Destinations Menu");
    Serial2.println("Please input three destinations (latitude, longitude) when prompted.");
    Serial2.println("Warning: Coordinates will be off by a very small amount due to Arduino limitations with float precision");
    delay(2000);

    Serial2.println("Input your first destination latitude coordinate: ");
    latitB = stringToFloatConversion();
    Serial2.println("Input your first destination longitude coordinate: ");
    lonB = stringToFloatConversion();
    Serial2.println("Input your second destination latitude coordinate: ");
    latitC = stringToFloatConversion();
    Serial2.println("Input your second destination longitude coordinate: ");
    lonC = stringToFloatConversion();
    Serial2.println("Input your third and final destination latitude coordinate: ");
    latitD = stringToFloatConversion();
    Serial2.println("Input your third and final destination longitude coordinate: ");
    lonD = stringToFloatConversion();

    delay(1000);

    Serial2.println("Your first destination coordinate is: ");
    Serial2.print("Latitude: ");
    Serial2.println(latitB, 6);
    Serial2.print("Longitude: ");
    Serial2.println(lonB, 6);

    Serial2.println("Your second destination coordinate is: ");
    Serial2.print("Latitude: ");
    Serial2.println(latitC, 6);
    Serial2.print("Longitude: ");
    Serial2.println(lonC, 6);

    Serial2.println("Your third and final destination coordinate is: ");
    Serial2.print("Latitude: ");
    Serial2.println(latitD, 6);
    Serial2.print("Longitude: ");
    Serial2.println(lonD, 6);

    Serial2.println("Are these destinations correct?   'y': yes   'n': no   ");  // This checks if our data is correct
    while (Serial2.available() == 0) {}                                       // Wait for user input in terminal
    f = Serial2.read();
    if (f == 'y') {                                                           // If our destination coordinates are correct
      Serial2.println("Destinations have been confirmed. Proceeding to main menu.");
      Quit = false;                                                           // ...we can quit the menu by breaking out of
    }                                                                         // the entire while loop (and function)
    else if (f == 'n') {                                                      // Else, we stay in the menu until valid coordinates
      Serial2.println("Destination have not been confirmed. Going back to Destination menu");
    }
    else {
      Serial2.println("Input isn't clear. Going back to Destination menu");
    }

  }

  }
*/
