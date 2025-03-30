#!/usr/bin/env python3

import struct
import sys


# See the following files from Cypress FX3 SDK for reference
#  * cyfx3sdk/util/elf2img/elf2img.c
#  * cyfx3sdk/util/elf2img/readme.txt


class FX3ImageSection:
    def __init__(self, index: int, size: int, start: int):
        self.index = index
        self.size = size
        self.start = start

    def __str__(self):
        return f'Section #{self.index}: size = 0x{self.size:04x}, start = 0x{self.start:08x}'


class FX3Image:
    HEADER_FORMAT = '2s2B'
    HEADER_SIZE = 4

    IMAGE_TYPE_BINARY = 0xB0

    EEPROM_SPEEDS = {
        0: '100 kHz',
        1: '400 kHz',
        2: '1 MHz',
    }

    SECTION_HEADER_FORMAT = '<2I'
    SECTION_HEADER_SIZE = 8

    def __init__(self, path: str):
        with open(path, 'rb') as f:
            self.path = path

            header = f.read(FX3Image.HEADER_SIZE)
            magic, self.i2c_config, self.image_type = struct.unpack(FX3Image.HEADER_FORMAT, header)
            assert magic == b'CY'

            self.sections = []
            self.stored_checksum = 0
            self.actual_checksum = 0
            self.entry_point = 0

            while self._load_section(f):
                pass

    def __str__(self):
        image_type = 'Binary' if self.image_type == FX3Image.IMAGE_TYPE_BINARY else 'Unknown'
        i2c_config_warning = '\n* Warning: Unknown bit set in I2C Config' if self.i2c_config & 0xC1 else ''
        eeprom_size = (self.i2c_config & 0xE) >> 1
        eeprom_speed = (self.i2c_config & 0x30) >> 4

        if self.stored_checksum == self.actual_checksum:
            checksum = f'{self.actual_checksum:#0x}'
        else:
            checksum = \
f'''
Warning: checksums don't match
* Stored checksum: 0x{self.stored_checksum:2x}
* Actual checksum: 0x{self.actual_checksum:2x}
'''

        sections = [str(section) for section in self.sections]
        sections = '\n'.join(sections)

        return f'''
Image: {self.path}
Image type: {image_type} {self.image_type:#0x}
I2C Config: {self.i2c_config:#0x}{i2c_config_warning}
* EEPROM Size: {2 ** eeprom_size} kB
* EEPROM Speed: {FX3Image.EEPROM_SPEEDS[eeprom_speed]}
{sections}
Checksum: {checksum}
'''

    def _load_section(self, f):
        header = f.read(FX3Image.SECTION_HEADER_SIZE)
        size, start = struct.unpack(FX3Image.SECTION_HEADER_FORMAT, header)

        if size == 0:
            # Termination section
            self.entry_point = start
            self.stored_checksum = struct.unpack('<I', f.read(4))[0]
            return False

        for _ in range(size):
            dword = struct.unpack('<I', f.read(4))

            # Simulate C language unsigned integer overflow
            self.actual_checksum = (self.actual_checksum + dword[0]) & 0xFFFF_FFFF

        section = FX3ImageSection(len(self.sections), size, start)
        self.sections.append(section)

        return True


def _main():
    if len(sys.argv) < 2:
        print(f'Usage: {sys.argv[0]} file.img')
        exit(1)

    image = FX3Image(sys.argv[1])
    print(image)


if __name__ == '__main__':
    _main()
