#pragma once

#include "../ParamInfo.h"

namespace Params::WarriorEZ
{
	static const constexpr ParamInfo WarriorEZ_Rev_1[] = {
        ParamInfo("lrem",    2, 0,    1, 0),
        ParamInfo("powr",    3, 0,    1, 0),
        ParamInfo("wigg",    4, 0,    1, 0),
        ParamInfo("pwig",    5, 0,    1, 0),
        ParamInfo("e2la",    6, 0,  255, 0),
        ParamInfo("e2ha",    7, 0,    1, 0),
        ParamInfo("e2rd",    8, 0,  255, 0),
        ParamInfo("e2dt",    9, 0,  255, 0),
        ParamInfo("kcod",   10, 0,    1, 0),
        ParamInfo("save",   11, 0,  170, 0),

        ParamInfo("dflt",   13, 6,    0, 0),
        ParamInfo("over",   14, 4,    0, 0),
        ParamInfo("cmod",   15, 4,   13, 0),
        ParamInfo("nmxc",   15, 0,  255, 0),
        ParamInfo("cont",   16, 2,  221, 3),
        ParamInfo("brgt",   17, 2,  254, 3),
        ParamInfo("hcon",   18, 2,  254, 3),
        ParamInfo("vcon",   19, 2,  254, 3),
        ParamInfo("rota",   20, 2,   63, 3),

        ParamInfo("keys",   22, 4,   63, 3),
        ParamInfo("hwid",   23, 4,  254, 3),
        ParamInfo("hpos",   24, 4,  254, 3),
        ParamInfo("vhgt",   25, 4,  254, 3),
        ParamInfo("vpos",   26, 4,   63, 3),
        ParamInfo("pinc",   27, 4,  254, 3),
        ParamInfo("rgan",   28, 1,  254, 0),
        ParamInfo("ggan",   29, 1,  254, 0),
        ParamInfo("bgan",   30, 1,  254, 0),
        ParamInfo("rg1 ",   31, 1,  254, 0),
        ParamInfo("gg1 ",   32, 1,  254, 0),
        ParamInfo("bg1 ",   33, 1,  254, 0),
        ParamInfo("para",   34, 8,   63, 3),

        ParamInfo("rcur",   37, 0,  255, 0),
        ParamInfo("gcur",   38, 0,  255, 0),
        ParamInfo("bcur",   39, 0,  255, 0),
        ParamInfo("lran",   40, 0,    0, 0),
        ParamInfo("hran",   41, 0,    0, 0),
	

        ParamInfo("osk1",   49, 0,  255, 0), // CUSTOM
        ParamInfo("osk2",   50, 0,  255, 0), // CUSTOM
        ParamInfo("oskd",   51, 0,  255, 0), // CUSTOM
	
        ParamInfo(),
	};
}