from matmul import *
from unittest import TestCase

class TestMatmul(TestCase):
    def test_matmulWithThreeLoop(self):
        A = np.array([[1, 2], [3, 4], [5, 6]])
        B = np.array([[1, 2, 3], [4, 5, 6]])
        C = matmulWithThreeLoop(A, B)
        self.assertTrue(np.array_equal(C, np.array([[9, 12, 15], [19, 26, 33], [29, 40, 51]])))

    def test_matmulWithInnerProduct(self):
        A = np.array([[1, 2], [3, 4], [5, 6]])
        B = np.array([[1, 2, 3], [4, 5, 6]])
        C = matmulWithInnerProduct(A, B)
        self.assertTrue(np.array_equal(C, np.array([[9, 12, 15], [19, 26, 33], [29, 40, 51]])))

    def test_MatmulWithOuterProduct(self):
        A = np.array([1, 2, 3])
        B = np.array([4, 5, 6])
        C = outerProduct(A, B)
        self.assertTrue(np.array_equal(C, np.array([[4, 5, 6], [8, 10, 12], [12, 15, 18]])))



if __name__ == '__main__':
    from unittest import main
    main()