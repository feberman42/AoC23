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

red_max = 12
green_max = 13
blue_max = 14
sum = 0

for game in games:
	possible = True
	for pull in game:
		colors = pull.split(', ')
		for color in colors:
			if "g" in color and int(color.split()[0]) > green_max:
				possible = False
			if "b" in color and int(color.split()[0]) > blue_max:
				possible = False
			if "d" in color and int(color.split()[0]) > red_max:
				possible = False
	if possible:
		sum += games.index(game) + 1

print(sum)
exit(0)
