import sys
import unittest
sys.path.append("../")

from pni.utils import Shape



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

    def test_manipulation(self):
        pass

    def test_container_properties(self):
        s = Shape(3)

        self.assertTrue(len(s) == s.rank)
        s.dim(0,self.nx)
        s.dim(1,self.ny)
        s.dim(2,self.nz)

        self.assertTrue(s[0] == self.nx)
        self.assertTrue(s[1] == self.ny)
        self.assertTrue(s[2] == self.nz)

        print s[4]






