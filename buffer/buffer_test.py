from unittest import TestCase, main
import numpy as np

from Buffer import *

class TestBuffer(TestCase):
    def test_buffer(self):
        buffer = Buffer(4, 2, 2)
       

        # Test the buffer address calculation
        self.assertEqual(buffer.get_addr(0, 0), 0)
        self.assertEqual(buffer.get_addr(0, 1), 2)
        self.assertEqual(buffer.get_addr(1, 0), 4)
        self.assertEqual(buffer.get_addr(1, 1), 6)

        # Test the buffer read and write
        # if write , we need write N bank one time
        buffer.write([0, 2], np.array([[1, 2], [3, 4]]), np.array([[1, 1], [0x0f, 0x00]]))
        print(buffer)

if __name__ == "__main__":
    main()