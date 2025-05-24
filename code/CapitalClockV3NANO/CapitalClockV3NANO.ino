//BY JACOB STENTON

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
float count; //initialising basic varibale to calculate earnings per second (eps)

String useMode = "StartUp";//this determines which screen the display starts in - changeing to "Display" will start on the main display screen
bool startUp = false;//boolean to determin if the startup screen has already run for later

#define modeButton 11 //first button - for changing screens
#define upButton 9 //second - for increasing salary
#define downButton 5 //third - for decreasing salary

int modeButtonVal, prevModeButtonVal = 1; //states and previous states for the mode button so it doesn't contantly change modes

int upButtonVal, downButtonVal, upHold, downHold; //states for up and down buttons, as well as ints to count how long they have been held down

int seconds, minutes, hours, days, years; //integers for the useage time shown on the main display



void setup() {
  Serial.begin(9600);//starts serial - mainly for debuging
//
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;)
    ; //code taken from https://www.youtube.com/watch?v=OzfljKHH0p0 - sets up the display and checks it is properly connected
  }

  pinMode(modeButton, INPUT_PULLUP);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP); //sets the buttons so they activate when released

  display.clearDisplay();
  display.setTextColor(WHITE); //clears the main display and sets pixel colour to white. - this display only has one colour (white means ON - black OFF)
}


void loop() {
// Mode Button
  //this section controls what the screen is displaying based on what mode it is set to
  modeButtonVal = digitalRead(modeButton); //sets the mode state var to be the same as the mode button
  if (modeButtonVal == LOW && modeButtonVal != prevModeButtonVal) { //if the mode button is pressed and is not the same as its previous state (this prevents continuous presses)
    if (useMode == "Display"){ // if mode is on display 
      useMode = "Salary";//change it to salary
    } else if (useMode == "Salary"){ //if mode is "Salary"
      useMode = "Display"; //change to display
    }
    delay(20);//debounce
  }

  prevModeButtonVal = modeButtonVal; //prevous button value is set to the current value

// Modes
  if(useMode == "StartUp"){ //if mode is on startup
    display.clearDisplay();

    display.setTextSize(2); //sets text size (1,2,3)
    display.setCursor(24,0); //sets where the text will start 
    display.println("WELCOME");//prints text "welcome" onto screen

    display.setTextSize(1);
    display.setCursor(18,18);
    display.println("by Jacob Stenton");
    display.println();
    display.println("please input your    salary :)"); // basic welcome text to display on the start up screen
    display.display(); //display previosuly set text

    delay(5000); // waits x amount of seconds (5)

    if (startUp == false){ //if first startup
      startUp = true; //startup has now run
      useMode = "Salary";//change mode to salary
    } else {
      useMode = "Display";//if startup has run change screen to the main display
      
    }

  } else if(useMode == "Display"){//if on disaply screen
      display.clearDisplay();

      display.setTextSize(2);
      display.setCursor(31,0);
      display.println("_GBP_"); //title

      count = salary/31540000; //takes input salary and divides it by seconds in a year.
      savings += count; //adds count to the main savings number
      amount = String(savings, 4); //changes savings into a string with 4 decimal places

    

      display.setCursor(0,16);
      display.println(amount); //prints the amount
    
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
      } //calculates how long the gadet has been running for - from seconds to years
      
      display.setTextSize(1);
      display.setCursor(0,56);
      display.println(String(years) + "Y" + String(days) + "D" + String(hours) + "H" + String(minutes) + "M" + String(seconds) + "S"); //prints time stat


      display.display();
      delay(1000); // does everything once every seconds
  
  } else if(useMode == "Salary"){
      display.clearDisplay();

      display.setTextSize(2);
      display.setCursor(17,0);
      display.println("_SALARY_"); //title

      display.setTextSize(1);
      display.setCursor(10,20);
      display.println("Earnings per year?"); 

      int buffer; // creates a tempery buffer for text spacing
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
        buffer = 90; //determines the buffer based on how many digits the input salary has
      } 


// buttons
    
      upButtonVal = digitalRead(upButton); // up button value set to the actual button value
      if (upButtonVal == LOW) { // if buttons is pressed down (these buttons should be continuous for ease of input - they dont have a prevoious value or a debounce)
        if(upHold > 200){ //checks if how long the button has been held down
          salary += 1000000; //increases salary by larger value the longer it has been held down
        } else if (upHold > 100) {
          salary += 10000;
        } else {
          salary += 1000;
        }

        if (salary >= 99999999) {
          salary = 99999000; //stops the salary going too many digits hight - More than 8 or  9 digits seems to cause problems with timing 
        }
        delay(50);
        upHold += 1; // calculates how long the button has been pressed down
      }
      
      if (upButtonVal == HIGH){
        upHold = 0; // if the button is released the hold down value is reset
      }

      downButtonVal = digitalRead(downButton); //same logic as up button
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
      display.setCursor(buffer,34); //uses the buffer to set the cursur
      display.println(String(salary,0)); //turns the salary into a string and displays it

      display.setTextSize(1);
      display.setCursor(0,56);
      display.println("press MODE to confirm");//gives some intruction on how to go back to the main display

      display.display();
  } else {
    // useMode error
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0,40);
      display.println("error");//prints and error message if the modes are not correctly setting
      display.display();
  }
}
