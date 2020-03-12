void serialEvent(){
    while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void parseCommand(){
  inputString.trim();
  if( inputString == "CAL" ){
   Serial.println( "Calibrando" );
   //calibrate(); 
  }
  else if( inputString == "READ" ){
   Serial.println( "Midiendo" ); 
  }
  else{
   Serial.println("Comando invalido"); 
  }
}
