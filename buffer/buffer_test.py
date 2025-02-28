from unittest import TestCase, main
import numpy as np

from Buffer import *

class TestBuffer(TestCase):
    def test_buffer(self):
        buffer = Buffer(2, 4, 2)
        self.assertEqual(buffer.N, 2)
        self.assertEqual(buffer.M, 4)
        self.assertEqual(buffer.K, 2)
        self.assertTrue(np.array_equal(buffer.buffer, np.zeros((4, 2, 2), dtype=np.uint8)))

        print(buffer)

        addr = buffer.get_addr(1, 1)
        self.assertEqual(addr, 6)

        data = buffer.read(6)
        print(data)
        self.assertTrue(np.array_equal(data, np.zeros(2, dtype=np.uint8)))

        buffer.write([6, 8], np.array([1, 31]), [0x00ff, 0b11])
        
        
if __name__ == "__main__":
    main()