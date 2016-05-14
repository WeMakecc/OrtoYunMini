/**********************************************************************************/

#define DEBUG 1

/**********************************************************************************/

#define pinLamp1     7            // Relay right Light
#define pinLamp2     8            // Relay left Light
#define pinPump1     12           // Relay Pump 1
#define pinPump2     13           // Relay Pump 2 - Fertilizzante

/**********************************************************************************/

dht11 DHT;
#define DHT11_PIN 4
int  DHT_h, DHT_t;

/**********************************************************************************/

static byte  fertil  = 0;
boolean statusLight1 = false;
boolean statusLight2 = false;
boolean statusPump1  = false;
boolean statusPump2  = false;
byte lastTimeSet = 0;

/**********************************************************************************/

byte currHour = 0;
byte currMin  = 0;
byte lastMin  = -1;
byte writeMin = -1;

/**********************************************************************************/

char* logFile = "/mnt/sd/arduino/www/orto.log";
