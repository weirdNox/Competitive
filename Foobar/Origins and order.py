def testDate(date):
    numberOfDaysPerMonth = {
        1:31,
        2:28,
        3:31,
        4:30,
        5:31,
        6:30,
        7:31,
        8:31,
        9:30,
        10:31,
        11:30,
        12:31
    }
    
    # Test month
    if date[0] > 12:
        return False
    
    # Test day
    if date[1] > numberOfDaysPerMonth[date[0]]:
        return False
    
    return True

def answer(x, y, z):
    possibleDates = [[x,y,z], [x,z,y], [y,z,x], [y,x,z], [z,x,y], [z,y,x]]
    correctDates = []
    
    for i in range(6):
        date = possibleDates[i]
        if testDate(date) and not date in correctDates:
            correctDates.append(date)

    if len(correctDates) == 1:
        return str(correctDates[0][0]).zfill(2)+"/"+str(correctDates[0][1]).zfill(2)+"/"+str(correctDates[0][2]).zfill(2)
    else:
        return "Ambiguous"
