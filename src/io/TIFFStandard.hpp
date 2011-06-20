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


class TIFFStandard{
private:
	//class cannot be copied
	TIFFStandard(const TIFFStandard &o){}
	//cannot be assigned
	TIFFStandard &operator=(const TIFFStandard &){return *this;}
protected:
	typedef std::map<UInt16,String> _TAGNameMap;
	_TAGNameMap _tifftags;    //!< map for standard TIFF tags
	_TAGNameMap _comptags;    //!< int to name map for compression
	_TAGNameMap _phinttags;   //!< int to name map for Photometric Interpretation
public:
	TIFFStandard();
	virtual ~TIFFStandard();

	String getTagName(UInt16 tid);
	String getCompression(const UInt16 cid);
	String getPhotometricInterpretation(const UInt16 pid);

};


//end of namespace
}
}




#endif /* __TIFFSTANDARD_HPP__ */
