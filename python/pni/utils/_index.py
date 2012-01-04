#loading the Index object

from pniutils import Index

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
