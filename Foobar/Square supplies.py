import math

def answer(n):
	root = 1;
	numberOfTimes = 0

	while True:
		if math.pow(root+1, 2) <= n:
			root += 1

		else:
			break

	while root > 0:
		if math.pow(root, 2) <= n:
			n -= math.pow(root, 2)
			numberOfTimes += 1
			continue

		root -= 1

	return numberOfTimes