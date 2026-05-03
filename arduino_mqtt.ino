#include "Config.h"

#include <WiFi.h>
#ifdef SSL_ROOT_CA
  #include <WiFiClientSecure.h>
#endif
#include <PubSubClient.h>
#include <ArduinoJson.h>

void setup() {

#ifdef LOGGER_ENABLED
  // Inicializamos comunicaciones serial
  Serial.begin(BAUDS);
  
  Serial.begin(115200);
  delay(100);
  Serial.println();
#endif

  // Nos conectamos a la wifi
  wifi_connect();

  mqtt_connect(deviceID);

  suscribirseATopics();
  
  on_setup();

}

void loop() {

  wifi_loop();
  mqtt_loop();

  on_loop();
}


