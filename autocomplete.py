class Node:
	def __init__(self, value, parent):
		self.value = value
		self.children = {}
		self.parent = parent
		self.isWord = False

class Autocomplete:
	def __init__(self, list_words):
		self.list_words = list_words
		self.trie_root = Node(None, None)
		self.build_trie()

	def build_trie(self):
		for word in list_words:
			word = word.lower()
			parent = self.trie_root
			for i in range(len(word)):
				if word[i] not in parent.children:
					parent.children[word[i]] = Node(word[i], parent)
				parent = parent.children[word[i]]
			parent.isWord = True

	def find_autocomplete(self, ip):
		if ip == None or ip[0] not in self.trie_root.children:
			return None

		parent = self.trie_root

		for it in range(len(ip)):
			if ip[it] not in parent.children:
				return None
			else:
				parent = parent.children[ip[it]]

		auto_list = self.get_autocomplete_list(parent)

		for it in range(len(auto_list)):
			auto_list[it] = ip+auto_list[it]

		if parent.isWord == True:
			auto_list.append(ip)

		return auto_list

	def get_autocomplete_list(self, parent):
		auto_list = []
		stack = []
		word_leaf_nodes = []

		for key in parent.children:
			stack.append(parent.children[key])

		while stack:
			elem = stack.pop()
			if not elem.children:
				word_leaf_nodes.append(elem)
			else:
				if elem.isWord == True:
					word_leaf_nodes.append(elem)			
				for key in elem.children:
					stack.append(elem.children[key])

		for node in word_leaf_nodes:
			word = ""
			while node != parent:
				word = node.value+word
				node = node.parent
			auto_list.append(word)

		return auto_list


if __name__ =="__main__":
	list_words = ["abc", "acd", "bcd", "def", "a", "aba"]
	auto_complete = Autocomplete(list_words)

	# if input is taken from user need to loop over entire tree for
	# generating all the words in the dictionary
	auto_list = auto_complete.find_autocomplete("a")

	for word in auto_list:
		print(word)