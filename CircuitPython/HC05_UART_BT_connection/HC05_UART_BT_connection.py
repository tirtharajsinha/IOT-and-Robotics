import board
import busio
import digitalio
import neopixel
import time

pixel_pin = board.NEOPIXEL
num_pixels = 1

print(f"RX : {board.RX} || TX : {board.TX}")

uart = busio.UART(board.TX, board.RX, baudrate=9600)


pixels = neopixel.NeoPixel(pixel_pin, num_pixels,
                           brightness=0.3, auto_write=False,pixel_order="RGB")

COLORS={
    "WHITE" : (255,255,255),
    "RED" : (255, 0, 0),
    "YELLOW" : (255, 150, 0),
    "GREEN" : (0, 255, 0),
    "CYAN" : (0, 255, 255),
    "BLUE" : (0, 0, 255),
    "PURPLE" : (180, 0, 255),
    "BLACK" : (0,0,0)
}

while True:
    data = uart.read(32)  # read up to 32 bytes
    # print(data)  # this is a bytearray type

    if data is not None:
        # convert bytearray to string
        data_string = ''.join([chr(b) for b in data])
        timestamp=f"UART on {time.localtime().tm_hour}.{time.localtime().tm_min}.{time.localtime().tm_sec} : "
        print(timestamp,data_string)
        
        if data_string.replace("neo:","") in COLORS.keys():
            pixels[0] = COLORS[data_string.replace("neo:","")]
            pixels.show()
        
        
