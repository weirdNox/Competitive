def base10toN(num,n):
    num_rep={0:'0',
             1:'1',
             2:'2',
             3:'3',
             4:'4',
             5:'5',
             6:'6',
             7:'7',
             8:'8',
             9:'9',
             10:'a',
             11:'b',
             12:'c',
             13:'d',
             14:'e',
             15:'f',
             16:'g',
             17:'h',
             18:'i',
             19:'j',
             20:'k',
             21:'l',
             22:'m',
             23:'n',
             24:'o',
             25:'p',
             26:'q',
             27:'r',
             28:'s',
             29:'t',
             30:'u',
             31:'v',
             32:'w',
             33:'x',
             34:'y',
             35:'z'}
    new_num_string=''
    current=num
    while current!=0:
        remainder=current%n
        if remainder < 36:
            remainder_string=num_rep[remainder]
        elif remainder >= 36:
            remainder_string='('+str(remainder)+')'
        else:
            remainder_string=str(remainder)
        new_num_string=remainder_string+new_num_string
        current=current/n
    return new_num_string

def balance(numString):
    i = len(numString) - 1
    carry = 0
    dictionary = []

    while i >= 0:
        digit = int(numString[i]) + carry

        if digit == 0:
            dictionary.append("-")
            carry = 0

        elif digit == 1:
            dictionary.append("R")
            carry = 0

        elif digit == 2:
            dictionary.append("L")
            carry = 1

        else:
            dictionary.append("-")
            carry = 1

        i -= 1

    if carry == 1:
        dictionary.append("R")

    return dictionary

def answer(n):
    return balance(base10toN(n, 3))
