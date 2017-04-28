import math

# Memoization optimization
class Memoize:
	def __init__(self, f):
		self.f = f
		self.memo = {}

	def __call__(self, *args):
		if not args in self.memo:
			self.memo[args] = self.f(*args)
		return self.memo[args]

# Calculate the number of combinations of n elements in groups of k elements
def combinations(n, k):
	if k > n:
		return 0
	return math.factorial(n)/(math.factorial(n-k)*math.factorial(k))

# Number of ways to arrange m rabbits, so that k are visible only from
# one side.
#
# * If m == k, there is only one way: lined up with increasing size. Return 1
# * If k == 1, the tallest rabbit must be on the first place. So, the only thing
# we can change is the order of the smaller rabbits. Return (m-1)!
# * If m > k and k > 1, the tallest person stays at i, where i is member of
# [k, m]. For each i, there are C(m-1, i-1) ways to choose who will go
# behind and in front of the tallest. For each of those, there are (m-i)! ways
# to arrange who is behind and waysToArrangeFromOneSide(i-1, k-1) to arrange
# who is in front. Return the summation
# * Else, it is impossible. Return 0
def waysToArrangeFromOneSide(m, k):
	if m == k:
		return 1

	if k == 1:
		return math.factorial(m-1)

	if m > k and k > 1:
		i = k
		summation = 0
		while i <= m:
			summation += combinations(m-1, i-1) * math.factorial(m-i) * \
							waysToArrangeFromOneSide(i-1, k-1)
			i += 1

		return summation

	return 0

# As waysToArrangeFromOneSide is recursive, this saves us a LOT of 
# time (sometimes, around 85% of the calls are cached!!)
waysToArrangeFromOneSide = Memoize(waysToArrangeFromOneSide)


# Number of ways to arrange n rabbits, so that x are visible from the west
# and y are visible from the east.
#
# j is the position of the tallest rabbit, and it is member of [x, n-y+1], 
# because it needs to let at least x-1 smaller rabbits to the west and y-1 
# smaller rabbits to the east.
# For each j, I split the line in two (with center in j), get the number of
# ways to arrange the rabbits of each side (with waysToArrangeFromOneSide), 
# and multiply them. For each of these choices, there are C(n-1, j-1) ways to 
# choose which rabbits will be to the east of j and to the west.
# Then I add it to the summation variable, pass to the next j, and 
# in the end return the summation in a string.
def answer(x, y, n):
	j = x
	summation = 0
	while j <= n - y + 1:
		summation += combinations(n-1, j-1) * \
		waysToArrangeFromOneSide(j-1, x-1) * waysToArrangeFromOneSide(n-j, y-1)
		j += 1

	return str(summation)
