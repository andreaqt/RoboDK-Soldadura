from robodk import robolink
import time

RDK = robolink.Robolink()

#asignamos led a tipo item
led_rojo = RDK.Item("led_rojo")
led_verde = RDK.Item("led_verde")
led_amarillo = RDK.Item("led_amarillo")
led_off = RDK.Item("led_off")

# Añadimos mqttc y topic como argumentos para que la función pueda publicar
def red_on(mqttc, topic):
    mqttc.publish(topic, "RED ON")
    led_rojo.setVisible(True)

def red_off(mqttc, topic):
    mqttc.publish(topic, "RED OFF")
    led_rojo.setVisible(False)

def yellow_on(mqttc, topic): 
    mqttc.publish(topic, "AMARILLO ON")
    led_amarillo.setVisible(True)

def yellow_off(mqttc, topic):
    mqttc.publish(topic, "AMARILLO OFF")
    led_amarillo.setVisible(False)

def green_on(mqttc, topic):
    mqttc.publish(topic, "VERDE ON")
    led_verde.setVisible(True)

def green_off(mqttc, topic):
    mqttc.publish(topic, "VERDE OFF")
    led_verde.setVisible(False)

def inicializar_leds():
    led_rojo.setVisible(False)
    led_verde.setVisible(False)
    led_amarillo.setVisible(False)
    led_off.setVisible(True)

def secuencia_semaforo(mqttc, status_topic):
    red_on(mqttc, status_topic)
    time.sleep(2)
    red_off(mqttc, status_topic)
    yellow_on(mqttc, status_topic)
    time.sleep(2)
    yellow_off(mqttc, status_topic)
    green_on(mqttc, status_topic)
    time.sleep(2)
    green_off(mqttc, status_topic)
