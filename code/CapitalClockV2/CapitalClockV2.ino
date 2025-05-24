#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//------------------------------------------------------------------
// Seconds in a year 31540000

String amount;
float salary;
float savings;
float count;

String useMode = "StartUp";
bool startUp = false;

#define modeButton 11
#define upButton 9
#define downButton 5

int modeButtonVal, prevModeButtonVal = 1;

int upButtonVal, downButtonVal, upHold, downHold;

int seconds, minutes, hours, days, years;



void setup() {
  Serial.begin(9600);

if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;)
    ;
  }

  pinMode(modeButton, INPUT_PULLUP);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);

  display.clearDisplay();
  display.setTextColor(WHITE);
}


void loop() {
// Mode Button
  modeButtonVal = digitalRead(modeButton);
  if (modeButtonVal == LOW && modeButtonVal != prevModeButtonVal) {
    
    if (useMode == "Display"){
      useMode = "Salary";
    } else if (useMode == "Salary"){
      useMode = "Display";
    }
    delay(20);
  }

  prevModeButtonVal = modeButtonVal;
  Serial.println(useMode);

// Modes
  if(useMode == "StartUp"){
    display.clearDisplay();

    display.setTextSize(2);
    display.setCursor(24,0);
    display.println("WELCOME");

    display.setTextSize(1);
    display.setCursor(18,18);
    display.println("by Jacob Stenton");
    display.println();
    display.println("please input your    salary :)");
    display.display();

    delay(10000);

    if (startUp == false){
      useMode = "Salary";
    } else {
      useMode = "Display";
    }

  } else if(useMode == "Display"){
      display.clearDisplay();

      display.setTextSize(2);
      display.setCursor(31,0);
      display.println("_GBP_");

      count = salary/31540000;
      savings += count;
      amount = String(savings, 4);

    

      display.setCursor(0,16);
      display.println(amount);
    
    //SMHDY RUNTIME
      seconds += 1;
      if (seconds == 60){
        seconds = 0;
        minutes += 1;
      }
      if (minutes == 60){
        minutes = 0;
        hours += 1;
      }
      if (hours == 24){
        hours = 0;
        days += 1;
      }
      if (days == 365){
        days = 0;
        years += 1;
      }
      
      display.setTextSize(1);
      display.setCursor(0,56);
      display.println(String(years) + "Y" + String(days) + "D" + String(hours) + "H" + String(minutes) + "M" + String(seconds) + "S");


      display.display();
      delay(1000);
  
  } else if(useMode == "Salary"){
      display.clearDisplay();

      display.setTextSize(2);
      display.setCursor(17,0);
      display.println("_SALARY_");

      display.setTextSize(1);
      display.setCursor(10,20);
      display.println("Earnings per year?");

      int buffer; //12 - num 10
      if (salary >= 10000000){
        buffer = 18;
      } else if (salary >= 1000000) {
        buffer = 30;
      } else if (salary >= 100000) {
        buffer = 42;
      } else if (salary >= 10000) {
        buffer = 54;
      } else if (salary >= 1000) {
        buffer = 66;
      } else if (salary >= 100) {
        buffer = 78;
      } else {
        buffer = 90;
      } 


// buttons
    
      upButtonVal = digitalRead(upButton);
      if (upButtonVal == LOW) {
        if(upHold > 200){
          salary += 1000000;
        } else if (upHold > 100) {
          salary += 10000;
        } else {
          salary += 1000;
        }

        if (salary >= 99999999) {
          salary = 99999000;
        }
        delay(50);
        upHold += 1;
      }
      
      if (upButtonVal == HIGH){
        upHold = 0;
      }

      downButtonVal = digitalRead(downButton);
      if (downButtonVal == LOW) {
        if(downHold > 200){
          salary -= 1000000;
        } else if (upHold > 50) {
          salary -= 10000;
        } else {
          salary -= 1000;
        }

        if (salary < 0){
          salary = 0;
        }
        delay(50);
        downHold += 1;
      }

      if (downButtonVal == HIGH){
        downHold = 0;
      }

//-------

      display.setTextSize(2);
      display.setCursor(buffer,34);
      display.println(String(salary,0));

      display.setTextSize(1);
      display.setCursor(0,56);
      display.println("press MODE to confirm");

      display.display();
  } else {
    // useMode error
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0,40);
      display.println("error");
      display.display();
  }
}
