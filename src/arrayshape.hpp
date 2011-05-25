//declaration of the NumArrayShape class

#ifndef __ARRAYSHAPE_HPP__
#define __ARRAYSHAPE_HPP__

#include <string>

#include "exceptions.hpp"


namespace pni{
namespace utils{

//! Shape object

//! ArrayShape objects describe the shape of an array. In particular
//! they are important to access array data stored in a linear,
//! contiguous stream of data. In all cases we assume C-ordering.
//! This means that the last index in the array varies fastest.
//! Each array is stored as a linear sequence of data values. To
//! mimic the behavior of a multidimensional array we need to map
//! each tuple of indices to a linear memory location. Consider an
//! array of \f$M\f$ dimension and \f$N_i\f$ elements along each dimension.
//! Furthermore we assume an multidimensional index for an array element
//! \f$(i_0,i_1,....,i_{(M-1)})\f$. From this the linear memory location can be
//! obtained with
//!\f[
//! 	o = \sum_{j=0}^{M-1} i_jS_j
//!\f]
//! where S_j is the stride of each dimension which is determined by
//!\f[
//! S_j = \prod_{k=j}^{M-2} N_{k+1}
//! with S_{M-1} = 1
//!\f]
//! After an ArrayShape object has been instantiated all its parameters
//! can be adjusted dynamically to whatever values are required.
//! The class takes care about all kinds of adoptions.
//! This might not be true for array classes using this ArrayShape type.

class ArrayShape{
    protected:
        unsigned int _rank;          //!< the number of dimensions
        unsigned int *_dimstrides;   //!< the strides for the offset calculation
        unsigned int *_shape;        //!< the number of values along each dimension
        unsigned long _size;         //!< the total number of elements in the array
        
        //! compute dimension strides

        //! compute the stride for each dimension - used internally to recompute
        //! the stride for each dimension if the shape is changed.
        void _compute_dimstrides();

        //! compute total number of elements

        //! used internally to recompute the number of elements in the array
        //! once the shape is changed in a way so that the size is changed.
        void _compute_size();
    public:
        static const MemoryAllocationError DIMSTRIDE_ALLOC_ERROR;
        static const MemoryAllocationError SHAPE_ALLOC_ERROR;
        //! default constructor
        ArrayShape();
        //! copy constructor
        ArrayShape(const ArrayShape &s);
        //! constructor taking the rank and shape of an array

        //! \param r rank (the number of dimensions) of the array
        //! \param s number of elements in each dimension
        ArrayShape(const unsigned int r,const unsigned int *s);
        //! destructor
        virtual ~ArrayShape();
        
        //! set the rank of the shape object

        //! sets the number of dimensions for the array
        //! \param r number of dimensions (rank)
        virtual void setRank(const unsigned int &r);
        //! return the array rank

        //! \return array rank
        virtual unsigned int getRank() const;
        //! set the dimensions of the array

        //! This methods is used to set all dimension of an array in a single
        //! method call.
        //! \param *s array with number of elements in each direction
        virtual void setDimensions(const unsigned int *s);
        //! set a single dimension of the shape object

        //! Use this method to set a single dimension in an array to a new value.
        //! If the index i is larger than the rank of the shape an exception
        //! will be raised.
        //! \param i index of the dimension to set
        //! \param d new number of elements along dimension i
        virtual void setDimension(const unsigned int &i,const unsigned int &d);
        //! get all dimensions of the shape

        //! Returns a constant pointer to the dimension array of the shape object.
        //! The returned pointer is const and thus its content cannot be altered.
        //! \return pointer to dimensions
        virtual const unsigned int *getDimensions() const;
        //! get a single dimension of the shape

        //! return the number of elements along dimension i. Raises an exception
        //! if i is larger than the rank of the shape.
        //! \param i index of the dimension
        //! \return the number of elements along dimension i
        virtual unsigned int getDimension(const unsigned int &i) const;
        //! get total number of elements in the array

        //! \return number of elements available in an array of this shape
        virtual unsigned int getSize() const {return _size;}
        
        //! compute element offset

        //! This method computes the offset for the element in an array
        //! characterized by the indices in index. The offset is the address of
        //! the element in a linear buffer.

        //! \params *index pointer to an array of element indices
        virtual unsigned int getOffset(const unsigned int *index);
        
        //the assignment operator must be a member function
        //and cannot be declared as a friend function
        ArrayShape &operator=(const ArrayShape &);
        
        //! equality operator for array shapes

        //! It returns true if the rank and dimension of two arrays are equal, false otherwise
        //! \return boolean value representing shape equality
        friend bool operator==(const ArrayShape &,const ArrayShape &);
        //! inequality operator for array shapes

        //! Returns true if either the rank or one of the dimensions in two shape objects
        //! differ.
        //! \return boolean value
        friend bool operator!=(const ArrayShape &,const ArrayShape &);
        //! [] operator

        //! This operator allows reading access to the array dimensions. You cannot
        //! use this operator to set array dimensions.
        //! \sa void setDimensions(const unsigned int *s), void setDimension(const unsigned int &i,const unsigned int &d)
        const unsigned int operator[](unsigned int i) const { return _shape[i];}
};

}
}

#endif
