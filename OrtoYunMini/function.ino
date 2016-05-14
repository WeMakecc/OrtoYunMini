/**********************************************************************************/

void getTempHum() {
  int chk;
  Serial.print("DHT11, \t");
  chk = DHT.read(DHT11_PIN);    // READ DATA
  switch (chk){
    case DHTLIB_OK:  
                Serial.println("OK,\t"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.println("Checksum error,\t"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.println("Time out error,\t"); 
                break;
    default: 
                Serial.println("Unknown error,\t"); 
                break;
  }

  DHT_h = DHT.humidity;
  DHT_t = DHT.temperature;
  
  #ifdef DEBUG
    Serial.println("--- BEGIN getTempHum ---");
    Serial.print("Humidity: ");    Serial.println(DHT_h,1);
    Serial.print("Temperature: "); Serial.println(DHT_t,1);
    Serial.println("---- END getTempHum ----");
  #endif
  
}

/**********************************************************************************/

String getTime() {
  String result;
  Process time;
  time.begin("date");
  time.addParameter("+%d/%m/%Y %T");
  time.run();
  while(time.available()>0) {
    char c = time.read();
    if(c != '\n') result += c;
  }
  
  return result;
}

/**********************************************************************************/

byte getInterval( char* string ) {
  String result;
  Process time;
  time.begin("date");
  time.addParameter(string);
  time.run();
  while(time.available()>0) {
    char c = time.read();
    if(c != '\n') result += c;
  }
  return result.toInt();
}

/**********************************************************************************/

void apriGocciolatore() {
   digitalWrite(pinPump2,HIGH);
   
   #ifdef DEBUG
    Serial.println("--- BEGIN apriGocciolatore ---");
    Serial.print( "Gocciolatore: HIGH" ); 
    Serial.println("---- END apriGocciolatore ----");
   #endif
}

/**********************************************************************************/

void chiudiGocciolatore() {
   digitalWrite(pinPump2,LOW);
   
   #ifdef DEBUG
    Serial.println("--- BEGIN chiudiGocciolatore ---");
    Serial.print( "Gocciolatore: LOW" ); 
    Serial.println("---- END chiudiGocciolatore ----");
   #endif
}

/**********************************************************************************/
