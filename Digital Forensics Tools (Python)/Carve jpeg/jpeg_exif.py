import sys
import tags
import struct


class ExifParseError(Exception):
    def init(__self__):
        pass


def carve(f, start, end):

    f.seek(start)
    chunk = f.read(end-start+1)

    return chunk


def find_jfif(f, max_length=None):

    soi = []
    eoi = []
    arr = []
    chunk = f.read()
    for i in range(0, len(chunk)):
        if chunk[i] == 0xFF and chunk[i+1] == 0xD8:
            soi.append(i)
        if chunk[i] == 0xFF and chunk[i+1] == 0xD9:
            eoi.append(i+1)


    y = 0
    x = 0
    for y in range( 0, len(soi)):
        for x in range (0,len(eoi)):
            if max_length == None:
                if soi[y] < eoi[x]:
                    arr.append((soi[y], eoi[x] ))

            else:
                if (eoi[x] - soi[y]) < max_length and soi[y] < eoi[x]:

                    arr.append((soi[y], eoi[x]))

            x += 1
        y += 1

    return arr

def isExif(f):
    arr = []
    arr = find_jfif(f)
    for i in range(0, len(arr)-10):
        if carve(f,i,i+10) == b'Exif\x00\x00MM\x00\x2a':
            return i
        else:
            i=i+1
    return

def parse_exif(f):

    arr = []
    arr = find_jfif(f)
    len_results = 0
    results = []

    for i in range(0,len(arr)):
        #print(exif( f, (arr[i])[0] , (arr[i])[1] ))
        #if isExif( f, (arr[i])[0] , (arr[i])[1] ):
        chunk = carve(f, (arr[i])[0] , (arr[i])[1])

        #print('chunk',chunk[:400]) # READS THE FILE

        #appoOffesetSize = 0#int.from_bytes(chunk[4:6],'big') #16 TRASH
        #print(appoOffesetSize, 'appoOffesetSize')

        newEntry = chunk[4:4+2]  #b'\xff\xe1
        exif_bytes = chunk[4:]
        #print(exif_bytes[:20])
        #print('exif bytes')

        howBig = int.from_bytes(exif_bytes[2:4],'big')
        #print(howBig, 'howBig')
        Exiftag = exif_bytes[4:14] #'Exif'
        #print(Exiftag, 'Exiftag')

        # if (Exiftag == b'Exif\x00\x00MM\x00\x2a'):
        #     pass
        # else:
        #     print(False)#DEUBG checks if the jpeg has exif tag
        #     continue
        k=0
        #print(len(chunk), "lengthy ")
        for i in range(0, len(chunk)-8):
            #print("hit thhis point")
        #    if i < 100:
        #        print(carve(f,i,i+8))
            if (carve(f,i,i+8) == b'Exif\x00\x00MM\x00'):
                k= i + 2
            else:
                i=i+1
        bom_bytes = exif_bytes[k:] #carve tag, type format, component and data from here
        #print(bom_bytes[:400], 'bom')

        offset = exif_bytes[k+4:k+8]
        offsetInt = int.from_bytes(offset,'big')
        #print(offsetInt, 'offset')
        ifd_start = offsetInt#int.from_bytes(offset,'big')
        #print(ifd_start,'ifd_sss')

        #tagArr = []

        entriesCounter = int.from_bytes(bom_bytes[ifd_start:ifd_start+2],'big')
        #print(entriesCounter, 'DEBUG')


        i = 0
        while (i<2):
            for h in range(0, entriesCounter): #loops over number of entries in file

                tagNumber = int.from_bytes(bom_bytes[ifd_start+2:ifd_start+4],'big')
                formatCode = int.from_bytes(bom_bytes[ifd_start+4:ifd_start+6],'big')
                componentsNumb = int.from_bytes(bom_bytes[ifd_start+6:ifd_start+10],'big')
                data = int.from_bytes(bom_bytes[ifd_start+10:ifd_start+14],'big')
                value = bom_bytes[ data: data + componentsNumb ]



                #tagArr.append(tagNumber)

                #DEGUB
                #print(hex(tagNumber), 'tagNumber') #shows in hex #0x110 = \0x01 \0x10 in the file
                #print(formatCode, 'formatCode')
                #print(componentsNumb, 'componentsNumb')
                #print(data, 'data')
                #print(value, 'value')
                #DEBUG



                if formatCode == 2: #ascii
                    valueFormatted =  value[0:-1].decode()
                    ifd_start = ifd_start + 12 #increment idf_start position to next entrie

                elif formatCode == 3: #Resolution unit
                    #if componentsNumb == 1:
                        #data = int.from_bytes(bom_bytes[ifd_start+10:ifd_start+12],'big')

                    data = int.from_bytes(bom_bytes[ifd_start+10:ifd_start+12],'big')
                    #data = struct.unpack('>%dH' % componentsNumb,bom_bytes[ifd_start+10:ifd_start+12])
                    valueFormatted = data

                    ifd_start = ifd_start + 12 #increment idf_start position to next entrie

                elif formatCode == 4: #ExifIFDPointer
                    valueFormatted =  data
                    ifd_start = ifd_start + 12 #increment idf_start position to next entrie

                elif formatCode == 5: #XResolution YResolution

                    ( numerator, denominator )= struct.unpack('>LL',bom_bytes[data:data+ 8])

                    valueFormatted = '%s/%s' % (numerator,denominator) # e.g(72/1)
                    ifd_start = ifd_start + 12 #increment idf_start position to next entrie
                else:
                    pass

                for key,keyValue in tags.TAGS.items():
                    if key == tagNumber:
                        results.append((keyValue, valueFormatted))
                        results.sort(key=lambda tup: tup[0])
                        #sorted_by_second = sorted(data, key=lambda tup: tup[1]) You can use this to sort too


            ifd_start = 12 * entriesCounter + 10
            #print(entriesCounter, 'entries')
            offset = bom_bytes[ifd_start:ifd_start+4]
            offsetInt = int.from_bytes(offset,'big')
            #print(bom_bytes[offsetInt:offsetInt+2], 'agora')
            #print(offset, 'offset2')
            #print(offsetInt, 'offsetInt')
            if(offsetInt != 0):
                #print(ifd_start, 'ifd_start - bef')
                ifd_start = offsetInt
                #print(ifd_start, 'ifd_start - after')
                #print(bom_bytes[ifd_start:ifd_start+12], 'bomAft')
                #print(bom_bytes[ifd_start+10:ifd_start+12], 'debugg')

                len_results = len(results)
                #print('rrrrr',results)
                i=i+1
                continue
            else:
                len_results = len(results)
                break



    resultsPrint = {}
    for i in range (0, len_results):
        resultsPrint[results[i][0]] = results[i][1]

    #print(resultsPrint) #DEBUG
    #print(tagArr)


    return resultsPrint
