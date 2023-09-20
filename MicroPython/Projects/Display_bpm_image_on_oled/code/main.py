import ssd1306
import machine
import utime as time
import framebuf
import math
import json
from bmp_reader import *

clockPin = 17
dataPin = 16
bus = 0
DISPLAY_RES = (128, 64)


i2c = machine.I2C(bus, sda=machine.Pin(dataPin), scl=machine.Pin(clockPin))
display = ssd1306.SSD1306_I2C(128, 64, i2c)

def convert_bmp_to_bytearray(filename):
  with open(filename, "rb") as f:
    contents = f.read()
  header_size = 14
  byte_array = contents[header_size:]
  return bytearray(byte_array)


barr=convert_bmp_to_bytearray("Ui.bmp")
fbuff = framebuf.FrameBuffer(barr, 128, 64, framebuf.MONO_HLSB)


display.invert(0)
display.rotate(False)
display.fill(0)
display.show()
display.blit(fbuff, 0, 0,0)
display.show()

print(fbuff)