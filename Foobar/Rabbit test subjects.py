def answer(y, x):
    sortedY = sorted(y)
    sortedX = sorted(x)
    
    rate = (float(sortedX[0])-sortedY[0])/float(sortedX[0])
    
    return int(round(rate*100, 0))