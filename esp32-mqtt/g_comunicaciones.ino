void suscribirseATopics() {
  mqtt_subscribe(TOPIC_COMANDO);
  mqtt_subscribe(TOPIC_STATUS);
  mqtt_subscribe(TOPIC_BUTTON);
}

void alRecibirMensajePorTopic(char* topic, String incomingMessage) {

  //lee el mensaje enviado por button
  if (strcmp(topic, TOPIC_BUTTON) == 0 ) {

    infoln("Mensaje crudo recibido: [" + incomingMessage + "]");
    incomingMessage.trim();
    if(incomingMessage == "on") {
      enviarMensajePorTopic(TOPIC_COMANDO, "1");
    }
    else warnln("**>> Solicitud no reconocida!");
    
  }

    //gestiona los estados de los leds que reciben por la mqtt
    if (strcmp(topic, TOPIC_STATUS) == 0 ) {
    incomingMessage.trim();
    if(incomingMessage == "RED ON") {
      digitalWrite(LED_RED, HIGH);
    }
    if(incomingMessage == "RED OFF") {
      digitalWrite(LED_RED, LOW);
    }
    if(incomingMessage == "AMARILLO ON") {
      digitalWrite(LED_YELLOW, HIGH);
    }
    if(incomingMessage == "AMARILLO OFF") {
      digitalWrite(LED_YELLOW, LOW);
    }
    if(incomingMessage == "VERDE ON") {
      digitalWrite(LED_GREEN, HIGH);
    }
    if(incomingMessage == "VERDE OFF") {
      digitalWrite(LED_GREEN, LOW);
    }

    else warnln("**>> Solicitud no reconocida!");
  }

}

void enviarMensajePorTopic(const char* topic, String outgoingMessage) {

  mqtt_publish(topic, outgoingMessage.c_str());

}
