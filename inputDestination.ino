void inputDestination() {       // The function that will allow us to input our destination coordinates.

  char d;
  bool Quit = true;

  while ( Quit == true ) {
    Serial2.println("Menu celu");
    Serial2.println("Po wyświetleniu monitu wprowadź miejsce docelowe.");
    delay(5000);
    Serial2.println("Podaj szerokość geograficzną: ");
    latitB = stringToFloatConversion();
    Serial2.println("Podaj długość geograficzną: ");
    lonB = stringToFloatConversion();
    Serial2.println("Twoje współrzędne docelowe to: ");
    Serial2.println(latitB, 6);
    Serial2.println(lonB, 6);

    Serial2.println("Zatwierdzić 't': tak  'n': nie  ");              // This checks if our data is correct
    while (Serial2.available() == 0) {}                                       // Wait for user input in terminal
    d = Serial2.read();
    if (d == 'y') {                                                           // If our destination coordinates are correct
      Serial2.println("Powrót do głównego menu");
      Quit = false;                                                           // ...we can quit the menu by breaking out of
    }                                                                         // the entire while loop (and function)
    else if (d == 'n') {                                                      // Else, we stay in the menu until valid coordinates
      Serial2.println("Ponowny wybór celu");
    }
    else {
      Serial2.println("Zły wybór. Ponowny wybór celu");
    }

  }

}
