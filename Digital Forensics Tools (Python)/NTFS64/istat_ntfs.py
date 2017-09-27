import datetime
import struct
import math

def as_signed_le(bs):
    signed_format = {1: 'b', 2: 'h', 4: 'l', 8: 'q'}
    if len(bs) <= 0 or len(bs) > 8:
        raise ValueError()

    fill = b'\x00'
    if ((bs[-1] & 0x80) >> 7) == 1:
        fill = b'\xFF'

    while len(bs) not in signed_format:
        bs = bs + fill
    result = struct.unpack('<' + signed_format[len(bs)], bs)[0]
    return result

def getAttributes(item):
    dict = {16:('$STANDARD_INFORMATION',
            '(16-0)'), 48:('$FILE_NAME',
            '(48-3)'), 128:('$DATA', '(128-2)')
            }
    if item in dict:
        return dict[item]


def getAttributesFlag(item):
    dict = {0x0001: 'Read Only', 0x0002: 'Hidden',
            0x0004: 'System', 0x0020: 'Archive',
            0x0040: 'Device', 0x0080: '#Normal',
            0x0100: 'str_temporary', 0x0200: 'Sparse file',
            0x0400: 'Reparse file', 0x0800: 'Compressed',
            0x1000:'Offline',0x2000: 'Content is not being indexed for faster searches',
            0x4000: 'Encrypted'}
    return dict[as_signed_le(item)]

def getSecPerCluster(f, sector_size=512):
    boot_partition = f[:sector_size]
    return as_signed_le(boot_partition[13:14])

def getSectorSize(f, sector_size=512):
    boot_partition = f[:sector_size]
    return as_signed_le(boot_partition[11:13])

def getClusterSize(f, sector_size=512):
    return getSectorSize(f, sector_size)*getSecPerCluster(f, sector_size)

def getMFT(f, sector_size=512):
    boot_partition = f[:sector_size]
    return as_signed_le(boot_partition[48:56])*getClusterSize(f, sector_size)

def getMFTSize(f, sector_size=512):
    boot_partition = f[:sector_size]
    val = as_signed_le(boot_partition[64:65])
    if val >= 0:
        return val*getClusterSize(f, sector_size)
    else:
        return int(math.pow(2, abs(val)))

def getEntry(f, address, sector_size):
    entries = f[getMFT(f,sector_size)+address*getMFTSize(f,sector_size):
    getMFT(f)+address*getMFTSize(f,sector_size)+getMFTSize(f,sector_size)]
    return entries


def dataParser(f, attribute):
    lst_offset = as_signed_le(attribute[32:34])
    header_run = attribute[lst_offset]
    mask = 0x0f
    cluste_bef = 0
    result = []
    while header_run != 0:
        str_tempRunOffset = as_signed_le(bytes([header_run>>4]))
        str_tempRunLength = as_signed_le(bytes([header_run&mask]))
        lst_offset+=1
        cluster_length = as_signed_le(attribute[lst_offset: lst_offset+str_tempRunLength])
        cluster_off = as_signed_le(attribute[lst_offset+str_tempRunLength:
                                    lst_offset+str_tempRunLength+str_tempRunOffset])
        current_cluster = cluste_bef+cluster_off
        for x in range(0, cluster_length):
            result.append(current_cluster+x)
        cluste_bef = current_cluster
        lst_offset += str_tempRunLength+str_tempRunOffset
        header_run = attribute[lst_offset]
    str_temp = ''
    count = 0
    str_result = []
    for y in range(0,len(result)):
        if count == 8:
            str_result.append(str_temp)
            str_temp = str(result[y])+' '
            count = 1
        else:
            str_temp += str(result[y])+' '
            count +=1
    str_result.append(str_temp)
    return str_result


def istat_ntfs(f, address, sector_size=512, offset=0):
    result = []
    f.seek(offset)
    chunk = f.read()
    entries = getEntry(chunk, address,sector_size)
    result.append('MFT Entry Header Values:')
    result.append('Entry: {}        Sequence: {}'.format(address, as_signed_le(entries[16:18])))
    result.append('$LogFile Sequence Number: {}'.format(as_signed_le(entries[8:16])))
    result.append('Allocated File')
    result.append('Links: {}'.format(as_signed_le(entries[18:20])))
    result.append('')
    attribute_off = as_signed_le(entries[20:22])
    attribute_lst = []
    while(1):
        header_attr = entries[attribute_off: attribute_off+16]
        if header_attr[:4] == b'\xff\xff\xff\xff':
            break
        size_attr = as_signed_le(header_attr[4:8])
        attribute_id = getAttributes(as_signed_le(header_attr[0:4]))
        if attribute_id != None:
            nameLength = as_signed_le(header_attr[9:10])
            if as_signed_le(header_attr[8:9]) == 0:
                non_resident = 'Resident'
            else:
                non_resident = 'Non-Resident'
            b = entries[attribute_off: attribute_off+size_attr]
            if non_resident == 'Resident':
                contentSize = as_signed_le(b[16:20])
            else:
                contentSize = as_signed_le(b[48:56])
            if non_resident == 'Resident':
                attributeStr = 'Type: {} {}   Name: N/A   {}   size: {}'.format(attribute_id[0],
                attribute_id[1], non_resident, contentSize)
            else:
                attributeStr = 'Type: {} {}   Name: N/A   {}   size: {}  init_size: {}'.format(attribute_id[0],
                attribute_id[1], non_resident, contentSize, as_signed_le(b[56:64]))
            attribute_lst.append(attributeStr)
            contentOffset = as_signed_le(b[20:22])
            content = b[contentOffset: contentOffset+contentSize]
            if attribute_id[0] == '$STANDARD_INFORMATION':
                result.append('{} Attribute Values:'.format(attribute_id[0]))
                result.append('Flags: {}'.format(getAttributesFlag(content[32:36])))
                result.append('Owner ID: {}'.format(0))
                time_created = into_localtime_string(as_signed_le(content[0:8]))
                result.append('Created:\t{}'.format(time_created))
                time_modified = into_localtime_string(as_signed_le(content[8:16]))
                result.append('File Modified:\t{}'.format(time_modified))
                mfttime_modified = into_localtime_string(as_signed_le(content[16:24]))
                result.append('MFT Modified:\t{}'.format(mfttime_modified))
                accessedTime = into_localtime_string(as_signed_le(content[24:32]))
                result.append('Accessed:\t{}\n'.format(accessedTime))
                result.append('')
            elif attribute_id[0] == '$FILE_NAME':
                        result.append('{} Attribute Values:'.format(attribute_id[0]))
                        result.append('Flags: {}'.format(getAttributesFlag(content[56:60])))
                        result.append('Name: {}'.format(content[66:].decode('utf-16le').strip()))
                        seqNumber = as_signed_le(content[6:8])
                        result.append('Parent MFT Entry: {} \tSequence: {}'.format(as_signed_le(content[:6]), seqNumber))
                        result.append('Allocated Size: {}   \tActual Size: {}'.format(as_signed_le(content[40:48]), as_signed_le(content[48:56])))
                        time_created = into_localtime_string(as_signed_le(content[8:16]))
                        result.append('Created:\t{}'.format(time_created))
                        time_modified = into_localtime_string(as_signed_le(content[16:24]))
                        result.append('File Modified:\t{}'.format(time_modified))
                        mfttime_modified = into_localtime_string(as_signed_le(content[24:32]))
                        result.append('MFT Modified:\t{}'.format(mfttime_modified))
                        accessedTime = into_localtime_string(as_signed_le(content[32:40]))
                        result.append('Accessed:\t{}'.format(accessedTime))
                        result.append('')
            else:
                if non_resident == 'Non-Resident':
                    attribute_lst.extend(dataParser(chunk, content))
        attribute_off += size_attr
    result.append('Attributes:')
    result.extend(attribute_lst)
    return result

def into_localtime_string(windows_timestamp):
    """
    Convert a windows timestamp into istat-compatible output.

    Assumes your local host is in the EDT timezone.

    :param windows_timestamp: the struct.decoded 8-byte windows timestamp
    :return: an istat-compatible string representation of this time in EDT
    """
    dt = datetime.datetime.fromtimestamp((windows_timestamp - 116444736000000000) / 10000000)
    hms = dt.strftime('%Y-%m-%d %H:%M:%S')
    fraction = windows_timestamp % 10000000
    return hms + '.' + str(fraction) + '00 (EDT)'


if __name__ == '__main__':
    import argparse

    parser = argparse.ArgumentParser(description='Display details of a meta-data structure (i.e. inode).')
    parser.add_argument('-o', type=int, default=0, metavar='imgoffset',
                        help='The offset of the file system in the image (in sectors)')
    parser.add_argument('-b', type=int, default=512, metavar='dev_sector_size',
                        help='The size (in bytes) of the device sectors')
    parser.add_argument('image', help='Path to an NTFS raw (dd) image')
    parser.add_argument('address', type=int, help='Meta-data number to display stats on')
    args = parser.parse_args()
    with open(args.image, 'rb') as f:
        result = istat_ntfs(f, args.address, args.b, args.o)
        for line in result:
            print(line.strip())
            pass
