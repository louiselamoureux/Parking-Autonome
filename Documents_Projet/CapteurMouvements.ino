const int CM1=5;
/*const int CM2=4;*/
void setup() {
pinMode(CM1,INPUT);
/*pinMode(CM2,INPUT);*/
Serial.begin(9600);
}
void loop() {
  if(digitalRead(CM1)==HIGH){
   Serial.println("mouvement detecte");
  }
  if(digitalRead(CM1)==LOW){
   Serial.println("pas de mouvement detecte");
  }
/*    if(digitalRead(CM2)==HIGH){
   Serial.println("mouvement detecte");
  }
  if(digitalRead(CM2)==LOW){
   Serial.println("pas de mouvement detecte");
  }*/
}
