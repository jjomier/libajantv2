/* SPDX-License-Identifier: MIT */
/**
	@file		pixelformat.cpp
	@brief		Contains the implementation of the AJAPixelFormat class.
	@copyright	(C) 2010-2022 AJA Video Systems, Inc.  All rights reserved.
**/

//---------------------------------------------------------------------------------------------------------------------
//	Includes
//---------------------------------------------------------------------------------------------------------------------
#include "ajabase/common/types.h"
#include "ajabase/common/public.h"	// Needed to pull in definition of size_t
#include "ajabase/common/pixelformat.h"

//---------------------------------------------------------------------------------------------------------------------
//	Defines and structures
//---------------------------------------------------------------------------------------------------------------------

struct AJAPixelFormatEntry
{
	AJA_PixelFormat 	pixelFormat;
	uint32_t			fourcc;
	uint32_t			bitDepth;
	AJAScaleType		scaleType;
	AJASubSampleType	subSampleType;
	uint32_t			planeCount;
	bool				isRGB;
	const char*			pName;
};

//---------------------------------------------------------------------------------------------------------------------
//	Format table  (the fourcc's aren't right in this yet...change as needed)
//---------------------------------------------------------------------------------------------------------------------
AJAPixelFormatEntry AJAPixelFormatTable[AJA_PixelFormat_Size] = 
{
	{AJA_PixelFormat_Unknown,			 AJA_FOURCC(' ',' ',' ',' '),	  0,	AJAScaleTypeNone,	  AJASubSampleNone,		0,	false,	"Unknown"},
	{AJA_PixelFormat_YCbCr10,			 AJA_FOURCC('v','2','1','0'),	  10,	AJAScaleTypeNone,	  AJASubSample422,		1,	false,	"10 Bit YCbCr"},
	{AJA_PixelFormat_YCbCr8,			 AJA_FOURCC('2','v','u','y'),	  8,	AJAScaleTypeNone,	  AJASubSample422,		1,	false,	"8 Bit YCbCr"},
	{AJA_PixelFormat_ARGB8,				 AJA_FOURCC('b','g','r','A'),	  8,	AJAScaleTypeNone,	  AJASubSample4444,		1,	true,	"8 Bit ARGB"},
	{AJA_PixelFormat_RGBA8,				 AJA_FOURCC('r','g','b','a'),	  8,	AJAScaleTypeNone,	  AJASubSample4444,		1,	true,	"8 Bit RGBA"},
	{AJA_PixelFormat_RGB10,				 AJA_FOURCC('1','0','r','b'),	  10,	AJAScaleTypeNone,	  AJASubSample444,		1,	true,	"10 Bit RGB"},
	{AJA_PixelFormat_YUY28,				 AJA_FOURCC('Y','U','Y','2'),	  8,	AJAScaleTypeNone,	  AJASubSample422,		1,	false,	"8 Bit YCbCr Alternate"},
	{AJA_PixelFormat_ABGR8,				 AJA_FOURCC('a','r','g','B'),	  8,	AJAScaleTypeNone,	  AJASubSample4444,		1,	true,	"8 Bit RGBA OpenGL"},
	{AJA_PixelFormat_RGB_DPX,			 AJA_FOURCC('R','1','0','k'),	  10,	AJAScaleTypeNone,	  AJASubSample444,		1,	true,	"10 Bit RGB DPX"},
	{AJA_PixelFormat_YCbCr_DPX,			 AJA_FOURCC('d','p','x','2'),	  10,	AJAScaleTypeNone,	  AJASubSample422,		1,	false,	"10 Bit YCbCr DPX"},
	{AJA_PixelFormat_DVCPRO,			 AJA_FOURCC('2','v','u','y'),	  8,	AJAScaleTypeDVCPro,	  AJASubSample422,		1,	false,	"DVC Pro"},
	{AJA_PixelFormat_QREZ,				 AJA_FOURCC('2','v','u','y'),	  8,	AJAScaleTypeQRez,	  AJASubSample422,		1,	false,	"QRez"},
	{AJA_PixelFormat_HDV,				 AJA_FOURCC('2','v','u','y'),	  8,	AJAScaleTypeHDV,	  AJASubSample422,		1,	false,	"HDV"},
	{AJA_PixelFormat_RGB8_PACK,			 AJA_FOURCC('r','g','b',' '),	  8,	AJAScaleTypeNone,	  AJASubSample444,		1,	true,	"8 Bit RGB"},
	{AJA_PixelFormat_BGR8_PACK,			 AJA_FOURCC('b','g','r',' '),	  8,	AJAScaleTypeNone,	  AJASubSample444,		1,	true,	"8 Bit BGR"},
	{AJA_PixelFormat_YCbCrA10,			 AJA_FOURCC(' ',' ',' ',' '),	  10,	AJAScaleTypeNone,	  AJASubSample422,		1,	false,	"10 Bit YCbCrA"},
	{AJA_PixelFormat_RGB_DPX_LE,		 AJA_FOURCC('r','1','0','k'),	  10,	AJAScaleTypeNone,	  AJASubSample444,		1,	true,	"10 Bit RGB DPX LE"},
	{AJA_PixelFormat_RGB12,				 AJA_FOURCC(' ',' ',' ',' '),	  12,	AJAScaleTypeNone,	  AJASubSample444,		1,	true,	"RGB12"},			//tmp name, may need to change
	{AJA_PixelFormat_RGB12P,			 AJA_FOURCC(' ',' ',' ',' '),	  12,	AJAScaleTypeNone,	  AJASubSample444,		1,	true,	"RGB12P"},
	{AJA_PixelFormat_PRORES_DVPRO,		 AJA_FOURCC('a','c','p','n'),	  8,	AJAScaleTypeDVCPro,	  AJASubSample422,		1,	false,	"ProRes DVC Pro"},
	{AJA_PixelFormat_PRORES_HDV,		 AJA_FOURCC('a','c','p','n'),	  8,	AJAScaleTypeHDV,	  AJASubSample422,		1,	false,	"ProRes HDV"},
	{AJA_PixelFormat_RGB10_PACK,		 AJA_FOURCC(' ',' ',' ',' '),	  10,	AJAScaleTypeNone,	  AJASubSample444,		1,	true,	"RGB10Pack"},		//tmp name, may need to change
	{AJA_PixelFormat_YCbCr12_444,		 AJA_FOURCC(' ',' ',' ',' '),	  12,	AJAScaleTypeNone,	  AJASubSample444,		1,	false,	"12 Bit YCbCr444"}, //tmp name, may need to change
	{AJA_PixelFormat_YCbCr12_422,		 AJA_FOURCC(' ',' ',' ',' '),	  12,	AJAScaleTypeNone,	  AJASubSample422,		1,	false,	"12 Bit YCbCr422"}, //tmp name, may need to change
	{AJA_PixelFormat_RGB16,				 AJA_FOURCC('b','4','8','r'),	  16,	AJAScaleTypeNone,	  AJASubSample444,		1,	true,	"16 Bit RGB"},
	{AJA_PixelFormat_YCbCr10_4K_RQ,		 AJA_FOURCC(' ',' ',' ',' '),	  10,	AJAScaleTypeNone,	  AJASubSample422,		1,	false,	"10 Bit YCbCr 4K RQ"},
	{AJA_PixelFormat_BAYER10_DPX_LJ,	 AJA_FOURCC(' ',' ',' ',' '),	  10,	AJAScaleTypeNone,	  AJASubSampleBayer,	1,	true,	"Bayer 10 Bit DPX LJ"},
	{AJA_PixelFormat_BAYER10_DPX_LJ,	 AJA_FOURCC(' ',' ',' ',' '),	  10,	AJAScaleTypeNone,	  AJASubSampleBayer,	1,	true,	"Bayer 12 Bit DPX LJ"},
	{AJA_PixelFormat_BAYER10_HS,		 AJA_FOURCC(' ',' ',' ',' '),	  10,	AJAScaleTypeNone,	  AJASubSampleBayer,	1,	true,	"Bayer 10 Bit HS"},
	{AJA_PixelFormat_BAYER12_HS,		 AJA_FOURCC(' ',' ',' ',' '),	  12,	AJAScaleTypeNone,	  AJASubSampleBayer,	1,	true,	"Bayer 12 Bit HS"},
	{AJA_PixelFormat_BAYER12_PACK_HS,	 AJA_FOURCC('C','1','2','s'),	  12,	AJAScaleTypeNone,	  AJASubSampleBayer,	1,	true,	"Bayer 12 Bit Packed HS"},
	{AJA_PixelFormat_RAW10,				 AJA_FOURCC('C','1','0','s'),	  10,	AJAScaleTypeNone,	  AJASubSampleBayer,	1,	true,	"RAW 10 Bit"},			// CION Raw 10 bit
	{AJA_PixelFormat_RAW10_HS,			 AJA_FOURCC('C','1','0','h'),	  10,	AJAScaleTypeNone,	  AJASubSampleBayer,	1,	true,	"RAW 10 Bit HS"},		// CION Raw 10 bit HS
	{AJA_PixelFormat_YCBCR10_420PL,		 AJA_FOURCC(' ',' ',' ',' '),	  10,	AJAScaleTypeNone,	  AJASubSample420,		3,	false,	"10 Bit YCbCr 420 Packed 3-Plane"},
	{AJA_PixelFormat_YCBCR10_422PL,		 AJA_FOURCC(' ',' ',' ',' '),	  10,	AJAScaleTypeNone,	  AJASubSample422,		3,	false,	"10 Bit YCbCr 422 Packed 3-Plane"},
	{AJA_PixelFormat_YCBCR8_420PL,		 AJA_FOURCC(' ',' ',' ',' '),	  8,	AJAScaleTypeNone,	  AJASubSample420,		3,	false,	"8 Bit YCbCr 420 3-Plane"},
	{AJA_PixelFormat_YCBCR8_422PL,		 AJA_FOURCC(' ',' ',' ',' '),	  8,	AJAScaleTypeNone,	  AJASubSample422,		3,	false,	"8 Bit YCbCr 422 3-Plane"},
	{AJA_PixelFormat_YCBCR8_420PL3,		 AJA_FOURCC('I','4','2','0'),	  8,	AJAScaleTypeNone,	  AJASubSample420,		3,	false,	"8 Bit YCbCr 420 3-Plane"},
	{AJA_PixelFormat_YCBCR8_422PL3,		 AJA_FOURCC('Y','4','2','B'),	  8,	AJAScaleTypeNone,	  AJASubSample422,		3,	false,	"8 Bit YCbCr 422 3-Plane"},
	{AJA_PixelFormat_YCBCR10_420PL3LE,	 AJA_FOURCC('Y','3',0xb,0xa),	  10,	AJAScaleTypeNone,	  AJASubSample420,		3,	false,	"10 Bit YCbCr 420 Unpacked 3-Plane LE"},	// from FFmpeg
	{AJA_PixelFormat_YCBCR10_422PL3LE,	 AJA_FOURCC('Y','3',0xa,0xa),	  10,	AJAScaleTypeNone,	  AJASubSample422,		3,	false,	"10 Bit YCbCr 422 Unpacked 3-Plane LE"},	// from FFmpeg
	{AJA_PixelFormat_YCBCR10_420PL2,	 AJA_FOURCC('2','Y','2','0'),	  10,	AJAScaleTypeNone,	  AJASubSample420,		2,	false,	"10 Bit YCbCr 420 Packed 2-Plane LE"},		// AJA ad hoc 4cc
	{AJA_PixelFormat_YCBCR10_422PL2,	 AJA_FOURCC('2','Y','2','2'),	  10,	AJAScaleTypeNone,	  AJASubSample422,		2,	false,	"10 Bit YCbCr 422 Packed 2-Plane LE"},		// AJA ad hoc 4cc
	{AJA_PixelFormat_YCBCR8_420PL2,      AJA_FOURCC('N','V','1','2'),	  8,	AJAScaleTypeNone,	  AJASubSample420,		2,	false,	"8 Bit YCbCr 420 2-Plane"},					// from FFmpeg
	{AJA_PixelFormat_YCBCR8_422PL2,      AJA_FOURCC('N','V','1','6'),	  8,	AJAScaleTypeNone,	  AJASubSample422,		2,	false,	"8 Bit YCbCr 422 2-Plane"},					// from FFmpeg
	{AJA_PixelFormat_YCBCR10_420PL2LE,	 AJA_FOURCC('P','0','1','0'),	  10,	AJAScaleTypeNone,	  AJASubSample420,		3,	false,	"10 Bit YCbCr 420 Unpacked 2-Plane LE"},	// from FFmpeg
	{AJA_PixelFormat_YCBCR10_422PL2LE,	 AJA_FOURCC('N','V','2','0'),	  10,	AJAScaleTypeNone,	  AJASubSample422,		3,	false,	"10 Bit YCbCr 422 Unpacked 2-Plane LE"}		// from FFmpeg
};
const size_t AJAPixelFormatTableSize = sizeof(AJAPixelFormatTable) / sizeof(AJAPixelFormatEntry);



AJAPixelFormat::AJAPixelFormat()
{
	m_format = AJA_PixelFormat_Unknown;
}

AJAPixelFormat::AJAPixelFormat(AJA_PixelFormat format)
{
	if (!QueryIsValid(format))
		format = AJA_PixelFormat_Unknown;
	m_format = format;
}

AJAPixelFormat::~AJAPixelFormat()
{
}

void AJAPixelFormat::Set(AJA_PixelFormat format)
{
	if (!QueryIsValid(format))
		format = AJA_PixelFormat_Unknown;
	m_format = format;
}

AJA_PixelFormat AJAPixelFormat::Query(void)
{
	return m_format;
}

uint32_t AJAPixelFormat::QueryFourCC(void)
{
	return AJAPixelFormatTable[m_format].fourcc;
}

const char* AJAPixelFormat::QueryDisplayName(void)
{
	return AJAPixelFormatTable[m_format].pName;
}

bool AJAPixelFormat::QueryRgb(void)
{
	return AJAPixelFormatTable[m_format].isRGB;
}

uint32_t AJAPixelFormat::QueryBitDepth(void)
{
	return AJAPixelFormatTable[m_format].bitDepth;
}

uint32_t AJAPixelFormat::QueryBitDepth(AJA_PixelFormat format)
{
	if (!QueryIsValid(format))
		format = AJA_PixelFormat_Unknown;
	return AJAPixelFormatTable[format].bitDepth;
}

AJASubSampleType AJAPixelFormat::QuerySubSampleType()
{
	return AJAPixelFormatTable[m_format].subSampleType;
}

AJASubSampleType AJAPixelFormat::QuerySubSampleType(AJA_PixelFormat format)
{
	if (!QueryIsValid(format))
		format = AJA_PixelFormat_Unknown;
	return AJAPixelFormatTable[format].subSampleType;
}

uint32_t  AJAPixelFormat::QueryPlaneCount()
{
	return AJAPixelFormatTable[m_format].planeCount;
}

uint32_t AJAPixelFormat::QueryPlaneCount(AJA_PixelFormat format)
{
	if (!QueryIsValid(format))
		format = AJA_PixelFormat_Unknown;
	return AJAPixelFormatTable[format].planeCount;
}

bool AJAPixelFormat::QueryIsValid()
{
	return m_format > AJA_PixelFormat_Unknown && m_format < AJA_PixelFormat_Size;
}

bool AJAPixelFormat::QueryIsValid(AJA_PixelFormat format)
{
	return format > AJA_PixelFormat_Unknown && format < AJA_PixelFormat_Size;
}

AJAScaleType AJAPixelFormat::QueryScaleType(void)
{
	return AJAPixelFormatTable[m_format].scaleType;
}

int AJAPixelFormat::QueryNumberPossibleFormats()
{
	return AJAPixelFormatTableSize-1; //don't count AJA_PixelFormat_Unknown
}

bool AJAPixelFormat::QueryFormatAtIndex(int index,AJAPixelFormat& fmt)
{
	if(index >=0 && (size_t)index < AJAPixelFormatTableSize-1)
	{
		//+1 skip AJA_PixelFormat_Unknown
		fmt.Set(AJAPixelFormatTable[index+1].pixelFormat);
		return true;
	}
	else
	{
		return false;
	}
}

bool AJAPixelFormat::QueryIsScalable(uint32_t bitmapWidth,uint32_t wireWidth,uint32_t xAspect,uint32_t yAspect,
									 AJA_PixelFormat *pMatchingFormat,AJA_PixelFormat *pScalingFormat)
{
	bool bIsScalable = false;
	AJA_PixelFormat scalingFormat = AJA_PixelFormat_Unknown;

	if (yAspect)
	{
		if (xAspect == yAspect)
			return bIsScalable;

		uint32_t correctedBitmapWidth = (bitmapWidth * xAspect) / yAspect;
		if (wireWidth == correctedBitmapWidth)
		{
			switch (bitmapWidth)
			{
			case 1440:
				bIsScalable	  = true;
				scalingFormat = AJA_PixelFormat_HDV;
				break;
			case 1280: 
				bIsScalable	  = true;
				scalingFormat = AJA_PixelFormat_DVCPRO;
				break;
			case 960:
				bIsScalable	  = true;
				scalingFormat = AJA_PixelFormat_HDV;
				break;
			default:
				bIsScalable	  = false;
				break;
			}
		}
	}

	if (pMatchingFormat)
	{
		if (bIsScalable)
			*pMatchingFormat = AJA_PixelFormat_YCbCr8;
		else
			*pMatchingFormat = AJA_PixelFormat_Unknown;
	}

	if (pScalingFormat)
	{
		*pScalingFormat = scalingFormat;
	}

	return bIsScalable;
}

bool AJAPixelFormat::ConvertWidth(AJAScaleType scaleType,int xIn,int &xOut)
{
	bool bOk = false;
	xOut	 = xIn;
	switch (scaleType)
	{
	case AJAScaleType1280To1920:
		if (xIn == 1280)
		{
			xOut = 1920;
			bOk	 = true;
		}
		else if (xIn == 1920)
		{
			xOut = 1280;
			bOk = true;
		}
		break;
	case AJAScaleType960To1280:
		if (xIn == 1280)
		{
			xOut = 960;
			bOk	 = true;
		}
		else if (xIn == 960)
		{
			xOut = 1280;
			bOk = true;
		}
		break;
	case AJAScaleType1440To1920:
		if (xIn == 1440)
		{
			xOut = 1920;
			bOk	 = true;
		}
		else if (xIn == 1920)
		{
			xOut = 1440;
			bOk = true;
		}
		break;
	default:
		{
			xOut = xIn;
			bOk = false;
		}
		break;
	}
	return bOk;
}

bool AJAPixelFormat::ConvertAspect(AJAScaleType scaleType,int hSpacingIn, int vSpacingIn, int &hSpacingOut,int &vSpacingOut)
{
	bool bOk	= false;
	hSpacingOut = hSpacingIn;
	vSpacingOut = vSpacingIn;
	switch (scaleType)
	{
	case AJAScaleType1280To1920:
		if (hSpacingIn == vSpacingIn)
		{
			hSpacingOut = 3; vSpacingOut = 2; bOk  = true;
		}
		break;
	case AJAScaleType960To1280:
	case AJAScaleType1440To1920:
		if (hSpacingIn == vSpacingIn)
		{
			hSpacingOut = 4; vSpacingOut = 3; bOk  = true;
		}
		break;
	default:
		break;
	}
	return bOk;
}

bool AJAPixelFormat::QueryScaleType(int xWire,int xBitmap,AJA_PixelFormat &primaryFormat,AJAScaleType &scaleType)
{
	bool bOk = true;
	if ((xWire == 1920) && (xBitmap == 1440))
	{
		scaleType	  = AJAScaleType1440To1920;
		primaryFormat = AJA_PixelFormat_YCbCr8;
	}
	else if ((xWire == 1920) && (xBitmap == 1280))
	{
		scaleType	  = AJAScaleType1280To1920;
		primaryFormat = AJA_PixelFormat_YCbCr8;
	}
	else if ((xWire == 1280) && (xBitmap == 960))
	{
		scaleType	  = AJAScaleType960To1280;
		primaryFormat = AJA_PixelFormat_YCbCr8;
	}
	else
	{
		bOk = false;
	}

	return bOk;
}


int AJAPixelFormat::QueryFullScaleWidth(int scaledWidth, int height)
{
	int fullScaleWidth = scaledWidth;
	
	if (height == 1080 && scaledWidth == 1280)
		fullScaleWidth = 1920;
	
	else if (height == 1080 && scaledWidth == 1440)
		fullScaleWidth = 1920;
	
	else if (height == 720 && scaledWidth == 960)
		fullScaleWidth = 1280;
		
	return fullScaleWidth;
}


AJA_PixelFormat AJAPixelFormat::QueryScaledPixelFormat(int scaledWidth, int height)
{
	AJA_PixelFormat pixelFormat = AJA_PixelFormat_Unknown;
	
	if (height == 1080 && scaledWidth == 1280)
		pixelFormat = AJA_PixelFormat_DVCPRO;
	
	else if (height == 1080 && scaledWidth == 1440)
		pixelFormat = AJA_PixelFormat_HDV;
	
	else if (height == 720 && scaledWidth == 960)
		pixelFormat = AJA_PixelFormat_HDV;
		
	return pixelFormat;
}
