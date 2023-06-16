int ledpin=13;
int pirpin=8;
int val=0;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledpin,OUTPUT);
  pinMode(pirpin,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
 val=digitalRead(pirpin);
 digitalWrite(ledpin,val);
 if(val==1)
 {
  digitalWrite(ledpin,HIGH);
 }
}
