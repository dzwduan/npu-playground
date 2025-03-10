
import numpy as np

layer = {
    'layer_1' : 5,
    'layer_2' : 4,
    'layer_3' : 8,
    # 'layer_4' : 6,
}

mem_space = {
    'layer_1' : np.zeros(layer['layer_1'], dtype=int),
	'layer_2' : np.zeros(layer['layer_2'], dtype=int),
	'layer_3' : np.zeros(layer['layer_3'], dtype=int),
	# 'layer_4' : np.zeros(layer['layer_4'], dtype=int),
}

def init_mem_space(mem_space):
	mem_space['layer_1'][0] = 0

	mem_space['layer_2'][0] = 4
	mem_space['layer_2'][1] = -1
	mem_space['layer_2'][2] = -1
	mem_space['layer_2'][3] = -1

	mem_space['layer_3'][0] = 2
	mem_space['layer_3'][1] = -1
	mem_space['layer_3'][3] = 0

	# mem_space['layer_4'][0] = 0

def alloc_mem_space(mem_space, layer_name, size):
	"""
	从mem_space中分配size大小的空间，返回分配的起始地址
	"""
	if layer_name not in layer:
		return -1
	idx = 0
	ret_addr = -1
	can_alloc = False
	space_size = mem_space[layer_name].size
	print(space_size)
	# idx遍历一个layer所占的空间
	while idx < space_size and ret_addr == -1:
		if mem_space[layer_name][idx] == 0:
			can_alloc = True
			# 从idx开始，尝试分配size大小的空间
			for i in range(1, size):
				# 检查是否越界
				if idx + i >= space_size:
					can_alloc = False
					idx = space_size 
					break
				# 跳过已分配的空间
				if mem_space[layer_name][idx + i] != 0:
					can_alloc = False
					idx = idx + i + mem_space[layer_name][idx + i]
					break
			if can_alloc:
				mem_space[layer_name][idx] = size
				for i in range(1, size):
					mem_space[layer_name][idx + i] = -1
				ret_addr = idx
				idx = space_size # 仅用于退出while循环
		else:
			idx = idx + mem_space[layer_name][idx]
	return ret_addr

		

def test_alloc_memspace(mem_space):
	init_mem_space(mem_space)
	ret = alloc_mem_space(mem_space, 'layer_2', 1)
	assert ret == -1, "Test failed"
	print("Test passed")

if __name__ == "__main__":
	test_alloc_memspace(mem_space)