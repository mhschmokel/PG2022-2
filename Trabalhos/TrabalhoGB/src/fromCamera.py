import cv2 as cv

def processCamera():
    camera = cv.VideoCapture(0)

    while True:
        img = camera.read()

        cv.imshow('Camera', img)

        k = cv.waitKey(20) & 0xFF

        if cv.getWindowProperty('Camera', cv.WND_PROP_VISIBLE) < 1:
            break

        if k == 27:
            break
    
    camera.release()
    cv.destroyAllWindows()