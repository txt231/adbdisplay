#pragma once

#include <stdint.h>
#include "FourCC.h"

class ParamInfo
{
public:
	constexpr inline ParamInfo() noexcept
		: Id{0}
		, Reg{0}
		, Min{0}
		, Max{0}
		, Flags{0}
	{}
	constexpr inline ParamInfo(const uint32_t id, const uint8_t reg, const uint8_t minVal, const uint8_t maxVal, const uint8_t _5, const uint8_t flags) noexcept
		: Id{id}
		, Reg{reg}
		, Min{minVal}
		, Max{maxVal}
		, Flags{flags}
	{}
	constexpr inline ParamInfo(const char* pId, const uint8_t reg, const uint8_t minVal, const uint8_t maxVal, const uint8_t _5, const uint8_t flags) noexcept
		: Id{FourCC(pId)}
		, Reg{reg}
		, Min{minVal}
		, Max{maxVal}
		, Flags{flags}
	{}
	
	
	const uint32_t Id; // FourCC 
	const uint8_t Reg;
	const uint8_t Min;
	const uint8_t Max;
	const uint8_t Flags;
	
	inline bool Cacheable() const
	{
		return (Flags & 1) != 0;
	}
	inline bool Flag_2() const // write cache or something?
	{
		return (Flags & 2) != 0;
	}
	inline bool IsInverse() const
	{
		return (Flags & 4) != 0;
	}
	inline bool ReadOnly() const
	{
		return (Flags & 8) != 0;
	}
};