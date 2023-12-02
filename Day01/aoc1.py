import sys

argc = len(sys.argv)

if (argc != 2):
    print("Invalid number of arguments!\nUsage: python3 aoc1 input_path")
    exit(1)

try:
    input = open(sys.argv[1])
except FileNotFoundError:
    print(sys.argv[1], ": No such file!")
    exit(2)
except PermissionError:
    print(sys.argv[1], " : Invalid persmission!")
    exit(3)
    
lines = input.readlines()
digit_list = ['one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']

result = 0
for line in lines:
    f = 0
    l = len(line)
    f_int = 0
    l_int = 0
    while line[f:f+1].isdigit() == False and f < len(line):
        f += 1
    while line[l:l+1].isdigit() == False and l >= 0:
        l -= 1
    for digit in digit_list:
        if line.find(digit) < f and line.find(digit) != -1:
            f = line.find(digit)
            f_int = digit_list.index(digit) + 1
        if line.rfind(digit) > l and line.rfind(digit) != -1:
            l = line.rfind(digit)
            l_int = digit_list.index(digit) + 1
    if f_int == 0:
        f_int = int(line[f])
    if l_int == 0:
        l_int = int(line[l])
    result += f_int * 10 + l_int

print(result)
exit(0)
