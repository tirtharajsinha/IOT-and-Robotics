import os
import neopixel
import socketpool
import wifi
import board
import mdns
from adafruit_httpserver import Server, Request, Response, GET, POST, JSONResponse
import microcontroller

ssid = "SINHA_NCBN"
password = "19061969"
pixel_pin = board.NEOPIXEL
num_pixels = 1
current_color = (0, 0, 100)

pixel = neopixel.NeoPixel(pixel_pin, num_pixels, brightness=0.3)
pixel.fill(current_color)

print("Connecting to", ssid)
wifi.radio.connect(ssid, password)
print("Connected to", ssid)

current_color = (0, 100, 100)
pixel.fill(current_color)

mdns_server = mdns.Server(wifi.radio)
mdns_server.hostname = "esp32s3"
mdns_server.advertise_service(service_type="_http", protocol="_tcp", port=80)


pool = socketpool.SocketPool(wifi.radio)
server = Server(pool, "/static", debug=True)


@server.route("/")
def base(request: Request):
    """
    Serve a default static plain text message.
    """
    data = {
        "temperature": microcontroller.cpu.temperature,
        "frequency": microcontroller.cpu.frequency,
        "voltage": microcontroller.cpu.voltage,
        "Current Led Color": current_color,
    }

    return JSONResponse(request, data)


@server.route("/change-neopixel-color/<r>/<g>/<b>", GET)
def change_neopixel_color_handler_url_params(
    request: Request, r: str = "0", g: str = "0", b: str = "0"
):
    """Changes the color of the built-in NeoPixel using URL params."""

    # e.g. /change-neopixel-color/255/0/0
    global current_color

    pixel.fill((int(r), int(g), int(b)))

    curpix = ",".join(map(str, current_color))
    print(curpix)

    res = f"Previous NeoPixel Color : ({curpix}) \nChanged NeoPixel to color : ({r}, {g}, {b})"

    current_color = (int(r), int(g), int(b))

    return Response(request, res)


server.serve_forever(str(wifi.radio.ipv4_address))
