def getColumnVector(matrix):
    columnVector = []

    for row in matrix:
        for item in row:
            columnVector.append([item])

    return columnVector

def getToggleMatrix(m):
    toggleMatrix = [[0 for column in range(m**2)] for row in range(m**2)]

    row = 0
    column = 0

    for n in range(len(toggleMatrix)):
        for i in range(m):
            toggleMatrix[n][i*m + column] = 1

        for j in range(m):
            toggleMatrix[n][row * m + j] = 1
        
        column += 1
        if column == m:
            column = 0
            row += 1            

    return toggleMatrix

def subtractRows(matrix, i, k):
    rowI = matrix[i]
    rowK = matrix[k]

    for a in range(len(rowI)):
        rowK[a] = rowK[a] ^ rowI[a]


def a(matrix):
    matrix = list(matrix)

    n = len(matrix)
    newMatrix = []
    rowsLeft = range(n)

    for column in range(n):
        rowsWithNonZero = [row for row in rowsLeft if matrix[row][column] != 0]
        if rowsWithNonZero != []:
            pivot = rowsWithNonZero[0]
            rowsLeft.remove(pivot)
            newMatrix.append(matrix[pivot])
            for row in rowsWithNonZero[1:]:
                subtractRows(matrix, pivot, row)

    if rowsLeft != []:
        return False # Singular

    solution = [0 for i in range(n)]
    for i in range(n-1, -1, -1):
        solution[i] = newMatrix[i][n]
        for k in range(i-1, -1, -1):
            newMatrix[k][n] = (newMatrix[k][n]-newMatrix[k][i]*solution[i]) % 2

    return solution

def pprint(A):
    n = len(A)
    for i in range(0, n):
        line = ""
        for j in range(0, n+1):
            line += str(A[i][j]) + "\t"
            if j == n-1:
                line += "| "
        print(line)
    print("")
    
def solveGaussJordan(matrix):
    pprint(matrix)
    n = len(matrix)
    
    for col in range(n):
        rowsWithNonZero = [row for row in range(col,n)  if matrix[row][col] != 0]
        if rowsWithNonZero == []:
            return False
        maxRow = rowsWithNonZero[0]
         
        if maxRow != col:
            for tmpCol in range(col, n+1):
                tmp = matrix[maxRow][tmpCol]
                matrix[maxRow][tmpCol] = matrix[col][tmpCol]
                matrix[col][tmpCol] = tmp
            
        for row in range(col+1, n):
            if matrix[row][col] == 1:
                for tmpCol in range(col, n+1):
                    matrix[row][tmpCol] = matrix[row][tmpCol] ^ matrix[col][tmpCol]
                    
    solution = [0 for i in range(n)]
    for row in range(n-1, -1, -1):
        solution[row] = matrix[row][n]
        for aboveRows in range(row-1, -1, -1):
            matrix[aboveRows][n] = matrix[aboveRows][n] ^ (matrix[aboveRows][row] * solution[row])
            
    return solution
    
def gauss(A):
    n = len(A)

    for i in range(0, n):
        # Search for maximum in this column
        maxEl = abs(A[i][i])
        maxRow = i
        for k in range(i+1, n):
            if abs(A[k][i]) > maxEl:
                maxEl = abs(A[k][i])
                maxRow = k

        # Swap maximum row with current row (column by column)
        for k in range(i, n+1):
            tmp = A[maxRow][k]
            A[maxRow][k] = A[i][k]
            A[i][k] = tmp

        # Make all rows below this one 0 in current column
        for k in range(i+1, n):
            c = -A[k][i]/A[i][i]
            for j in range(i, n+1):
                if i == j:
                    A[k][j] = 0
                else:
                    A[k][j] += c * A[i][j]

    # Solve equation Ax=b for an upper triangular matrix A
    x = [0 for i in range(n)]
    for i in range(n-1, -1, -1):
        x[i] = A[i][n]/A[i][i]
        for k in range(i-1, -1, -1):
            A[k][n] -= A[k][i] * x[i]
    return x

def answer(matrix):
    m = len(matrix)
    gridVector = getColumnVector(matrix)

    toggleMatrix = getToggleMatrix(m)

    augmentedMatrix = list(toggleMatrix)
    for row in range(len(gridVector)):
        augmentedMatrix[row].append(gridVector[row][0])

    solution = gauss(augmentedMatrix)
    
    if solution == False:
        return -1

    return solution.count(1)

print answer([[0,1,0], [1,1,1], [0,1,0]])
print answer([[1,1], [0,0]])

""" CHECK /u/Bliss86 """



"""
http://martin-thoma.com/solving-linear-equations-with-gaussian-elimination/
http://codingthematrix.com/slides/Gaussian_Elimination.pdf


for c in col label list:
    rows with nonzero = [r for r in rows left if rowlist[r][c] != 0]
        if rows with nonzero != []:
            pivot = rows with nonzero[0]
            rows left.remove(pivot)
            new rowlist.append(rowlist[pivot])
            for r in rows with nonzero[1:]:
                multiplier = rowlist[r][c]/rowlist[pivot][c]
                rowlist[r] -= multiplier * rowlist[pivot]"""

"""
#!/usr/bin/env python
# -*- coding: utf-8 -*-


def pprint(A):
    n = len(A)
    for i in range(0, n):
        line = ""
        for j in range(0, n+1):
            line += str(A[i][j]) + "\t"
            if j == n-1:
                line += "| "
        print(line)
    print("")


def gauss(A):
    n = len(A)

    for i in range(0, n):
        # Search for maximum in this column
        maxEl = abs(A[i][i])
        maxRow = i
        for k in range(i+1, n):
            if abs(A[k][i]) > maxEl:
                maxEl = abs(A[k][i])
                maxRow = k

        # Swap maximum row with current row (column by column)
        for k in range(i, n+1):
            tmp = A[maxRow][k]
            A[maxRow][k] = A[i][k]
            A[i][k] = tmp

        # Make all rows below this one 0 in current column
        for k in range(i+1, n):
            c = -A[k][i]/A[i][i]
            for j in range(i, n+1):
                if i == j:
                    A[k][j] = 0
                else:
                    A[k][j] += c * A[i][j]

    # Solve equation Ax=b for an upper triangular matrix A
    x = [0 for i in range(n)]
    for i in range(n-1, -1, -1):
        x[i] = A[i][n]/A[i][i]
        for k in range(i-1, -1, -1):
            A[k][n] -= A[k][i] * x[i]
    return x


if __name__ == "__main__":
    from fractions import Fraction
    n = input()

    A = [[0 for j in range(n+1)] for i in range(n)]

    # Read input data
    for i in range(0, n):
        line = map(Fraction, raw_input().split(" "))
        for j, el in enumerate(line):
            A[i][j] = el
    raw_input()

    line = raw_input().split(" ")
    lastLine = map(Fraction, line)
    for i in range(0, n):
        A[i][n] = lastLine[i]

    # Print input
    pprint(A)

    # Calculate solution
    x = gauss(A)

    # Print result
    line = "Result:\t"
    for i in range(0, n):
        line += str(x[i]) + "\t"
    print(line)
    """