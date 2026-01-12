# script originally by Brutus
from PIL import Image
import base64,zlib
import sys

tilesheet=[]
image = Image.open(sys.argv[1]).convert("RGB").resize((256,256))
image_data=list(image.getdata())
image_width=image.size[0]
for i in range(65536):
    x=((i%8)+(int(i/64)*8))%image_width

    y=(int(i/8)%8)+(int(i/(image_width*8))*8)

    pixel=x+(y*image_width)
    temp=len(tilesheet)
    if pixel < len(image_data):
        try:tilesheet.append((int(image_data[pixel][0]/8)<<10)+(int(image_data[pixel][1]/8)<<5)+int(image_data[pixel][2]/8))
        except:print(image_data[pixel])
    else:
        tilesheet.append(0)
def list_to_huge_string(data):
    lower_16 = bytearray()
    upper_16 = bytearray()

    for value in data:
        lower = value & 0xFFFF
        upper = (value >> 16) & 0xFFFF

        lower_16.append(lower & 0xFF)
        lower_16.append((lower >> 8) & 0xFF)

        upper_16.append(upper & 0xFF)
        upper_16.append((upper >> 8) & 0xFF)

    compressed_lower = zlib.compress(lower_16, level=2, wbits=-15)
    compressed_upper = zlib.compress(upper_16, level=2, wbits=-15)

    encoded_lower = base64.b64encode(compressed_lower).decode('utf-8').strip('=')
    encoded_upper = base64.b64encode(compressed_upper).decode('utf-8').strip('=')

    return encoded_upper, encoded_lower

def list_to_binary_string(data):
        if len(data) != 1<<16:
             raise ValueError(f'expected table size of 65536 '
                         f'but got {len(data)}')
        output=""
        for value in data:
            output+="0"*(16-len(bin(value)[2:]))+bin(value)[2:]
        return output
             
print(list_to_huge_string(tilesheet)[1])
#with open("output.bin", "wb") as f:
#    for num in tilesheet:f.write(num.to_bytes(2, byteorder='big'))
