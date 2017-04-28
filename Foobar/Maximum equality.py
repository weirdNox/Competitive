def answer(x):
    numberOfRabbits = 0
    i = 0
    while i < len(x):
        numberOfRabbits += x[i]
        i += 1

    remainderRabbits =  numberOfRabbits % len(x)

    if remainderRabbits != 0:
        return len(x) - 1
    
    return len(x)

"""
NOT CORRECT - UNIFORM DISTRIBUTION
def answer(x):
    numberOfRabbits = 0
    i = 0
    while i < len(x):
        numberOfRabbits += x[i]
        i += 1

    remainderRabbits =  numberOfRabbits % len(x)

	equalByLowNumber = len(x) - remainderRabbits;
    equalByHighNumber = remainderRabbits;
    
    if equalByLowNumber >= equalByHighNumber:
        returnValue = equalByLowNumber
    else:
        returnValue = equalByHighNumber
    
    return len(x)
"""

"""
NOT CORRECT - UNIFORM DISTRIBUTION BRUTEFORCE
def answer(x):
    while True:
        lowIndex = x.index(min(x))
        highIndex = x.index(max(x))

        if x[highIndex] - x[lowIndex] <= 1:
            break
        
        x[lowIndex] += 1
        x[highIndex] -= 1

    return  x.count(max(set(x), key=x.count))

"""
