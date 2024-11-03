# Door-Lock-System

Project Highlights:
- Dual Microcontrollers: HMI_ECU for user interaction and Control_ECU for managing door functions and security.
- Inter-ECU Communication: Utilized UART to facilitate data exchange between HMI_ECU and Control_ECU.
- Password Authentication: Secure password storage in external EEPROM, with I2C communication to manage data retrieval and storage.
- Automatic Door Control: Motorized door locking/unlocking via H-bridge, managed by motion detection with a PIR sensor.
- Security Features: Buzzer alert for incorrect password attempts and a timed system lock after consecutive failed entries.

Hardware Used:
- ATmega32 microcontroller for both ECUs.
- LCD, keypad, with EEPROM for secure authentication.
- Motorized H-bridge for door control.
- PIR sensor for motion detection and a buzzer for alerts.
