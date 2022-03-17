#include <IRremote.hpp>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd1(0x27, 16, 2); // << Address 1
LiquidCrystal_I2C lcd2(0x26, 16, 2); // << Address 2

Servo servomoteur1;
Servo servomoteur2;

int X=6;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(X, 9, NEO_GRB + NEO_KHZ800);


unsigned long MS;
unsigned long start;
int temps_stationnementA=0;
int temps_stationnementsecA=0;
int temps_stationnementminA=0;
int temps_stationnementfinA=0;

int temps_stationnementB=0;
int temps_stationnementsecB=0;
int temps_stationnementminB=0;
int temps_stationnementfinB=0;

int paiementA=0;
int paiementB=0;

const int trig_ultrason1 = 24;
const int echo_ultrason1 =26;
float DCU1 = 0;

const int trig_ultrason2 = 50;
const int echo_ultrason2 =48;
float DCU2 = 0;

int nmbr_places=2;

const int CM1=10;
const int CM2=5;
const int CM3=7;
const int CM4=8;
const int CM5=32;
const int CM6=30;

int ECM1=0;
int ECM2=0;
int ECM3=0;
int ECM4=0;
int ECM5=0;
int ECM6=0;

int pos_arceau1 = 1;
int pos_arceau2 = 1;

int ECIA=0;
int ECIB=0;

IRrecv IR(6);

void setup() {

  Serial.begin(9600);

  pinMode(CM1,INPUT);
  pinMode(CM2,INPUT);
  pinMode(CM3,INPUT);
  pinMode(CM4,INPUT);

  strip.begin();
  strip.show();
  
  servomoteur1.attach(3);
  servomoteur2.attach(28);
  
  IR.enableIRIn();

  pinMode(echo_ultrason1, INPUT);
  pinMode(trig_ultrason1, OUTPUT);
  digitalWrite(trig_ultrason1, HIGH);
  digitalWrite(trig_ultrason1, LOW);
  DCU1 = pulseIn(echo_ultrason1,HIGH)/58;

  pinMode(echo_ultrason2, INPUT);
  pinMode(trig_ultrason2, OUTPUT);
  digitalWrite(trig_ultrason2, HIGH);
  digitalWrite(trig_ultrason2, LOW);
  DCU2 = pulseIn(echo_ultrason2,HIGH)/58;
  
  lcd1.init();
  lcd1.backlight();
  lcd2.init();
  lcd2.backlight();
  
  start=millis();

  lcd2.setCursor(3, 0);
  lcd2.print("Au revoir !");
}
void arceau_se_baisse1() {
  
  for (int position = 90; position >=0; position --){
        Serial.println("L'arceau 1 se baisse");
        servomoteur1.write(position);  
        delay(15);  
        pos_arceau1=0;
        ECIA=0;
        ECIB=0;
    }
   
}
void arceau_se_leve1() {
  for (int position = 0; position <=90; position ++){
        Serial.println("L'arceau 1 se lève");
        servomoteur1.write(position);  
        delay(15); 
        pos_arceau1=1; 
        ECIA=0;
        ECIB=0;
        
        
    }
   
}
void arceau_se_baisse2() {
  
  for (int position = 90; position >=0; position --){
        Serial.println("L'arceau 2 se baisse");
        servomoteur2.write(position);  
        delay(15);  
        pos_arceau2=0;
        ECIB=0;
        ECIA=0;
    }
   
}
void arceau_se_leve2() {
  for (int position = 0; position <=90; position ++){
        Serial.println("L'arceau 2 se lève");
        servomoteur2.write(position);  
        delay(15); 
        pos_arceau2=1; 
        ECIB=0;
        ECIA=0;
        
    }
   
}
void paiement_A() {
  temps_stationnementsecA=((MS / 1000) % 60)-temps_stationnementsecA;
  temps_stationnementminA=((MS / 1000) / 60)-temps_stationnementminA;  
  temps_stationnementfinA=temps_stationnementsecA+60*temps_stationnementminA;
  if(temps_stationnementfinA>0 && temps_stationnementfinA<=30){
    paiementA=temps_stationnementfinA*0.50;
    
  }
  if(temps_stationnementfinA>30 && temps_stationnementfinA<=50){
    paiementA=temps_stationnementfinA*0.40;
    
}
if(temps_stationnementfinA>50 && temps_stationnementfinA<=400){
    paiementA=temps_stationnementfinA*0.30;
    
}
  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd2.print("Temps");
  lcd2.setCursor(8, 0);
  lcd2.print(temps_stationnementfinA);
  lcd2.setCursor(12, 0);
  lcd2.print("Sec.");
  lcd2.setCursor(0, 1);
  lcd2.print("Cout :");
  lcd2.setCursor(8, 1);
  lcd2.print(paiementA);
  temps_stationnementminA=0;
  temps_stationnementsecA=0;
  lcd2.setCursor(10, 1);
  lcd2.print("Euros");
  delay(7000);
  lcd2.clear();
  lcd2.setCursor(3, 0);
  lcd2.print("Au revoir !");
}
void paiement_B() {
  temps_stationnementsecB=((MS / 1000) % 60)-temps_stationnementsecB;
  temps_stationnementminB=((MS / 1000) / 60)-temps_stationnementminB;  
  temps_stationnementfinB=temps_stationnementsecB+60*temps_stationnementminB;
 
  if(temps_stationnementfinA>0 && temps_stationnementfinA<=30){
    paiementB=temps_stationnementfinB*0.50;
    
  }
  if(temps_stationnementfinB>30 && temps_stationnementfinB<=50){
    paiementB=temps_stationnementfinB*0.40;
    
}
if(temps_stationnementfinB>50 && temps_stationnementfinB<=400){
    paiementB=temps_stationnementfinB*0.30;
    
}
  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd2.print("Temps");
  lcd2.setCursor(8, 0);
  lcd2.print(temps_stationnementfinB);
  lcd2.setCursor(10, 0);
  lcd2.print("Sec.");
  lcd2.setCursor(0, 1);
  lcd2.print("Cout :");
  lcd2.setCursor(8, 1);
  lcd2.print(paiementB);
  temps_stationnementminB=0;
  temps_stationnementsecB=0;
  lcd2.setCursor(10, 1);
  lcd2.print("Euros");
  delay(7000);
  lcd2.clear();
  lcd2.setCursor(3, 0);
  lcd2.print("Au revoir !");
}

void loop() {

  MS = millis()-start;
  
  Serial.println("ECIA=");
  Serial.println(ECIA);
  Serial.println("ECIB=");
  Serial.println(ECIB);
  if(IR.decode()){
    Serial.println(IR.decodedIRData.decodedRawData, HEX);
  if(IR.decodedIRData.decodedRawData == 0xBF40FF00){
    ECIA=1;
    }
    else if(IR.decodedIRData.decodedRawData == 0xEA15FF00){
    ECIB=1;
    }
  delay(1500);
  IR.resume();
}
  
  
  ECM1=digitalRead(CM1);
    Serial.println("ECM1=");
    Serial.println(ECM1);
    
  ECM2=digitalRead(CM2);
    Serial.println("ECM2=");
    Serial.println(ECM2);
    
  ECM3=digitalRead(CM3);
    Serial.println("ECM3=");
    Serial.println(ECM3);
    
  ECM4=digitalRead(CM4);
    Serial.println("ECM4=");
    Serial.println(ECM4);

 ECM5=digitalRead(CM5);
    Serial.println("ECM5=");
    Serial.println(ECM5);

 ECM6=digitalRead(CM6);
    Serial.println("ECM6=");
    Serial.println(ECM6);
 
  if(pos_arceau1==1&&ECIA==1&&ECM1==0){
    arceau_se_baisse1();
    temps_stationnementsecA=((MS / 1000) % 60);
    temps_stationnementminA=((MS / 1000) / 60);  
  }
  if(pos_arceau1==1&&ECIB==1&&ECM1==0){
    arceau_se_baisse1();
    temps_stationnementsecB=((MS / 1000) % 60);
    temps_stationnementminB=((MS / 1000) / 60);
  }
  if(ECM1==1&&ECM2==1&&pos_arceau1==0){
    arceau_se_leve1();
  }

  if(pos_arceau2==1&&ECIA==1&&ECM5==0){
    arceau_se_baisse2();
    paiement_A();
  }
  if(pos_arceau2==1&&ECIB==1&&ECM5==0){
    arceau_se_baisse2();
    paiement_B();
  }
  if(ECM5==1&&ECM6==1&&pos_arceau2==0){
    arceau_se_leve2();
  }

  strip.show();

 if(ECM3==0){
  strip.setPixelColor(0, 223, 0, 0);  
  strip.setPixelColor(1, 0, 0, 0); 
    
}
else{
  strip.setPixelColor(1, 0, 0, 0);  
  strip.setPixelColor(0, 0, 223, 0); 
  
}
if(ECM4==0){
  strip.setPixelColor(2, 223, 0, 0); 
  strip.setPixelColor(3, 0, 0, 0);
  
}

else{
    strip.setPixelColor(3, 0, 0, 0); 
    strip.setPixelColor(2, 0, 223, 0);
    
}

if(ECM3==1&&ECM4==1){
  nmbr_places=2;
}
if(ECM3==0&&ECM4==1){
  nmbr_places=1;
}
if(ECM3==1&&ECM4==0){
  nmbr_places=1;
}
if(ECM3==0&&ECM4==0){
  nmbr_places=0;
}
  lcd1.setCursor(3, 0);
  lcd1.print("Bienvenue !");
  lcd1.setCursor(0, 1);
  lcd1.print("Nbr. places :");
  lcd1.setCursor(14, 1);
  lcd1.print(nmbr_places);
  
  
if (DCU1<= 2){
  /*tone (13, 12000);*/
   strip.setPixelColor(0, 255,165,0);  
   strip.setPixelColor(1, 255,165,0);
 }
  /*else{
  noTone(13);
 }*/
digitalWrite(trig_ultrason1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_ultrason1, LOW);
  DCU1 = pulseIn(echo_ultrason1,HIGH)/58;
 
  if (DCU2<= 3){
  /*tone (52, 12000);*/
   strip.setPixelColor(2, 255,165,0);  
   strip.setPixelColor(3, 255,165,0); 
 }
 /*else{
  noTone(52);
 }*/
  digitalWrite(trig_ultrason2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_ultrason2, LOW);
  DCU2 = pulseIn(echo_ultrason2,HIGH)/58;

}
