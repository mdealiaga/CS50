import sys

k = 0

#ensures only one numeric digit is entered
if len(sys.argv) < 2:
    print('Enter at least one number')
    sys.exit()
elif len(sys.argv) > 2:
    print('Enter only one number')
    sys.exit()
else:
    try:
        k = int(sys.argv[1])
    except:
        print('Please input a number')

#prompts userfor plaintext
plaintext = input('plaintext: ')

#switches ascii characters by k amount, outputs cythertext
print('cythertext: ', end='')
for i in range(len(plaintext)):
    if plaintext[i].isupper():
        print(chr(((ord(plaintext[i])-65+k)%26)+65), end='')
    elif plaintext[i].islower():
        print(chr(((ord(plaintext[i])-97+k)%26)+97), end='')
    else:
        print(plaintext[i], end='')
print('')