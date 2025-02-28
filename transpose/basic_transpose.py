import numpy as np

def dump_array(arr, dim):
    if dim == 2:
        for row in range(arr.shape[0]):
            for col in range(arr.shape[1]):
                # 使用固定宽度格式化，确保对齐
                print(f"({row:2d},{col:2d})@{arr[row,col]:4d}", end=' | ')
            print()  # 每行结束换行
    elif dim == 3:
        for row in range(arr.shape[0]):
            for col in range(arr.shape[1]):
                for ch in range(arr.shape[2]):
                    c = col * arr.shape[2] + ch
                    # 修正3维数组的打印格式deepseek acceleratortr
                    print(f"({row:2d},{c:2d})@{arr[row,col,ch]:4d}", end=' | ')
                print()

def mk2k1mk0(arr, K0):
    M = arr.shape[0]
    K = arr.shape[1]
    K1 = (K + K0 - 1) // K0
    # Pad the array if K is not divisible by K0
    pad_width = K1 * K0 - K
    if pad_width > 0:
        arr = np.pad(arr, ((0, 0), (0, pad_width)), mode='constant')
    arr2 = arr.reshape(M, K1, K0)
    return arr2.transpose(1,0,2)

if __name__ == '__main__':
    arr = np.arange(49).reshape(7, 7)
    dump_array(arr, 2)
    print()
    arr2 = mk2k1mk0(arr, 4)
    dump_array(arr2, 3)

