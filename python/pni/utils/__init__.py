#import general purpose objects
from pniutils import DataObject
from pniutils import NumericObject
from pniutils import Index
from pniutils import Shape

#import Buffer objects
from pniutils import UInt8Buffer
from pniutils import Int8Buffer
from pniutils import UInt16Buffer
from pniutils import Int16Buffer
from pniutils import UInt32Buffer
from pniutils import Int32Buffer
from pniutils import UInt64Buffer
from pniutils import Int64Buffer
from pniutils import Float32Buffer
from pniutils import Float64Buffer
from pniutils import Float128Buffer

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

#import arrays
from pniutils import Float64Array

#import enumerations
from pniutils import TypeClass
from pniutils import TypeID


#======================Extending wrapped objects===============================
#------------Extending the shape object----------------------------------------
def Shape__getitem__(self,i):
    if isinstance(i,slice):
        indices = i.indices(len(self))
        l = []
        for i  in range(*indices):
            l.append(self[i])

        return l
    else:
        return self.dim(i)

#-------------------------------------------
def Shape__setitem__(self,i,value):
    if isinstance(i,slice):
        indices = i.indices(len(self))
        if isinstance(value,tuple) or isinstance(value,list):
            for i in range(*indices):
                self.dim(i,value[i])
        else:
            for i in range(*indices):
                self.dim(i,value)
    
    else:
        self.dim(i,value)

#------------------------------------------
def Shape__len__(self):
    return self.rank

#------------------------------------------
def Shape__str__(self):
    ostr = "Shape(%i) [" %(self.rank)
    for i in range(len(self)):
        ostr += "%i " %(self[i])

    ostr = ostr[:-1]
    ostr += "]"
    return ostr

Shape.__len__ = Shape__len__
Shape.__getitem__ = Shape__getitem__
Shape.__setitem__ = Shape__setitem__
Shape.__str__ = Shape__str__

#----------------Extending the index object-------------------------------------
def Index__getitem__(self,i):
    if isinstance(i,slice):
        indices = i.indices(len(self))
        l = [] 
        for i in range(*indices):
            l.append(self[i])

        return l
    else:
        return self.get(i)

#-----------------------------------------
def Index__setitem__(self,i,value):
    if isinstance(i,slice):
        indices = i.indices(len(self))
        if isinstance(value,list) or isinstance(value,tuple):
            for i in range(*indices):
                self.set(i,value[i])
        else:
            for i in range(*indices):
                self.set(i,value)
    else:
        self.set(i,value)

#-----------------------------------------
def Index__len__(self):
    return self.rank

#-----------------------------------------
def Index__str__(self):
    ostr = "Index (%i) [" %(self.rank)
    for i in range(len(self)):
        ostr += "%i " %(self[i])

    ostr = ostr[:-1]
    ostr += "]"
    return ostr

Index.__setitem__ = Index__setitem__
Index.__getitem__ = Index__getitem__
Index.__len__ = Index__len__
Index.__str__ = Index__str__

#--------------Extending scalar objects----------------------------------------
def IntScalar__str__(self):
    ostr = "%s = %i (%s)" %(self.name,self.value,self.unit)
    return ostr

def UIntScalar__str__(self):
    ostr = "%s = %u (%s)" %(self.name,self.value,self.unit)
    return ostr

UInt8Buffer.__str__ = UIntScalar__str__
Int8Buffer.__str__  = IntScalar__str__
UInt16Buffer.__str__ = UIntScalar__str__
Int16Buffer.__str__  = IntScalar__str__
UInt32Buffer.__str__ = UIntScalar__str__
Int32Buffer.__str__  = IntScalar__str__
UInt64Buffer.__str__ = UIntScalar__str__
Int64Buffer.__str__  = IntScalar__str__

def FloatScalar__str__(self):
    ostr = "%s = %g (%s)" %(self.name,self.value,self.unit)
    return ostr

Float32Buffer.__str__ = FloatScalar__str__
Float64Buffer.__str__ = FloatScalar__str__
Float128Buffer.__str__ = FloatScalar__str__
