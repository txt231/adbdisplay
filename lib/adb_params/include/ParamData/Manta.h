#pragma once

#include "../ParamInfo.h"


namespace Params::Manta
{
	static const constexpr ParamInfo Manta_Rev_1[] = {
		ParamInfo("lrem",    2,  0,    1, 0),
		ParamInfo("powr",    3,  0,    1, 0),
		ParamInfo("wigg",    4,  0,    1, 0),
		ParamInfo("adft",    5, 10,    1, 8),
		ParamInfo("e2la",    6,  0,  255, 0),
		ParamInfo("e2ha",    7,  0,  255, 0),
		ParamInfo("e2rd",    8,  0,  255, 0),
		ParamInfo("e2dt",    9,  0,  255, 0),
		ParamInfo("kcod",   10,  0,  254, 0),
		ParamInfo("save",   11,  0,    3, 0),
		ParamInfo("dflt",   12, 10,    1, 8),
		ParamInfo("swpt",   13,  2,    4, 0),
		ParamInfo("lcnt",   14,  2,   63, 0),
		ParamInfo("rgan",   15,  2,   63, 0),
		ParamInfo("ggan",   16,  2,   63, 0),
		ParamInfo("bgan",   17,  2,   63, 0),
		ParamInfo("lbrt",   18,  2,   63, 0),
		ParamInfo("bklt",   19,  2,   32, 0),

		ParamInfo("shrp",   22,  2,    5, 7),
		ParamInfo("hpos",   23,  8,  255, 3),
		ParamInfo("vpos",   24,  8,   64, 7),

		ParamInfo("clok",   28,  8,   40, 3),
		ParamInfo("phas",   29,  8,   64, 3),

		ParamInfo("reso",   39,  0,   18, 0),

		ParamInfo("rddg",   42,  0,  255, 0),
		ParamInfo("grdg",   43,  0,  255, 0),
		ParamInfo("bldg",   44,  0,  255, 0),
		ParamInfo("pass",   45,  0,  255, 0),
		ParamInfo(),
	};

	static const constexpr ParamInfo Manta_Rev_2[] = {
		ParamInfo("lrem",    2,  0,    1, 0),
		ParamInfo("powr",    3,  0,    1, 0),
		ParamInfo("wigg",    4,  0,    1, 0),
		ParamInfo("adft",    5, 10,    1, 8),
		ParamInfo("e2la",    6,  0,  255, 0),
		ParamInfo("e2ha",    7,  0,    1, 0),
		ParamInfo("e2rd",    8,  0,  255, 0),
		ParamInfo("e2dt",    9,  0,  255, 0),
		ParamInfo("kcod",   10,  0,  138, 0),
		ParamInfo("save",   11,  0,    3, 0),
		ParamInfo("dflt",   12, 10,    1, 8),

		ParamInfo("swpt",   13,  2,    4, 0),
		ParamInfo("lcnt",   14,  2,   63, 0),
		ParamInfo("rgan",   15,  2,   63, 0),
		ParamInfo("ggan",   16,  2,   63, 0),
		ParamInfo("bgan",   17,  2,   63, 0),
		ParamInfo("lbrt",   18,  2,   63, 0),
		ParamInfo("bklt",   19,  2,   32, 0),

		ParamInfo("shrp",   22,  2,    5, 7),
		ParamInfo("hpos",   23,  8,  144, 3),
		ParamInfo("vpos",   24,  8,   56, 7),

		ParamInfo("clok",   28,  8,   32, 3),
		ParamInfo("phas",   29,  8,   62, 3),

		ParamInfo("reso",   39,  0,   18, 0),

		ParamInfo("rddg",   42,  0,  255, 0),
		ParamInfo("grdg",   43,  0,  255, 0),
		ParamInfo("bldg",   44,  0,  255, 0),
		ParamInfo(),
	};

}