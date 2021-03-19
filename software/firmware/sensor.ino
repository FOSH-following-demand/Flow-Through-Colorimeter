void calibrate(){
 doMeasure = false;
 c = 0;
 int intense = 50;
 
 while( c < 65500 & intense < 255){ 
  intense++;
  analogWrite( 9, intense );
  delay( 2 );
  tcs.getRawData(&r, &g, &b, &c);
  Serial.print(c);; Serial.print("  "); Serial.println(intense);
 }
 Serial.print( "Calibrado: " );
 Serial.println( intense );
}

void measure(){
  long rCum=0, gCum=0, bCum=0, cCum=0;
  for( int i = 0; i < 5; i++ ){
    tcs.getRawData(&r, &g, &b, &c);
    rCum += r; gCum += g; bCum += b, cCum += c;
  }
  rCum /= 5; gCum /= 5; bCum /= 5; cCum /= 5;
  Serial.print("R: "); Serial.print(rCum, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(gCum, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(bCum, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(cCum, DEC); Serial.print(" ");
  Serial.println(" ");
}
