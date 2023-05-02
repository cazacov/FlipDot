# FlipDot34Nano Sync Version
Library to control flip-dot dispalys with 34-pin connector. For example Lawo Luminator / Mark IV Industries 804/74-3.02

This synchonous version is using delayMicroseconds calls to control timing.

## Arduino Pinout
D3 - 595 SER - DATA pin
D5 - 595 RCLK - LATCH pin
D6 - 595 SRCLK - CLOCK pin

A0-A2 - Board-ID configuration DIP switches (connecting to ground)
A4 - I2C SDA
A5 - I2C SCL