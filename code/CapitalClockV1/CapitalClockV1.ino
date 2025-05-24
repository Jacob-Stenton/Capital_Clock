#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//------------------------------------------------------------------

const int x = 128;
const int y = 64;
const int reset = -1;

Adafruit_SSD1306 display(x,y, &Wire, reset);

//------------------------------------------------------------------
//seconds in a year 31536000//
String amount;
float salary;
float savings;
float count = salary / 31536000;

String useMode;
bool startUp = false;




void setup() {
  Serial.begin(9600);

if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;)
    ;
  }

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  
  

  for(float Amnt = 0; Amnt >= 0 ; Amnt += count){
    display.clearDisplay();

    display.setCursor(0,0);
    display.println("GBP");
    display.setCursor(0,16);

    amount = String(Amnt);
    display.println(amount);

    display.display();
    delay(1000);
  }
 

  //delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
