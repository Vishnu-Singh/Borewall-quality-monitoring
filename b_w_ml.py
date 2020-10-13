from serial import Serial
import paho.mqtt.publish as pub


#port='COM43' #For Windows
port='/dev/ttyACM0' #for Linux
boudrate=9600
timeout=5
host='192.168.1.5'  #PC ipAddress
ser=Serial(port,boudrate,timeout=timeout)
def publish(rawData):
    rData=str(rawData)
    d=rData.split(':')
    
    topic=d[0].split(sep='\'')[1]
    payload=d[1].split(sep='\\')[0]
    print(topic+" : "+payload)
    pub.single(topic,payload,hostname=host)

def value(data):
    t_d=[]
    r_data=data.decode()
    ext_data=r_data.split(':')
    print(len(ext_data))
    topic=ext_data[0]
    value=ext_data[1].split('\r')[0]
    t_d.append(topic)
    t_d.append(value)
    '''
    print(topic,value)
    if topic=='PH':
        t_d.append(value)
        print('\t\t',t_d)
    if topic=='turbidity':
        t_d.append(value)
        print('\t\t',t_d)
    f_d.append(t_d)
    if len(f_d) is not []:
        return f_d'''
    return t_d

def upload():
    rawData=ser.readline();
    #print(rawData)
    publish(rawData)

def cal_data():
    i=0
    pre=[]
    d=[]
    while i<5:
       
        t_v=value(ser.readline())
        if t_v[0]=='turbidity':
            pre.append(float(t_v[1]))
        if t_v[0]=='PH':
            pre.append(float(t_v[1]))
        i+=1
        
        if(len(pre)==2):
            #len(pre)
            print(type(pre[0]))
            #pre.reverse()
            #print(i)
    d.append(pre)
    print(len(d[0]),d) 
    if len(d[0])==2:
        #d.reverse()
        #print(d)
        return d
#while True:
 #   cal_data()
  #  upload()
