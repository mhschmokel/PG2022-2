import cv2 as cv
from Filter import *

def blurFunction(img):
  return cv.GaussianBlur(img, (13, 13), 5, 0)

def grayFunction(img):
  return cv.cvtColor(img, cv.COLOR_BGR2GRAY)

def invertFunction(img):
  return cv.bitwise_not(img)

def cannyFunction(img):
  return cv.Canny(img, 25, 75)

def pencilSketchFunction(img):
  sk_gray, sk_color = cv.pencilSketch(img, sigma_s=60, sigma_r=0.07, shade_factor=0.1)
  return sk_color

def handleFilter(*args):
    filters[args[1]].isActive = not filters[args[1]].isActive

filters = {
            'blur': Filter(blurFunction),
            'gray': Filter(grayFunction),
            'invert': Filter(invertFunction),
            'canny': Filter(cannyFunction),
            'pencilSketch': Filter(pencilSketchFunction),
        }