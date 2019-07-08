
class BinaryHeap():
	def __init__(self, elements, MAXMIN=True):
		self.elements = elements
		self.heapSize = len(self.elements)
		self.arrayLength = len(self.elements)
		self.MAXMIN = MAXMIN # True for max heap and false for min heap

	def __repr__(self):
		ret_str = ""
		ret_str += "final heap array: " + str(self.elements)
		index = 0
		curr_level_final_index = 2*index
		level = 0
		while(index < self.heapSize):
			ret_str += "\nlevel " + str(level) + " elements:\n"

			for current_index in range(index, min(curr_level_final_index+1, self.heapSize)):
				ret_str += str(self.elements[current_index]) + ', '

			index = curr_level_final_index+1
			curr_level_final_index = 2*index
			level += 1

		return ret_str

	def leftChild(self,index):
		return (index << 1) + 1

	def rightChild(self,index):
		return (index << 1) + 2

	def parent(self,index):
		return ((index+1) >>> 1) -1

	def swap(self,index1, index2):
		tempSwap = self.elements[index1]
		self.elements[index1] = self.elements[index2]
		self.elements[index2] = tempSwap

	def maxHeapify(self,index):
		lchild_index = self.leftChild(index)
		rchild_index = self.rightChild(index)

		if lchild_index < self.heapSize and self.elements[lchild_index] > self.elements[index]:
			largest = lchild_index
		else:
			largest = index

		if rchild_index < self.heapSize and self.elements[rchild_index] > self.elements[largest]:
			largest = rchild_index

		if largest != index:
			self.swap(largest, index)
			self.maxHeapify(largest)

	def minHeapify(self,index):
		lchild_index = self.leftChild(index)
		rchild_index = self.rightChild(index)

		if lchild_index < self.heapSize and self.elements[lchild_index] < self.elements[index]:
			smallest = lchild_index
		else:
			smallest = index

		if rchild_index < self.heapSize and self.elements[rchild_index] < self.elements[smallest]:
			smallest = rchild_index

		if smallest != index:
			self.swap(smallest, index)
			self.minHeapify(smallest)

	def heapify(self,index):
		if self.MAXMIN == True:
			self.maxHeapify(index)
		else:
			self.minHeapify(index)

	def buildHeap(self):
		for index in range((self.heapSize//2), -1, -1):
			self.heapify(index)

	def insert(self, val):

		def comparison_index(index, parent_index):
			if self.MAXMIN == True:
				if self.elements[parent_index] < self.elements[index]:
					return parent_index
				else:
					return index
			else:
				if self.elements[parent_index] > self.elements[index]:
					return parent_index
				else:
					return index

		self.elements.append(val)
		self.arrayLength += 1
		self.heapSize += 1

		index = self.arrayLength-1
		while(index > 0):
			parent_index = self.parent(index)
			index = comparison_index(index, parent_index)
			if index != parent_index:
				self.swap(index, parent_index)
				index = parent_index
			else:
				break

	def delete(self, index):
		self.swap(index, self.heapSize-1)
		self.elements.pop(self.arrayLength-1)
		self.heapSize -= 1
		self.arrayLength -= 1
		self.heapify(index)

	def HeapSort(self):
		self.buildHeap()

		sortedArray = []

		for it in range(self.arrayLength, 1, -1):
			sortedArray.append(self.elements[0])
			self.swap(0, self.heapSize-1)
			self.heapSize -= 1
			self.heapify(0)

		self.heapSize = self.arrayLength

		return sortedArray

if __name__ == '__main__':
	# array_elems = [16,4,10,14,7,9,3,2,8,1,6,2,4,8,21]
	array_elems = [4,50,7,55,90,87]

	heap = BinaryHeap(array_elems,False)
	heap.buildHeap()
	print(repr(heap))
	# print("sortedArray: ", heap.HeapSort())

	heap.insert(2)
	print(repr(heap))
	heap.delete(0)
	print(repr(heap))

