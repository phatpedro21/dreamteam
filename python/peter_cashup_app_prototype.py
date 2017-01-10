#This is a prototype cashing up app. It askes a user to input how many of each value of coin or note they have, and the
# beggining float. It will then print a 'receipt' of takings, and tell the user how much money has been counted 
# and the takings minus the float

#Note to nathan, any line starting with a '#' is a comment, and does nothing in the program, they just give info
#about the program :)

#First I am defining some functions to perform repeated tasks

#This function formats integers into pounds and pence format (e.g. 10 = 10p and 110 = £1.10)
def int_to_pounds(value):
	converted_string = ""
	#Assuming you can see what i've done here, NEVER do it like this, I have no idea what I was doing
	#And I'm 99% sure this is a terrible way of doing what I was aiming to do
	if value < 100:
		converted_string = '%i p' % value
	else:
		if value % 100:
			pence = str(value % 100)
		else:
			pence = '00'
		pounds = (value - value%100) / 100
		
		converted_string = '£%i.%s' % (pounds, pence)
		
	return converted_string	
	

currency_values = [1,2,5,10,20,50,100,200,500,1000]
amounts_of_coins = []

for value in currency_values:	
	amounts_of_coins.append(int(input("Please enter the number of " + int_to_pounds(value) + " coins you have: ")))

total_cash = 0
for index, value in enumerate(currency_values):
	total_cash += amounts_of_coins[index] * value

print("Total cash amount: " + int_to_pounds(total_cash))

float = int(input("Please enter the amount of float you began with (in pence e.g. 2050 = £20.50): "))

print ("Your total takings are: " + int_to_pounds(total_cash - float))
	
	
	
		
	