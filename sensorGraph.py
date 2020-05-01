import time
import paho.mqtt.client as mqtt
import json
from collections import defaultdict

def on_connect(client, userdata, flags, rc):
    print('Connected with result code', str(rc))
    global connected
    connected = True


def on_message(client, uerdata, msg):
    bad = False
    error = False
    global pub
    global pubS
    global pubT
    global rec
    global recS
    global recM
    global subs

    try:
        d = json.loads(msg.payload.decode('utf-8'))
        if msg.topic == 'Obstacle Detection board':
            if d.keys() != {'id', 'pub', 'rec', 'dist', 'time'}:
                # not all fields are there
                bad = True
        elif msg.topic == 'pixy':
            if d.keys() != {'id', 'pub', 'rec', 'x_coordinate', 'y_coordinate', 'height', 'width', 'signature', 'time'}:
                # not all of the fields required are there
                bad = True
        elif msg.topic == 'arm':
            if d.keys() != {'id', 'pub', 'rec', 'status', 'time'}:
                bad = True
        elif msg.topic == 'rover':
            if d.keys() != {'id', 'pub', 'rec', 'status', 'atDestination', 'time'}:
                bad = True
        elif msg.topic == 'topics':
            if d.keys() != {'id', 'topic1', 'topic2', 'topic3', 'topic4'}:
                bad = True
            subs[d['topic1']].append(d['id'])#adds board to topic
            subs[d['topic2']].append(d['id'])
            subs[d['topic3']].append(d['id'])
            subs[d['topic4']].append(d['id'])   
        else:
            bad = True

    except Exception as ex:
        bad = True
        error = True
        print(ex)
    
    
    
    if(error == False):
        for i in subs[msg.topic]:
            rec[i] = rec[i] + 1
        
        try:
            pub[d['id']] = d['pub']#updates board publishes
        except:
            pass
        
        if(bad == False):
            pubT[d['id']] = time.strftime("%H:%M:%S", time.localtime())#updates last successful publish time
            pubS[d['id']] = pubS[d['id']] + 1#updates successful board publishes
            recS[d['id']] = d['rec']#updates successful recieves
            recM[d['id']] = rec[d['id']] - d['rec']#updates missed number of recieves
            
            
        #print(msg.topic, str(msg.payload))
        
        print(' Stats:')
        #print(pub, bad)
        for client in pub:
            
            print(client,':')
            print('Publishing Attempts:', pub[client])
            print('Publishing Successes:', pubS[client])
            print('Publishings Recieved:', recS[client])
            print('Publishings Missed:', recM[client])
            print('Time of last Publishing Success:', pubT[client])
            print('')
        


connected = False
pub = {}#times board thinks it published
pub = defaultdict(lambda:0,pub)
pubS = {}#times board successfully published
pubS = defaultdict(lambda:0,pubS)
pubT = {}#Last time that board successfully published
pubT = defaultdict(lambda:0,pubT)
rec = {}#times board should have recieved message
rec = defaultdict(lambda:0,rec)
recS = {}#times board successfully recieved message
recS = defaultdict(lambda:0,recS)
recM = {}#times board missed message
recM = defaultdict(lambda:0,recM)
subs = {}#boards that belong to each topic
subs = defaultdict(lambda:[],subs)


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
# client.subscribe('pixy')
# client.subscribe('arm')
# client.subscribe('rover')
# client.subscribe('topics')

try:
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    print('Exiting')
    client.disconnect()
    client.loop_stop()
