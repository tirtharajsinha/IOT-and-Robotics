import network,neopixel
from secrets import secrets
from netConnector import netConnector
from machine import Pin
import json
import tinyweb
from time import sleep
from _thread import allocate_lock
import board_details
import re
import uasyncio



# CONST values
HOSTNAME="esp32"
HOST="0.0.0.0"
PORT=80
STATIC="www"


# Wifi connection
station = network.WLAN(network.STA_IF)
netConnector.connect_STA(station,secrets.SSID, secrets.PASSWORD, HOSTNAME)


# Initializing server
app = tinyweb.webserver()

# Iniatializing led conf
np = neopixel.NeoPixel(Pin(18), 1)
np[0] = (0, 0, 0)
np.write()

led = Pin(2, Pin.OUT)
led_state = False


def templateEngine(template,context):
    found = re.findall(r"\{\{\s*(.*?)\s*\}\}",template)
    print(found)



async def index(req, resp):
    await resp.send_file('www/index.html')

@app.route('/www/<fn>')
async def files_css(req, resp, fn):
    await resp.send_file('{}/{}'.format(STATIC,fn))
                    


class boardInfo():
    def get(self, data):
        boardDetail=board_details.boardDetails()
        context={
            "IPADDRESS":station.ifconfig()[0],
            "HOSTNAME":HOSTNAME,
            "DEVICENAME":boardDetail.BoardName,
            "FlashMB":boardDetail.DispFlash,
            "UsedMB":boardDetail.DispUsed,
            "FreeMB":boardDetail.DispFree,
            "AvailableMB":boardDetail.DispAvail
            }
        print(data)
        return context,200
   
   
async def neopixelColorPicker(req, resp):
    await resp.send_file("www/colorpicker.html")



class neopixelController():
    def get(self, args):
        content={"status":200}
#         print(args)
#         print(args["r"],args["g"],args["b"],args["a"])
        r,g,b=int(args["r"]),int(args["g"]),int(args["b"])
        np[0] = (r, g, b)
        np.write()
        
        return content



async def Led(req, resp):
    await resp.send_file("www/led.html")
    global led_state
   


    

class LedController():
    def get(self,args):
        global led_state
        
        if 'LED' in args.keys():
            if args["LED"]=="toggle":
                if led_state:
                    led.off()
                    led_state=False
                else:
                    led.on()
                    led_state=True
            content={"LED_STATE":led_state}
            return content,200
        return {"status":404},404

    
    
        
    
def run():
    app.add_route("/", index)
    app.add_resource(boardInfo, '/boardInfo')
    
    app.add_route("/neopixel", neopixelColorPicker)
    app.add_resource(neopixelController, '/setneopixel')
    
    app.add_route("/led", Led)
    app.add_resource(LedController, '/setled')
    
    app.run(host=HOST, port=PORT)


if __name__ == '__main__':
    try:
        print(f"Starting tinyweb server on {HOST}:{PORT}....")
        run()
    
    except KeyboardInterrupt as e:
        print(' CTRL+C pressed - terminating...')
        web.shutdown()
        np[0] = (0, 0, 0)
        np.write()
        uasyncio.get_event_loop().run_until_complete(all_shutdown())
    



    



    
    