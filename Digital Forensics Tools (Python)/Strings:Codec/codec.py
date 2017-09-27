def encode(codepoint):

    if codepoint <= 0x7F: # seven bits are 0b1111111 = 0x7F
        return bytes([codepoint])

    elif codepoint <= 0x7FF: # 11 bits are 0b11111111111 = 0x7FF
        firstpart = codepoint >> 6
        firstpart = 0b11000000 | firstpart # 0x110XXXXX "bitwise or" the first part

        mask = 0b00000111111
        secondpart = codepoint & mask
        secondpart = 0b10000000 | secondpart # 0x10XXXXXX "bitwise or" the second part
        return bytes([firstpart, secondpart])

    elif codepoint <= 0xFFFF: # 16 bits are 0b1111111111111111 = 0xFFFF

        firstpart = codepoint >> 12
        firstpart = 0b11100000 | firstpart
        #print(bin(firstpart) + 'aft')

        mask = 0b0000111111
               #0b0010000010101100
        secondpart = (codepoint >> 6) & mask
        #print(bin(secondpart) + 'bef')
        secondpart = 0b10000000 | secondpart
        #print(bin(secondpart) + 'aft')

        mask = 0b0000000000111111
        thirdpart = (codepoint) & mask
        #print(bin(thirdpart) + 'bef')
        thirdpart = 0b10000000 | thirdpart
        #print(bin(thirdpart) + 'aft')
        return bytes([firstpart, secondpart, thirdpart])


    elif codepoint <= 0x1FFFFF: # 21 bits bits are 0b11111111111111111111 = 0x1FFFFF

        firstpart = codepoint >> 18
        firstpart = 0b11110000 | firstpart


        mask = 0b000111111
        secondpart = (codepoint >> 12) & mask
        secondpart = 0b10000000 | secondpart

        mask = 0b000000000111111
        thirdpart = (codepoint >> 6) & mask
        thirdpart = 0b10000000 | thirdpart


        mask = 0b000000000000000111111
        fourthpart = codepoint & mask
        fourthpart = 0b10000000 | fourthpart

        return bytes([firstpart,secondpart,thirdpart,fourthpart])

def decode(bytes_object):

    if bytes_object.count(b"") == 2:
        return bytes_object[0]

    elif bytes_object.count(b"") == 3:

        firstpart = bytes_object[0]
        mask = 0b00011111
        firstpart = mask & firstpart


        secondpart = bytes_object[1]
        mask = 0b00111111
        secondpart = mask & secondpart

        return (firstpart << 6) | secondpart

    elif bytes_object.count(b"") == 4:
        #print( bytes_object[0] * bytes_object[1] * bytes_object[2])
        firstpart = bytes_object[0]
        mask = 0b00001111
        firstpart = mask & firstpart


        secondpart = bytes_object[1]
        mask = 0b00111111
        secondpart = mask & secondpart


        thirdpart = bytes_object[2]
        mask = 0b00111111
        thirdpart = mask & thirdpart

        return (((firstpart << 6) | secondpart )<<6 ) | thirdpart
    elif bytes_object.count(b"") == 5:
        firstpart = bytes_object[0]
        mask = 0b00000111
        firstpart = mask & firstpart


        secondpart = bytes_object[1]
        mask = 0b00111111
        secondpart = mask & secondpart


        thirdpart = bytes_object[2]
        mask = 0b00111111
        thirdpart = mask & thirdpart


        fourthpart = bytes_object[3]
        mask = 0b00111111
        fourthpart = mask & fourthpart



        return ((((firstpart << 6) | secondpart ) <<6 ) | thirdpart) <<6 | fourthpart


def main():
    print(encode(36))
    print(encode(162))
    print(encode(8364))
    print(encode(66376))
    #print(encode(573441))

    print(decode(encode(36)))
    print(decode(encode(162)))
    print(decode(encode(8364)))
    print(decode(encode(66376)))
    #print(decode(encode(66376)))

if __name__ == '__main__':
    main()
