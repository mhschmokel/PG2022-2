import cv2 as cv
from tkinter import filedialog

def processFile():
    file_path = filedialog.askopenfilename()

    img = cv.imread(file_path)
    img = cv.resize(img, (0,0), fx=0.5, fy=0.5)
    
    cv.imshow('File', img)

    while True:
        
        k = cv.waitKey(1) & 0xFF

        if cv.getWindowProperty('File', cv.WND_PROP_VISIBLE) < 1:
            break

        if k == 27:
            break
    
    cv.destroyAllWindows()
    