import sys
import unittest
sys.path.append("../")

from pni.utils import Index


#implementing test fixture
class IndexTest(unittest.TestCase):
    def setUp(self):
        self.nx = 100;
        self.ny = 5;
        self.nz = 27;

    def tearDown(self):
        pass

    def test_creation(self):
        i1 = Index()
        self.assertTrue(i1.rank == 0)

        i1.rank = 2
        self.assertTrue(i1.rank == 2)

        #test copy construction
        i2 = Index(i1)
        self.assertTrue(i2.rank == i1.rank)


    def test_manipulation(self):
        i1 = Index(2)
        self.assertTrue(i1[0] == 0)
        self.assertTrue(i1[1] == 0)

        i1[0] = 100
        i1[1] = 200
        self.assertTrue(i1[0] == 100)
        self.assertTrue(i1[1] == 200)

        i1.rank = 3
        self.assertTrue(i1[0] == 0)
        self.assertTrue(i1[1] == 0)
        self.assertTrue(i1[2] == 0)

    def test_container(self):
        i1 = Index(2)

        self.assertTrue(len(i1) == 2)
        i1.rank = 10
        i1[:] = 10 
        i1[:] = (10,9,8,7,6,5,4,3,2,1)
        self.assertTrue( i1[1:4] == [9,8,7])

    def test_comparison(self):
        i1 = Index(2)
        i2 = Index(2)

        i1[0] = 100; i1[1] = 200
        i2[0] = 100; i2[1] = 200
        self.assertTrue(i1 == i2)
        i2[0] = 101
        self.assertTrue(i1 != i2)

        i2.rank = 3
        self.assertTrue(i1 != i2)

