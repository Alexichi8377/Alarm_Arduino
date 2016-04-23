#include <Arduino.h>
#include "output.h"
#include "buzzer.h"
#include "lcd.h"
#include "alarm.h"

int timerAlarm = 0;

int counter = 0;
int freq[] = {440,880,440,880,440,880,440,880};

void triggerBuzzer(){
  tone(buzzer,440);
  timerAlarm = millis();
}

void updateBuzzer(){
  if(timerAlarm <= 0) return;

  if(millis() - timerAlarm > 250)
  {
    noTone(buzzer);
    tone(buzzer, freq[counter]);
   
    counter++;
    if(counter > 7){
      timerAlarm = 0;
      counter = 0;
      setIsTriggered(0);
      displayCodeEntryScreen();
      digitalWrite(ledYellow,1);
    }
    else{
      timerAlarm = millis();
    }
  }
  /*else if(millis() - timerAlarm > 750)
  {
    noTone(buzzer);
    tone(buzzer, 392);
  }
  else if(millis() - timerAlarm > 500)
  {
    noTone(buzzer);
    tone(buzzer, 660);
  }
  else if(millis() - timerAlarm > 250 && counter==0)
  {
    noTone(buzzer);
    tone(buzzer, 880);
    counter = 1;
  }*/
}



