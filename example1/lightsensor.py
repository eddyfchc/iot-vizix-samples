#!/usr/bin/python

import RPi.GPIO as GPIO
import paho.mqtt.client as mqtt
import time

serialNumber="SENSOR002"

# mqtt 
mqtt_broker="192.168.1.10"
mqtt_port=1883
mqtt_topic="/v1/data/ALEB/LightSensor"
mqttc = mqtt.Client()

# gpio init
pin_to_circuit = 7
GPIO.setmode(GPIO.BOARD)

# rc_time function
def rc_time (pin_to_circuit):
    count = 0
  
    #Output on the pin for 
    GPIO.setup(pin_to_circuit, GPIO.OUT)
    GPIO.output(pin_to_circuit, GPIO.LOW)
    time.sleep(1)

    #Change the pin back to input
    GPIO.setup(pin_to_circuit, GPIO.IN)
  
    #Count until the pin goes high
    while (GPIO.input(pin_to_circuit) == GPIO.LOW):
        count += 1

    return count

# main
try:
    mqttc.connect(mqtt_broker, mqtt_port, 60)
    sequenceNumber=1
    while True:
        timestamp=str(long(time.time()*1000)) 
	payload="sn,"+`sequenceNumber`+"\n"
        value=rc_time(pin_to_circuit)
	payload+=serialNumber+","+timestamp+",status,"+`value`
        mqttc.publish(mqtt_topic,payload)
  	sequenceNumber=sequenceNumber+1

	
except KeyboardInterrupt:
    pass
finally:
    GPIO.cleanup()

