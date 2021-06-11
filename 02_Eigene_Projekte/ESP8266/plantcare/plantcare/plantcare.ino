
// wifi und mqtt
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* SSID = "FRITZ!Box 7590 YX";
const char* PSK = "80834268567657765952";
const char* MQTT_BROKER = "test.mosquitto.org";
 
WiFiClient espClient;
PubSubClient client(espClient);

// pumpe
#define SensorPin A0  // used for Arduino and ESP8266
int pin_relais = 5;
String sensorValueString;
char sensorValueBuffer[10];

void setup() { 
  
  // wifi und mqtt
  Serial.begin(115200);
  setup_wifi();
  client.setServer(MQTT_BROKER, 1883);

  // set pins as output
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pin_relais, OUTPUT);

  
  digitalWrite(pin_relais, HIGH );   // zu anfang ist pumpe aus

  // pumpe
  Serial.begin(9600); // baudrate für hygrometer

}

void setup_wifi() {
    WiFi.begin(SSID, PSK);
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
    }
    
    Serial.println(WiFi.localIP());
}

void loop() {
  float sensorValue = analogRead(SensorPin);
  Serial.println(sensorValue);

  if (sensorValue > 600) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(pin_relais, LOW);   // turn the LED on (HIGH is the voltage level)
    Serial.println("jetzt gibts wasser!");
    delay(5000);                       // wait for a second
    
  } 
  // else {
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(pin_relais, HIGH );   // turn the LED on (HIGH is the voltage level)
    delay(5000);
    //Serial.println("jetzt nicht :(");
  //}

  if (!client.connected()) {
      while (!client.connected()) {
          client.connect("ESP8266Client");
          delay(100);
      }
  }

  sensorValueString = String(sensorValue);
  sensorValueString.toCharArray(sensorValueBuffer, sensorValueString.length()+1);
  
  client.loop();
  client.publish("/anton/plantcare", sensorValueBuffer);
}
