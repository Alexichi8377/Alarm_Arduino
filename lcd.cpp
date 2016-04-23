#include <Arduino.h>
#include <LiquidCrystal.h>
#include "lcd.h"
#include "output.h"

// create LCD
LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7);

void displayCodeEntryScreen(){ //Displaying start screen for users to enter PIN
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter PIN:");
  lcd.setCursor(0,3);
  lcd.print("By Alexandre Renoux");
  lcd.setCursor(11,0);
}

void invalidCode () {
    lcd.clear();
    delay(50);
    lcd.print("Wrong password");
    digitalWrite(ledRed, LOW); //turn on
    delay(2500);
    digitalWrite(ledRed, HIGH);//turn off
    delay(500);
    displayCodeEntryScreen();
    
  }
