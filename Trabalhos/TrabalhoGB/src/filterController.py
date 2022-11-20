from Filter import *
from FilterFunctions import *

class filterController():

    def initButtons(*args, cv):
        cv.createButton('No filter', handleFilter, 'noFilter', cv.QT_RADIOBOX, True)
        cv.createButton('Blur', handleFilter, 'blur', cv.QT_RADIOBOX, False)
        cv.createButton('Gray', handleFilter, 'gray', cv.QT_RADIOBOX, False)
        cv.createButton('Invert', handleFilter, 'invert', cv.QT_RADIOBOX, False)
        cv.createButton('Canny', handleFilter, 'canny', cv.QT_RADIOBOX, False)
        cv.createButton('Pencial Sketch', handleFilter, 'pencilSketch', cv.QT_RADIOBOX, False)
        cv.createButton('HDR', handleFilter, 'hdr', cv.QT_RADIOBOX, False)
        cv.createButton('Equalize', handleFilter, 'equalize', cv.QT_RADIOBOX, False)
        cv.createButton('Dilate', handleFilter, 'dilate', cv.QT_RADIOBOX, False)