int eyePin = 5;
int buttonPin = 2;
int onPin = 1;
int buttonState = 0;
int ascend = 1;
int eye_brightness = 0;
int fadeAmount = 5;
int ledPins [8] = {0, 1, 9, 3, 4, 6, 7, 8};
int loopnum = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(1, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(eyePin, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(eyePin, HIGH);
}

void fadeEyes(){
  analogWrite(eyePin, eye_brightness);
  eye_brightness = eye_brightness + fadeAmount;
  if(eye_brightness <= 0 || eye_brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
}

void ascend_leds() {
  digitalWrite(ledPins[onPin], LOW);
  if(++onPin == 8){
    onPin = 0;
  }
  digitalWrite(ledPins[onPin], HIGH);
}

void descend_leds() {
  digitalWrite(ledPins[onPin], LOW);
  if(--onPin == 0){
    onPin = 8;
  }
  digitalWrite(ledPins[onPin], HIGH);
}

void loop() {
  fadeEyes();
  if(++loopnum == 15){
    loopnum = 0;
    if(ascend == 1){
      ascend_leds();      
    }else{
      descend_leds();
    }
    buttonState = digitalRead(buttonPin);
    if(buttonState == HIGH){
      ascend = -ascend;      
    }
  }
  delay(50);
  // put your main code here, to run repeatedly:

}
