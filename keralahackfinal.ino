#include <FirebaseArduino.h>      
#include <DHT.h>           
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>   
 
#define FIREBASE_HOST "agrihack-d6e3b-default-rtdb.firebaseio.com"              // the project name address from firebase id
#define FIREBASE_AUTH "ZvsUt3qhiW5WSpdCVgAMsBLumtWZcT8J8KLnzARu"               
#define WIFI_SSID "STC_Medlycott"                                  
#define WIFI_PASSWORD "9895681391asd"            
                                      // Digital pin connected to DHT11
#define DHTTYPE DHT11  
const int sensor_pin = A0;  
const int DHTPIN = 5;  // Initialize dht type as DHT 11
const int sensorValue = 4;
int ts = 12;
int ms = 14;
int ls = 15;
int hs = 13;
DHT dht(DHTPIN, DHTTYPE);                                                    
 
void setup() 
{
Serial.begin(115200);
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println( WIFI_SSID );

  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);

  Serial.println();
  Serial.print("Connecting");
pinMode(ts, OUTPUT); 
pinMode(hs, OUTPUT); 
pinMode(ms, OUTPUT); 
pinMode(ls, OUTPUT); 
  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      Serial.print(".");        
  }


  Serial.println();

  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );                              //prints local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                 // connect to the firebase
 
}
 
void loop() 
{
  int h = dht.readHumidity();
  int humr=h;
  
 
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  int tempr=t-4;
   float moisture_percentage;

  moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ) );

  Serial.print("Soil Moisture(in Percentage) = ");
  Serial.print(moisture_percentage);
  Serial.println("%");
   // read the input on analog pin 0

    delay(300);// print out the value you read
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor !");

  }
  Serial.print("Humidity: ");  
  Serial.print(h);
  String fireHumid = String(h);               //Humidity integer to string conversion
  
  Serial.print("%  Temperature: ");  
  Serial.print(t);  
  Serial.println("°C ");
  String fireTemp = String(t) ;           //Temperature integer to string conversion
  delay(500);
float randt = random(27, 30); 
float  randh = random(38, 40); 
 
 
 
  Firebase.setFloat("/DHT11/Humidity", humr);            //setup path to send Humidity readings
  Firebase.setFloat("/DHT11/Temperature", tempr); 
  Firebase.setFloat("/DHT11/Moisture", moisture_percentage); 
delay(300);

String sett = Firebase.getString("/SET/temperature");
String seth = Firebase.getString("/SETH/humidity");
String hswitch = Firebase.getString("/Lswitch/state");
String lswitch = Firebase.getString("/Hswitch/state");
String mswitch = Firebase.getString("/Mswitch/state");
String tswitch = Firebase.getString("/Tswitch/state");
  delay(300);
   Serial.print(sett);
    Serial.print(seth);
   Serial.print(hswitch);
    Serial.print(lswitch);
     Serial.print(mswitch);
      Serial.print(tswitch);//setup path to send Temperature readings
      delay(500);
    if (Firebase.failed()) 
    {
 
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error()); 
      return;
  }
 delay(500); 
if(hswitch=="ON"){
  digitalWrite(hs, HIGH);
}
if(hswitch=="OFF"){
  digitalWrite(hs, LOW);
}
if(lswitch=="ON"){
  digitalWrite(ls, HIGH);
}
if(lswitch=="OFF"){
  digitalWrite(ls, LOW);
}
if(mswitch=="ON"){
  digitalWrite(ms, HIGH);
}
if(mswitch=="OFF"){
  digitalWrite(ms, LOW);
 
}
if(tswitch=="ON"){
  digitalWrite(ts, HIGH);
}
if(tswitch=="OFF"){
  digitalWrite(ts, LOW);
}

int tempi = sett.toInt();
int humi = seth.toInt();




if( moisture_percentage>10 ){
  digitalWrite(ms, LOW); 
}
delay(300);
}
