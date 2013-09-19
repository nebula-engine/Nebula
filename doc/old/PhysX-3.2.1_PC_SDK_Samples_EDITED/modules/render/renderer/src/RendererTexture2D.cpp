

#include <RendererTexture2D.h>
#include <RendererTexture2DDesc.h>
#include "foundation/PxMath.h"

using namespace SampleRenderer;

static PxU32 computeCompressedDimension(PxU32 dimension)
{
	if(dimension < 4)
	{
		dimension = 4;
	}
	else
	{
		PxU32 mod = dimension % 4;
		if(mod) dimension += 4 - mod;
	}
	return dimension;
}

PxU32 RendererTexture2D::computeImageByteSize(PxU32 width, PxU32 height, RendererTexture2D::Format format)
{
	PxU32 size = 0;
	PxU32 numPixels = width * height;
	switch(format)
	{
	case RendererTexture2D::FORMAT_B8G8R8A8:
	case RendererTexture2D::FORMAT_R8G8B8A8:
		size = numPixels * sizeof(PxU8) * 4;
		break;
	case RendererTexture2D::FORMAT_A8:
		size = numPixels * sizeof(PxU8) * 1;
		break;
	case RendererTexture2D::FORMAT_R32F:
		size = numPixels * sizeof(float);
		break;
	case RendererTexture2D::FORMAT_DXT1:
		width  = computeCompressedDimension(width);
		height = computeCompressedDimension(height);
		size   = computeImageByteSize(width, height, RendererTexture2D::FORMAT_B8G8R8A8) / 8;
		break;
	case RendererTexture2D::FORMAT_DXT3:
	case RendererTexture2D::FORMAT_DXT5:
		width  = computeCompressedDimension(width);
		height = computeCompressedDimension(height);
		size   = computeImageByteSize(width, height, RendererTexture2D::FORMAT_B8G8R8A8) / 4;
		break;
	case RendererTexture2D::FORMAT_PVR_2BPP:
		{
			PxU32 bytesPerBlock = 8 * 4 * 2; //8 by 4 pixels times bytes per pixel
			width = PxMax(PxI32(width / 8), 2);
			height = PxMax(PxI32(height / 4), 2);
			size = width*height*bytesPerBlock / 8;
		}
		break;
		case RendererTexture2D::FORMAT_PVR_4BPP:
		{
			PxU32 bytesPerBlock = 4 * 4 * 4; //4 by 4 pixels times bytes per pixel
			width = PxMax(PxI32(width / 4), 2);
			height = PxMax(PxI32(height / 4), 2);
			size = width*height*bytesPerBlock / 8;
		}
		break;
			
	}
	RENDERER_ASSERT(size, "Unable to compute Image Size.");
	return size;
}

PxU32 RendererTexture2D::getLevelDimension(PxU32 dimension, PxU32 level)
{
	dimension >>=level;
	if(!dimension) dimension=1;
	return dimension;
}

bool RendererTexture2D::isCompressedFormat(Format format)
{
	return (format >= FORMAT_DXT1 && format <= FORMAT_DXT5) || (format == FORMAT_PVR_2BPP) || (format == FORMAT_PVR_4BPP);
}

bool RendererTexture2D::isDepthStencilFormat(Format format)
{
	return (format >= FORMAT_D16 && format <= FORMAT_D24S8);
}

PxU32 RendererTexture2D::getFormatNumBlocks(PxU32 dimension, Format format)
{
	PxU32 blockDimension = 0;
	if(isCompressedFormat(format))
	{
		blockDimension = dimension / 4;
		if(dimension % 4) blockDimension++;
	}
	else
	{
		blockDimension = dimension;
	}
	return blockDimension;
}

PxU32 RendererTexture2D::getFormatBlockSize(Format format)
{
	return computeImageByteSize(1, 1, format);
}

RendererTexture2D::RendererTexture2D(const RendererTexture2DDesc &desc)
{
	m_format      = desc.format;
	m_filter      = desc.filter;
	m_addressingU = desc.addressingU;
	m_addressingV = desc.addressingV;
	m_width       = desc.width;
	m_height      = desc.height;
	m_numLevels   = desc.numLevels;
}

RendererTexture2D::~RendererTexture2D(void)
{

}

PxU32 RendererTexture2D::getWidthInBlocks(void) const
{
	return getFormatNumBlocks(getWidth(), getFormat());
}

PxU32 RendererTexture2D::getHeightInBlocks(void) const
{
	return getFormatNumBlocks(getHeight(), getFormat());
}

PxU32 RendererTexture2D::getBlockSize(void) const
{
	return getFormatBlockSize(getFormat());
}
