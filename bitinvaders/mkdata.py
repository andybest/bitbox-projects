# Export images to C file

import os
from itertools import izip_longest

from PIL import Image

"""
Converts assets to RGB555 format and outputs as C arrays.
e.g. for a 4x4 image named "myImage.png", the output would be:

const uint16_t image_myImage = {
    0xFF00, 0x0000, 0xFF00, 0x00FF,
    0xFF00, 0x0000, 0xFF00, 0x00FF,
    0xFF00, 0x0000, 0xFF00, 0x00FF,
    0xFF00, 0x0000, 0xFF00, 0x00FF }

"""

def grouper(iterable, n, fillvalue=None):
    args = [iter(iterable)] * n
    return izip_longest(*args, fillvalue=fillvalue)

def iterate_files():
    images = {}
    
    for root, dirs, filenames in os.walk('./assets'):
        for f in filenames:
            asset_name = os.path.splitext(f)[0]
            images[asset_name] = convert_asset('./assets/' + f, asset_name)
    
    header = make_header(images.keys())
    
    cfile = "#include \"imageAssets.h\"\n\n"
    cfile += "\n".join(images.values())
    
    with open("imageAssets.h", "w") as f:
        f.write(header)
        
    with open("imageAssets.c", "w") as f:
        f.write(cfile)
    

def convert_asset(asset_path, asset_name):
    image = Image.open(asset_path)
    imagedata = image.getdata()
    
    output = "const uint16_t image_" + asset_name + "_pixels[] = {\n"
    
    outputpixels = []
    for p in list(imagedata):
        pixel = rgb_32_to_16(p[0], p[1], p[2])
        pixstring = "0x" + format(pixel, 'x')
        outputpixels.append(pixstring)
    
    grouped = grouper(outputpixels, 8)
    
    for group in grouped:
        line = "   "
        for pixstring in group:
            line += " " + pixstring + ","
            # Align each pixel
            line += " " * (6 - len(pixstring)) 
        output += line + "\n"
    
    # Remove the last newline and comma
    output = output[:output.rfind(",")]
    output += " };\n\n"
    
    output += "const struct RGB555Image image_" + asset_name + " = { "
    output += str(image.width) + ", "
    output += str(image.height) + ", "
    output += "image_" + asset_name + "_pixels };\n"
    print output
    return output
    
def rgb_32_to_16(r, g, b):
    newR = r >> 3
    newG = g >> 3
    newB = b >> 3
    return (newR << 10) | (newG << 5) | newB
    
def make_header(image_names):
    output = "#pragma once\n\n#include <stdint.h>\n\n"
    
    # Definition of image struct
    output += "typedef struct RGB555Image {\n    uint16_t width, height;\n    "
    output += "const uint16_t *pixels;\n} RGB555Image;\n\n"
    
    for i in image_names:
        output += "const struct RGB555Image image_" + i + ";\n"
    
    return output

if __name__ == '__main__':
    iterate_files()