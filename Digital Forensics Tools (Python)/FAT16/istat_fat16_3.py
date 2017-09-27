import struct
import math


def as_unsigned(bs, endian='<'):
    unsigned_format = {1: 'B', 2: 'H', 4: 'L', 8: 'Q'}
    if len(bs) <= 0 or len(bs) > 8:
        raise ValueError()
    fill = '\x00'
    while len(bs) not in unsigned_format:
        bs = bs + fill
    result = struct.unpack(endian + unsigned_format[len(bs)], bs)[0]
    return result

def is_allocated(data):
    if hex(data) == 0xe5 or 0x00:
        return 'Not Allocated'
    else:
        return 'Allocated'

def decode_fat_day(date_bytes):
    v = as_unsigned(date_bytes)
    day = 0x1F & v
    month = (0x1E0 & v) >> 5
    year = ((0xFE00 & v) >> 9) + 1980
    return '{}-{:02}-{:02}'.format(year, month, day)

def decode_fat_time(time_bytes, tenths=0, tz='EDT'):
    v = as_unsigned(time_bytes)
    second = int(int(0x1F & v) * 2)
    if tenths > 100:
        second += 1
    minute = (0x7E0 & v) >> 5
    hour = (0xF800 & v) >> 11
    return '{:02}:{:02}:{:02} ({})'.format(hour, minute, second, tz)

def get_filename(dirent):
    reserved = dirent[12:13]
    reserved_bin = as_unsigned(reserved[0:])
    bit_4 = (reserved_bin & 0b00001000)
    bit_3 = (reserved_bin >> 3)
    byte = dirent[8:11]
    extension = dirent[8:11].decode('ascii', 'ignore').strip()
    filename = dirent[:8].decode('ascii', 'ignore').strip()
    #print(filename)
    if bit_4 != 0:     #base is lower
        filename = filename.lower()
    if bit_3 != 0:    #extension lower
        extension = extension.lower()

    if extension != '' :
        return filename + '.' + extension
    else:
        return filename

def get_file_attribute(data):
    attributes = ''
    byte = data
    if byte & 0x10:
        attributes+= 'Directory'
    elif byte & 0x08:
        attributes+= 'Volume'
    else:
        attributes+= 'File'

    if byte & 0x01:
        attributes+= ', Read Only'
    if byte & 0x02:
        attributes+= ', Hidden'
    if byte & 0x04:
        attributes+= ', System'
    if byte & 0x20:
        attributes+= ', Archive'
    return attributes

def as_le_unsigned(bytes):
    table = {1: 'B', 2: 'H', 4: 'L', 8:'Q'}
    return struct.unpack('<' + table[len(bytes)], bytes)[0]

def number_sector_in_reserved_area(bytes):
    return as_le_unsigned(bytes[0xE:0xE+2])

def get_number_of_fats(bytes):
    return as_le_unsigned(bytes[0x10:0x10+1])


def get_reserved_sector_count(data):
    return as_le_unsigned(data[0xE:0xE+2])

def get_fat_count(data):
    return as_le_unsigned(data[0x10:0x11])

def get_sector_in_fat(data):
    return as_le_unsigned(data[0x16:0x16+2])

def get_root_dir_sector(data):
    as_le_unsigned(data[0xD:0xD+1])
    entries = as_le_unsigned(data[0x11:0x11+2])
    sec_size = as_le_unsigned(data[0xB:0xB+2])
    return entries*32 // sec_size

def get_sector_in_cluster(data):
    return as_le_unsigned(data[0xD:0xD+1])

def get_sector_size(data):
    return as_le_unsigned(data[0xB:0xB+2])

def get_cluster_number(num, data):
    result = []
    offs = 4
    start = num
    end = start+1
    bef = None

    while offs < len(data)-2:
        if as_le_unsigned(data[offs:offs+2]) >= as_le_unsigned(b'\xf8\xff'):
            result.append((start, end, 'EOF'))
            start = end
            end = start+1
            bef = None
        elif as_le_unsigned(data[offs:offs+2]) == 0:
            start = end
            end = start+1
            bef = None
        elif bef == None:
            bef = as_le_unsigned(data[offs:offs+2])
            end+=1
        elif as_le_unsigned(data[offs:offs+2]) == bef+1:
            bef = as_le_unsigned(data[offs:offs+2])
            end+=1
        else:
            result.append((start, end, as_le_unsigned(data[offs:offs+2])))
            start = end
            end = start+1
            bef = None
        offs+=2

    return result


def get_first_cluster(bytes):
    return as_le_unsigned(bytes[26:28])

def get_max_root_directory_entries(fs_bytes):
    return as_le_unsigned(fs_bytes[0x11:0x11+2])

def get_cluster_size(fs_bytes):
    return sector_per_cluster(fs_bytes) * get_sector_size(fs_bytes)

def get_sector_size(fs_bytes):
    return as_le_unsigned(fs_bytes[0xB:0xB+2])


def get_reserved_area_size(fs_bytes):
    return as_le_unsigned(fs_bytes[14:16]) * get_sector_size(fs_bytes)

def get_fat_size(fs_bytes):
    return as_le_unsigned(fs_bytes[22:24]) * get_sector_size(fs_bytes)

def sector_per_cluster(fs_bytes):
    return as_le_unsigned(fs_bytes[0xD:0xD+1])


def get_root_directory_area(fs_bytes):
    start = get_reserved_area_size(fs_bytes) + get_number_of_fats(fs_bytes) * get_fat_size(fs_bytes)
    length = get_max_root_directory_entries(fs_bytes) * 32  # 32 bytes / entry
    return fs_bytes[start:start + length]

def istat_fat16(f, address, sector_size=512, offs=0):

    chunk = f.read()

    while chunk[0x36:0x36 + 8].decode("ascii").strip() != "FAT16":
        chunk = chunk[sector_size:]

    root_bytes = get_root_directory_area(chunk)
    max_root = get_max_root_directory_entries(chunk)
    if address > max_root:
        start = get_cluster_size(chunk)*get_sector_size(chunk)
        lower_bound_root_sector = as_unsigned(chunk[0x16:0x16 + 2])*as_unsigned(chunk[16:17])+1
        inode_start = lower_bound_root_sector*sector_size+(32*(address-3))
        entry = chunk[inode_start:inode_start+32]
    else:
        offs = 32*(address-3)
        entry = root_bytes[offs:offs+32]




    reserved_sectors = get_reserved_sector_count(chunk)
    fats = get_fat_count(chunk)
    sector_in_fat = get_sector_in_fat(chunk)

    i = 0
    while i < fats:
        reserved_sectors+= sector_in_fat
        i+=1

    b = chunk[ get_reserved_sector_count(chunk)*get_sector_size(chunk)*(i-1) : get_reserved_sector_count(chunk)*get_sector_size(chunk)*(i-1) + get_sector_size(chunk)*as_le_unsigned(chunk[0x16:0x18])]

    root_dir_sector = get_root_dir_sector(chunk)
    reserved_sectors+= root_dir_sector
    cluster_start = reserved_sectors
    cluster_list = get_cluster_number(2, b)
    first_cluster = get_first_cluster(entry)
    startc = 0
    nums = 0
    for item in cluster_list:
        if(first_cluster == item[0]):
            start_cluster = item[0]
            startc = (item[0]-2)*get_sector_in_cluster(chunk)+cluster_start
            end_cluster = item[1]
            numc = end_cluster - start_cluster
            nums = numc*get_sector_in_cluster(chunk)
            x = item[2]
            if type(x) is int:
                x = (x-2)*get_sector_in_cluster(chunk)+cluster_start

    result = []
    result.append('Directory Entry: '+ str(address))
    result.append(is_allocated(entry[0]))

    if entry[0xB] & 0x10:
        size = ((startc+nums-1)-startc+1)* 512
    else:
        size = as_unsigned(entry[28:])
    result.append('File Attributes: '+str(get_file_attribute(entry[11])))
    result.append('Size: ' + str(size))
    result.append('Name: ' + get_filename(entry))
    result.append( '' )
    result.append('Directory Entry Times:')
    result.append('Written:\t' + decode_fat_day(entry[24:26]) + ' ' + decode_fat_time(entry[22:24]))
    result.append('Accessed:\t' + decode_fat_day(entry[18:20]) + ' ' + decode_fat_time(bytes([0])))
    result.append('Created:\t' + decode_fat_day(entry[16:18]) + ' ' + decode_fat_time(entry[14:16],entry[13] ))
    result.append( '' )
    result.append('Sectors:')
    if startc+nums > size:
        sectors_used = math.ceil(size/512)
        sector_list = list(range(startc, startc+sectors_used))
        sector_list.append(0)
    else:
        sector_list = list(range(startc, (startc+nums)))
    #print(sector_list)
    length = len(sector_list)//8
    #print(str(length))
    if length == 0:
        result.append(' '.join(str(x) for x in sector_list))
    else:
        start = 0
        end = start+8
        for k in range(0, length):
            result.append(' '.join(str(x) for x in sector_list[start:end]))
            start = end
            end = start+8
        mod = len(sector_list)%8
        if mod !=0:
            result.append(' '.join(str(x) for x in sector_list[end-8:]))


    return result

if __name__ == '__main__':
    # values below are from the directory entry in adams.dd that corresponds to the
    # creation date/time of the `IMAGES` directory in the root directory, at
    # metadata address 5; it starts at offs 0x5240 from the start of the image
    #print(decode_fat_day(bytes.fromhex('E138')), decode_fat_time(bytes.fromhex('C479'), 0))
    with open('spiff.dd', 'rb') as f:
        print(istat_fat16(f, 679, 512, 2))
        #print(istat_fat16(f, 5))
