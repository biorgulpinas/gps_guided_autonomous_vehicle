void compassBearingDegrees() {  // Odczytuje z portu szeregowego kierunek odczytany z magnetometru
                                // i przekształca je w zmienną float

  String inputFloat = "";

  while (SerialNano.available() == 0) {} // Serial monitor will not do anything until input is entered
  inputFloat = SerialNano.readString();
  headingDegrees = inputFloat.toFloat(); // WARNING: THIS IS NOT SUPER ACCURATE AT 6TH DECIMAL PLACE
  Serial2.print("Aktualny kierunek = ");
  Serial2.println(headingDegrees);                                            
}

}

