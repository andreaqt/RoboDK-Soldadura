from robodk import robolink    # RoboDK API
from robodk import robomath    # Robot toolbox
import Leds_conf as leds
import Movimientos as mov
import time
import threading

RDK = robolink.Robolink()

import paho.mqtt.client as mqtt

station_commands_topic = "giirob/pr2/station/demo/commands"
station_status_topic = "giirob/pr2/station/demo/status"


def handle_message(mqttc, topic, payload, init_all, simulacion):
    msg = payload.strip()
    
    # topic
    if topic == station_commands_topic: 
        # le damos 1 en JSON de mqtt
        if msg == "1":
            # Creamos un hilo para ejecutar la secuencia sin bloquear el cliente MQTT
            hilo_leds = threading.Thread(target=leds.secuencia_semaforo, args=(mqttc, station_status_topic))
            hilo_leds.start() 
            mov.simulacion()
            # El programa sigue aquí inmediatamente mientras los LEDs parpadean de fondo

def move_robot(position):
    robot = RDK.Item("myRobotUR", ITEM_TYPE_ROBOT)
    target = RDK.Item(position).setAsCartesianTarget()
    if robot.Valid() and target.Valid():
        robot.MoveJ(target)
        #robot.MoveL(target)

