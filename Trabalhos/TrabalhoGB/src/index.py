from tkinter import *
import fromCamera as cam
import fromFile as file

root = Tk()

cameraButton = Button(root, text="Camera",command=cam.processCamera)
cameraButton.pack()

fileButton = Button(root, text="Open file", command=file.processFile)
fileButton.pack()

exitButton = Button(root, text="Exit", command=root.quit)
exitButton.pack()

root.mainloop()