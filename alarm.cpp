#include <Arduino.h>
#include "lcd.h"
#include "alarm.h"
#include "buzzer.h"
#include "output.h"

int _isTriggered = 0;
int alarmActive = 0;

void alarmTriggered(){
  _isTriggered = 1;
  digitalWrite(ledYellow,0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Intrus detecte");
  triggerBuzzer();
}

void activate(){
    lcd.clear();
    delay(50);
    lcd.print("Alarme");
    lcd.setCursor(0,1);
    lcd.print("Active");
    alarmActive = 1;
    digitalWrite(ledGreen, LOW);//turn on
    delay(2500);
    displayCodeEntryScreen();
    digitalWrite(ledGreen, HIGH);// turn off
}

void deactivate(){
    _isTriggered = 0;
    lcd.clear();
    delay(50);
    noTone(buzzer);
    lcd.print("Alarme");
    lcd.setCursor(0,1);
    lcd.print("Desactive");
    alarmActive = 0;
    digitalWrite(ledYellow, LOW);//turn on
    delay(2500);
    displayCodeEntryScreen();
    digitalWrite(ledYellow, HIGH);// turn off
    
}

int isTriggered(){
 return _isTriggered; 
}

int isActive(){
 return alarmActive; 
}

void setIsTriggered(int v){
 _isTriggered = v; 
}

void setAlarmActive(int v){
 alarmActive = v; 
}
