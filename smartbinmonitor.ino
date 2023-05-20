/*************************************************************
  This code was made by our team 'INVENTORS' in AIET HACKAATHON-2023, JAIPUR
 *************************************************************/
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "Zv3xJ-0uTeVNXLGIsa6oONRvI0D8DRGa";
char ssid[] = "Pixel";
char password[] = "tanmay123";
char templateId[] = "TMPL3lgf5DN83";

int garbage;
int maxDistance = 23; // Maximum distance (in cm) for full tank level

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, password);
  Blynk.connectWiFi(ssid, password);
  Blynk.config(auth, templateId);
  
  pinMode(D1, OUTPUT);
  pinMode(D2, INPUT);
}

void loop() {
  Blynk.run();

  long duration;
  int distance;

  digitalWrite(D1, LOW);
  delayMicroseconds(2);
  digitalWrite(D1, HIGH);
  delayMicroseconds(10);
  digitalWrite(D1, LOW);

  duration = pulseIn(D2, HIGH);
  distance = duration * 0.034 / 2;
  distance -= 3;
  if(distance<0){distance=0;}
  if(distance>23){distance=23;}
  garbage = maxDistance-distance;
  
  int percentage = map(garbage, 0, maxDistance, 0, 100);
  Serial.println(percentage);
  Blynk.virtualWrite(V0, percentage);
  
  delay(1000);
}
