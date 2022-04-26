import os

from PIL import Image
import pyperclip


def process_pic(file_name, invert):
    currentImage = Image.open("Imgs/" + file_name, 'r')
    width, height = currentImage.size
    pic_size_local = int(width * height / 8)
    temp_hex = 0x00
    bit_count = 0
    next_line_count = 0
    output_list = ['// ' + str(int(width / 8)) + ' x ' + str(int(height)) +
                   '\n' + 'const uint8_t ' + file_name.split('.')[0] + '[' + str(pic_size_local) + '] = {']

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
    output_list.append('};')
    temp = "".join(output_list)
    return temp, pic_size_local


final_list = []
total_pics = 0
pic_size = 0

invert = int(input("Invert?"))

for file in os.listdir("Imgs"):
    if file.endswith(".png"):

        print(file)
        pic_data, pic_size = process_pic(file, invert=invert)
        final_list.append(pic_data)
        total_pics += 1


final = "\n\n".join(final_list)
# print('[' + str(total_pics) + ']' + '[' + str(pic_size) + ']')
print(final)
pyperclip.copy(final)
print("\n---------------------------\nCopied " + str(total_pics) + ".")

input("Press any key")
