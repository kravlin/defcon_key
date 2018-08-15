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
int visualizerStep = -1;
int visualizerDir = 1;
int slowFill = 0;

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
  visualizerStep = -1;
  visualizerDir = 1;
}

//////VISUALIZERS GO HERE//////

void fillDown() {
  visualizerStep = visualizerStep + visualizerDir;
  if(visualizerStep > -1 && visualizerStep < 8){
    if(visualizerDir == 1){
      digitalWrite(ledPins[visualizerStep], HIGH);
    }else{
      digitalWrite(ledPins[visualizerStep], LOW);
    }
  }
  else{
    visualizerDir = -visualizerDir;
  }
}

void fillUp(){
  visualizerStep = visualizerStep + visualizerDir;
  if(visualizerStep > -1 && visualizerStep < 8){
    if(visualizerDir == 1){
      digitalWrite(ledPins[7-visualizerStep], HIGH);
    }else{
      digitalWrite(ledPins[7-visualizerStep], LOW);
    }
  }
  else{
    visualizerDir = -visualizerDir;
  }
}

void traceLight(){
  if(visualizerStep == -1){
     digitalWrite(ledPins[++visualizerStep], HIGH);   
  }else{
    if(visualizerDir == 1){
      digitalWrite(ledPins[visualizerStep++], LOW);
      digitalWrite(ledPins[visualizerStep], HIGH);
    }else{
      digitalWrite(ledPins[visualizerStep--], LOW);
      digitalWrite(ledPins[visualizerStep], HIGH);
    }
    if(visualizerStep <= 0 || visualizerStep >= 7){
      visualizerDir = -visualizerDir;
    }   
  }
}

void traceDark(){
  //This is a setup for doing this well, instead of poorly.
  if(visualizerStep == -1){
    for(int i= 1; i <= 7; i++){
      digitalWrite(ledPins[i], HIGH);
    }
    visualizerStep++;
  }else{
    if(visualizerDir == 1){
      digitalWrite(ledPins[visualizerStep++], HIGH);
      digitalWrite(ledPins[visualizerStep], LOW);
    }else{
      digitalWrite(ledPins[visualizerStep--], HIGH);
      digitalWrite(ledPins[visualizerStep], LOW);
    }
    if(visualizerStep <= 0 || visualizerStep >= 7){
      visualizerDir = -visualizerDir;
    }
  }
}

void expand(){
  visualizerStep = visualizerStep + visualizerDir;
  if(visualizerDir == 1){
    digitalWrite(ledPins[3-visualizerStep], HIGH);
    digitalWrite(ledPins[4+visualizerStep], HIGH);
  }else{
    digitalWrite(ledPins[3-visualizerStep], LOW);
    digitalWrite(ledPins[4+visualizerStep], LOW);
  }
  if(visualizerStep <= -1 || visualizerStep >= 4){
    visualizerDir = -visualizerDir;
  }
}

void contract(){
  visualizerStep = visualizerStep + visualizerDir;
  if(visualizerDir == 1){
    digitalWrite(ledPins[visualizerStep], HIGH);
    digitalWrite(ledPins[7-visualizerStep], HIGH);
  }else{
    digitalWrite(ledPins[visualizerStep], LOW);
    digitalWrite(ledPins[7-visualizerStep], LOW);
  }
  if(visualizerStep <= -1 || visualizerStep >= 4){
    visualizerDir = -visualizerDir;
  }
}

void slowfillUp(){
  if(visualizerStep == -1){
    visualizerStep++;
  }
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
  if(buttonPushed == LOW && buttonState > 0){
    cycleVisualizer();
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
