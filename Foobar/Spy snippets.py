def removeUnnecessaryWords(searchList, searchTerms):
	while True:
		first = searchList[0]
		del searchList[0]

		if set(searchTerms) <= set(searchList):
			continue

		searchList.insert(0, first)
		break

def answer(document, searchTerms):
	searchList = []
	end = 0

	documentWords = document.split()

	while True:
		searchList.append(documentWords[end])
		if set(searchTerms) <= set(searchList):
			break
		end += 1

	removeUnnecessaryWords(searchList, searchTerms)
	chosenList = list(searchList)

	end += 1
	while end < len(documentWords):
		searchList.append(documentWords[end])
		if searchList[-1] == searchList[0]:
			removeUnnecessaryWords(searchList, searchTerms)
			if len(searchList) < len(chosenList):
				chosenList = list(searchList)

		end += 1

	return ' '.join(chosenList)

print answer("world there hello hello where world", ["hello", "world"])
print answer("many google employees can program", ["google", "program"])
print answer("a b c d a", ["a", "c", "d"])


"""
BRUTEFORCE - TOO SLOW
def combinations(rest, prefix = [], result = []):
    if rest:
        first = rest.pop()
        for item in first:
            prefix.append(item)
            combinations(rest, prefix, result)
            prefix.pop()
        rest.append(first)
    else:
        result.append(list(reversed(prefix)))
    return result

def getTermsIndexes(document, searchTerms):
    termIndexes = []

    for i in range(len(searchTerms)):
        lastIndex = 0
        done = False
        termLength = len(searchTerms[i])

        indexList = []

        while not done:
            index = document.find(searchTerms[i], lastIndex)
            if index == -1:
                done = True
            elif (index-1 == -1 or document[index-1] == " ") and (index+termLength >= len(document) or document[index+termLength] == " "):
                indexList.append(index)

            lastIndex = index + 1

        termIndexes.append(indexList)

    return termIndexes

def getWordCount(document, combination):
    words = document[combination[0]:combination[1]+1].count(" ") + 1
    
    return words

def getFullWords(document, combination):
    end = combination[1]

    while True:
        if end+1 >= len(document) or document[end+1] == " ":
            end += 1
            break
        end += 1

    return document[combination[0]:end]

def answer(document, searchTerms):
    termIndexes = getTermsIndexes(document, searchTerms)
    allCombinations = combinations(termIndexes)

    for i in range(len(allCombinations)):
        combination = allCombinations[i]
        combination = [min(combination), max(combination)]
        allCombinations[i] = combination

    allCombinations = sorted(allCombinations, key=lambda x: x[0])

    selectedCombination = []
    selectedWordCount = 0
    for i in range(len(allCombinations)):
        wordCount = getWordCount(document, allCombinations[i])
        if (not selectedWordCount==0) and wordCount >= selectedWordCount:
            continue
        
        selectedCombination = allCombinations[i]
        selectedWordCount = wordCount

    return getFullWords(document, selectedCombination)
"""