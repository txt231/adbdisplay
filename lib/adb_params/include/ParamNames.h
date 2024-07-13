#pragma once

#include <stdint.h>

#include "FourCC.h"

class ParamNameEntry
{
public:
	constexpr inline ParamNameEntry(const uint32_t id, const char* pName)
		: m_Id{id}
		, m_pName{pName}
	{}
	constexpr inline ParamNameEntry(const char* pId, const char* pName)
		: m_Id{FourCC(pId)}
		, m_pName{pName}
	{}

	const uint32_t m_Id;
	const char* m_pName; 
};


static const constexpr ParamNameEntry ParamNames[] {
	ParamNameEntry("powr", "Power State"),

	ParamNameEntry("cont", "Contrast"),
	ParamNameEntry("brgt", "Brightness"),
	ParamNameEntry("hcon", "Horizontal Convergence"),
	ParamNameEntry("vcon", "Vertical Convergence"),
	ParamNameEntry("rota", "Rotation"),


	ParamNameEntry("hwid", "Horizontal Width"),
	ParamNameEntry("hpos", "Horizontal Pos"),
	ParamNameEntry("vhgt", "Vertical Height"),
	ParamNameEntry("vpos", "Vertical Pos"),


	ParamNameEntry("pinc", "Pincushion"),
	ParamNameEntry("keys", "Keystone"),

	ParamNameEntry("rgan", "Red Gain"),
	ParamNameEntry("ggan", "Green Gain"),
	ParamNameEntry("bgan", "Blue Gain"),

	ParamNameEntry("hvlt", "High Voltage"),

	ParamNameEntry("hfoc", "Horizontal Focus"),


	// described in one of the patents where they hook ADC up to rgb outputs, and use it to calibrate whitepoint
	// ParamNameEntry("rcur", "Red Current"),
	// ParamNameEntry("gcur", "Green Current"),
	// ParamNameEntry("bcur", "Blue Current"),
};