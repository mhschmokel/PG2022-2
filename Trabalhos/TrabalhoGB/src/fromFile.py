import cv2 as cv
from tkinter import filedialog
from FilterFunctions import *
from filterController import *

def processFile():
    filters_controller = filterController()
    
    file_path = filedialog.askopenfilename()

    img = cv.imread(file_path)
    img = cv.resize(img, (0,0), fx=0.5, fy=0.5)

    cv.imshow('File', img)

    filters_controller.initButtons(cv=cv)

    originalImg = img

    while True:

        img = originalImg
        
        for filter in filters.items():
            if filter[1].isActive:
                img = filter[1].function(img)

        cv.imshow('File', img)

        k = cv.waitKey(1) & 0xFF

        if cv.getWindowProperty('File', cv.WND_PROP_VISIBLE) < 1:
            break

        if k == 27:
            break
    
    cv.destroyAllWindows()
    