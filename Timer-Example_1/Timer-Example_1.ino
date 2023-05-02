unsigned long myTime;

void setup() {
  Serial.begin(9600);
  myTime = millis();
}
void loop() {
  if (millis() == myTime+3000){
    Serial.println("banana");
    myTime = millis();
  }

}