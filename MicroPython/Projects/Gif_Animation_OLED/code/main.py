import ssd1306
import machine
import utime as time
import framebuf
import base64
import math
import json

clockPin = 8
dataPin = 9
bus = 0
DISPLAY_RES = (128, 64)


FILENAME = "rickroll_82Frames.json"
NUM_OF_FRAMES = 82
VIDEO_RES = [64, 64]
FRAME_LATENCY = 0.1  # In milliseconds
INVERT = 1


i2c = machine.I2C(bus, sda=machine.Pin(dataPin), scl=machine.Pin(clockPin))
display = ssd1306.SSD1306_I2C(128, 64, i2c)

with open(FILENAME, "r") as f:
    movie = json.loads(f.read())
    f.close()


def custom_to_buff(data):
    global RES_SET
    width = data[0]
    height = data[1]
    fbuff = framebuf.FrameBuffer(data[2:], width, height, framebuf.MONO_HLSB)
    if not RES_SET:
        VIDEO_RES[0] = width
        VIDEO_RES[1] = height
        RES_SET = True
    return fbuff


def show_image(image, x=0, y=0):
    display.blit(image, x, y)
    display.show()


frames = []
RES_SET = False
for f in movie:
    frames.append(custom_to_buff(bytearray(base64.b64decode(f))))
NUM_OF_FRAMES = len(frames)

del movie


X, Y = 0, 0
if DISPLAY_RES[0] != VIDEO_RES[0]:
    X = (DISPLAY_RES[0] - VIDEO_RES[0]) // 2

if DISPLAY_RES[1] != VIDEO_RES[1]:
    Y = (DISPLAY_RES[1] - VIDEO_RES[1]) // 2


curFrame = 0

display.invert(INVERT)
prevtime = time.time_ns()
while True:
    if (time.time_ns() - prevtime) / 1e9 > FRAME_LATENCY:
        prevtime = time.time_ns()
        if curFrame == NUM_OF_FRAMES:
            curFrame = 0
        show_image(frames[curFrame], X, Y)
        curFrame += 1
