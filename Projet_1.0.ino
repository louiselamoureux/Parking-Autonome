#include <Servo.h>
Servo servomoteur;
int pos_arceau = 1;
const int trig_ultrason1 = 5;
const int echo_ultrason1 = 4;
float DCU = 0;
int ECI=0;

void setup() {
  pinMode(echo_ultrason1, INPUT);
  pinMode(trig_ultrason1, OUTPUT);
  digitalWrite(trig_ultrason1, LOW);
  servomoteur.attach(3);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig_ultrason1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_ultrason1, LOW);
  DCU = pulseIn(echo_ultrason1,HIGH)/58;
  Serial.print("Distance en cm :");
  Serial.println(DCU);

  if(pos_arceau==1&&ECI==1){
    arceau_se_baisse();
  }
  if(pos_arceau==0&&DCU<10){
    arceau_se_leve();
  }
}
void arceau_se_baisse() {
  for (int position = 0; position <=90; position ++){
        servomoteur.write(position);  
        delay(15);  
    }
   
}
void arceau_se_leve() {
  for (int position = 90; position >=0; position --){ 
        servomoteur.write(position);  
        delay(15);  
    }
   
}
