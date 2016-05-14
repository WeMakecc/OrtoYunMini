/*
 * Progetto Orto Arduino Yùn ( Internet of Greens )
 *
 * Autore: Alfieri Mauro
 * Twitter: @mauroalfieri
 *
 */
#include <FileIO.h>
#include <HttpClient.h>
#include <dht11.h>
#include "ortoConfig.h"

void setup() {
  Serial.begin(115200);
  
  Bridge.begin();
  FileSystem.begin();
  
  pinMode(pinLamp1,OUTPUT);
  pinMode(pinLamp2,OUTPUT);
  pinMode(pinPump1,OUTPUT);
  pinMode(pinPump2,OUTPUT);
  
  /** Alimentazione **/
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  digitalWrite(2,1);
  digitalWrite(3,1);
  /** Alimentazione end **/
  
  digitalWrite(pinLamp1,0);
  digitalWrite(pinLamp2,0);
  digitalWrite(pinPump1,0);
  digitalWrite(pinPump2,0);
}

void loop () {
  currMin  = getInterval("+%M");
  currHour = getInterval("+%H");
  
  /**********************************************************************************/
  
  #ifdef DEBUG  
    Serial.println("\n------------------");
    Serial.println( getTime() );
  #endif
  
  /**********************************************************************************/
  if ( (currMin == 0 || currMin == 30) && currMin != lastMin ) {
    lastMin = currMin;
    
    /**********************************************************************************/
    
    getTempHum();
    
    /**********************************************************************************/
  
  } // end if 0/30 min

  /**********************************************************************************/
  
  if ( ((20 <= currHour && currHour <= 23)  || (5 <= currHour && currHour <= 7)) && currMin == 20 && currMin != lastMin ) {
    // Controllo livello acqua irrigazione
  }
  
  /**********************************************************************************/
  
  // FERTILIZZANTE
  if ( currHour == 22 && currMin == 30 && statusPump2 == false ) {
    apriGocciolatore();
    fertil = 1;
    delay( 1300 ); // con 1300 millisecondi fa 10ml
    chiudiGocciolatore();
    statusPump2 = true;
  } else { 
    fertil = 0;
  }
  if ( currHour == 22 && currMin == 35  && statusPump2 == true) { statusPump2 = false; }

  /**********************************************************************************/
  
  if ( 7 <= currHour && currHour <= 20 && statusLight1 == false ) { // Luci accese
     digitalWrite(pinLamp1,HIGH);
     statusLight1 = true;
  }
  
  if ( ((21 <= currHour && currHour <= 23)  || (0 <= currHour && currHour <= 6)) && statusLight1 == true ) { // Luci accese
    digitalWrite(pinLamp1,LOW);
    statusLight1 = false;
  }
  
  /**********************************************************************************/
  
  if ( 7 <= currHour && currHour <= 20 && statusLight2 == false ) { // Luci accese
     digitalWrite(pinLamp2,HIGH);
     statusLight2 = true;
  }
   
  if ( ((21 <= currHour && currHour <= 23)  || (0 <= currHour && currHour <= 6)) && statusLight2 == true ) { // Luci accese
    digitalWrite(pinLamp2,LOW);
    statusLight2 = false;
  }
  
  /**********************************************************************************/
  
  if (( 8 <= currHour && currHour <= 21 ) && (0 <= currMin && currMin <= 15)) {
      if ( !statusPump1 ) {
        digitalWrite(pinPump1,HIGH); delay( 100 );
        statusPump1 = true;
      }
  } else {
     if ( statusPump1 ) {
         digitalWrite(pinPump1,LOW); delay( 100 );
         statusPump1 = false;
     }
  }
   
  /**********************************************************************************/
  
  #ifdef DEBUG
    Serial.print  ( "Controllo curr: " );
    Serial.print  ( currMin );
    Serial.print  ( " last: " );
    Serial.print( lastMin );
    Serial.print  ( " write: " );
    Serial.println( writeMin );
  #endif
  
  /**********************************************************************************/
  
  if ( currMin != writeMin ) {
    writeMin = currMin;
    
    getTempHum();
    
    String dataString;
    dataString += getTime();
    dataString += " "; dataString += String( DHT_t );        // Temperatura -   pos 3
    dataString += " "; dataString += String( DHT_h );        // Umidità     -   pos 4
    dataString += " "; dataString += String( statusPump2 );  // Fertilizzante - pos 5
    dataString += " "; dataString += String( statusPump1 );  // Irrigazione -   pos 6
    dataString += " "; dataString += String( statusLight1 ); // Luce uno -      pos 7
    dataString += " "; dataString += String( statusLight2 ); // Luce due -      pos 8
    
    File dataFile = FileSystem.open(logFile, FILE_APPEND);
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
    }
  }
  
  /**********************************************************************************/
  delay(30000);
  
} // end loop
