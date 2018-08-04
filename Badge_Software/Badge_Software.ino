int eyePin = 5;
int buttonPin = 2;
int onPin = 1;
int buttonState = 0;
int currStep = 0;
int eye_brightness = 0;
int fadeAmount = 5;
int mode = 0;
int ledPins [8] = {3, 1, 0, 4, 6, 7, 8, 9};
int visualizer = 0;
int visualizerStep = 0;
int visualizerDir = 1;
int slowFill = 0;
int challengeONE = 0;
int letterLookup('a','b','c','d','e','d','f','g','h
int ONEmsg[] = {{1,1,0,1,0,1,1,0,1},{0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,1,0,1,0,1,1,0,1,1,0,0,1,1,0,1,1,0,1,1,0,0,1,0,1,0,1,1,0,0,1,1,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,1,0,1,1,0,1,0,1,0,0,1,1,0,1,1,0,0,1,0,0,1,0,1,1,0,1,1,0,0,1,0,1,0,1,0,1,0,0,1,0,0,1,0,1,1,0,1,0,0,1,0,0,1,1,0,0,1,0,1,0,1,0,1,0,0,1,0,0,1,1,0,1,0,1,0,1,0,0,1,0,1,1,0,0,1,1,0,0,1,0,1,0,1,0,1,0,0,1,0,1,1,0,1,0,0,1,1,0,1,1,0,1,1,0,0,1,1,0,1,1,0,1,1,0,0,1,1,0,1,1,0,0,1,0,1,0,0,1,0,1,0,1,1,0,1,0,1,1,0,1,1,0,1,0,1};
int challengeTWO = 1;
int challengeTHREE = 0;
int challengeFOUR = 1;



void setup() {
  // put your setup code here, to run once:
  for (int i=0; i < 8; i++){
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(eyePin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(eyePin, HIGH);
}

void visualize(){
  if(visualizer == 0){
    //This is effectively the "off but still eyes" choice
    delay(1);
  }
  else if(visualizer == 1){
    fillDown();
  }else if(visualizer == 2){
    fillUp();
  }else if(visualizer == 3){
    traceLight();
  }else if(visualizer == 4){
    traceDark();
  }else if(visualizer == 5){
    expand();
  }else if(visualizer == 6){
    contract();
  }else if(visualizer == 7){
    slowfillUp();
  }
}

void cycleVisualizer(){
  if(visualizer == 7){
    visualizer = 0;
  }
  else{
    visualizer++;
  }
  for (int i=0; i<8; i++){
    digitalWrite(ledPins[i], LOW);
  }
  visualizerStep = 0;
  visualizerDir = 1;
}

//////VISUALIZERS GO HERE//////

void fillDown() {
  if(visualizerDir == -1){
    digitalWrite(ledPins[visualizerStep], LOW);
  }else{
    digitalWrite(ledPins[visualizerStep], HIGH);
  }
  visualizerStep = visualizerStep + visualizerDir;
  if(visualizerStep <= -1 || visualizerStep >= 8){
    visualizerDir = -visualizerDir;
  }
}

void fillUp(){
  if(visualizerDir == 1){
    digitalWrite(ledPins[7-visualizerStep], HIGH);
  }else{
    digitalWrite(ledPins[7-visualizerStep], LOW);
  }
  visualizerStep = visualizerStep + visualizerDir;
  if(visualizerStep <= -1 || visualizerStep >= 8){
    visualizerDir = -visualizerDir;
  }
}

void traceLight(){
  if(visualizerDir == -1){
    digitalWrite(ledPins[visualizerStep--], LOW);
    digitalWrite(ledPins[visualizerStep], HIGH);
  }else{
    digitalWrite(ledPins[visualizerStep++], LOW);
    digitalWrite(ledPins[visualizerStep], HIGH);
  }
  if(visualizerStep <= 0 || visualizerStep >= 7){
    visualizerDir = -visualizerDir;
  }
}

void traceDark(){
  if(visualizerDir == -1){
    digitalWrite(ledPins[visualizerStep--], HIGH);
    digitalWrite(ledPins[visualizerStep], LOW);
  }else{
    digitalWrite(ledPins[visualizerStep++], HIGH);
    digitalWrite(ledPins[visualizerStep], LOW);
  }
  if(visualizerStep <= 0 || visualizerStep >= 7){
    visualizerDir = -visualizerDir;
  }
}

void expand(){
  if(visualizerDir == -1){
    digitalWrite(ledPins[3-visualizerStep], LOW);
    digitalWrite(ledPins[4+visualizerStep], LOW);
    visualizerStep--;
  }else{
    digitalWrite(ledPins[3-visualizerStep], HIGH);
    digitalWrite(ledPins[4+visualizerStep], HIGH);
    visualizerStep++;
  }
  if(visualizerStep <= -1 || visualizerStep >= 4){
    visualizerDir = -visualizerDir;
  }
}

void contract(){
  if(visualizerDir == -1){
    digitalWrite(ledPins[visualizerStep], LOW);
    digitalWrite(ledPins[7-visualizerStep], LOW);
    visualizerStep--;
  }else{
    digitalWrite(ledPins[visualizerStep], HIGH);
    digitalWrite(ledPins[7-visualizerStep], HIGH);
    visualizerStep++;
  }
  if(visualizerStep <= -1 || visualizerStep >= 4){
    visualizerDir = -visualizerDir;
  }
}

void slowfillUp(){
  if(visualizerStep < 8){
    if(slowFill > 0){
      digitalWrite(ledPins[slowFill-1], LOW);
    }
    digitalWrite(ledPins[slowFill], HIGH);
    if(slowFill == 7-visualizerStep){
      visualizerStep++;
      slowFill = 0;
    }else{
      slowFill++;
    }
  }else{
    int evenOrOdd = visualizerStep % 2;
    if(evenOrOdd == 1){
      for(int i = 0; i < 8; i++){
        digitalWrite(ledPins[i], LOW);
      }
    }else{
      for(int i = 0; i < 8; i++){
        digitalWrite(ledPins[i], HIGH);
      }
    }
    visualizerStep++;
    if(visualizerStep == 14){
      visualizerStep = 0;
      clearLED();
    }
  }
}

/////////GAME CODE//////////////////

void showStatus(){
  clearLED();
  if(challengeONE == 1){
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], HIGH);    
  }
  if(challengeTWO == 1){
    digitalWrite(ledPins[2], HIGH);
    digitalWrite(ledPins[3], HIGH);    
  }
  if(challengeTHREE == 1){
    digitalWrite(ledPins[4], HIGH);
    digitalWrite(ledPins[5], HIGH);    
  }
  if(challengeFOUR == 1){
    digitalWrite(ledPins[6], HIGH);
    digitalWrite(ledPins[7], HIGH);
  }
}

void displayCode(int message[], int arrayLength){
  clearLED();
  int LEDs[] = {0,0,0,0,0,0,0,0};
  for(int i = 0; i < arrayLength; i++){
    for(int j = 7; j >= 0; j--){
      if(j != 0){
        LEDs[j] = LEDs[j-1];        
      }else{
        LEDs[j] = message[i];
      }
    }
    for(int j = 0; j < 8; j++){
      if(LEDs[j] == 1){
//        digitalWrite(ledPins[j], HIGH);        
      }else{
//        digitalWrite(ledPins[j], LOW); 
      }
    }
    delay(50);
  }
}

void gameONE(){
  clearLED();
  for(int i = 0; i < 225; i++){
    for(int j = 0; i < 8; i++){
      if(ONEmsg[i+j] == 1){
        digitalWrite(ledPins[j], HIGH);
      }else{
        digitalWrite(ledPins[j], LOW); 
      }
    }
  delay(50);
  }
}

void gameTWO(){
  
}

void gameTHREE(){
  
}

void gameFOUR(){
  
}

/////EYE CODE///////////////////////

void fadeEyes(){
  analogWrite(eyePin, eye_brightness);
  eye_brightness = eye_brightness + fadeAmount;
  if(eye_brightness <= 0 || eye_brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
}

//////BUTTON CHECKING CODE/////////

void clearLED(){
  for(int i = 0; i < 8; i++){
    digitalWrite(ledPins[i], LOW);
  }
}

void checkButton(){
      int buttonPushed = digitalRead(buttonPin);
      if(buttonPushed == HIGH){
        buttonState++;
      }
      if(buttonPushed == LOW && buttonState > 0 && buttonState <= 40){
        cycleVisualizer();
        buttonState = 0;
      }
      else if(buttonState > 40){
        showStatus();
        delay(1500);
        clearLED();
        if(challengeONE == 0){
 //         gameONE();
        }else if(challengeTWO == 0){
          gameTWO();
        }else if(challengeTHREE == 0){
          gameTHREE();
        }else if(challengeFOUR == 0){
          gameFOUR();
        }
        buttonState = 0;
      }
}

void loop() {
  if((currStep % 64) == 0){
    visualize();
  }
  if((currStep % 16) == 0){
    fadeEyes();
  }
  if((currStep % 4) == 0){
    checkButton();     
  }
  delay(6);
  if(currStep == 128){
    currStep = 0;
  }
  currStep++;
}
