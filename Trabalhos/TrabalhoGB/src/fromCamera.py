import cv2 as cv
from FilterFunctions import *
from filterController import *

def processCamera():
    filters_controller = filterController()

    camera = cv.VideoCapture(0)
    
    res, imgCap = camera.read()
    cv.imshow('Camera', imgCap)

    filters_controller.initButtons(cv=cv)

    while True:
        res, imgCap = camera.read()

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