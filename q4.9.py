class Node:
	def __init__(self, data):
		self.data = data
		self.left = None
		self.right = None
		self.level = 0

	def __repr__(self):
		ret_str = ''

		if self.right is not None:
			ret_str += repr(self.right)

		ret_str += self.level*'    '+str(self.data) + '\n'

		if self.left is not None:
			ret_str += repr(self.left)

		return ret_str

def buildBST(build_array):
	head = None

	for elem in build_array:
		if head == None:
			head = Node(elem)
			head.level = 0
			continue

		temp_head=head

		while(True):
			if elem <= temp_head.data:
				if temp_head.left is None:
					temp_head.left = Node(elem)
					temp_head.left.level = temp_head.level+1
					break
				else:
					temp_head = temp_head.left
			else:
				if temp_head.right is None:
					temp_head.right = Node(elem)
					temp_head.right.level = temp_head.level+1
					break
				else:
					temp_head = temp_head.right
	return head


def prepend_arrays(listOfArrays, prepend_val):
	retArrays = [[]]
	
	for arr in listOfArrays:
		retArrays += [[prepend_val] + arr]

	return retArrays[1:]

def findPossibleArrays(head):
	if head == None:
		return None
	if head.left is None and head.right is None:
		return [[head.data]]
	if head.left is None and head.right is not None: 
		return prepend_arrays(findPossibleArrays(head.right), head.data)
	if head.left is not None and head.right is None: 
		return prepend_arrays(findPossibleArrays(head.left), head.data)

	return getPermutations(findPossibleArrays(head.left), findPossibleArrays(head.right), head.data)

def getPermutations(leftArrays, rightArrays, currentData):

	retArrays = [[]]
	for larr in leftArrays:
		for rarr in rightArrays:
			if len(larr) < len(rarr): 
				retArrays += getPermHelper(larr, rarr)
			else:
				retArrays += getPermHelper(rarr, larr)

	return(prepend_arrays(retArrays[1:], currentData))


def getPermHelper(arr1, arr2):
	if len(arr1) == 1:
		return(getPermHelperExtend(arr1[0], [arr2]))

	else:
		retArrays = getPermHelper(arr1[1:], arr2)
		return(getPermHelperExtend(arr1[0], retArrays, arr1[1]))

def getPermHelperExtend(prepend_val, listOfArrays, contraintVal=None):
	if contraintVal is None:
		contraintVal = prepend_val

	retArrays = [[]]
	for arr in listOfArrays:
		for it in range(len(arr)):
			if it==0:
				retArrays += [[prepend_val] + arr]
			else:
				retArrays += [arr[:it] + [prepend_val] + arr[it:]]

			if arr[it] == contraintVal:
				break

			if it == len(arr)-1:
				retArrays += [arr + [prepend_val]]

	return retArrays[1:]


if __name__=='__main__':

	# build_array = [4,2,6,1,3,5,7]
	# build_array = [2,1,3]
	# build_array = [2,1,4,3,5,0]
	build_array = [8,4,12,2,6,10,14,1,3,5,7,9,11,13,15]


	head = None
	head = buildBST(build_array)
	# print(repr(head))

	possible_arrays = findPossibleArrays(head)

	# print(possible_arrays)
	for arr in possible_arrays:
		print(arr)

