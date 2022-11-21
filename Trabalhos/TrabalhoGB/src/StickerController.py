import cv2 as cv
import numpy as np
from Sticker import *

class StickController():
    def initButtons(*args, cv):
      cv.createButton('None', handleStickerIndex, 0, cv.QT_RADIOBOX, False)
      cv.createButton('Dog meme', handleStickerIndex, 1, cv.QT_RADIOBOX, False)
      cv.createButton('Troll', handleStickerIndex, 2, cv.QT_RADIOBOX, False)
      cv.createButton('Bom dia', handleStickerIndex, 3, cv.QT_RADIOBOX, False)
      cv.createButton('Check', handleStickerIndex, 4, cv.QT_RADIOBOX, False)
      cv.createButton('Fuleco', handleStickerIndex, 5, cv.QT_RADIOBOX, False)

stickersOnScreen = []
stickerIndex = 0

stickersImages = [
  None,
  cv.imread("stickers/dogMeme.png", cv.IMREAD_UNCHANGED),
  cv.imread("stickers/troll.png", cv.IMREAD_UNCHANGED),
  cv.imread("stickers/bomdia.png", cv.IMREAD_UNCHANGED),
  cv.imread("stickers/check.png", cv.IMREAD_UNCHANGED),
  cv.imread("stickers/fuleco.png", cv.IMREAD_UNCHANGED),
]

stickersScalePercent = [
  0,
  25,
  15,
  45,
  20,
  35,
]

def stickerTransparent(background, sticker, x_offset=None, y_offset=None):
  bg_h, bg_w, bg_channels = background.shape
  fg_h, fg_w, fg_channels = sticker.shape

  assert bg_channels == 3, f'background image should have exactly 3 channels (RGB). found:{bg_channels}'
  assert fg_channels == 4, f'sticker image should have exactly 4 channels (RGBA). found:{fg_channels}'

  if x_offset is None: x_offset = (bg_w - fg_w) // 2
  if y_offset is None: y_offset = (bg_h - fg_h) // 2

  w = min(fg_w, bg_w, fg_w + x_offset, bg_w - x_offset)
  h = min(fg_h, bg_h, fg_h + y_offset, bg_h - y_offset)

  if w < 1 or h < 1: return

  bg_x = max(0, x_offset)
  bg_y = max(0, y_offset)
  fg_x = max(0, x_offset * -1)
  fg_y = max(0, y_offset * -1)
  sticker = sticker[fg_y:fg_y + h, fg_x:fg_x + w]
  background_subsection = background[bg_y:bg_y + h, bg_x:bg_x + w]

  sticker_colors = sticker[:, :, :3]
  alpha_channel = sticker[:, :, 3] / 255

  alpha_mask = np.dstack((alpha_channel, alpha_channel, alpha_channel))

  composite = background_subsection * (1 - alpha_mask) + sticker_colors * alpha_mask

  background[bg_y:bg_y + h, bg_x:bg_x + w] = composite

  return background

def handleStickerIndex(*args):
  global stickerIndex
  stickerIndex = args[1]

def mouseCallback(event, x, y, flags, param):
  global stickerIndex, stickers
  if event == cv.EVENT_LBUTTONDOWN and stickerIndex != 0:
    sticker = Sticker(x, y, cv.cvtColor(stickersImages[stickerIndex], cv.COLOR_BGR2BGRA), stickersScalePercent[stickerIndex])
    stickersOnScreen.append(sticker)