import numpy as np
from PIL import Image

img = Image.open("src/timg.jpg").convert("L")
img_array = np.array(img)

height, width = img_array.shape

for h in range(height):
    for w in range(width):
        if img_array[h][w] < 200:
            img_array[h][w] = 0

img2 = Image.fromarray(img_array)
img2.save("src/timg.jpg")
