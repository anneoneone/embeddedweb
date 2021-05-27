#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* SSID = "FRITZ!Box 7590 YX";
const char* PSK = "80834268567657765952";
const char* MQTT_BROKER = "test.mosquitto.org";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
    Serial.begin(115200);
    setup_wifi();
    client.setServer(MQTT_BROKER, 1883);
}
 
void setup_wifi() {
    WiFi.begin(SSID, PSK);
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
    }
    
    Serial.println(WiFi.localIP());
}
void loop() {
    if (!client.connected()) {
        while (!client.connected()) {
            client.connect("ESP8266Client");
            delay(100);
        }
    }
    client.loop();
    client.publish("/anton/philipp", "Hello World");
}
