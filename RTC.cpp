#include "lcd.h"
#include "RTC.h"

RTC_DS1307 RTC;

void printTime(){
   //display time and date
  DateTime now = RTC.now();

  //DATE
  lcd.setCursor(0,1);
  lcd.print(now.month(), DEC);
  lcd.print('/'); 
  //We print the day
  lcd.print(now.day(), DEC);
  lcd.print('/');  
  //We print the year
  lcd.print(now.year(), DEC);
  lcd.print(' ');

  //TIME
  lcd.setCursor(11,1);
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.setCursor(14,1);
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);
  //delay(1); 
}
