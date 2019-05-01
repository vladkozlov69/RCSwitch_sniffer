/*
  Simple example for receiving
  
  https://github.com/sui77/rc-switch/
*/

#include <RCSwitch.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

RCSwitch mySwitch = RCSwitch();
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Ready");
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
}

void loop() {
  if (mySwitch.available()) {
    
    int value = mySwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      Serial.print("Received ");
      Serial.print( mySwitch.getReceivedValue() );
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
      
      lcd.setCursor(0,0);
      lcd.print(mySwitch.getReceivedValue());
      lcd.setCursor(1,1);
      lcd.print( mySwitch.getReceivedBitlength() );
      lcd.print("bit/p:");
      lcd.println( mySwitch.getReceivedProtocol() );
    }

    mySwitch.resetAvailable();
  }
}
