const int CM1=5;
/*int val;*/
void setup(){
Serial.begin(9600); 
}
void loop(){
Serial.println(analogRead(CM1)); 
/*val=analogRead(CM1);
if(val>=100){
  analogWrite(CM1,0);}*/
}
