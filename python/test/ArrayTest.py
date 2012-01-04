import sys
import unittest
sys.path.append("../")

from pni.utils import Array

#implementing test fixture
class ArrayTest(unittest.TestCase):
    def setUp(self):
        self.s1 = Shape(3)
        self.s1[0] = 4; self.s1[1] = 5; self.s1[2] = 6

        self.s2 = Shape(2)
        self.s2[0] = 100; self.s2[1] = 1024;


    def tearDown(self):
        pass

    def test_creation(self):
        a = Float64Array()
        a.shape = self.s1

        def test_buffer_assignment(a,b):
            a.buffer = b

        b = Float64Buffer(2)

        self.assertRaises(UserWarning,test_buffer_assignment,a,b)

        b = Float64Buffer(self.s1.size)
        a.buffer = b

        a1 = Float64Array(self.s1,b)

        a2 = Float64Array()
        a2.shape = self.s1
        a2.allocate()

        a2.buffer = Float64Buffer(self.s1.size)

    def test_access(self):
        pass







