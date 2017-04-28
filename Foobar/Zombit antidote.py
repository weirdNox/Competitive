def answer(meetings):
    sortedMeetings = []
    possibleMeetings = []
    
    sortedMeetings = sorted(meetings, key=lambda x:x[1])
    possibleMeetings.append(0)
    
    for i in range(1, len(sortedMeetings)):
        if sortedMeetings[i][0] >= sortedMeetings[possibleMeetings[len(possibleMeetings)-1]][1]:
            possibleMeetings.append(i)
    print possibleMeetings
    return len(possibleMeetings)