import time

class netConnector:
    def connect_WAP(ap,ssid, pswd):
        ssid = ssid
        password = pswd

        ap.active(True)
        ap.config(essid=ssid, password=password)
        print("creating WAP as {} :".format(ssid))
        print("[", end="")
        while not ap.active():
            print("#", end="")
            time.sleep(1)
        print("]")
        print('Access Point successfully created')
        print(ap.ifconfig())


    def connect_STA(station,ssid, pswd,HOSTNAME=None):
        ssid = ssid
        password = pswd
        if station.isconnected() == True:
            print("Already connected")
            print(station.ifconfig())
            print("ip address :",station.ifconfig()[0])
            print("Hostname :",station.config('hostname'))
            return

        station.active(True)
        
        if HOSTNAME==None:
            mac = station.config('mac')
            HOSTNAME = 'esp32-' + ''.join('{:02x}'.format(b) for b in mac[3:])
            
        station.config(dhcp_hostname = HOSTNAME)
        station.connect(ssid, password)
        print("Connecting to {} :".format(ssid))
        print("[", end="")
        timetaken = 0
        while station.isconnected() == False:
            print("#", end="")
            time.sleep(1)
            timetaken += 1
        print("] : {}s".format(timetaken))

        print("Connection successful")
        print(station.ifconfig())
        print("ip address :",station.ifconfig()[0])
        print("Hostname :",station.config('hostname'))

        
