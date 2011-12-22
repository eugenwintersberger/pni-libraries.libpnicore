import sys
import unittest
sys.path.append("../")

from pni.utils import Shape
from pni.utils import Index



#implementing test fixture
class ShapeTest(unittest.TestCase):
    def setUp(self):
        self.nx = 100;
        self.ny = 5;
        self.nz = 27;

    def tearDown(self):
        pass

    def test_constructors(self):
        #test default constructor
        s = Shape()
        self.assertTrue(s.rank == 0)
        self.assertTrue(s.size == 0)
        
        s.rank = 2
        s.dim(0,self.nx)
        s.dim(1,self.ny)
        self.assertTrue(s.dim(0) == self.nx)
        self.assertTrue(s.dim(1) == self.ny)
        self.assertTrue(s.size == self.nx*self.ny)

        #test standard constructor
        s2 = Shape(2)
        self.assertTrue(s2.rank == 2)
        self.assertTrue(s2.dim(0) == 0)
        self.assertTrue(s2.dim(1) == 0)

        s2.dim(0,self.ny)
        s2.dim(1,self.nx)
        self.assertTrue(s2.dim(0) == self.ny)
        self.assertTrue(s2.dim(1) == self.nx)
        self.assertTrue(s2.size == self.ny*self.nx)

        #test copy construction
        s3 = Shape(s2)
        self.assertTrue(s3.rank == s2.rank)
        for i in range(s3.rank):
            self.assertTrue(s3.dim(i) == s2.dim(i))

        self.assertTrue(s3.size == s2.size)

    def test_offset_and_index(self):
        i = Index(2)
        s = Shape(2)
        
        s[0] = 6
        s[1] = 9

        i[0] = 3 
        i[1] = 4 
        self.assertTrue(s.offset(i) == 31)

        i1 = Index(2)
        i1[0] = 1 
        i1[1] = 7 
        s.index(16,i)
        self.assertTrue(i1 == i)
    
    def test_shape_manipulation(self):
        s = Shape(2)

        s[0] = 100; s[1] = 200;
        self.assertTrue(s.size == 100*200)

        s.rank = 3
        self.assertTrue(s.size == 0)
        self.assertTrue(s.rank == 3)
        s[0] = 1; s[1] = 2; s[2] = 4
        self.assertTrue(s.size == 1*2*4)


    def test_container_properties(self):
        s = Shape(3)

        self.assertTrue(len(s) == s.rank)
        s.dim(0,self.nx)
        s.dim(1,self.ny)
        s.dim(2,self.nz)

        self.assertTrue(s[0] == self.nx)
        self.assertTrue(s[1] == self.ny)
        self.assertTrue(s[2] == self.nz)

        s[0] = self.nz
        s[1] = self.ny
        s[2] = self.nx

        self.assertTrue(s[0] == self.nz)
        self.assertTrue(s[1] == self.ny)
        self.assertTrue(s[2] == self.nx)

        def test_index(i):
            return s[i]

        self.assertRaises(UserWarning,test_index,4)

        #initialize with slice
        s = Shape(5)
        s[:] = [1,2,3,4,5]
        self.assertTrue(s[1:4] == [2,3,4])

        








