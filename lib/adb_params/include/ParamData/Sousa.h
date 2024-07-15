#pragma once

#include "../ParamInfo.h"

namespace Params::Sousa
{

	static const constexpr ParamInfo Sousa_Rev_1[] = {
	
		ParamInfo("svol",   1, 0,  50, 0, 0x0003),
		ParamInfo("smvl",   1, 0, 255, 0, 0x0000), // added in later macos
		ParamInfo("treb",   2, 0, 100, 0, 0x0003),
		ParamInfo("bass",   3, 0, 100, 0, 0x0003),
		ParamInfo("hvol",   4, 0,  50, 0, 0x0003),
		ParamInfo("isns",   5, 0,   1, 0, 0x0000),
		ParamInfo("msns",   6, 0,   1, 0, 0x0000),
		ParamInfo("hsns",   7, 0,   1, 0, 0x0000),
		ParamInfo("esns",   8, 0,   1, 0, 0x0000),

		ParamInfo("ins0",  11, 0,   1, 0, 0x0003),
		ParamInfo("ins1",  12, 0,   1, 0, 0x0003),
		ParamInfo("lthr",  13, 0,   1, 0, 0x0003),
		ParamInfo("tcpu",  14, 0,   1, 0, 0x0003),
		ParamInfo("pwig",  15, 0,   1, 0, 0x0000),

		ParamInfo("stro",  18, 0,   1, 0, 0x0003),
		ParamInfo("snst",  19, 0,   1, 0, 0x0003),
		ParamInfo("e2al",  20, 0, 255, 0, 0x0000),
		ParamInfo("e2ds",  21, 0, 255, 0, 0x0000),
		ParamInfo("kypd",  22, 0, 255, 0, 0x0000),


		ParamInfo("osk1",  49, 0, 255, 0, 0x0000), // CUSTOM
		ParamInfo("osk2",  40, 0, 255, 0, 0x0000), // CUSTOM
		ParamInfo("oskd",  41, 0, 255, 0, 0x0000), // CUSTOM
	
		ParamInfo(),
	};

}