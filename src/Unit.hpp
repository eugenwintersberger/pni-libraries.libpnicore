/*
 * Unit.hpp
 *
 *  Created on: Jun 29, 2011
 *      Author: eugen
 */

#ifndef UNIT_HPP_
#define UNIT_HPP_

extern "C"{
#include <udunits2.h>
}

#include <iostream>
#include <boost/shared_ptr.hpp>
#include "PNITypes.hpp"


namespace pni {
namespace utils {

//! a physical unit

//!
class Unit {
private:
	//default constructor
	//An instance of Unit can only be obtained from the
	//UnitSystem factory or from the copy constructor.
	Unit(){ _unit = NULL;}
protected:
	ut_unit *_unit;
public:
	//! shared pointer to a Unit object
	typedef boost::shared_ptr<Unit> sptr;
	Unit(const Unit &o);
	virtual ~Unit();

	Unit &operator=(const Unit &);

	//!get the name of the unit
	virtual String getName() const;
	//!get the symbol for the unit
	virtual String getSymbol() const;

	//! scale this instance of class Unit
	virtual void setScale(const Float64 &s);
	//! scale operator
	Unit &operator *=(const Float64 &s);
	//! add an offset to this instance of class Unit
	virtual void setOffset(const Float64 &o);
	//! offset operator
	Unit &operator +=(const Float64 &o);

	//! create a new Unit by scaling a Unit object with a scalar
	friend Unit operator*(const Float64 &s,const Unit &u);
	//! create a new Unit by scaling a Unit object with a scalar
	friend Unit operator*(const Unit &u,const Float64 s);
	//! create a new Unit by multiplying two Unit objects
	friend Unit operator*(const Unit &a,const Unit &b);

	//! create a new Unit by inverting a Unit object and scale
	friend Unit operator/(const Float64 &s,const Unit &u);
	friend Unit operator/(const Unit &u,const Float64 &s);
	//! create a new Unit by dividing two Unit objects
	friend Unit operator/(const Unit &a,const Unit &b);

	//! equality operator

	//! This operator checks units for equality. Not only
	//! that the units must be equal they must also come
	//! from the same unit system. In other words
	//! they must i.g. come from the same factory.
	friend bool operator==(const Unit &a,const Unit &b);
	//! inequality operator
	friend bool operator!=(const Unit &a,const Unit &b);

	//subtraction and addition operators should check
	//if units are equal or at least convertible


	friend ostream &operator<<(ostream &o,const Unit &u);

};


//end of namespace
}
}

#endif /* UNIT_HPP_ */
