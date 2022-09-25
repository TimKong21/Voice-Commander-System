# Voice Commander 
This is a year 2020 BMET graduation project from course: [BMET 4402 Biomedical Engineering Technology Project](https://www.bcit.ca/outlines/20201011965/).
The project was made for a quadriplegic client who needed a customized and portable voice commander to 
interact with his/her door openning switch wirelessly. Corresponding work was split evenly between
three members and only software related document is presented in this repository.

## Project Description
The central technology used for wireless communication is the radio frequency which mainly served the purpose of low power consumption.
An RF transmitter-receiver module was built along with a voice recognition module and a processing module. 

The modules combined as a whole system called the ***"V-Map"***. 
Below shows a summary of the functions of the front-end modules:

- The [voice recognition module](https://github.com/TimKong21/Voice-Commender-/tree/main/reference%20documents/voice%20recognition%20module) learns and recognizes the pre-trained commands
- The [processing module](https://github.com/TimKong21/Voice-Commender-/tree/main/reference%20documents/arduino%20interface) decodes message from the voice recognition module and transmits signal to the transmitter module
- The [transmitter module](https://github.com/TimKong21/Voice-Commender-/tree/main/reference%20documents/transmitter%20module) consists of an encoder and a transmitter. The address defined by the processing module will be converted into serial data and transmitted to the receiver module.

On the other end, a [receiver module](https://github.com/TimKong21/Voice-Commender-/tree/main/reference%20documents/receiver%20module) with matching address was built to control a solid-state relay 
to produce a simple switch closure signal that manipulates the door opening switch wirelessly
 
For more detailed description. Please refer to [architectural design.pdf](https://github.com/TimKong21/Voice-Commender-/blob/main/architectural%20design.pdf)

## Prototype Demonstration Video
- [Video link](https://drive.google.com/file/d/1lbnJuV_TK72wu2umAgaJuwPUvwt3Io0S/view?usp=sharing)

## Acknowledgements
 - BMET instructors for technical guidance and advice
 - Client for inputs and encouragement
 - BMET alumni for reference documentation of past year projects
 - BMET class of 2020 for supports and share of ideas
  
