# ESP32 Display Host

- Controls matrix panels. 
- Provides REST API allowing external clients send commands over WiFi.
- Communicates with matrix panels using RS422 or I2C interfaces.

## RS-422
 This interface is used in Brose controoler boards VM_IIC

### Hardware
![ESP32 with RS422 interface](./_img/ESP32_RS422.png?raw=true)

### ESP32 pins
- SCL pin -> MAX485 transciever -> RS422
- SDA pin -> MAX485 transciever -> RS422
- DISPLAY -> Relay -> Bus display board 24V ON/OFF
- LIGHT   -> Relay -> Bus display lamp  24V ON/OFF

![ESP32 with RS422 interface](./_img/ESP32_DisplayHost.jpg?raw=true)


### Software

#### Libraries
- [LeoDJ's Brose_VM-IIC](https://github.com/LeoDJ/Brose_VM-IIC)