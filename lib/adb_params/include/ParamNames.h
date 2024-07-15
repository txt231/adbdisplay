#pragma once

#include <stdint.h>

#include "FourCC.h"

namespace Params
{
	class ParamNameEntry
	{
	public:
		constexpr inline ParamNameEntry()
			: Id{0}
			, pName{nullptr}
		{}
		constexpr inline ParamNameEntry(const uint32_t id, const char* pName)
			: Id{id}
			, pName{pName}
		{}
		constexpr inline ParamNameEntry(const char* pId, const char* pName)
			: Id{FourCC(pId)}
			, pName{pName}
		{}

		const uint32_t Id;
		const char* pName; 
	};


	static const constexpr ParamNameEntry ParamNames[] {
		ParamNameEntry("lrem", "OSD Mode"), // disables osd and allows config over ADB

		ParamNameEntry("powr", "Power State"),

		ParamNameEntry("cont", "Contrast"),
		ParamNameEntry("brgt", "Brightness"),
		ParamNameEntry("hcon", "Horizontal Convergence"),
		ParamNameEntry("vcon", "Vertical Convergence"),
		ParamNameEntry("rota", "Rotation"),
		ParamNameEntry("rot ", "Rotation"),


		ParamNameEntry("hwid", "Horizontal Width"),
		ParamNameEntry("hpos", "Horizontal Pos"),
		ParamNameEntry("vhgt", "Vertical Height"),
		ParamNameEntry("vpos", "Vertical Pos"),
		ParamNameEntry("pinc", "Pincushion"),
		ParamNameEntry("keys", "Keystone"),

		ParamNameEntry("rgan", "Red Gain"),
		ParamNameEntry("ggan", "Green Gain"),
		ParamNameEntry("bgan", "Blue Gain"),
		ParamNameEntry("rg2 ", "Red Cut"),
		ParamNameEntry("gg2 ", "Green Cut"),
		ParamNameEntry("bg2 ", "Blue Cut"),

		ParamNameEntry("hvlt", "High Voltage"),

		ParamNameEntry("scor", "S correction"),
		ParamNameEntry("scor", "C correction"),

		ParamNameEntry("hfoc", "Horizontal Focus"),


		// described in one of the patents where they hook an ADC up to rgb outputs, and use it to calibrate whitepoint
		// ParamNameEntry("rcur", "Red Current"),
		// ParamNameEntry("gcur", "Green Current"),
		// ParamNameEntry("bcur", "Blue Current"),
	

		ParamNameEntry()
	};


	static const char* GetNameById(const uint32_t id)
	{
		const ParamNameEntry* pParam = ParamNames;
		for(; pParam->Id != 0; pParam++)
		{
			if (pParam->Id != id)
				continue;
		
			return pParam->pName;
		}
		return nullptr;
	}

	static inline constexpr const char* GetNameById(const char* pId)
	{
		return GetNameById(FourCC(pId));
	}
}