#prompt user for change input
while True:
    try:
        user_input = input('How much change is owed?: ')
        user_input = float(user_input)
        if user_input>0:
            break
    except ValueError:
        print('Please input a positive numeric value.')
        
#convert to cents
change_owed = int(user_input*100)

#determine number of coins
coin_count = 0
coin_count = int(coin_count)
coin_count += int(change_owed/25)
change_owed = int(change_owed%25)
coin_count += int(change_owed/10)
change_owed = int(change_owed%10)
coin_count += int(change_owed/5)
change_owed = int(change_owed%5)
coin_count += change_owed

#print final coin count
print(coin_count)