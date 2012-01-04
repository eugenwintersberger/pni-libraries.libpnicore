#loading scalar objects

#import scalar objects
from pniutils import ScalarObject
from pniutils import UInt8Scalar
from pniutils import Int8Scalar
from pniutils import UInt16Scalar
from pniutils import Int16Scalar
from pniutils import UInt32Scalar
from pniutils import Int32Scalar
from pniutils import UInt64Scalar
from pniutils import Int64Scalar
from pniutils import Float32Scalar
from pniutils import Float64Scalar
from pniutils import Float128Scalar


#this class of Scalar objects is not yet finished. It should
#later replace all the existing single objects and allow creation 
#of a scalar object from a single instance.
class Scalar(object):
    """
    class Scalar:
    This is a class that represents a Scalar object without a 
    further type specification. 
    """
    def __init__(self,name,unit,dtype,ref=None,desc="None"):
        if ref:
            #an already existing reference object is passed and will 
            #be used to construct the scalar
            self.__ref = ref
            #set the format string according to the reference
            self.__str_fmt = ""
        else:
            #the scalar is constructed from scratch
            pass
            

    def __get_value(self):
        return self.__ref.value()

    def __set_value(self,value):
        self.__ref.value(value)

    value = property(__get_value,__set_value)

    def __get_unit(self):
        return self.__ref.unit

    def __set_unit(self,unit):
        self.__ref.unit = unit

    unit = property(__get_unit,__set_unit)

    def __get_description(self):
        return self.__ref.description

    def __set_description(self,desc):
        self.__ref.description = desc

    description = property(__get_description,__set_description)



#--------------Extending scalar objects----------------------------------------
def IntScalar__str__(self):
    ostr = "%s = %i (%s)" %(self.name,self.value,self.unit)
    return ostr

def UIntScalar__str__(self):
    ostr = "%s = %u (%s)" %(self.name,self.value,self.unit)
    return ostr

UInt8Scalar.__str__ = UIntScalar__str__
Int8Scalar.__str__  = IntScalar__str__
UInt16Scalar.__str__ = UIntScalar__str__
Int16Scalar.__str__  = IntScalar__str__
UInt32Scalar.__str__ = UIntScalar__str__
Int32Scalar.__str__  = IntScalar__str__
UInt64Scalar.__str__ = UIntScalar__str__
Int64Scalar.__str__  = IntScalar__str__

def FloatScalar__str__(self):
    ostr = "%s = %g (%s)" %(self.name,self.value,self.unit)
    return ostr

Float32Scalar.__str__ = FloatScalar__str__
Float64Scalar.__str__ = FloatScalar__str__
Float128Scalar.__str__ = FloatScalar__str__
