#include <Adafruit_MQTT_FONA.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#include <SerialESP8266wifi.h>

#define Relay             2
#define WLAN_SSID         ""//your ssid i.e wifi name
#define WLAN_PASS         ""//your password
#define AIO_SERVER        ""//Adafrit server
#define AIO_SERVERPORT    ""
#define AIO_USERNAME      ""//username
#define AIO_KEY           ""//auth key
WifiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe Light = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/Button"); // Feeds name should be same everywhere



void MQTT_connect();



void setup() {
  Serial.begin(115200);

  pinMode(Relay, OUTPUT);
  
  // connect to wifi access point
  Serial.println();Serial.println();
  Serial.print("connecting to");
  Serial.print(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while(WiFi.status() !=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mqtt.subscribe(&Light);

}

void loop() {
  
  int8_t ret;

  if (mqtt.connected()){
    return;
  }

  Serial.print("Connecting to MQTT...");
  uint8_t retries = 3;

  while ((ret=mqtt.connect() !=0){
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 secs....");
    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries==0){
      while(1);
    }
  }
  Serial.println("MQTT Connected!");
  // put your main code here, to run repeatedly:

}
