import os
from tabulate import tabulate

res = os.popen("ls -l /dev/serial/by-id/ | awk '{print $9 \" \" $11}'",'r',1)

ports=res.read().strip()

data= []
ports=ports.split("\n")
for port in ports:
	port=port.split()
	data.append([port[0],port[1].replace("../..","/dev")])

print()
print (tabulate(data, headers=["Device Name", "Port"]))
print()
print(f"{len(ports)} Devices Found\n")

