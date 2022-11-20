import cv2 as cv

class Sticker:
  def __init__(self, x, y, image, scale):
    self.x = x
    self.y = y
    self.scale = scale
    
    width = int(image.shape[1] * scale / 100)
    height = int(image.shape[0] * scale / 100)
    dim = (width, height)
    self.image = cv.resize(image, dim, interpolation = cv.INTER_AREA)