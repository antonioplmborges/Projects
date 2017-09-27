import sys
import struct
import uuid


def parse_mbr(mbr_bytes):

    entries = [0x1BE,0x1BE+16,0x1BE+16+16,0x1BE+16+16+16]
    arrEntries = []
    counter = 0
    for x in entries:
        partition = mbr_bytes[x:x+16]
        if int.from_bytes(partition, 'big') != 0 :
            number = counter
            type_mbr = partition[4]
            start = partition[8:12]
            end = partition[12:16]

            type_mbrInt = str(hex(type_mbr))
            startInt = struct.unpack('<I',start)[0]
            endInt = struct.unpack('<I',end)[0] + startInt - 1

            d = {"type": type_mbrInt, "end" : endInt,  "start" : startInt, "number": number }
            arrEntries.append(d)
            counter = counter + 1
    #print(arrEntries)
    return arrEntries


def parse_gpt(gpt_file, sector_size=512):
    chunk = gpt_file.read()
    mbr = chunk[:sector_size] #not needed

    header = chunk[sector_size:sector_size + sector_size]
    #print(chunk, 'header')
    #print(header[0x48],' 48') #starting index of entrues
    #print(header[0x50],' 50') #number of entries
    #print(header[0x54], ' 54') #size of single partition entry

    arrEntries = [] #array of dictionary of entries
    number = 0 #index of entrie
    sizeIndex = sector_size + sector_size #size offset for sectors

    for x in range(0,header[0x50]):

        entrie = chunk[sizeIndex : sizeIndex + sector_size] #carve entrie

        if int.from_bytes(entrie, 'big') == 0: #check if entrie is empty
            break
        else:
            index = 0
            while index < sector_size:  #check sectors of the entry
                entrieSec = entrie[index:index+128]

                if int.from_bytes(entrieSec, 'big') == 0: #check sectors of the entry is not empty
                    break
                else:
                    type_guid = entrieSec[0:16]
                    start = entrieSec[0x20:0x20+8]
                    end = entrieSec[0x20+8:0x20+16]
                    startInt = int.from_bytes(start,'little')
                    endInt = int.from_bytes(end,'little')
                    name = entrieSec[0x38:0x38+72]
                    nameStr = name.decode('UTF-16-LE','ignore').split('\x00')
                    type_gpt = uuid.UUID(bytes_le = type_guid)

                    d = {"start" : startInt, "end" : endInt, "number": number, "name": nameStr[0], "type": type_gpt }
                    #print(d)
                    arrEntries.append(d)
                    number = number + 1
                    index = index + header[0x54]

        sizeIndex = sector_size + sizeIndex


    #print(arrEntries)

    return arrEntries
