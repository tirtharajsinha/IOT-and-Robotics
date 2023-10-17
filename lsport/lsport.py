import subprocess as sp

from tabulate import tabulate

pipe = sp.Popen("ls -l /dev/serial/by-id/ | awk '{print $9 \" \" $11}'",shell=True, stdout=sp.PIPE, stderr=sp.PIPE)
res = pipe.communicate()


ports=res[0].decode(encoding='utf-8').strip()

data= []

if ports=="":
	ports=[]
else:
	ports=ports.split("\n")


for port in ports:
	port=port.split()
	data.append([port[0],port[1].replace("../..","/dev")])

print()
print (tabulate(data, headers=["Device Name", "Port"]))
print()
print(f"{len(ports)} Devices Found\n")

print("If you don't see your device here, Then run lsusb -t to find the driver is install or not.")


