import argparse

def print_strings(file_obj, encoding, min_len):
    #file_obj.
    #print(file_obj.name)
    #print(encoding)
    #print(min_len)

    if encoding == 's':
        result = ''
        byte_size = 1
        while True:
            f = file_obj.read(byte_size)
            if f:
                a = f.decode('utf-8','ignore')
                if len(a)!=0 and ord(a) in range (32,127):
                    result += a
                        #print(a)
                else:
                    if len(result) >= min_len:
                        print(''.join(result))
                    result= ''

            else:
                if len(result) >= min_len:
                    print(''.join(result))
                break

    if encoding == 'l':
        result = ''
        byte_size = 2
        while True:
            f = file_obj.read(byte_size)
            if f:
                a = f.decode('utf-16-le','ignore')

                if len(a)!=0 and ord(a) in range (32,127):
                        result += ''.join(a)
                        #print(a)
                else:
                    if len(result) >= min_len:
                        print(''.join(result))
                    result= ''
            #f = file_obj.read(byte_size)
            else:
                if len(result) >= min_len:
                    print(''.join(result))
                break

    if encoding == 'b':
        result = ''
        byte_size = 2
        while True:
            f = file_obj.read(byte_size)
            if f:
                a = f.decode('utf-16-be','ignore')

                if len(a)!=0 and ord(a) in range (32,127):
                        result += ''.join(a)
                        #print(a)
                else:
                    if len(result) >= min_len:
                        print(''.join(result))
                    result= ''
            #f = file_obj.read(byte_size)
            else:
                if len(result) >= min_len:
                    print(''.join(result))
                break







def main():
    parser = argparse.ArgumentParser(description='Print the printable strings from a file.')
    parser.add_argument('filename')
    parser.add_argument('-n', metavar='min-len', type=int, default=4,
                        help='Print sequences of characters that are at least min-len characters long')
    parser.add_argument('-e', metavar='encoding', choices=('s', 'l', 'b'), default='s',
                        help='Select the character encoding of the strings that are to be found. ' +
                             'Possible values for encoding are: s = UTF-8, b = big-endian UTF-16, ' +
                             'l = little endian UTF-16.')
    args = parser.parse_args()

    with open(args.filename, 'rb') as f:
        print_strings(f, args.e, args.n)

if __name__ == '__main__':
    main()
