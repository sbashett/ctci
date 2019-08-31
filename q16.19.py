
def get_pond_size(matrix, row_index, col_index):
	# print("checking:", row_index, col_index, matrix[row_index][col_index] )
	if row_index >= len(matrix) or row_index < 0 or col_index >= len(matrix[0]) or col_index < 0 or matrix[row_index][col_index] != 0:
		return 0

	else:
		matrix[row_index][col_index] = -1
		return get_pond_size(matrix, row_index, col_index+1) + \
				get_pond_size(matrix, row_index, col_index-1) + \
				get_pond_size(matrix, row_index+1, col_index) + \
				get_pond_size(matrix, row_index-1, col_index) + \
				get_pond_size(matrix, row_index-1, col_index-1) + \
				get_pond_size(matrix, row_index+1, col_index-1) + \
				get_pond_size(matrix, row_index-1, col_index+1) + \
				get_pond_size(matrix, row_index+1, col_index+1) + 1

def get_connected_pond_sizes(matrix):
	if len(matrix) == 0 or len(matrix[0]) == 0:
		return None

	ret_val = []
	
	for row_index in range(len(matrix)):
		for col_index in range(len(matrix[0])):
			if matrix[row_index][col_index] == 0:
				ret_val.append(get_pond_size(matrix, row_index, col_index))

	return ret_val


if __name__ == '__main__':
	matrix = [[0,2,1,0], [0,1,0,1], [1,1,0,1], [0,1,0,1]]

	for it in matrix:
		print(it)

	ret_val = get_connected_pond_sizes(matrix)

	print(ret_val)