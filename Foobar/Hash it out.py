def decodeNumber(number, prevDecodedNumber):
	while number < 32895 and (number ^ prevDecodedNumber) % 129 > 0:
		number += 256

	return (number ^ prevDecodedNumber) / 129

def answer(digest):
	message = []

	for i in range(len(digest)):
		if i == 0:
			message.append(decodeNumber(digest[i], 0))

		else:
			message.append(decodeNumber(digest[i], message[i-1]))
		

	return message

print answer([0, 129, 3, 129, 7, 129, 3, 129, 15, 129, 3, 129, 7, 129, 3, 129])
