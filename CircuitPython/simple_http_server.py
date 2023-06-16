import os
import neopixel
import socketpool
import wifi
import board

from adafruit_httpserver import Server, Request, Response, GET, POST

ssid = "SINHA_NCBN"
password = "19061969"

print("Connecting to", ssid)
wifi.radio.connect(ssid, password)
print("Connected to", ssid)

pool = socketpool.SocketPool(wifi.radio)
server = Server(pool, "/static", debug=True)

pixel = neopixel.NeoPixel(board.NEOPIXEL, 1)


@server.route("/")
def base(request: Request):
    """
    Serve a default static plain text message.
    """
    return Response(request, "Hello from the CircuitPython HTTP Server!")

@server.route("/change-neopixel-color/<r>/<g>/<b>", GET)
def change_neopixel_color_handler_url_params(
    request: Request, r: str = "0", g: str = "0", b: str = "0"):
    """Changes the color of the built-in NeoPixel using URL params."""

    # e.g. /change-neopixel-color/255/0/0

    pixel.fill((int(r), int(g), int(b)))

    return Response(request, f"Changed NeoPixel to color ({r}, {g}, {b})")


server.serve_forever(str(wifi.radio.ipv4_address))
