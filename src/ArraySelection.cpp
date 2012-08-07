#include "ArraySelection.hpp"

namespace pni{
namespace utils{
//=====================implementation of constructors and destructor===========
ArraySelection::ArraySelection(const ArraySelection &s):
    _oshape(s._oshape),
    _offset(s._offset),
    _stride(s._stride),
    _rank(s._rank),
    _shape(s._shape),
    _size(s._size)
{}

//-----------------------------------------------------------------------------
ArraySelection::ArraySelection(ArraySelection &&s):
    _oshape(std::move(s._oshape)),
    _offset(std::move(s._offset)),
    _stride(std::move(s._stride)),
    _rank(std::move(s._rank)),
    _shape(std::move(s._shape)),
    _size(std::move(s._size))
{
    s._offset = std::vector<size_t>();
    s._oshape = std::vector<size_t>();
    s._stride = std::vector<size_t>();
    s._rank = 0;
    s._shape = std::vector<size_t>();
    s._size = 0;
}
//===========implementation of assignment operators============================
ArraySelection &ArraySelection::operator=(const ArraySelection &s)
{
    if(this == &s) return *this;
    _oshape = s._oshape;
    _offset = s._offset;
    _stride = s._stride;
    _rank   = s._rank;
    _shape  = s._shape;
    _size   = s._size;
    return *this;
}

//-----------------------------------------------------------------------------
ArraySelection &ArraySelection::operator=(ArraySelection &&s)
{
    if(this == &s) return *this;
    _oshape = std::move(s._oshape);
    _offset = std::move(s._offset);
    _stride = std::move(s._stride);
    _rank   = std::move(s._rank);
    s._rank = 0;
    _shape  = std::move(s._shape);
    _size   = std::move(s._size);
    s._size = 0;
    return *this;
}

//======================implementation of general purpose methods==============

ArraySelection ArraySelection::create(const std::vector<Slice> &s)
{
    std::vector<size_t> shape(s.size());
    std::vector<size_t> offset(s.size());
    std::vector<size_t> stride(s.size());

    size_t index = 0;
#ifdef NOFOREACH
    for(auto iter = s.begin();iter!=s.end();++iter)
    {
        auto slice = *iter;
#else
    for(auto slice: s)
    {
#endif
        offset[index] = slice.first();
        stride[index] = slice.stride();
        shape[index] = pni::utils::size(slice);
        index++;
    }

    return ArraySelection(shape,offset,stride);
}

//-----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const ArraySelection &s)
{
    o<<"original data:"<<std::endl;
    for(size_t i=0;i<s._oshape.size();i++)
    {
        o<<i<<":\t"<<s._oshape[i]<<"\t"<<s._offset[i]<<"\t"<<s._stride[i];
        o<<std::endl;
    }
    o<<"effective shape: ( ";
#ifdef NOFOREACH
    for(auto iter = s._shape.begin();iter!=s._shape.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: s._shape)
    {
#endif
        o<<v<<" ";
    }
    o<<")"<<std::endl;

    return o;
}
//end of namespace
}
}
