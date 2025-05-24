#define modeButton 11
#define upButton 9
#define downButton 5
#define selectButton 3

int modeButtonVal = 0;
int upButtonVal = 0;
int downButtonVal = 0;
int selectButtonVal = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(modeButton, INPUT_PULLUP);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  modeButtonVal = digitalRead(modeButton);
  Serial.print(modeButtonVal);
  upButtonVal = digitalRead(upButton);
  Serial.print(upButtonVal);
  downButtonVal = digitalRead(downButton);
  Serial.print(downButtonVal);
    selectButtonVal = digitalRead(selectButton);
  Serial.println(selectButtonVal);




}
