import fractions

# Returns the number of lattice points (lattice points = P(int, int)) contained
# in the boundary of the triangle given. The formula for the number of lattice 
# points in a segment from (a,b) to (c,d) is |gcd(a-c, b-d)| + 1, including 
# the endpoints. For each side of the triangle, I only count one endpoint, so 
# there's no repetition in counting, therefore the formula becomes |gcd(a-c, b-d)|.
def getLatticePointsInBoundary(vertices):
    inAB = abs(fractions.gcd(vertices[1][0]-vertices[0][0], \
                         vertices[1][1]-vertices[0][1]))

    inBC = abs(fractions.gcd(vertices[1][0]-vertices[2][0], \
                         vertices[1][1]-vertices[2][1]))

    inCA = abs(fractions.gcd(vertices[2][0]-vertices[0][0], \
                         vertices[2][1]-vertices[0][1]))

    return inAB + inBC + inCA


# Returns the area of triangle, using A = |(Ax(By-Cy) + Bx(Cy-Ay) + Cx(Ay-By))/2|
def areaOfTriangle(vertices):
    return abs(vertices[0][0]*(vertices[1][1]-vertices[2][1]) + \
               vertices[1][0]*(vertices[2][1]-vertices[0][1]) + \
               vertices[2][0]*(vertices[0][1]-vertices[1][1])) / 2.0

# Returns the number of lattice points inside the given triangle.
# Uses Pick's Theorem, that states that A = i + b/2 - 1, where A is the area,
# i is the number of lattice points in the interior of the triangle and
# b is the number of lattice points on te boundary of the triangle.
# In order to i, becomes i = A - b/2 + 1
def answer(vertices):
    latticeInPerimeter = getLatticePointsInBoundary(vertices)
    area = areaOfTriangle(vertices)

    latticePointsInTriangle = area - latticeInPerimeter / 2.0 + 1
    return int(latticePointsInTriangle)

print answer([[91207, 89566], [-88690, -83026], [67100, 47194]]) == 1730960165
print answer([[2, 3], [6, 9], [10, 160]]) == 289
print answer([[-1, -1], [1, 0], [0, 1]]) == 1