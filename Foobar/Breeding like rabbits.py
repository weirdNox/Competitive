# I was doing this for fun, but from now on I'll comment things
# correctly as this may be read by someone else.

# Memoization to speed up recursive function.
zombitsMemo = {0: 1, 1: 1, 2: 2}
def getNumberOfZombits(time): # Implementation of the function R
    if not time in zombitsMemo:
        if time % 2 == 0: # is even
            newTime = time/2
            zombitsMemo[time] = getNumberOfZombits(newTime) + getNumberOfZombits(newTime+1) + newTime

        else: # is odd
            newTime = time/2 # integer, so rounds down
            zombitsMemo[time] = getNumberOfZombits(newTime-1) + getNumberOfZombits(newTime) + 1

    return zombitsMemo[time]


def guessInput(number):
    low, high = 0, number
    possibleInput = 0

    print "Trying even numbers"
    while True: # Binary search algorithm-like only for even numbers because
                # they get bigger outputs fisrt, so we try those before
        mid = low + (high - low) / 2
        
        if mid % 2 != 0:
            mid -= 1  # make even if odd

        print "Trying R("+str(mid)+")"
        midOutput = getNumberOfZombits(mid)
        
        if midOutput == number:
            possibleInput = mid
            break
        
        elif midOutput < number:
            low = mid + 1
        
        else:
            high = mid - 1
        
        if low + 2 > high: # Get out of here if solution not found
            break
    
    low, high = low, number
    print "Trying odd numbers"
    while True: # Binary search algorithm-like, this time for odd numbers
        mid = low + (high - low) / 2
        
        if mid % 2 == 0:
            mid -= 1  # make odd if even
        
        print "Trying R("+str(mid)+")"
        midOutput = getNumberOfZombits(mid)
        
        if midOutput == number:
            possibleInput = mid
            break
        
        elif midOutput < number:
            low = mid + 1
        
        else:
            high = mid - 1
            
        if low + 2 > high: # Get out of here if solution not found
            break
            
    if possibleInput == 0: # If there is no solution found, return "None"
        return "None"
        
    return possibleInput # Or return possibleInput

def answer(str_S):
    number = int(str_S) # Parse number to int or long
    return guessInput(number)


# Helper for analyzing with Plotly
def createPlot(min = 0, max = 500):
    for i in range(max + 1):
        print str(i) + "," + str(getNumberOfZombits(i))
