  
int ir_pin=8;
int plat=7;
int plat_stop=9;
int turbidity_pin=A0;
int volt_pin=A1;
int current_pin=A2;
float R1=47000.0;
float R2=33000.0;
int value=0;
float voltage;
int motor=6;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ir_pin,INPUT);
  pinMode(plat,OUTPUT);
  pinMode(turbidity_pin,INPUT);
  pinMode(volt_pin,INPUT);
  pinMode(current_pin,INPUT);
  pinMode(plat_stop,INPUT_PULLUP);
  pinMode(motor,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  getPHValue();
  getCurrent();
  getVolt();
  fallDetection();
  getTurbidity();
}

void getPHValue() {
  String ph;
        String phdata = Serial.readStringUntil(':');
        if(phdata != ""){
            ph = Serial.readStringUntil('$');
            float phvalue=ph.toFloat();
            Serial.print("PH:");
            Serial.println(phvalue);
            
        }
    //return ph;
}

void fallDetection(){
  if(digitalRead(ir_pin)==HIGH){
      digitalWrite(plat,HIGH);
      //if(digitalRead(plat_stop)==LOW){
        //Serial.println("plat Stoped");
        delay(100*4);
        digitalWrite(plat,LOW);
     // }
      Serial.print("Fall:");
      Serial.println('1');
  }else{
    digitalWrite(plat,LOW);
    Serial.print("Fall:");
    Serial.println('0');
  }
}

void getVolt(){
   value = analogRead(volt_pin);
  voltage = value * (5.0/1024)*((R1 + R2)/R2);
  if(voltage<4)
    digitalWrite(motor,LOW);
  else
    digitalWrite(motor,HIGH);
  Serial.print("voltage:");
  Serial.println(voltage);
}

void getCurrent(){
  float readAmpsADC = analogRead(current_pin);
   voltage = fabs(fmap(readAmpsADC, 0.0, 1024.0, 0.00, 5.0)); //this maps the measured voltage in volts from 0 t 5V
   float amps = voltage * (10.0/3.7575); 
   Serial.print("current:");
   Serial.println(amps);
}

void getTurbidity(){
  int val=analogRead(turbidity_pin);
  Serial.print("turbidity:");
  Serial.println(val);
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
