#include <Ethernet.h>
#include <PubSubClient.h>

#include <TimeLib.h>

#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 
 
int photocellPin = 0;
int photocellReading;
int LEDpin = 11;
int sequenceNumber = 1;
unsigned long time;  

byte mac[] = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
char topic[] = "/v1/data/ALEB/WeatherSensor";
char brokerId[] = "client001";
char serialNumber[] = "SENSOR0001";

IPAddress ip(10, 42, 0, 3);
IPAddress server(34,240,137,175);

void callback(char* topic, byte* payload, unsigned int length);

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);

void callback(char* topic, byte* payload, unsigned int length) {
  // nothing to do
}

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // Needed for Leonardo only
//  pinMode(13, OUTPUT);
  setSyncProvider( requestSync);  //set function to call when sync required
  Serial.println("Waiting for sync message");
  
  Ethernet.begin(mac, ip);   
  if (client.connect(brokerId)) {
    Serial.println("Connected to MQTT broker");
  } else {
    Serial.println("Unable to connect to MQTT broker");
  }
}
 
void loop() {
  if (Serial.available()) {
    processSyncMessage();
  }

  time = now();
  photocellReading = analogRead(photocellPin);  
  photocellReading = 1023 - photocellReading;

  String msg = "";
  msg = msg + "sn," + sequenceNumber + "\n";
  
  if(photocellReading<100) {
    msg = msg + serialNumber + ","+time+"000,weather,sunny";
  } else {
    msg = msg + serialNumber + ","+time+"000,weather,cloudy";
  }

  char payload[msg.length()+1];
  msg.toCharArray(payload, msg.length()+1);

  client.publish(topic, payload);

  Serial.print("reading: ");
  Serial.println(photocellReading);    
  Serial.println(payload);
  
  delay(2000);
  sequenceNumber = sequenceNumber + 1;
  client.loop();
}

void processSyncMessage() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     
     if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
       setTime(pctime); // Sync Arduino clock to the time received on the serial port
     }
  }
}

time_t requestSync()
{
  Serial.write(TIME_REQUEST);  
  return 0; // the time will be sent later in response to serial mesg
}
