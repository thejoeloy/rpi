import cv2 as cv
img = cv.imread("king.jpg")

cv.imshow("Display window", img);
k = cv.waitKey(0)
