import sys
import unittest
sys.path.append("../")

from pni.utils import UInt8Scalar
from pni.utils import Int8Scalar
from pni.utils import UInt16Scalar
from pni.utils import Int16Scalar
from pni.utils import UInt32Scalar
from pni.utils import Int32Scalar
from pni.utils import UInt64Scalar
from pni.utils import Int64Scalar

from pni.utils import Float32Scalar
from pni.utils import Float64Scalar
from pni.utils import Float128Scalar


#implementing test fixture
class ScalarTest(unittest.TestCase):
    def setUp(self):
        pass

    def tearDown(self):
        pass
