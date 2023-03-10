#include "Texture.h"

namespace
{
#pragma pack(push, 1)
	struct BitmapFileHeader
	{
		uint16_t type;
		uint32_t size;
		uint16_t reserved1;
		uint16_t reserved2;
		uint32_t offset;
	};

	struct BitmapInfoHeader
	{
		uint32_t size;
		int width, height;
		uint16_t planes;
		uint16_t bits;
		uint32_t compression;
		uint32_t imageSize;
		int xResolution, yResolution;
		uint32_t numColors;
		uint32_t importantColors;
	};

	uint32_t MakeStringAligned(uint32_t rowStride, uint32_t alignStride)
	{
		uint32_t newStride = rowStride;
		while (newStride % alignStride != 0)
		{
			newStride++;
		}
		return newStride;
	}
#pragma pack(pop)
	X::Color GetBilinearFilteredPixelColor(const Texture& tex, float u, float v)
	{
		float uTex = u * static_cast<float>(tex.GetWidth());
		float vTex = v * static_cast<float>(tex.GetHeight());

		int uInt = static_cast<int>(uTex);
		int vInt = static_cast<int>(vTex);

		float uRatio = uTex - static_cast<float>(uInt);
		float vRatio = vTex - static_cast<float>(vInt);


		float uOpposite = 1.0f - uRatio;
		float vOpposite = 1.0f - vRatio;

		X::Color a = tex.GetPixel(uInt, vInt) * uOpposite;
		X::Color b = tex.GetPixel(uInt + 1, vInt) * uRatio;
		X::Color c = tex.GetPixel(uInt, vInt + 1) * uOpposite;
		X::Color d = tex.GetPixel(uInt + 1, vInt + 1) * uRatio;

		return (a + b) * vOpposite
			+ (c + d) * vRatio;
		return 0;
	}

}

void Texture::Load(const std::string& fileName)
{
	mFileName = fileName;

	FILE* file = nullptr;
	fopen_s(&file, fileName.c_str(), "rb");
	if (file == nullptr)
	{
		return;
	}

	BitmapFileHeader fileHeader;
	BitmapInfoHeader infoHeader;
	fread(&fileHeader, sizeof(fileHeader), 1, file);
	fread(&infoHeader, sizeof(infoHeader), 1, file);

	if (infoHeader.bits != 24)
	{
		fclose(file);
		return;
	}

	mWidth = infoHeader.width;
	mHeight = infoHeader.height;
	mPixels = std::make_unique<X::Color[]>(mWidth * mHeight);

	fseek(file, fileHeader.offset, SEEK_SET);

	uint32_t rowStride = mWidth * infoHeader.bits / 8;
	uint32_t paddedStride = MakeStringAligned(rowStride, 4);
	std::vector<uint8_t> paddingBytes(paddedStride - rowStride);
	for (int h = 0; h < mHeight; ++h)
	{
		for (int w = 0; w < mWidth; ++w)
		{
			uint8_t r, g, b;
			fread(&b, sizeof(uint8_t), 1, file);
			fread(&g, sizeof(uint8_t), 1, file);
			fread(&r, sizeof(uint8_t), 1, file);
			uint32_t index = w + ((mHeight - h - 1) * mWidth);
			mPixels[index] = { r / 255.0f, g / 255.0f, b / 255.0f , 1.0f};
		}
		fread((char*)paddingBytes.data(), paddingBytes.size(), 1, file);
	}
	fclose(file);
}

const std::string& Texture::GetFileName() const
{
	return mFileName;
}

X::Color Texture::GetPixel(float u, float v, AddressMode mode, bool filter) const
{
	switch (mode)
	{
	case AddressMode::Clamp:
	{
		u = std::clamp(u, 0.0f, 1.0f);
		v = std::clamp(v, 0.0f, 1.0f);
	}
		break;
	case AddressMode::Wrap:
	{
		while (u > 1.0f)
		{
			u -= 1.0f;
		}
		while (u < 0.0f)
		{
			u += 1.0f;
		}
		while (v > 1.0f)
		{
			v -= 1.0f;
		}
		while (v < 0.0f)
		{
			v += 1.0f;
		}
	}
		break;
	case AddressMode::Mirror:
	{
		while (u > 2.0f)
		{
			u -= 2.0f;
		}
		u = (u > 1.0f) ? (2.0f - u) : u;
		while (v > 2.0f)
		{
			v -= 2.0f;
		}
		v = (v > 1.0f) ? (2.0f - v) : v;
	}
		break;
	case AddressMode::Border:
	{
		//if outside the boundaries, return border color
		if (u > 1.0f || u < 0.0f || v>1.0f || v < 0.0f)
		{
			return X::Colors::Pink;
		}
	}
		break;
	default:
		break;
	}
	if(filter)
		return GetBilinearFilteredPixelColor(*this, u, v);
	
	int uIndex = static_cast<int>(u * (mWidth - 1));
	int vIndex = static_cast<int>(v * (mHeight - 1));
	return GetPixel(uIndex, vIndex);
	
}

X::Color Texture::GetPixel(int x, int y) const
{
	x = std::clamp(x, 0, mWidth - 1);
	y = std::clamp(y, 0, mHeight - 1);
	return mPixels[x + (y * mWidth)];
}

int Texture::GetHeight() const
{
	return mHeight;
}

int Texture::GetWidth() const
{
	return mWidth;
}
