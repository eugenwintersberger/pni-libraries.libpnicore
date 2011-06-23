/*
 * TIFFTag.hpp
 *
 *  Created on: Jun 17, 2011
 *      Author: eugen
 */

#ifndef __TIFFSTANDARD_HPP__
#define __TIFFSTANDARD_HPP__

#include <map>
#include "../PNITypes.hpp"

namespace pni{
namespace utils{

//! \ingroup IO
//! \brief holds TIFF standard values

//! This class provides methods to primarily access TIFF standard names
//! and constants.
class TIFFStandard{
private:
	//class cannot be copied
	TIFFStandard(const TIFFStandard &o){}
	//cannot be assigned
	TIFFStandard &operator=(const TIFFStandard &){return *this;}
protected:
	typedef std::map<UInt16,String> _TAGNameMap; //!< map to relate TIFF tags to strings
	_TAGNameMap _tifftags;    //!< map for standard TIFF tags
	_TAGNameMap _comptags;    //!< int to name map for compression
	_TAGNameMap _phinttags;   //!< int to name map for Photometric Interpretation
public:
	//! default constructor
	TIFFStandard();
	//! destructor
	virtual ~TIFFStandard();

	//! get the entry name of a standard TIFF entry tag
	String getTagName(UInt16 tid);
	//! get the compression name for a TIFF compression ID
	String getCompression(const UInt16 cid);
	//! get the photometric interpretation key for a TIFF entry ID
	String getPhotometricInterpretation(const UInt16 pid);

};


//end of namespace
}
}




#endif /* __TIFFSTANDARD_HPP__ */
