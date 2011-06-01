
#ifndef __ARRAYSELECTION_HPP__
#define __ARRAYSELECTION_HPP__

#include "Array.hpp"

class ArraySelection{
protected:
public:
	ArraySelection();
	ArraySelection(const ArraySelection &);
	ArraySelection(const ArrayObject *);
	ArraySelection(const ArrayObject::sptr &);
	virtual ~ArraySelection();

	virtual
};


#endif
