import time
import paho.mqtt.client as mqtt
import json
from collections import defaultdict
import matplotlib.pyplot as plt



def plot(x_list, y_list):

    plt.scatter(x_list, y_list, s=1)
    
    plt.xlabel("Time (s)")
    plt.ylabel("Distance (cm)")

    plt.show()

def on_connect(client, userdata, flags, rc):
    print('Connected with result code', str(rc))
    global connected
    connected = True

def on_message(client, uerdata, msg):

    global dists
    global times

    msg_info = json.loads(msg.payload.decode('utf-8'))

    print("Time: ", msg_info["time"])
    print("Distance: ", msg_info["distance"])
    print()

    dists.append(msg_info['distance'])
    times.append(msg_info['time'])

if __name__ == "__main__":

    connected = False

    dists = []
    times = []


    broker_address = 'soldier.cloudmqtt.com'
    port = 10132
    user = 'DS'
    password = 'ds'

    client = mqtt.Client('StatsAndVerify')
    client.username_pw_set(user, password=password)
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect(broker_address, port=port)

    client.loop_start()

    while connected != True:
        time.sleep(0.1)

    client.subscribe('Obstacle Detection board')
   
    try:
        while True:
            time.sleep(1)

    except KeyboardInterrupt:
        
        print('Exiting')
        client.disconnect()
        client.loop_stop()

        print("Times: ", times)
        print("Distances: ", dists)

        plot(times, dists)
