#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <FirebaseESP32.h>

#define SENSOR  27
#define hijau  34
#define kuning 35
#define merah 32

LiquidCrystal_I2C lcd(0x27, 16, 2); 

const char* ssid = "mar";
const char* password = "mar140401#";

const int trigPin1 = 16;  // Pin Trigger Sensor Ultrasonik 2 RX
const int echoPin1 = 17;  // Pin Echo Sensor Ultrasonik 2 TX

#define FIREBASE_HOST "https://banjir-64482-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "XkmGkviY6DCS4iRMLAkl7bJwwNxcSWXBy7HfW39d"
FirebaseData fbdo;

//flow Sensor
long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;
boolean ledState = LOW;
float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

long duration1, distance1;  // Variabel untuk Sensor Ultrasonik 1
long duration2, distance2;  // Variabel untuk Sensor Ultrasonik 2


AsyncWebServer server(80);

void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}


TinyGPS gps;
SoftwareSerial ss(3, 1);
char str[200];
bool newData = false;
unsigned long chars;
unsigned short sentences, failed;

void setup() {
  pinMode(SENSOR, INPUT_PULLUP);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(hijau,OUTPUT);
  pinMode(kuning,OUTPUT);
  pinMode(merah,OUTPUT);

  lcd.begin();
  lcd.home ();
  ss.begin(9600);

  Serial.print("Simple TinyGPS library v. "); Serial.println(TinyGPS::library_version());

  attachInterrupt(digitalPinToInterrupt(SENSOR), pulseCounter, FALLING);

  Serial.begin(9600);

    if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/jarak", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(distance1).c_str());
  });
  server.begin();
}

void loop() {

    Firebase.setInt(fbdo,"/Banjir/KTM",distance1);
    Firebase.setInt(fbdo,"/Banjir/FLW",flowRate);
    
    for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      char c = ss.read();
      if (gps.encode(c)) 
        newData = true;
    }
  }

  float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("Lokasi:");
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    sprintf(str,"https://www.google.com/maps/place/%f,%f", flat, flon);
    Firebase.setString(fbdo,"/Banjir/LOC",str);
  // Mengukur jarak menggunakan Sensor Ultrasonik 1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;


    // Fungsi Sensor Flow
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    
    pulse1Sec = pulseCount;
    pulseCount = 0;


    flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
    previousMillis = millis();


    flowMilliLitres = (flowRate / 60) * 1000;

    totalMilliLitres += flowMilliLitres;

    Serial.print("Flow rate: ");
    Serial.print(int(flowRate));  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.print("\t");       // Print tab space


    Serial.print("Output Liquid Quantity: ");
    Serial.print(totalMilliLitres);
    Serial.print("mL / ");
    Serial.print(totalMilliLitres / 1000);
    Serial.println("L");

    lcd.setCursor(0,1);
    lcd.print("FR:");
    lcd.print(flowRate);
    lcd.print("   ");
    lcd.setCursor(8,1);
    lcd.print("KT:");
    lcd.print(distance1);
    lcd.print("   ");
    delay(300);

    Serial.print(distance1);
    
     if(distance1 < 30){
       digitalWrite(hijau,HIGH);
       //Firebase.setInt(fbdo,"/Banjir/TDK",1);
     }else{
       digitalWrite(hijau,LOW);
     }
     if(distance1 < 50){
       digitalWrite(kuning,HIGH);
     }else{
       digitalWrite(kuning,LOW);
     }
         if(distance1 < 100){
       digitalWrite(merah,HIGH);
       //Firebase.setInt(fbdo,"/Banjir/BJR",1);
     }else{
       digitalWrite(merah,LOW);
     }
  }
}
