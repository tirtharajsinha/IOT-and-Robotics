from machine import Pin
import utime

pir = Pin(16, Pin.IN, Pin.PULL_DOWN)
led = Pin(25, Pin.OUT)
n = 0

print("Starting up the PIR Module")
utime.sleep(1)
print("Ready")

while True:
    if pir.value() == 1:
        n += 1
        print("ALARM! Motion detected!", n)  # print the message.
        for i in range(20):
            led.toggle()
            utime.sleep(0.05)
        led.off()
    led.off()
