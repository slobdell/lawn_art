import cv2
import numpy as np

# DEFAULT COLOR (17, 2, 10)
MAX_COLOR = 255
MAX_USED = 17
TOTAL_LEVELS = MAX_COLOR / MAX_USED

img = cv2.imread("steps6.bmp")

rows, cols, bytes_ = img.shape

compressed = np.zeros((rows, cols), dtype=np.uint8)

max_in_image = 0

for r in xrange(rows):
    for c in xrange(cols):
        if img[r, c, 0] > max_in_image:
            max_in_image = img[r, c, 0]

multiplier = 255.0 / max_in_image

print "char brightnessMatrix[%s][%s] = {" % (rows, cols)
for r in xrange(rows):
    print "    {",
    for c in xrange(cols):
        compressed[r, c] = int(multiplier * img[r, c, 0]) / MAX_USED

        print "%s," % compressed[r, c],
    print "},"
print "};"
