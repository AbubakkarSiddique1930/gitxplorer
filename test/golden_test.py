import sys
import cv2
import pytesseract
from wand.image import Image

GOLDEN_FILE = 'test/golden.png'
TEXT_GOLDEN_FILE = 'test/text_golden.png'
TEST_FILES = [
    [f'Linux-img/{sys.argv[1]}.png', GOLDEN_FILE],
    [f'macOS-img/{sys.argv[1]}.png', GOLDEN_FILE],
    [f'Windows-img/{sys.argv[1]}.png', GOLDEN_FILE],
]
TEXT_TEST_FILES = [
    [f'Linux-img/{sys.argv[2]}.png', TEXT_GOLDEN_FILE],
    [f'macOS-img/{sys.argv[2]}.png', TEXT_GOLDEN_FILE],
    [f'Windows-img/{sys.argv[2]}.png', TEXT_GOLDEN_FILE],
]

COMPARE_TOLERANCE = 2

def compare(img1, img2):
    with Image(filename=img1) as i1:
        with Image(filename=img2) as i2:
            diff = i1.compare(i2, metric='absolute')
            return diff[1]

def golden_test():
    fails = []
    for file in TEST_FILES:
        result = compare(file[0], file[1])
        if result != 0:
            fails.append([file, result])
    return fails

def img_ocr(path):
    img = cv2.imread(path)
    gry = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    return pytesseract.image_to_data(gry, output_type=pytesseract.Output.DICT)

def compare_list_tol(lst1, lst2, tolerance):
    for e1, e2 in zip(lst1, lst2):
        if abs(e1-e2) > tolerance:
            return False
    return True

def bound_match(textd, golden_textd):
    return compare_list_tol(
        textd['left'], golden_textd['left'], COMPARE_TOLERANCE
        ) and compare_list_tol(
        textd['top'], golden_textd['top'], COMPARE_TOLERANCE
        ) and compare_list_tol(
        textd['width'], golden_textd['width'], COMPARE_TOLERANCE
        ) and compare_list_tol(
        textd['height'], golden_textd['height'], COMPARE_TOLERANCE)

def text_golden_test():
    fails = []
    for file in TEXT_TEST_FILES:
        textd = img_ocr(file[0])
        golden_textd = img_ocr(file[1])
        if textd['text'] != golden_textd['text']:
            fails.append([file, 'Text Mismatch'])
        if not bound_match(textd, golden_textd):
            fails.append([file, 'Transformation Mismatch'])
    return fails

def main():
    fail = False
    fails = golden_test()
    fails += text_golden_test()
    if len(fails) > 0:
        fail = True
        for f in fails:
            print(f'Failure: {f[0]} (diff: {f[1]})')

    if fail:
        exit(-1)


if __name__ == '__main__':
    main()