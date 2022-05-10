from math import comb
import os

from PIL import Image
import pyperclip


def process_pic(file_name, invert, serial_num):

    currentImage = Image.open("Imgs/" + file_name, 'r')
    width, height = currentImage.size
    pic_size_local = int(width * height / 8)
    temp_hex = 0x00
    bit_count = 0
    next_line_count = 0

    if serial_num == 1 and combined:
        output_list = ['// ' + str(int(width / 8)) + ' x ' + str(int(height)) +
                       '\n' + 'const uint8_t ' + file_name.split('.')[0] + '[' + str(total_pics) + '][' + str(pic_size_local) + '] = \n{{']
    if serial_num > 1 and combined:
        output_list = [',\n{']
    if not combined:
        output_list = ['// ' + str(int(width / 8)) + ' x ' + str(int(height)) +
                       '\n' + 'const uint8_t ' + file_name.split('.')[0] + '[' + str(pic_size_local) + '] = \n{']

    for y in range(0, height):
        for x in range(0, width):
            bit_count += 1
            k = currentImage.getpixel((x, y))
            if (k & invert) | ((1 - k) & (1 - invert)):
                temp_hex |= 0x01

            if bit_count == 8:
                bit_count = 0
                output_list.append("0x%02x" % temp_hex)
                output_list.append(',')
                temp_hex = 0x00
                next_line_count += 1
                if (next_line_count == 16):
                    next_line_count = 0
                    output_list.append('\n')
            else:
                temp_hex <<= 1
    
    if combined and serial_num != total_pics:
        output_list.append('}')
    if combined and serial_num == total_pics:
        output_list.append('}};')

    if not combined:
        output_list.append('};')
    temp = "".join(output_list)
    return temp, pic_size_local


final_list = []
total_pics = 0
pic_size = 0
serialnum = 0

invert = int(
    input("Invert?\n0 -> Don't Invert (default)\n1 -> Invert\n") or "0")

for file in os.listdir("Imgs"):
    if file.endswith(".png"):
        total_pics += 1

if total_pics > 1:
    combined = int(
        input("\nMultiple files detected\n0 -> Separated (default)\n1 -> Combined\n") or "0")

for file in os.listdir("Imgs"):
    if file.endswith(".png"):
        serialnum += 1
        print(file)
        pic_data, pic_size = process_pic(file, invert=invert, serial_num=serialnum)
        final_list.append(pic_data)

if combined:
    final = "".join(final_list)
else:
    final = "\n\n".join(final_list)

# print('[' + str(total_pics) + ']' + '[' + str(pic_size) + ']')
print(final)
pyperclip.copy(final)
print("\n---------------------------\nCopied " + str(total_pics) + ".")

input("Press any key")
