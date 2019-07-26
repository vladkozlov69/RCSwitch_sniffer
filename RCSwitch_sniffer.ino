#include <RCSwitch.h>
#include <Wire.h> 
#include <U8g2lib.h>

RCSwitch mySwitch = RCSwitch();

U8G2_PCD8544_84X48_1_4W_SW_SPI u8g2(U8G2_R0,/* clock=*/ 11, /* data=*/ 10, /* cs=*/ 7, /* dc=*/ 9, /* reset=*/ 8);  // Nokia 5110 Display

void setup() {
  Serial.begin(9600);
  u8g2.begin();
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x13_tr);
    u8g2.setCursor(0, 10);
    u8g2.print("433MHz sniffer");
    
    u8g2.setCursor(0, 25);
    u8g2.print("...READY...");

  } while ( u8g2.nextPage() );
  
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

      u8g2.clear();
      u8g2.firstPage();
      do {
        
        u8g2.setFont(u8g2_font_6x13_tr);
        u8g2.setCursor(0, 10);
        u8g2.print("433MHz sniffer");
    
        u8g2.setCursor(0, 25);
        u8g2.print(mySwitch.getReceivedValue());

        u8g2.setCursor(0, 35);
        u8g2.print(mySwitch.getReceivedBitlength());
        u8g2.print("bit/");
        u8g2.print(mySwitch.getReceivedDelay());
        u8g2.print("ms");

        u8g2.setCursor(0, 45);
        u8g2.print("Protocol:");
        u8g2.print(mySwitch.getReceivedProtocol());
        
      } while ( u8g2.nextPage() );
    }

    mySwitch.resetAvailable();
  }
}
