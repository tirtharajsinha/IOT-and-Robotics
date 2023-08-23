import os,gc
import esp


class boardDetails:
    stat = os.statvfs("/")
    size = stat[1] * stat[2]
    free = stat[0] * stat[3]
    used = size - free
    flashsize=esp.flash_size();

    KB = 1024
    MB = 1024 * 1024

    FlashMB=round(flashsize/MB,2)
    FlashKB=round(flashsize/KB,2)

    AvailableMB=round(size/MB,2)
    AvailableKB=round(size/KB,2)
    
    UsedMB=round(used/MB,2)
    UsedKB=round(used/KB,2)

    FreeMB=round(free/MB,2)
    FreeKB=round(free/KB,2)

    ramSize = (gc.mem_alloc() + gc.mem_free())/KB

    Board = os.uname()
    BoardName=Board[-1]
    
    
    DispFlash=f"{FlashMB} MB"
    DispAvail=f"{AvailableMB} MB"
    DispUsed=f"{UsedMB} MB"
    DispFree=f"{FreeMB} MB"
    
    
    if FlashMB<1:
        DispFlash=f"{FlashKB} KB"
    if AvailableMB<1:
        DispAvail=f"{AvailableKB} KB"
    if UsedMB<1:
        DispUsed=f"{UsedKB} KB"
    if FreeMB<1:
        DispFree=f"{FreeKB} KB"
    
#     print(DispFlash,DispAvail,DispUsed,DispFree)
# 
#     print("Size : {:,} bytes, {:,} KB, {} MB".format(size, FlashKB, FlashMB))
#     print("Used : {:,} bytes, {:,} KB, {} MB".format(used, UsedKB, UsedMB))
#     print("Free : {:,} bytes, {:,} KB, {} MB".format(free, FreeKB, FreeMB))
#     print("Ram Size : {} KB".format(ramSize))
# 
#     print("{} board with {} MB Flash".format(BoardName, size // MB))
