import sys
import base64, zlib

disk_str = """7Nc/bhNBFAbw5yQE8ydQDBIdQooAiSIVB4A70ANCEVREIi7cIpCg9wW4BTUVR+AAFFBSIFFQDG/3TS5gIqrfFv7283rezP46xzlfqziOday2nroaqx/mhNuxjNc57zTnPcu7baZOpznOWR96xNOc9zInvYoXW5/vbN5eTvjRl1vPsZAAAQIECBAgQIAAAQIECPwPgXVuso7FP2/VYi/e9Z1ocSPvFpmP5/zWb8WD+NNbXJj3OJk/l7Eb9+JN/hd/2+/G51z3qb/PFrHJ/NLv5/Pp+4jD+Ni/Z7b42vdz3m7ciUexk+uOsk39KPu0X12becr0+3qnTa9suaZ6ZcuV1Sun81evPDvvpte5W+yP55UtLo5e2fKdan1li0ujV7a4PHpliyujV7a4Onpli4PRK1tcG72yxfXRK2/OGvXei/jVT+JnfxK/+/P5qYsAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQIECBAgQIAAAQLnJvCXHToWAAAAABg0f+qJJNARyIABAwYMGDBgwIABAwYMGDBgwIABAwYMGDBgwIABAwYMGDBgwIABAwYMGDBgwIABAwYMGDBgwIABAwYMGDBgwIABAwYMGDBgwIABAwYMGDBgwIABAwYMGDBgwIABAwYMGDBgwIABAwYMGDBgwIABAwYMGDBgwIABAwYMGDBgwIABAwYMGDBgwIABAwYMGKjZoQMBAAAAAEH7Uy9SCGHAgAEDBgwYMGDAgAEDBgwYMGDAgAEDBgwYMGDAgAEDBgwYMGDAgAEDBgwYMGDAgAEDBgwYMGDAgAEDBgwYMGDAgAEDBgwYMGDAgAEDBgwYMGDAgAEDBgwYMGDAgAEDBgwYMGDAgAEDBgwYMGDAgAEDBgwYMGDAgAEDBgwYMGDAgAEDBgwYMGDAgAEDBgzUYwD8"""

def disk_to_bytearray(hugemem_str):
    decodedb64 = base64.b64decode(hugemem_str)
    return bytearray(zlib.decompress(decodedb64, wbits=-15))


# def list_to_huge_string(data):
#     data = bytearray(data)

#     while len(data) % 4 != 0:
#         data.append(0)

#     lower_16 = bytearray()
#     upper_16 = bytearray()

#     for i in range(0, len(data), 4):
#         lower_16.append(data[i])
#         lower_16.append(data[i+1])
#         upper_16.append(data[i+2])
#         upper_16.append(data[i+3])

#     compressed_lower = zlib.compress(lower_16, level=2, wbits=-15)
#     compressed_upper = zlib.compress(upper_16, level=2, wbits=-15)

#     encoded_lower = base64.b64encode(compressed_lower).decode('utf-8').strip('=')
#     encoded_upper = base64.b64encode(compressed_upper).decode('utf-8').strip('=')

#     return encoded_lower, encoded_upper


def main():
    with open("dump.hex", "wb") as f:
        f.write(disk_to_bytearray(disk_str))

if __name__ == '__main__':
    main()
