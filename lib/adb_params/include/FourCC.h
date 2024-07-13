#pragma once

#include <stdint.h>


// TODO: this should be inverse. doesnt really matter afaik
constexpr inline uint32_t FourCC(const char* pStr, const uint32_t count = 4) noexcept
{
	// return count > 0 ? (((uint32_t)pStr[0] << ((count-1)*8)) | (FourCC(pStr + 1, count - 1))) : 0;
	return count > 0 ? ((FourCC(pStr + 1, count - 1) << 8) | (uint32_t)pStr[0]) : 0;
};

