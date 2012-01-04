#module to extend numpy arrays with pni-type array functionality

import numpy
from pniutils import Shape

#import reference Buffers
from pniutils import UInt8RefBuffer
from pniutils import Int8RefBuffer
from pniutils import UInt16RefBuffer
from pniutils import Int16RefBuffer
from pniutils import UInt32RefBuffer
from pniutils import Int32RefBuffer
from pniutils import UInt64RefBuffer
from pniutils import Int64RefBuffer
from pniutils import Float32RefBuffer
from pniutils import Float64RefBuffer
from pniutils import Float128RefBuffer

#import reference Buffers
from pniutils import UInt8RefBufferGenerator
from pniutils import Int8RefBufferGenerator
from pniutils import UInt16RefBufferGenerator
from pniutils import Int16RefBufferGenerator
from pniutils import UInt32RefBufferGenerator
from pniutils import Int32RefBufferGenerator
from pniutils import UInt64RefBufferGenerator
from pniutils import Int64RefBufferGenerator
from pniutils import Float32RefBufferGenerator
from pniutils import Float64RefBufferGenerator
from pniutils import Float128RefBufferGenerator

#import reference arrays
from pniutils import UInt8RefArray
from pniutils import Int8RefArray
from pniutils import UInt16RefArray
from pniutils import Int16RefArray
from pniutils import UInt32RefArray
from pniutils import Int32RefArray
from pniutils import UInt64RefArray
from pniutils import Int64RefArray
from pniutils import Float32RefArray
from pniutils import Float64RefArray
from pniutils import Float128RefArray

def _ref_generator(ndarray,name,unit,description):
    dtype = ndarray.dtype

    #setup the shape object fo the reference array
    s = Shape(len(ndarray.shape))
    for i in range(s.rank):
        s.dim(i,ndarray.shape[i])

    if dtype.name == "uint8":
        rbuffer = UInt8RefBufferGenerator(ndarray)
        return UInt8RefArray(s,rbuffer,name,unit,description)

    if dtype.name == "int8":
        rbuffer = Int8RefBufferGenerator(ndarray)
        return Int8RefArray(s,rbuffer,name,unit,description)

    if dtype.name == "uint16":
        rbuffer = UInt16RefBufferGenerator(ndarray)
        return UInt16RefArray(s,rbuffer,name,unit,description)
    
    if dtype.name == "int16":
        rbuffer = Int16RefBufferGenerator(ndarray)
        return Int16RefArray(s,rbuffer,name,unit,description)

    if dtype.name == "uint32":
        rbuffer = UInt32RefBufferGenerator(ndarray)
        return UInt32RefArray(s,rbuffer,name,unit,description)

    if dtype.name == "int32":
        rbuffer = Int32RefBufferGenerator(ndarray)
        return Int32RefArray(s,rbuffer,name,unit,description)

    if dtype.name == "uint64":
        rbuffer = UInt64RefBufferGenerator(ndarray)
        return UInt64RefArray(s,rbuffer,name,unit,description)

    if dtype.name == "int64":
        rbuffer = Int64RefBufferGenerator(ndarray)
        return Int64RefArray(s,rbuffer,name,unit,description)

    if dtype.name == "float32":
        rbuffer = Float32RefBufferGenerator(ndarray)
        return Float32RefArray(s,rbuffer,name,unit,description)

    if dtype.name == "float64":
        rbuffer = Float64RefBufferGenerator(ndarray)
        return Float64RefArray(s,rbuffer,name,unit,description)

    if dtype.name == "float128":
        rbuffer = Float128RefBufferGenerator(ndarray)
        return Float128RefArray(s,rbuffer,name,unit,description)

    
    raise TypeError,"Unsupported array data type!"



class Array(numpy.ndarray):
    def __init__(self,**kargs):
        numpy.ndarray.__init__(self,**kargs)
        
        if kargs.has_key("name"):
            name = kargs["name"]
        else:
            name = "none"

        if kargs.has_key("unit"):
            unit = kargs["unit"]
        else:
            unit = "none"

        if kargs.has_key("desc"):
            desc = kargs["desc"]
        else:
            desc = "none"


        #from the dtype information we can create the 
        #proper ref-array
        self.__ref_array = _ref_generator(self,name,unit,desc)

    def _get_unit(self):
        return self.__ref_array.unit

    def _set_unit(self,unit):
        self.__ref_array.unit = unit

    def _get_description(self):
        return self.__ref_array.description

    def _set_description(self,description):
        self.__ref_array.description = description

    def _get_name(self):
        return self.__ref_array.name

    def _set_name(self,name):
        self.__ref_array.name = name

    def _get_reference(self):
        return self.__ref_array

    unit = property(_get_unit,_set_unit)
    name = property(_get_name,_set_name)
    description = property(_get_description,_set_description)

    ref = property(_get_reference) 
        


