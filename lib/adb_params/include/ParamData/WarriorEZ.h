#pragma once

#include "../ParamInfo.h"

namespace Params::WarriorEZ
{
	static const constexpr ParamInfo WarriorEZ_Rev_1[] = {

		ParamInfo("lrem",   2,  0,   1, 0, 0x0000),
		ParamInfo("powr",   3,  0,   1, 0, 0x0000),
		ParamInfo("wigg",   4,  0,   1, 0, 0x0000),
		ParamInfo("pwig",   5,  0,   1, 0, 0x0000),
		ParamInfo("e2la",   6,  0, 255, 0, 0x0000),
		ParamInfo("e2ha",   7,  0,   1, 0, 0x0000),
		ParamInfo("e2rd",   8,  0, 255, 0, 0x0000),
		ParamInfo("e2dt",   9,  0, 255, 0, 0x0000),
		ParamInfo("kcod",  10,  0,   1, 0, 0x0000),
		ParamInfo("save",  11, 85, 170, 0, 0x0000),

		ParamInfo("dflt",  13,  0,   0, 6, 0x0000),
		ParamInfo("over",  14,  0,   0, 4, 0x0000),

		ParamInfo("cmod",  15,  0,  13, 4, 0x0000),
		ParamInfo("nmxc",  15,  0, 255, 0, 0x0000),

		ParamInfo("cont",  16,  0, 221, 2, 0x0003),
		ParamInfo("brgt",  17,  0, 254, 2, 0x0003),
		ParamInfo("hcon",  18,  0, 254, 2, 0x0003),
		ParamInfo("vcon",  19,  0, 254, 2, 0x0003),
		ParamInfo("rota",  20,  0,  63, 2, 0x0003),

		ParamInfo("keys",  22,  0,  63, 4, 0x0003),
		ParamInfo("hwid",  23,  0, 254, 4, 0x0003),
		ParamInfo("hpos",  24,  0, 254, 4, 0x0003),
		ParamInfo("vhgt",  25,  0, 254, 4, 0x0003),
		ParamInfo("vpos",  26,  0,  63, 4, 0x0003),
		ParamInfo("pinc",  27,  0, 254, 4, 0x0003),
		ParamInfo("rgan",  28,  0, 254, 1, 0x0000),
		ParamInfo("ggan",  29,  0, 254, 1, 0x0000),
		ParamInfo("bgan",  30,  0, 254, 1, 0x0000),
		ParamInfo("rg1 ",  31,  0, 254, 1, 0x0000),
		ParamInfo("gg1 ",  32,  0, 254, 1, 0x0000),
		ParamInfo("bg1 ",  33,  0, 254, 1, 0x0000),
		ParamInfo("para",  34,  0,  63, 8, 0x0003),

		ParamInfo("rcur",  37,  0, 255, 0, 0x0000),
		ParamInfo("gcur",  38,  0, 255, 0, 0x0000),
		ParamInfo("bcur",  39,  0, 255, 0, 0x0000),
		ParamInfo("lran",  40,  0,   0, 0, 0x0000),
		ParamInfo("hran",  41,  0,   0, 0, 0x0000),

		ParamInfo("osk1",  49,  0, 255, 0, 0x0000), // CUSTOM
		ParamInfo("osk2",  40,  0, 255, 0, 0x0000), // CUSTOM
		ParamInfo("oskd",  41,  0, 255, 0, 0x0000), // CUSTOM
	

		ParamInfo("hvlt",  45, 154, 177, 0, 0x0000), // CUSTOM | range: 154-177 | default = 167
	
		ParamInfo(),
	};
}