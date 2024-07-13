#pragma once

#include <stdint.h>
#include "FourCC.h"

class ParamInfo
{
public:
	constexpr inline ParamInfo() noexcept
		: m_Id{0}
		, m_Reg{0}
		, m_3{0}
		, m_Max{0}
	{}
	constexpr inline ParamInfo(const uint32_t id, const uint8_t reg, const uint8_t _3, const uint8_t maxVal, const uint16_t typeId) noexcept
		: m_Id{id}
		, m_Reg{reg}
		, m_3{_3}
		, m_Max{maxVal}
	{
	}
	constexpr inline ParamInfo(const char* pId, const uint8_t reg, const uint8_t _3, const uint8_t maxVal, const uint16_t typeId) noexcept
		: m_Id{FourCC(pId)}
		, m_Reg{reg}
		, m_3{_3}
		, m_Max{maxVal}
	{}
	
	
	const uint32_t m_Id; // FourCC 
	const uint8_t m_Reg;
	const uint8_t m_3; // im guessing this is min, but unsure
	const uint8_t m_Max;
};