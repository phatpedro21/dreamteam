class thing:
	number = 1
	added = ''
	def __add__(self, y):
		self.added = y
		print(y)
	def get_added():
		print(added)
		
		
		
thing1 = thing()
thing1 + 4
thing1 + "elephant"

thing1.get_added
	

	
	