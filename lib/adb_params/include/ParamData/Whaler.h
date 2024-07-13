#pragma once

#include "../ParamInfo.h"

namespace Params::Whaler
{

	// i dont believe rev 1 or 2 is released to the public, disable them to make space for arduino.
	// static const constexpr ParamInfo Whaler_Rev_1[] = {
	// 	ParamInfo("lrem",    2, 0,    1, 0),
	// 	ParamInfo("powr",    3, 0,    1, 0),
	// 	ParamInfo("wigg",    4, 0,    1, 0),
	// 	ParamInfo("o/w?",    5, 0,    1, 0),
	// 	ParamInfo("e2la",    6, 0,  255, 0),
	// 	ParamInfo("e2ha",    7, 0,    1, 0),
	// 	ParamInfo("e2al",    8, 0,  255, 0),
	// 	ParamInfo("e2rd",    8, 0,  255, 0),
	// 	ParamInfo("e2dt",    9, 0,  255, 0),
	// 	ParamInfo("kcod",   15, 0,    1, 0),
	// 	ParamInfo("save",   16, 0,  255, 0),
	// 	ParamInfo("sgsv",   17, 0,  255, 0),
	// 	ParamInfo("dflt",   18, 0,    1, 0),
	// 	ParamInfo("over",   19, 0,    0, 0),
	// 	ParamInfo("pass",   20, 0,  255, 0),
	// 	ParamInfo("cont",   21, 0,   52, 3),
	// 	ParamInfo("brgt",   22, 0,   37, 3),
	// 	ParamInfo("hcon",   23, 0,   31, 3),
	// 	ParamInfo("vcon",   24, 0,  254, 3),
	// 	ParamInfo("rota",   25, 0,   63, 3),
	// 	ParamInfo("cmod",   26, 0,    5, 0),
	// 	ParamInfo("hwid",   45, 0,  254, 3),
	// 	ParamInfo("hpos",   46, 0,  254, 3),
	// 	ParamInfo("vhgt",   47, 0,  254, 3),
	// 	ParamInfo("vpos",   48, 0,  254, 3),
	// 	ParamInfo("pinc",   49, 0,  254, 3),
	// 	ParamInfo("keys",   50, 0,   63, 3),
	// 	ParamInfo("rgan",   51, 0,  254, 0),
	// 	ParamInfo("ggan",   52, 0,  254, 0),
	// 	ParamInfo("bgan",   53, 0,  254, 0),
	// 	ParamInfo("rg1 ",   54, 0,  254, 0),
	// 	ParamInfo("gg1 ",   55, 0,  254, 0),
	// 	ParamInfo("bg1 ",   56, 0,  254, 0),
	// 	ParamInfo("rbrf",   57, 0,  254, 0),
	// 	ParamInfo("gbrf",   58, 0,  254, 0),
	// 	ParamInfo("bbrf",   59, 0,  254, 0),
	// 	ParamInfo("para",   60, 0,  254, 3),
	// 	ParamInfo("bow ",   61, 0,  254, 3),
	// 	ParamInfo("g2g2",   62, 0,   63, 0),
	// 	ParamInfo("scor",   64, 0,  254, 3),
	// 	ParamInfo("ccor",   65, 0,  254, 3),
	// 	ParamInfo("tvco",   66, 0,   63, 3),
	// 	ParamInfo("bvco",   67, 0,   63, 3),
	// 	ParamInfo("sexy",   69, 0,  254, 3),
	// 	ParamInfo("hfoc",   70, 0,  254, 3),
	// 	ParamInfo("rcur",   88, 0,  255, 0),
	// 	ParamInfo("gcur",   89, 0,  255, 0),
	// 	ParamInfo("bcur",   90, 0,  255, 0),
	// 	ParamInfo("lran",   91, 0,    1, 0),
	// 	ParamInfo("hran",   92, 0,    1, 0),
	// 	ParamInfo("e2da",   93, 0,  255, 0),
	// 	ParamInfo("e2dd",   95, 0,  255, 0),
	// 	ParamInfo("orky",  125, 0,    1, 0),
	// 	ParamInfo(),
	// };

	// static const constexpr ParamInfo Whaler_Rev_2[] = {
	// 	ParamInfo("lrem",    2, 0,    1, 0),
	// 	ParamInfo("powr",    3, 0,    1, 0),
	// 	ParamInfo("wigg",    4, 0,    1, 0),
	// 	ParamInfo("e2la",    6, 0,  255, 0),
	// 	ParamInfo("e2ha",    7, 0,    1, 0),
	// 	ParamInfo("e2rd",    8, 0,  255, 0),
	// 	ParamInfo("e2dt",    9, 0,  255, 0),
	// 	ParamInfo("spkp",   14, 0,    1, 3),
	// 	ParamInfo("kcod",   15, 0,  254, 0),
	// 	ParamInfo("save",   16, 0,  254, 0),
	// 	ParamInfo("sgsv",   17, 0,  254, 0),
	// 	ParamInfo("dflt",   18, 0,    1, 8),
	// 	ParamInfo("over",   19, 0,    1, 3),
	// 	ParamInfo("pass",   20, 0,  255, 0),
	// 	ParamInfo("cont",   21, 0,   56, 3),
	// 	ParamInfo("brgt",   22, 0,   40, 3),
	// 	ParamInfo("hcon",   23, 0,   31, 3),
	// 	ParamInfo("vcon",   24, 0,  254, 3),
	// 	ParamInfo("rota",   25, 0,   63, 3),
	// 	ParamInfo("para",   27, 0,  254, 7),
	// 	ParamInfo("tvco",   28, 0,   63, 3),
	// 	ParamInfo("bvco",   29, 0,   63, 3),
	// 	ParamInfo("cmod",   30, 0,    5, 0),
	// 	ParamInfo("hwid",   53, 0,  254, 3),
	// 	ParamInfo("hpos",   54, 0,  254, 7),
	// 	ParamInfo("vhgt",   55, 0,  254, 7),
	// 	ParamInfo("vpos",   56, 0,  254, 7),
	// 	ParamInfo("pinc",   57, 0,  254, 7),
	// 	ParamInfo("keys",   58, 0,  254, 7),
	// 	ParamInfo("rgan",   59, 0,  254, 0),
	// 	ParamInfo("ggan",   60, 0,  254, 0),
	// 	ParamInfo("bgan",   61, 0,  254, 0),
	// 	ParamInfo("rg1 ",   62, 0,  254, 0),
	// 	ParamInfo("gg1 ",   63, 0,  254, 0),
	// 	ParamInfo("bg1 ",   64, 0,  254, 0),
	// 	ParamInfo("rbrf",   65, 0,  127, 0),
	// 	ParamInfo("gbrf",   66, 0,  127, 0),
	// 	ParamInfo("bbrf",   67, 0,  127, 0),
	// 	ParamInfo("bow ",   68, 0,  254, 3),
	// 	ParamInfo("g2g2",   69, 0,   63, 0),
	// 	ParamInfo("scor",   71, 0,  254, 3),
	// 	ParamInfo("ccor",   72, 0,  254, 3),
	// 	ParamInfo("sexy",   74, 0,   63, 3),
	// 	ParamInfo("hfoc",   75, 0,  254, 3),
	// 	ParamInfo("rcur",   88, 0,  255, 0),
	// 	ParamInfo("gcur",   89, 0,  255, 0),
	// 	ParamInfo("bcur",   90, 0,  255, 0),
	// 	ParamInfo("lran",   91, 0,    1, 8),
	// 	ParamInfo("hran",   92, 0,    1, 8),
	// 	ParamInfo("e2dl",   93, 0,  255, 0),
	// 	ParamInfo("e2dh",   94, 0,  255, 0),
	// 	ParamInfo("e2dd",   95, 0,  255, 0),
	// 	ParamInfo(),
	// };

	// this seems to be ColorSync 850, unsure if earlier AppleVision 850 is the same.
	// probably is since earlier revisions was removed in system 9
	static const constexpr ParamInfo Whaler_Rev_3[] = {

		ParamInfo("lrem",    2, 0,    1, 0),
		ParamInfo("powr",    3, 0,    1, 0),
		ParamInfo("wigg",    4, 0,    1, 0),
		// 5 = is version/revision related
		ParamInfo("e2la",    6, 0,  255, 0), // E2 lower address?
		ParamInfo("e2ha",    7, 0,    1, 0), // E2 high address?
		ParamInfo("e2rd",    8, 0,  255, 0), // E2 read?
		ParamInfo("e2dt",    9, 0,  255, 0), // E2 ?
        ParamInfo("dedi",   11, 0,    1, 8), // included in later macos
		ParamInfo("dflt",   12, 0,    1, 8),

		ParamInfo("spkp",   14, 0,    1, 3), // removed in later macos
		ParamInfo("kcod",   15, 0,  254, 0),
		ParamInfo("save",   16, 0,  254, 0),
		ParamInfo("sgsv",   17, 0,  254, 0),
		ParamInfo("adft",   18, 0,    1, 8),
		ParamInfo("over",   19, 0,    1, 3),
		ParamInfo("pass",   20, 0,  255, 0),
		ParamInfo("cont",   21, 0,   56, 3),
		ParamInfo("brgt",   22, 0,   40, 3),
		ParamInfo("hcon",   23, 0,  254, 3),
		ParamInfo("vcon",   24, 0,  254, 3),
		ParamInfo("rota",   25, 0,   63, 3),
		ParamInfo("para",   27, 0,  254, 7),
		ParamInfo("tvco",   28, 0,   63, 3),
		ParamInfo("bvco",   29, 0,   63, 3),
		ParamInfo("cmod",   30, 0,    5, 0),

		ParamInfo("hwid",   53, 0,  254, 3),
		ParamInfo("hpos",   54, 0,  254, 7),
		ParamInfo("vhgt",   55, 0,  254, 7),
		ParamInfo("vpos",   56, 0,  254, 7),
		ParamInfo("pinc",   57, 0,  254, 7),
		ParamInfo("keys",   58, 0,  254, 7),
		ParamInfo("rgan",   59, 0,  254, 0),
		ParamInfo("ggan",   60, 0,  254, 0),
		ParamInfo("bgan",   61, 0,  254, 0),
		ParamInfo("rg1 ",   62, 0,  254, 0),
		ParamInfo("gg1 ",   63, 0,  254, 0),
		ParamInfo("bg1 ",   64, 0,  254, 0),
		ParamInfo("rbrf",   65, 0,  127, 0), // removed in later macos 
		ParamInfo("gbrf",   66, 0,  127, 0), // removed in later macos
		ParamInfo("bbrf",   67, 0,  127, 0), // removed in later macos
		ParamInfo("bow ",   68, 0,  254, 3), // removed in later macos
		ParamInfo("g2g2",   69, 0,   63, 0), // removed in later macos
	
		// 70 = High voltage
		ParamInfo("hvlt",   70, 0,  177, 0), // CUSTOM | range: 154-177
	
		ParamInfo("scor",   71, 0,  254, 3), // removed in later macos 
		ParamInfo("ccor",   72, 0,  254, 3), // removed in later macos 

		ParamInfo("sexy",   74, 0,   63, 3), // removed in later macos 
		ParamInfo("hfoc",   75, 0,  254, 3), // removed in later macos 

        ParamInfo("osk1",   85, 0,  255, 0), // included in later macos
        ParamInfo("osk2",   86, 0,  255, 0), // included in later macos
        ParamInfo("oskd",   87, 0,  255, 0), // included in later macos
		ParamInfo("rcur",   88, 0,  255, 0),
		ParamInfo("gcur",   89, 0,  255, 0),
		ParamInfo("bcur",   90, 0,  255, 0),
		ParamInfo("lran",   91, 0,    1, 8),
		ParamInfo("hran",   92, 0,    1, 8),
		ParamInfo("e2dl",   93, 0,  255, 0),
		ParamInfo("e2dh",   94, 0,  255, 0),
		ParamInfo("e2dd",   95, 0,  255, 0),
		ParamInfo(),
	};
}
