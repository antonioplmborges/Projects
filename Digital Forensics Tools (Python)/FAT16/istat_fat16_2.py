import struct


def as_unsigned(bs, endian='<'):
    unsigned_format = {1: 'B', 2: 'H', 4: 'L', 8: 'Q'}
    if len(bs) <= 0 or len(bs) > 8:
        raise ValueError()
    fill = '\x00'
    while len(bs) not in unsigned_format:
        bs = bs + fill
    result = struct.unpack(endian + unsigned_format[len(bs)], bs)[0]
    return result


def decode_fat_time(time_bytes, tenths=0, tz='EDT'):
    v = as_unsigned(time_bytes)
    second = int(int(0x1F & v) * 2)
    if tenths > 100:
        second += 1
    minute = (0x7E0 & v) >> 5
    hour = (0xF800 & v) >> 11
    return '{:02}:{:02}:{:02} ({})'.format(hour, minute, second, tz)


def decode_fat_day(date_bytes):
    v = as_unsigned(date_bytes)
    day = 0x1F & v
    month = (0x1E0 & v) >> 5
    year = ((0xFE00 & v) >> 9) + 1980
    return '{}-{:02}-{:02}'.format(year, month, day)

def is_allocated(data):
    byte = hex(data)
    if byte == 0xe5 or 0x00:
        return 'Not Allocated'
    else:
        return 'Allocated'

def get_filename(dirent):
    byte = dirent[8:11]
    extension = dirent[8:11].decode('ascii', 'ignore').strip()
    filename = dirent[:8].decode('ascii', 'ignore').strip()
    #print(filename)
    if byte == 0x08:     #base is lower
        filename = filename.lower()
    elif byte == 0x10:    #extension lower
        extension = extension.lower()
    elif byte == 0x18:      #both lower
        extension = extension.lower()
        filename = filename.lower()

    if extension != '' :
        return filename + '.' + extension
    else:
        return filename

def get_file_attribute(data):
    byte = data
    if byte == 0x01:
        return 'Read-only'
    elif byte == 0x02:
        return 'Hidden file'
    elif byte == 0x04:
        return 'System file'
    elif byte == 0x08:
        return 'Volume label'
    elif byte == 0x0f:
        return 'Long file name'
    elif byte == 0x10:
        return 'Directory'
    elif byte == 0x20:
        return 'File, Archive'

def as_le_unsigned(bytes):
    table = {1: 'B', 2: 'H', 4: 'L', 8:'Q'}
    return struct.unpack('<' + table[len(bytes)], bytes)[0]

def number_sector_in_reserved_area(bytes):
    return as_le_unsigned(bytes[0xE:0xE+2])

def get_number_of_fats(bytes):
    return as_le_unsigned(bytes[0x10:0x10+1])

def number_sector_in_fat(bytes):
    return as_le_unsigned(bytes[0x16:0x16+2])

 #copied paste from fsstat_fat16



def get_reserved_sector_count(b):
    return as_le_unsigned(b[0xE:0xE+2])

def get_fat_count(b):
    return as_le_unsigned(b[0x10:0x11])

def get_sector_in_fat(b):
    return as_le_unsigned(b[0x16:0x16+2])

def get_root_dir_sector(b):
    as_le_unsigned(b[0xD:0xD+1])
    entries = as_le_unsigned(b[0x11:0x11+2])
    sec_size = as_le_unsigned(b[0xB:0xB+2])
    return entries*32 // sec_size

def get_sector_in_cluster(b):
    return as_le_unsigned(b[0xD:0xD+1])

def get_sector_size(b):
    return as_le_unsigned(b[0xB:0xB+2])

def get_cluster_number(num, b):
    result = []
    offset = 4
    start = num
    end = start+1
    prev = None

    while offset < len(b)-2:
        if as_le_unsigned(b[offset:offset+2]) >= as_le_unsigned(b'\xf8\xff'):
            result.append((start, end, 'EOF'))
            start = end
            end = start+1
            prev = None
        elif as_le_unsigned(b[offset:offset+2]) == 0:
            start = end
            end = start+1
            prev = None
        elif prev == None:
            prev = as_le_unsigned(b[offset:offset+2])
            end+=1
        elif as_le_unsigned(b[offset:offset+2]) == prev+1:
            prev = as_le_unsigned(b[offset:offset+2])
            end+=1
        else:
            result.append((start, end, as_le_unsigned(b[offset:offset+2])))
            start = end
            end = start+1
            prev = None
        offset+=2

    return result



#end of copy

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

def istat_fat16(f, address, sector_size=512, offset=0):
    chunk = f.read()
    count = 0
    print(chunk[0x36:0x36 +8], 'kgjxggxkjxxxxxxxxx')
    while chunk[0x36:0x36 + 8].decode("ascii").strip() != "FAT16":
        count+=1
        chunk= chunk[sector_size:]
    print(count)
    root_bytes = get_root_directory_area(chunk)
    max_root = get_max_root_directory_entries(chunk)
    if address > max_root:
        start = get_cluster_size(chunk)*get_sector_size(chunk)
        #inode_start = start+(address-515)*32
        lower_bound_root_sector = as_unsigned(chunk[0x16:0x16 + 2])*as_unsigned(chunk[16:17])+1
        inode_start = lower_bound_root_sector*sector_size+(32*(address-3))
        print('start:'+str(start))
        print('inode start:'+str(inode_start))
        entry = chunk[inode_start:inode_start+32]
    else:
        offset = 32*(address-3)
        entry = root_bytes[offset:offset+32]

    print(entry)
    result = []
    result.append('Directory Entry: '+str(address))
    result.append(is_allocated(entry[0]))
    #result.append('File Attributes: '+ get_file_attribute(entry[0xB]))
    #print(str(get_first_cluster(data)))

    reserved_sectors = get_reserved_sector_count(chunk)
    fats = get_fat_count(chunk)
    sector_in_fat = get_sector_in_fat(chunk)
    i = 0
    while i < fats:
        #result.append('* FAT {}: {} - {}'.format(i, reserved_sectors, reserved_sectors+sector_in_fat-1))
        reserved_sectors+= sector_in_fat
        i+=1

    x = get_reserved_sector_count(chunk)*get_sector_size(chunk)*(i-1)
    l = get_sector_size(chunk)*as_le_unsigned(chunk[0x16:0x18])
    b = chunk[x:x+l]

    root_dir_sector = get_root_dir_sector(chunk)
    reserved_sectors+= root_dir_sector
    cluster_start = reserved_sectors
    cluster_list = get_cluster_number(2, b)
    first_cluster = get_first_cluster(entry)
    startc = 0
    nums = 0
    for e in cluster_list:
        print(str(e[0]))
        if(first_cluster == e[0]):
            start = e[0]
            startc = (e[0]-2)*get_sector_in_cluster(chunk)+cluster_start
            end = e[1]
            numc = end-start
            nums = numc*get_sector_in_cluster(chunk)
            r = e[2]
            if type(r) is int:
                r = (r-2)*get_sector_in_cluster(chunk)+cluster_start
            #print(str(startc))
            #print(str(startc+nums-1))


    #print(str(startc))
    #print(str(startc+nums-1))
    if entry[0xB] & 0x10: #need to get size differently
        size = ((startc+nums-1)-startc+1)* 512
        print(size, "sizejdljfajs")
    else:
        size = as_unsigned(entry[28:])
        print(size, 'sizexxxxx')
    result.append('File Attributes: '+str(get_file_attribute(entry[11])))
    result.append('Size: ' + str(size))
    result.append('Name: ' + get_filename(entry))
    result.append('')
    result.append('Directory Entry Times:')
    result.append('Written:\t' + decode_fat_day(entry[24:26]) + ' ' + decode_fat_time(entry[22:24]))
    result.append('Accessed:\t' + decode_fat_day(entry[18:20]) + ' ' + decode_fat_time(bytes([0])))
    result.append('Created:\t' + decode_fat_day(entry[16:18]) + ' ' + decode_fat_time(entry[14:16],entry[13] ))
    result.append('')
    result.append('Sectors:')
    #if (startc+nums) > size:

    sector_list = list(range(startc, (startc+nums)))
    #print(sector_list)
    length = len(sector_list)//8
    #print(str(length))
    if length == 0:
        if (sector_list[len(sector_list) - 1] > size):
            sector_list[len(sector_list)-1] = 0
        print(sector_list[end-8:],"sector_list")
        result.append(' '.join(str(x) for x in sector_list))
    else:
        start = 0
        end = start+8
        for k in range(0, length):
            if (sector_list[len(sector_list) - 1] > size):
                sector_list[len(sector_list)-1] = 0
            print(sector_list[end-8:],"sector_list")
            result.append(' '.join(str(x) for x in sector_list[start:end]))
            start = end
            end = start+8
        mod = len(sector_list)%8
        if mod !=0:
            if (sector_list[len(sector_list) - 1] > size):
                sector_list[len(sector_list)-1] = 0
            print(sector_list[end-8:],"sector_list")
            result.append(' '.join(str(x) for x in sector_list[end-8:]))



    return result




if __name__ == '__main__':
    # values below are from the directory entry in adams.dd that corresponds to the
    # creation date/time of the `IMAGES` directory in the root directory, at
    # metadata address 5; it starts at offset 0x5240 from the start of the image
    #print(decode_fat_day(bytes.fromhex('E138')), decode_fat_time(bytes.fromhex('C479'), 0))
    with open('spiff.dd', 'rb') as f:
        print(istat_fat16(f, 679, 512, 2))
        #print(istat_fat16(f, 5))
