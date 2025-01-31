#!/usr/bin/env python3

import sys
import pypdf

def _extract_images(pdfpath: str):
    reader = pypdf.PdfReader(pdfpath)

    for pageindex, page in enumerate(reader.pages):
        for imageindex, image in enumerate(page.images):
            imagepath = f'{image.name}_{pageindex}_{imageindex}'

            with open(imagepath, "wb") as f:
                f.write(image.data)

def _main():
    for path in sys.argv[1:]:
        _extract_images(path)

if __name__ == '__main__':
    _main()
