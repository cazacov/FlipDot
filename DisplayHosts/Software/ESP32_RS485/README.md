# ESP32 RS485 Display Host

Control matrix panels with I2C over RS485. That interface is used in Brose controoler boards VM_IIC

## Hardware
![ESP32 with RS485 interface](./_img/ESP32_RS485.png?raw=true)

### ESP32 pins
- SCL pin -> MAX485 transciever -> RS485
- SDA pin -> MAX485 transciever -> RS485
- DISPLAY -> Relay -> Bus display board 24V ON/OFF
- LAMP    -> Relay -> Bus display lamp  24V ON/OFF