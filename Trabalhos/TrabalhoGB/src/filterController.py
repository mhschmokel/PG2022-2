from Filter import *
from FilterFunctions import *

class filterController():

    def initButtons(*args, cv):
        cv.createButton('Blur', handleFilter, 'blur', cv.QT_CHECKBOX, False)
        cv.createButton('Filter 2', handleFilter, 'filter2', cv.QT_CHECKBOX, False)
        cv.createButton('Filter 3', handleFilter, 'filter3', cv.QT_CHECKBOX, False)
        cv.createButton('Filter 4', handleFilter, 'filter4', cv.QT_CHECKBOX, False)
        cv.createButton('Filter 5', handleFilter, 'filter5', cv.QT_CHECKBOX, False)