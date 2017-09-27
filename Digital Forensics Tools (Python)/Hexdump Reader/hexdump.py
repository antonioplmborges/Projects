import sys
#import binascii

def dump_file(filename):
    """Write a file to standard out, with per-line character counts. Treats the file as a text file.

    :param filename: the path to a file
    """
    with open(filename, 'rb') as f:
        char_count = 0
        for line in f:  # when opened in text mode, files can be iterated over line-by-line
                        # unlike Java, the newline is *not* removed by default in python
            print('{:09}'.format(char_count), end=' ')
            print(line, end="")  # since the line already has a newline, we don't want another
            char_count += len(line)
    #print()
    print('total characters: {}'.format(char_count))


def hexify(byte_seq):
    """
    Transform a byte sequence into a list strings representing each byte, in hex.
    :param byte_seq: a sequence of byte values
    :return: a list of bytes as hex strings, without the leading '0x'

    >>> hexify(b'abc') # note the leading b; this is a "bytes literal"
    ['61', '62', '63']

    >>> hexify(bytes.fromhex('2Ef0 F1f2  '))  # bytes.fromhex is another way to write bytes literals
    ['2e', 'f0', 'f1', 'f2']
    """
    result = []
    for b in byte_seq:  # we can iterate over the bytes, since they're a sequence
        h = hex(b)  # hex() is a built-in that transforms a numerical value to its hex equivalent as a string
        #result.append(h[2:])  # slice off the first two characters (0x); take character 2 through the end;
                              # note that hex() is not zero-padded so sometimes the result will be a single character

        if len(str(h[2:]))==1:
            result.append(h[0]+h[2])
            #result.append(h[2])
        else:
            result.append(h[2:])


    return result

def asciify(byte_seq):
    result = []
    for b in byte_seq:  # we can iterate over the bytes, since they're a sequence
        a = chr(b)  # hex() is a built-in that transforms a numerical value to its hex equivalent as a string
        #result.append(h[2:])  # slice off the first two characters (0x); take character 2 through the end;
                              # note that hex() is not zero-padded so sometimes the result will be a single character
        if b in range(32,127):
            #result = ' '.join(a)
            result.append(a)

        else:
            #result = ' '.join('.')
            result.append('.')


        #    result.append(a,end='')
        #try:
            #int(a[2:],16)
            #if int(a[2:],16)<0x20 or int(a[2:],16)>0x7E:
            #result.append(a)

        #except ValueError:
            #result.append('.')

    return result



def dump_file_hex(filename):
    counter = 0
    with open(filename, 'rb') as f:  # when opened in binary mode, you can read() the entire file, or
                                 # read(16) some number of bytes at a time as an immutable sequence of bytes
        hex_length=0
        chunk = f.read(16)


        line_number = 0
        if len(chunk)==0:
            print('',end='')
        else:
            #print(line_number)
            while chunk:  # empty sequences (that is, of length 0) evaluate to false
                print('{:07x}'.format(line_number), end='0  ')  # print the line number, in hex, zero-padded to four places

                hex_list = hexify(chunk)
                ascii_list = asciify(chunk)
                line = ' '.join(hex_list)  # join() joins the list of strings, using the string it's called on
                                               # as the separator character



                print(line[0:24],end=' ')
                print(line[24:], end= ' ')
                chunk = f.read(16)
                line_number += 1

                if len(str(line)) != 47:
                    space= 47- len(str(line))
                    for x in range(0,space):
                        print(' ',end='')

                print(' |', end= '')

                #if hexify < 0x20 && >07E:

                hex_length = hex_length +len(hex_list)
                #print(len(ascii_list),end=' ')
                #print(len(hex_list),end='')
                for ascii_lst in ascii_list:
                    print(ascii_lst,end='')

                #for hex_lst in hex_list:

                    #print(str(hex_lst).encode('ascii'))
                    #print(str(hex_lst))
                    #if str(hex_lst) == '5c':
                    #    print( '\\', end= '')
                    #if len(str(binascii.unhexlify(str(hex_lst).encode('ascii')))) == 4:
                    #    print( str(binascii.unhexlify(str(hex_lst).encode('ascii')))[2], end= '')

                    #print(binascii.unhexlify(str(hex_lst).encode('ascii')))
                    #else:
                    #    print('.', end= '')
                        #print(binascii.unhexlify(str(hex_lst).encode('ascii')))

                print('|')
                counter = counter + len(line)
                #break
            #print(hex_length)
                #print(len(str(line)))
                #print(len(hex_list))
            #print(counter)
            #print(len(line))
            #print(len(hex_list))
            if len(hex_list) == 16 and counter>47:
                print('{:07x}'.format(line_number),end='0\n')
            elif hex_length == 16:
                print('{:07x}'.format(line_number),end='0\n')
            elif hex_length<10:
                print('{:07x}'.format(line_number-1),end='')
                print(len(hex_list))
            else:
                print('{:07x}'.format(line_number-1),end='')
                print(hex(len(hex_list))[2:])





def main():
    #dump_file(sys.argv[1])
    dump_file_hex(sys.argv[1])

if __name__ == '__main__':
    main()
