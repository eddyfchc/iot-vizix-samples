#include <Ethernet.h>
#include <PubSubClient.h>
 
int photocellPin = 0;
int photocellReading;
int LEDpin = 11;
int sequenceNumber = 1;
unsigned long time;   

byte mac[] = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
char topic[] = "/v1/test";
char brokerId[] = "client1";
char serialNumber[] = "TESTTAG0001";

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
  Ethernet.begin(mac, ip);   
  if (client.connect(brokerId)) {
    Serial.println("Connected to MQTT broker");
  } else {
    Serial.println("Unable to connect to MQTT broker");
  }
}
 
void loop() {
  time = millis();
  photocellReading = analogRead(photocellPin);  
  photocellReading = 1023 - photocellReading;

  String msg = "";
  msg = msg + "sn," + sequenceNumber + "\n";
  
  if(photocellReading<100) {
    msg = msg + serialNumber + ","+time+",status,ON";
  } else {
    msg = msg + serialNumber + ","+time+",status,OFF";
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
