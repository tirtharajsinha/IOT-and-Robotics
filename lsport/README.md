## Python dependency
```
pip install tabulate
```

## Setup for alias

### In the end of `~/.bashrc` add 
```
alias lsserial="ls -l /sys/class/tty/*/device/driver | grep -v \"platform/drivers/serial8250\" | awk '{print \$9}' | awk -F'/' '{print \"/dev/\" \$5}'"
alias lsport="python3 /home/tirtha/.config/lsport/lsport.py"
alias watch='watch '
```

### copy lsport directory to `~/.config`
```
cp -r lsport/ ~/.config
source .bashrc
```

### Run with  
```
lsport
lsserial
```

### Monitor with 
```
watch lsport
```

## If you don't see your device here, Then run `lsusb` and `lsusb -t` to find the corresponding driver is install or not.


