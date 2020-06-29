import random
import sys

if __name__=="__main__":
    numbers = [(x, y) for x in range(1, int(sys.argv[1])) for y in range(x+1, int(sys.argv[1]) + 1)]
    random.shuffle(numbers)
    print(sys.argv[1], sys.argv[2])
    for x in range(1, int(sys.argv[2])):
        print(numbers[x][0], numbers[x][1], random.randint(1, 1000))
