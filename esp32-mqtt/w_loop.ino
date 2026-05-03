// Variable estática que mantiene su valor entre ejecuciones de on_loop
static int antes = HIGH; 
static int led = LOW;

void on_loop() {

    int valor = digitalRead(botonPin);
    Serial.println(valor);
    
    // Comprobamos el cambio de estado: 
    // antes era 1 (sin pulsar) y ahora es 0 (pulsado)
    if (antes == HIGH && valor == LOW) {
      
      infoln("Botón pulsado. Enviando mensaje una sola vez.");

      enviarMensajePorTopic(TOPIC_BUTTON, "on");
      
    }
    
    // Actualizamos el estado anterior para la siguiente iteración
    antes = valor;
    
    // Retardo pequeño para el antirrebote (debounce) y liberar CPU
    delay(100);
}
