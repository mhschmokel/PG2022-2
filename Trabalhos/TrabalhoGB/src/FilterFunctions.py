import cv2 as cv
from Filter import *

def blurFunction(img):
  return cv.GaussianBlur(img, (13, 13), 5, 0)

def filter2(img):
  return img

def filter3(img):
  return img

def filter4(img):
  return img

def filter5(img):
  return img

def handleFilter(*args):
    filters[args[1]].isActive = not filters[args[1]].isActive

filters = {
            'blur': Filter(blurFunction),
            'filter2': Filter(filter2),
            'filter3': Filter(filter3),
            'filter4': Filter(filter4),
            'filter5': Filter(filter5),
        }