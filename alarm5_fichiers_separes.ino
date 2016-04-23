#include <VirtualWire.h>
#include <SPI.h>
#include <Wire.h>
#include "RTC.h"
#include "alarm.h"
#include "buzzer.h"
#include "keypad.h"
#include "lcd.h"
#include "output.h"
#include "sensors.h"
#include "rfid.h"

void setup(){
  Serial.begin(9600);
  lcd.begin(20, 4);
  //Adding time 
  Wire.begin();
  RTC.begin();
  SPI.begin(); //Init the SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  Serial.println("Scan PICC to see UID and type...");
  
  //If we remove the comment from the following line, we will set up the module time and date with the computer one
  RTC.adjust(DateTime(__DATE__, __TIME__));
  pinMode(buzzer, OUTPUT);
  
  // Initialise the IO and ISR
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(4000);  // Bits per sec
  vw_rx_start();       // Start the receiver PLL running
  
  //Pour le boitier central
  pinMode(ledYellow, OUTPUT);  //yellow light
  pinMode(ledGreen, OUTPUT);  //green light
  pinMode(ledRed, OUTPUT);  //red light
  digitalWrite(ledYellow, HIGH);
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledRed, HIGH);
  //initialize reedpin
  pinMode(bouton, INPUT);
  pinMode(led_bouton, OUTPUT);
  digitalWrite(led_bouton, HIGH);
  
  lcd.print("initialisation..");
  delay(2000);
  
  displayCodeEntryScreen();
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}

void loop(){
  printTime();
  checkRFID();
  keypad.getKey();
  if (isActive() == 1) {
    contactDetector();
    motionDetector();
  }
  if(isTriggered() == 1) {
    updateBuzzer();
  }
}

int rang = 0;   
//take care of some special events
void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
  case PRESSED:

    //lcd.write(eKey);
    switch (eKey){
    case '*': 
      checkPassword();
      rang = 0; 
      delay(1);
      break;

    case '#': 
      password.reset();  
      lcd.clear();
      delay(100); 
      displayCodeEntryScreen();
      rang = 0;
      break;
      
    case 'A':
      setActivation(true);
      password.reset(); 
      break;
    
    case 'B':
      setActivation(false);
      password.reset();
      break;

    default: 
      password.append(eKey);
      lcd.setCursor(11+rang,0);
      lcd.print(eKey);
      rang = rang +1;
      delay(1);
    }
  }
}

