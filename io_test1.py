import random
from collections import defaultdict

def get_random_index(length):
	return int(random.random() * length)	

def string_shuffle(s):
	str_len = len(s)
	indices = [i for i in range(len(s))]
	shuffle_indices = []

	while indices:
		random_index = get_random_index(len(indices))
		shuffle_indices.append(indices[random_index])
		indices.pop(random_index)

	ret_str = ""
	for it in shuffle_indices:
		ret_str += s[it]
	return ret_str

import json
stats = defaultdict(lambda:defaultdict(int))
for _ in range(5000):
	sstring = string_shuffle('abcdef')
	for j, letter in enumerate(sstring):
		stats[letter][j] += 1

print(json.dumps(stats, indent = 4))
