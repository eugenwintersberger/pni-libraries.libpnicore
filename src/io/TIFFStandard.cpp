/*
 * Implementation of class TIFFStandard
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Implementation of class TIFFStandard.
 *
 * Created on: Jun 17, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */


#include "TIFFStandard.hpp"

namespace pni{
namespace utils{

//------------------------------------------------------------------------------
TIFFStandard::TIFFStandard(){
	_tifftags[254] = String("NewSubfileType");
	_tifftags[255] = String("SubfileType");
	_tifftags[256] = String("ImageWidth");
	_tifftags[257] = String("ImageLength");
	_tifftags[258] = String("BitsPerSample");
	_tifftags[259] = String("Compression");
	_tifftags[262] = String("PhotometricInterpretation");
	_tifftags[263] = String("Threshholding");
	_tifftags[264] = String("CellWidth");
	_tifftags[265] = String("CellLength");
	_tifftags[266] = String("FillOrder");
	_tifftags[269] = String("DocumentName");
	_tifftags[270] = String("ImageDescription");
	_tifftags[271] = String("Make");
	_tifftags[272] = String("Model");
	_tifftags[273] = String("StripOffsets");
	_tifftags[274] = String("Orientation");
	_tifftags[277] = String("SamplesPerPixel");
	_tifftags[278] = String("RowsPerStrip");
	_tifftags[279] = String("StripByteCounts");
	_tifftags[280] = String("MinSampleValue");
	_tifftags[281] = String("MaxSampleValue");
	_tifftags[282] = String("XResolution");
	_tifftags[283] = String("YResolution");
	_tifftags[284] = String("PlanarConfiguration");
	_tifftags[285] = String("PageName");
	_tifftags[286] = String("XPosition");
	_tifftags[287] = String("YPosition");
	_tifftags[288] = String("FreeOffsets");
	_tifftags[289] = String("FreeByteCounts");
	_tifftags[290] = String("GrayResponseUnit");
	_tifftags[291] = String("GrayResponseCurve");
	_tifftags[292] = String("T4Options");
	_tifftags[293] = String("T6Options");
	_tifftags[296] = String("ResolutionUnit");
	_tifftags[297] = String("PageNumber");
	_tifftags[301] = String("TransferFunction");
	_tifftags[305] = String("Software");
	_tifftags[306] = String("DateTime");
	_tifftags[315] = String("Artist");
	_tifftags[316] = String("HostComputer");
	_tifftags[317] = String("Predictor");
	_tifftags[318] = String("WhitePoint");
	_tifftags[319] = String("PrimaryChromaticities");
	_tifftags[320] = String("ColorMap");
	_tifftags[321] = String("HalftoneHints");
	_tifftags[322] = String("TileWidth");
	_tifftags[323] = String("TileLength");
	_tifftags[324] = String("TileOffsets");
	_tifftags[325] = String("TileByteCounts");
	_tifftags[332] = String("InkSet");
	_tifftags[333] = String("InkNames");
	_tifftags[334] = String("NumberOfInks");
	_tifftags[336] = String("DotRange");
	_tifftags[337] = String("TargetPrinter");
	_tifftags[338] = String("ExtraSamples");
	_tifftags[339] = String("SampleFormat");
	_tifftags[340] = String("SMinSampleValue");
	_tifftags[341] = String("SMaxSampleValue");
	_tifftags[342] = String("TransferRange");
	_tifftags[512] = String("JPEGProc");
	_tifftags[513] = String("JPEGInterchangeFormat");
	_tifftags[514] = String("JPEGInterchangeFormatLength");
	_tifftags[515] = String("JPEGRestartLevel");
	_tifftags[517] = String("JPEGLosslessPredictors");
	_tifftags[518] = String("JPEGPointTransforms");
	_tifftags[519] = String("JPEGQTables");
	_tifftags[520] = String("JPEGDCTables");
	_tifftags[521] = String("JPEGACTables");
	_tifftags[529] = String("YCbCrCoefficients");
	_tifftags[530] = String("YCbCrSubSampling");
	_tifftags[531] = String("YCbCrPositioning");
	_tifftags[532] = String("ReferenceBlackWhite");
	_tifftags[33432] = String("Copyright");

	_comptags[1] = String("Uncompressed");
	_comptags[2] = String("CCITT 1D");
	_comptags[3] = String("Group 3 Fax");
	_comptags[4] = String("Group 4 Fax");
	_comptags[5] = String("LZW");
	_comptags[6] = String("JPEG");
	_comptags[32773] = String("PackBits");

	_phinttags[0] = String("WhiteIsZero");
	_phinttags[1] = String("BlackIsZero");
	_phinttags[2] = String("RGB");
	_phinttags[3] = String("RGB Palette");
	_phinttags[4] = String("Transparency mask");
	_phinttags[5] = String("CMYK");
	_phinttags[6] = String("YCbCr");
	_phinttags[8] = String("CIELab");
}

//------------------------------------------------------------------------------
TIFFStandard::~TIFFStandard(){

}


//------------------------------------------------------------------------------
String TIFFStandard::getTagName(const UInt16 tid){
	if(_tifftags.count(tid)){
		return _tifftags[tid];
	}else{
		return String("UNKNOWN");
	}
}

//------------------------------------------------------------------------------
String TIFFStandard::getCompression(const UInt16 cid){
	if(_comptags.count(cid)){
		return String(_comptags[cid]);
	}else{
		return String("UNKNOWN");
	}
}

//------------------------------------------------------------------------------
String TIFFStandard::getPhotometricInterpretation(const UInt16 pid){
	if(_phinttags.count(pid)){
		return String(_phinttags[pid]);
	}else{
		return String("UNKNOWN");
	}
}

//------------------------------------------------------------------------------
static TIFFStandard gTIFFStandard;

//end of namespace
}
}
