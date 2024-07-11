#pragma once

#include <stdint.h>

class ParamInfo
{
public:
	inline ParamInfo()
		: id(0)
	{}
	inline ParamInfo(uint32_t id, uint8_t reg, uint8_t min, uint8_t max, uint16_t type)
		: id(id)
		, reg(reg)
		, min(min)
		, max(max)
	{}
	
	uint32_t id; // FourCC 
	uint8_t reg;
	uint8_t min;
	uint8_t max;
};