from Filter import *
from FilterFunctions import *

class filterController():

    def initButtons(*args, cv):
        cv.createButton('Blur', handleFilter, 'blur', cv.QT_CHECKBOX, False)
        cv.createButton('Gray', handleFilter, 'gray', cv.QT_CHECKBOX, False)
        cv.createButton('Invert', handleFilter, 'invert', cv.QT_CHECKBOX, False)
        cv.createButton('Canny', handleFilter, 'canny', cv.QT_CHECKBOX, False)
        cv.createButton('Pencil Sketch', handleFilter, 'pencilSketch', cv.QT_CHECKBOX, False)