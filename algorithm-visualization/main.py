from alg_viz import Viz
from random import randint

def buble_sort(arr, f):
    done = False
    while not done:
        done = True
        for i in range(0, len(arr)-1):
            if f(arr, i, i+1):
                arr[i], arr[i+1] = arr[i+1], arr[i]
                done = False
    return arr

def search(arr, f, item):
    for i in range(0, len(arr)):
        if f(arr, i, item):
            return arr, i
    return arr, nan

def random_search(arr, f, item):
    for i in range(0, 3*len(arr)):
        index = randint(0,len(arr)-1)
        if f(arr, index, item):
            return arr, index
    return arr, nan

def compare(arr, i, h):
    return arr[i]>arr[h]

def compare1(arr, i, h):
    return arr[i]==h



o = Viz(buble_sort,compare, framerate=20)
arr = list(x+randint(0,155) for x in range(0,100))
o.load_data(arr)

# o = Viz(random_search, compare1, framerate=10)
# arr = [6, 0, 80, 2, 21, 16, 11, 93, 53, 6, 45, 28, 82, 8, 28, 47, 75, 30, 28, 38, 40, 9, 21, 18, 90, 96, 60, 54, 40, 33, 84, 13, 90, 30, 32, 35, 39, 44, 46, 65, 71, 44, 89, 64, 34, 28, 99, 112, 93, 68, 104, 118, 85, 35, 27, 89, 60, 59, 38, 61, 82, 31, 96, 34, 63, 91, 60, 69, 128, 76, 131, 91, 108, 77, 135, 124, 51, 68, 49, 89, 93, 58, 82, 98, 74, 107, 61, 76, 108, 63, 54, 105, 142, 86, 65, 52, 141, 136, 102, 82, 105, 127, 56, 92, 140, 155, 112, 65, 80, 131, 159, 106, 133, 68, 87, 110, 105, 100, 79, 110, 131, 106, 136, 103, 141, 74, 134, 157, 148, 108, 138, 140, 159, 168, 157, 95, 115, 147, 94, 92, 147, 171, 179, 172, 162, 102, 148, 126, 148, 106, 90, 119, 183, 131, 124, 174, 141, 127, 119, 162, 191, 96, 184, 105, 119, 194, 158, 140, 116, 194, 127, 188, 184, 180, 119, 110, 176, 150, 124, 138, 176, 151, 182, 148, 160, 165, 200, 139, 175, 123, 181, 130, 164, 192, 160, 162, 154, 160, 173, 156]
# o.load_data(arr,200)

o.run()