import cv2 as cv
from FilterFunctions import *
from filterController import *
from Sticker import *
from StickerController import *

def processCamera():
    filters_controller = filterController()
    sticker_controller = StickController()

    camera = cv.VideoCapture(0)
    
    res, imgCap = camera.read()
    cv.imshow('Camera', imgCap)

    filters_controller.initButtons(cv=cv)
    sticker_controller.initButtons(cv=cv)

    cv.setMouseCallback('Camera', mouseCallback)

    while True:
        res, imgCap = camera.read()

        for sticker in stickersOnScreen:
            imgCap = stickerTransparent(imgCap, sticker.image, int((sticker.x - sticker.image.shape[0]/2)), int((sticker.y - sticker.image.shape[1]/2)))
        
        for filter in filters.items():
            if filter[1].isActive:
                imgCap = filter[1].function(imgCap)

        if res: 
            cv.imshow('Camera', imgCap)

        k = cv.waitKey(20) & 0xFF

        if cv.getWindowProperty('Camera', cv.WND_PROP_VISIBLE) < 1:
            break

        if k == 27:
            break
    
    camera.release()
    cv.destroyAllWindows()