# Raspberry Pi Pico: http://educ8s.tv/part/RaspberryPiPico
# OLED DISPLAY: https://educ8s.tv/part/OLED096

import board, busio, displayio, time
from digitalio import DigitalInOut, Direction, Pull
import adafruit_displayio_ssd1306
import adafruit_imageload


IMAGE_FILE = "pinkpanther_12_frames.bmp"
SPRITE_SIZE = (64, 64)
FRAMES = 0
icon_grid=[]
currentFrames=0

MOVIE = [
    {"IMAGE_FILE": "pinkpanther_12_frames.bmp", "SPRITE_SIZE": (64, 64), "FRAMES": 12, "invert":True},
    {"IMAGE_FILE": "youtube.bmp", "SPRITE_SIZE": (64, 64), "FRAMES": 28, "invert":True},
    {"IMAGE_FILE": "alarm.bmp", "SPRITE_SIZE": (64, 64), "FRAMES": 28, "invert":True},
    {"IMAGE_FILE": "storm_28.bmp", "SPRITE_SIZE": (64, 64), "FRAMES": 28, "invert":True}
]

btn = DigitalInOut(board.IO0)
btn.direction = Direction.INPUT
btn.pull = Pull.UP





displayio.release_displays()


sda, scl = board.IO8, board.IO9
i2c = busio.I2C(scl, sda)

display_bus = displayio.I2CDisplay(i2c, device_address=0x3C)
display = adafruit_displayio_ssd1306.SSD1306(
    display_bus, width=128, height=64, rotation=0
)


group = displayio.Group()


def showFrames(frame, invert=True):
    global group
    global icon_grid
    global FRAMES
    #  load the spritesheet

    SPRITE_SIZE = frame["SPRITE_SIZE"]
    FRAMES=frame["FRAMES"]
    IMAGE_FILE=frame["IMAGE_FILE"]

    icon_bit, icon_pal = adafruit_imageload.load(
        IMAGE_FILE, bitmap=displayio.Bitmap, palette=displayio.Palette
    )
    if frame["invert"]:
        temp = icon_pal[0]
        icon_pal[0] = icon_pal[1]
        icon_pal[1] = temp

    icon_grid = displayio.TileGrid(
        icon_bit,
        pixel_shader=icon_pal,
        width=1,
        height=1,
        tile_height=SPRITE_SIZE[0],
        tile_width=SPRITE_SIZE[1],
        default_tile=0,
        x=32,
        y=0,
    )
    

    group.append(icon_grid)


showFrames(MOVIE[currentFrames])

display.show(group)

timer = 0
pointer = 0
btntimer=0

while True:
  if not btn.value and (btntimer + 2) < time.monotonic():
        print("BTN is down")
        group.pop()
        currentFrames+=1
        currentFrames=currentFrames%len(MOVIE)
        pointer = 0
        showFrames(MOVIE[currentFrames])
        print(currentFrames)
        
        btntimer = time.monotonic()
        
        
  if (timer + 0.1) < time.monotonic():
    icon_grid[0] = pointer
    pointer += 1
    timer = time.monotonic()
    if pointer > FRAMES-1:
      pointer = 0
