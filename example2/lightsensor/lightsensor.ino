#include <Ethernet.h>
#include <PubSubClient.h>
 
int photocellPin = 0;
int photocellReading;
int LEDpin = 11;
int LEDbrightness;  

byte mac[] = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
char topic[] = "/v1/test";
char broker_id[] = "client1";

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
  if (client.connect(broker_id)) {
    Serial.println("Connected to MQTT broker");
  } else {
    Serial.println("Unable to connect to MQTT broker");
  }
}
 
void loop() {
  photocellReading = analogRead(photocellPin);  
  photocellReading = 1023 - photocellReading;

  if(photocellReading<100) {
    client.publish(topic,"hello world"); 
  } else {
    client.publish(topic,"NOT hello world");
  }

  Serial.print("reading: ");
  Serial.println(photocellReading);    
  
  delay(2000);
  client.loop();
}
