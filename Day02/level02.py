import sys

argc = len(sys.argv)

if (argc != 2):
    print("Invalid number of arguments!\nUsage: python3 level01.py input_path")
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
games = []
for line in lines:
	games.append(line.strip(" Game0123456789").strip(': \n').split('; '))

sum = 0

for game in games:
	red_min = 0
	green_min = 0
	blue_min = 0
	for pull in game:
		colors = pull.split(', ')
		for color in colors:
			if "g" in color and int(color.split()[0]) > green_min:
				green_min = int(color.split()[0])
			if "b" in color and int(color.split()[0]) > blue_min:
				blue_min = int(color.split()[0])
			if "d" in color and int(color.split()[0]) > red_min:
				red_min = int(color.split()[0])
	sum += red_min * green_min * blue_min

print(sum)
exit(0)
