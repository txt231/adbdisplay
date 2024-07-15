#pragma once

#include "../ParamInfo.h"


namespace Params::Manta
{
	static const constexpr ParamInfo Manta_Rev_1[] = {

		ParamInfo("lrem",   2, 0,   1, 0, 0x0000),
		ParamInfo("powr",   3, 0,   1, 0, 0x0000),
		ParamInfo("wigg",   4, 0,   1, 0, 0x0000),
		ParamInfo("adft",   5, 0,   1,10, 0x0008),
		ParamInfo("e2la",   6, 0, 255, 0, 0x0000),
		ParamInfo("e2ha",   7, 0, 255, 0, 0x0000),
		ParamInfo("e2rd",   8, 0, 255, 0, 0x0000),
		ParamInfo("e2dt",   9, 0, 255, 0, 0x0000),
		ParamInfo("kcod",  10, 0, 254, 0, 0x0000),
		ParamInfo("save",  11, 0,   3, 0, 0x0000),
		ParamInfo("dflt",  12, 0,   1,10, 0x0008),
		ParamInfo("swpt",  13, 0,   4, 2, 0x0000),
		ParamInfo("lcnt",  14, 0,  63, 2, 0x0000),
		ParamInfo("rgan",  15, 0,  63, 2, 0x0000),
		ParamInfo("ggan",  16, 0,  63, 2, 0x0000),
		ParamInfo("bgan",  17, 0,  63, 2, 0x0000),
		ParamInfo("lbrt",  18, 0,  63, 2, 0x0000),
		ParamInfo("bklt",  19, 0,  32, 2, 0x0000),

		ParamInfo("shrp",  22, 0,   5, 2, 0x0007),
		ParamInfo("hpos",  23, 0, 255, 8, 0x0003),
		ParamInfo("vpos",  24, 0,  64, 8, 0x0007),

		ParamInfo("clok",  28, 0,  40, 8, 0x0003),
		ParamInfo("phas",  29, 0,  64, 8, 0x0003),

		ParamInfo("reso",  39, 0,  18, 0, 0x0000),

		ParamInfo("rddg",  42, 0, 255, 0, 0x0000),
		ParamInfo("grdg",  43, 0, 255, 0, 0x0000),
		ParamInfo("bldg",  44, 0, 255, 0, 0x0000),
		ParamInfo("pass",  45, 0, 255, 0, 0x0000),
		ParamInfo(),
	};

	static const constexpr ParamInfo Manta_Rev_2[] = {

		ParamInfo("lrem",   2, 0,   1, 0, 0x0000),
		ParamInfo("powr",   3, 0,   1, 0, 0x0000),
		ParamInfo("wigg",   4, 0,   1, 0, 0x0000),
		ParamInfo("adft",   5, 0,   1,10, 0x0008),
		ParamInfo("e2la",   6, 0, 255, 0, 0x0000),
		ParamInfo("e2ha",   7, 0,   1, 0, 0x0000),
		ParamInfo("e2rd",   8, 0, 255, 0, 0x0000),
		ParamInfo("e2dt",   9, 0, 255, 0, 0x0000),
		ParamInfo("kcod",  10, 0, 138, 0, 0x0000),
		ParamInfo("save",  11, 0,   3, 0, 0x0000),
		ParamInfo("dflt",  12, 0,   1,10, 0x0008),
		ParamInfo("swpt",  13, 0,   4, 2, 0x0000),
		ParamInfo("lcnt",  14, 0,  63, 2, 0x0000),
		ParamInfo("rgan",  15, 0,  63, 2, 0x0000),
		ParamInfo("ggan",  16, 0,  63, 2, 0x0000),
		ParamInfo("bgan",  17, 0,  63, 2, 0x0000),
		ParamInfo("lbrt",  18, 0,  63, 2, 0x0000),
		ParamInfo("bklt",  19, 0,  32, 2, 0x0000),

		ParamInfo("shrp",  22, 0,   5, 2, 0x0007),
		ParamInfo("hpos",  23, 48,144, 8, 0x0003),
		ParamInfo("vpos",  24, 8,  56, 8, 0x0007),

		ParamInfo("clok",  28, 8,  32, 8, 0x0003),
		ParamInfo("phas",  29, 2,  62, 8, 0x0003),

		ParamInfo("reso",  39, 0,  18, 0, 0x0000),

		ParamInfo("rddg",  42, 0, 255, 0, 0x0000),
		ParamInfo("grdg",  43, 0, 255, 0, 0x0000),
		ParamInfo("bldg",  44, 0, 255, 0, 0x0000),
		ParamInfo(),
	};

}