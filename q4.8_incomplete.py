from enum import Enum

class TraverseOrder(Enum):
	INORDER=0
	PREORDER=1
	POSTORDER=2

class Node(object):
	"""docstring for Node"""
	def __init__(self, data):
		super(Node, self).__init__()
		self.data = data
		self.left=None
		self.right=None
		self.level=-1

	def __repr__(self):
		ret=""
		if self.right is not None:
			ret += repr(self.right)
		ret += "    "*self.level + repr(self.data) +'\n'
		if self.left is not None:
			ret += repr(self.left)
		return ret


def build_tree(inorder_list, preorder_list, left_index, right_index, preorder_index, level=0):
	if right_index < left_index:
		return None
	if preorder_index[0] >= len(preorder_list): return None

	n=Node(preorder_list[preorder_index[0]])
	n.level=level

	inorder_search_index = inorder_list.index(n.data)
	preorder_index[0] += 1

	if right_index == left_index:
		return n	

	n.left = build_tree(inorder_list, preorder_list, left_index, inorder_search_index-1, preorder_index, level+1)
	n.right = build_tree(inorder_list, preorder_list, inorder_search_index+1, right_index, preorder_index, level+1)

	return n

# def find_first_common_ancestor(head, node1_val, node2_val, find_counter):
	
# 	if head == node1_val or head == node2_val:
# 		find_counter[0] += 1

# 	if find_counter[0] == 2:
# 		return head.data



# 	if find_counter[0] == 2:
# 		return 



if __name__=="__main__":

	inorder_list = [i+1 for i in range(15)]
	# preorder_list = [8,4,2,1,3,6,5,7,12,10,9,11,14,13,15]
	preorder_list = [10,5,3,3,-2,2,1,-3,11]
	inorder_list = [3,3,-2,5,2,1,10,-3,11]
	# preorder_list = [3,1,2]

	preorder_index = [0]
	head = build_tree(inorder_list, preorder_list, 0, len(inorder_list)-1, preorder_index)
	print_tree(head, TraverseOrder.INORDER)

	print(repr(head))

	# node1_val = 2, node2_val = 10

	# if node1_val==head.data or node2_val==head.data:
	# 	print("one of the node is the root so common ancestor doesnt exist")
	# 	exit()

	# find_counter=[0]
	# anc = find_first_common_ancestor(2,10,find_counter)
	# print("first common ancestor: ", anc)
