#prepearing the Shape object

from pniutils import Shape

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
