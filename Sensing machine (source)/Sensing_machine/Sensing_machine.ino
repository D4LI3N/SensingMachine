#define B1 2          //MODE button
#define S1_IN 3       //sound sensor
#define S2_ECHO 4     //ultrasonic sensor - ECHO
#define S2_TRIGGER 5  //ultrasonic sensor - TRIGGER
#define S3_IN A0      //temperature sensor

volatile int MODE = 1;
const int loopSpeed = 250;
int counter = 0;
long duration = 0;


void setup(){
  Serial.begin(9600);
  pinMode(S2_TRIGGER, OUTPUT);
  pinMode(S2_ECHO, INPUT);
  pinMode(B1, INPUT);
  pinMode(S1_IN, INPUT);
  attachInterrupt(digitalPinToInterrupt(B1),toggleMode,FALLING);
  
  Serial.println("-----Welcome to 'Sensing Machine'!-----\n\r");
  Serial.println("Three modes of measurment are avaliable:");
  Serial.println("  1.SOUND\n\r  2.DISTANCE(loop)\n\r  3.TEMPERATURE(loop)");
  Serial.println("Press the 'MODE' button to change mode.");
  changeMode();
}

void loop(){;}


void changeMode(){
  if(MODE==1 || MODE>3){
    MODE = 1;
    attachInterrupt(digitalPinToInterrupt(S1_IN),soundDetected,RISING);
    Serial.println("\n\r-----------SOUND CHANGE MODE------------");
    S1();
  }else if(MODE==2){
    detachInterrupt(digitalPinToInterrupt(S1_IN));
    Serial.println("\n\r-------------DISTANCE MODE--------------");
    S2();
  }else if(MODE==3){
    Serial.println("\n\r------------TEMPERATURE MODE------------");
    S3();
  }
}

void toggleMode(){
  ++MODE;
}

void soundDetected(){
  Serial.println("DETECTED SOUND "+(String)counter++);
}

void S1(){
  while(MODE==1){;}
  changeMode();
}

void S2(){
  while(MODE==2){
    digitalWrite(S2_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(S2_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(S2_TRIGGER, LOW);
    duration = pulseIn(S2_ECHO, HIGH);

    Serial.print("Distance: ");
    Serial.print((float)((duration/2) / 29.1)/100.0);
    Serial.println("cm");
    delay(loopSpeed);
  }
  changeMode();
}

void S3(){
  while(MODE==3){
    Serial.println("Temperature: "+(String)((((float)analogRead(S3_IN)/1024)*5000)/10)+"C");
    delay(loopSpeed);
  }
  changeMode();
}
