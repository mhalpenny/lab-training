//For onboard storage (leave for a later date)
#include <EEPROM.h>
#define FS_ADDR 0x01

// fan variables, pin D3 which has PWM
#define FAN_PIN 3;
int   fanSpeed;

void setup() {
  // set hardware settings for Mega
  pinMode(FAN_PIN, OUTPUT);
  EEPROM.get(FS_ADDR, fanSpeed);

  // check if fan is off, if true, turn on
  if(fanSpeed < 1){
    fanSpeed = 255; 
  }

  // send output to turn the fan on
  analogWrite(FAN_PIN, fanSpeed);
  Serial.begin(9600);

}
char   rx_byte = 0;
String input = "";

void loop() {
  if (Serial.available()   > 0) {    // is a character available?
    rx_byte = Serial.read();       //   get the character
  
    // check if a number was received
    if ((rx_byte   >= '0') && (rx_byte <= '9')) {
      input.concat(rx_byte);
      
    }
     else if (rx_byte == '\
') {
      Serial.print("Received: ");
      Serial.println(input);
       if(input.toInt() < 256) {
        fanSpeed = input.toInt();
        EEPROM.put(FS_ADDR,   fanSpeed);
      } else {
        Serial.println("Invalid Number");
       }
      input = "";
    }
    else {
      Serial.println("Not   a number.");
    }
  } // end: if (Serial.available() > 0)
  analogWrite(FAN_PIN,   fanSpeed);
}
