# Example 1: Send light sensor status messages with a RapsberryPI

## Materials

- one LDR sensor
- one 1uF capacitor
- one RaspberryPI

## Resources

Based on: https://pimylifeup.com/raspberry-pi-light-sensor/

How to install MQTT library: https://pypi.python.org/pypi/paho-mqtt/1.1#installation

How to install pip: sudo apt-get install python-pip

# Example 2: Zone change with Arduino

## Materials

- one arduino
- one arduino ethernet shield
- one LDR sensor
- one 10k ohm resistor

## Resources

Based on: https://learn.adafruit.com/photocells/using-a-photocell

MQTT lib for arduino: https://pubsubclient.knolleary.net/

Time Library: https://github.com/PaulStoffregen/Time

How to set time: https://github.com/PaulStoffregen/Time/blob/master/examples/TimeSerial/TimeSerial.ino

Post about how to set time: https://forum.arduino.cc/index.php?topic=367987.0

Command to set time: date +T%s\n > /dev/ttyACM0

# Example 3: Location change with Arduino

## Materials

- one arduino
- one arduino ethernet shield
- one LDR sensor
- one 10k ohm resistor
