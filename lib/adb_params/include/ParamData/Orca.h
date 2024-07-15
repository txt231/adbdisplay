#pragma once

#include "../ParamInfo.h"

namespace Params::Orca
{
	// i dont believe rev 1 or 2 is released to the public, disable them to make space for arduino.
	// static const constexpr ParamInfo Orca_Rev_1[] = {
	// 	ParamInfo("lrem",   2, 0,   1, 0, 0x0000),
	// 	ParamInfo("powr",   3, 0,   1, 0, 0x0000),
	// 	ParamInfo("wigg",   4, 0,   1, 0, 0x0000),

	// 	ParamInfo("e2la",   6, 0, 255, 0, 0x0000),
	// 	ParamInfo("e2ha",   7, 0,   1, 0, 0x0000),
	// 	ParamInfo("e2rd",   8, 0, 255, 0, 0x0000),
	// 	ParamInfo("e2dt",   9, 0, 255, 0, 0x0000),

	// 	ParamInfo("spkp",  14, 0,   1, 0, 0x0003),
	// 	ParamInfo("kcod",  15, 0,   1, 0, 0x0000),
	// 	ParamInfo("save",  16, 0, 254, 0, 0x0000),
	// 	ParamInfo("sgsv",  17, 0, 254, 0, 0x0000),
	// 	ParamInfo("dflt",  18, 0,   1, 0, 0x0000),
	// 	ParamInfo("over",  19, 0,   0, 0, 0x0000),
	// 	ParamInfo("pass",  20, 0, 255, 0, 0x0000),
	// 	ParamInfo("cont",  21, 0,  52, 0, 0x0003),
	// 	ParamInfo("brgt",  22, 0,  37, 0, 0x0003),
	// 	ParamInfo("hcon",  23, 0,  31, 0, 0x0003),
	// 	ParamInfo("vcon",  24, 0, 254, 0, 0x0003),
	// 	ParamInfo("rota",  25, 0,  63, 0, 0x0003),
	// 	ParamInfo("cmod",  26, 0,   5, 0, 0x0000),

	// 	ParamInfo("hwid",  45, 0, 254, 0, 0x0003),
	// 	ParamInfo("hpos",  46, 0, 254, 0, 0x0003),
	// 	ParamInfo("vhgt",  47, 0, 254, 0, 0x0003),
	// 	ParamInfo("vpos",  48, 0, 254, 0, 0x0003),
	// 	ParamInfo("pinc",  49, 0, 254, 0, 0x0003),
	// 	ParamInfo("keys",  50, 0,  63, 0, 0x0003),
	// 	ParamInfo("rgan",  51, 0, 254, 0, 0x0000),
	// 	ParamInfo("ggan",  52, 0, 254, 0, 0x0000),
	// 	ParamInfo("bgan",  53, 0, 254, 0, 0x0000),
	// 	ParamInfo("rg1 ",  54, 0, 254, 0, 0x0000),
	// 	ParamInfo("gg1 ",  55, 0, 254, 0, 0x0000),
	// 	ParamInfo("bg1 ",  56, 0, 254, 0, 0x0000),
	// 	ParamInfo("rbrf",  57, 0, 127, 0, 0x0000),
	// 	ParamInfo("gbrf",  58, 0, 127, 0, 0x0000),
	// 	ParamInfo("bbrf",  59, 0, 127, 0, 0x0000),
	// 	ParamInfo("para",  60, 0, 254, 0, 0x0003),
	// 	ParamInfo("bow ",  61, 0, 254, 0, 0x0003),
	// 	ParamInfo("g2g2",  62, 0,  63, 0, 0x0000),

	// 	ParamInfo("scor",  64, 0, 254, 0, 0x0003),
	// 	ParamInfo("ccor",  65, 0, 254, 0, 0x0003),
	// 	ParamInfo("tvco",  66, 0,  63, 0, 0x0003),
	// 	ParamInfo("bvco",  67, 0,  63, 0, 0x0003),

	// 	ParamInfo("sexy",  69, 0, 254, 0, 0x0003),
	// 	ParamInfo("hfoc",  70, 0, 254, 0, 0x0003),

	// 	ParamInfo("rcur",  88, 0, 255, 0, 0x0000),
	// 	ParamInfo("gcur",  89, 0, 255, 0, 0x0000),
	// 	ParamInfo("bcur",  90, 0, 255, 0, 0x0000),
	// 	ParamInfo("lran",  91, 0,   1, 0, 0x0000),
	// 	ParamInfo("hran",  92, 0,   1, 0, 0x0000),
	// 	ParamInfo("e2da",  93, 0, 255, 0, 0x0000),

	// 	ParamInfo("e2dd",  95, 0, 255, 0, 0x0000),

	// 	ParamInfo("svol", 102, 0,  50, 0, 0x0003),
	// 	ParamInfo("treb", 103, 0, 100, 0, 0x0003),
	// 	ParamInfo("bass", 104, 0, 100, 0, 0x0003),
	// 	ParamInfo("hvol", 105, 0,  50, 0, 0x0003),

	// 	ParamInfo("msns", 107, 0,   1, 0, 0x0000),

	// 	ParamInfo("isns", 109, 0,   1, 0, 0x0000),
	// 	ParamInfo("esns", 110, 0,   1, 0, 0x0000),
	// 	ParamInfo("pwdn", 111, 0,   1, 0, 0x0000),
	// 	ParamInfo("ins0", 112, 0,   1, 0, 0x0003),
	// 	ParamInfo("ins1", 113, 0,   1, 0, 0x0003),
	// 	ParamInfo("lthr", 114, 0,   1, 0, 0x0003),
	// 	ParamInfo("tcpu", 115, 0,   1, 0, 0x0003),
	// 	ParamInfo("surr", 116, 0,   1, 0, 0x0003),

	// 	ParamInfo("snst", 120, 0,   1, 0, 0x0003),
	// 	ParamInfo("orea", 121, 0, 255, 0, 0x0000),
	// 	ParamInfo("ored", 122, 0, 255, 0, 0x0000),

	// 	ParamInfo("orky", 125, 0,   1, 0, 0x0000),
	// 	ParamInfo(),
	// };

	// static const constexpr ParamInfo Orca_Rev_2[] = {
	// 	ParamInfo("lrem",   2, 0,   1, 0, 0x0000),
	// 	ParamInfo("powr",   3, 0,   1, 0, 0x0000),
	// 	ParamInfo("wigg",   4, 0,   1, 0, 0x0000),

	// 	ParamInfo("e2la",   6, 0, 255, 0, 0x0000),
	// 	ParamInfo("e2ha",   7, 0,   1, 0, 0x0000),
	// 	ParamInfo("e2rd",   8, 0, 255, 0, 0x0000),
	// 	ParamInfo("e2dt",   9, 0, 255, 0, 0x0000),

	// 	ParamInfo("spkp",  14, 0,   1, 0, 0x0003),
	// 	ParamInfo("kcod",  15, 0, 254, 0, 0x0000),
	// 	ParamInfo("save",  16, 0, 254, 0, 0x0000),
	// 	ParamInfo("sgsv",  17, 0, 254, 0, 0x0000),
	// 	ParamInfo("dflt",  18, 0,   1, 0, 0x0008),
	// 	ParamInfo("over",  19, 0,   1, 0, 0x0003),
	// 	ParamInfo("pass",  20, 0, 255, 0, 0x0000),
	// 	ParamInfo("cont",  21, 0,  56, 0, 0x0003),
	// 	ParamInfo("brgt",  22, 0,  40, 0, 0x0003),
	// 	ParamInfo("hcon",  23, 0,  31, 0, 0x0003),
	// 	ParamInfo("vcon",  24, 0, 254, 0, 0x0003),
	// 	ParamInfo("rota",  25, 0,  63, 0, 0x0003),

	// 	ParamInfo("para",  27, 0, 254, 0, 0x0007),
	// 	ParamInfo("tvco",  28, 0,  63, 0, 0x0003),
	// 	ParamInfo("bvco",  29, 0,  63, 0, 0x0003),
	// 	ParamInfo("cmod",  30, 0,   5, 0, 0x0000),

	// 	ParamInfo("hwid",  53, 0, 254, 0, 0x0003),
	// 	ParamInfo("hpos",  54, 0, 254, 0, 0x0007),
	// 	ParamInfo("vhgt",  55, 0, 254, 0, 0x0007),
	// 	ParamInfo("vpos",  56, 0, 254, 0, 0x0007),
	// 	ParamInfo("pinc",  57, 0, 254, 0, 0x0007),
	// 	ParamInfo("keys",  58, 0, 254, 0, 0x0007),
	// 	ParamInfo("rgan",  59, 0, 254, 0, 0x0000),
	// 	ParamInfo("ggan",  60, 0, 254, 0, 0x0000),
	// 	ParamInfo("bgan",  61, 0, 254, 0, 0x0000),
	// 	ParamInfo("rg1 ",  62, 0, 254, 0, 0x0000),
	// 	ParamInfo("gg1 ",  63, 0, 254, 0, 0x0000),
	// 	ParamInfo("bg1 ",  64, 0, 254, 0, 0x0000),
	// 	ParamInfo("rbrf",  65, 0, 127, 0, 0x0000),
	// 	ParamInfo("gbrf",  66, 0, 127, 0, 0x0000),
	// 	ParamInfo("bbrf",  67, 0, 127, 0, 0x0000),
	// 	ParamInfo("bow ",  68, 0, 254, 0, 0x0003),
	// 	ParamInfo("g2g2",  69, 0,  63, 0, 0x0000),

	// 	ParamInfo("scor",  71, 0, 254, 0, 0x0003),
	// 	ParamInfo("ccor",  72, 0, 254, 0, 0x0003),

	// 	ParamInfo("sexy",  74, 0,  63, 0, 0x0003),
	// 	ParamInfo("hfoc",  75, 0, 254, 0, 0x0003),

	// 	ParamInfo("rcur",  88, 0, 255, 0, 0x0000),
	// 	ParamInfo("gcur",  89, 0, 255, 0, 0x0000),
	// 	ParamInfo("bcur",  90, 0, 255, 0, 0x0000),
	// 	ParamInfo("lran",  91, 0,   1, 0, 0x0008),
	// 	ParamInfo("hran",  92, 0,   1, 0, 0x0008),
	// 	ParamInfo("e2dl",  93, 0, 255, 0, 0x0000),
	// 	ParamInfo("e2dh",  94, 0, 255, 0, 0x0000),
	// 	ParamInfo("e2dd",  95, 0, 255, 0, 0x0000),

	// 	ParamInfo("svol", 102, 0,  50, 0, 0x0003),
	// 	ParamInfo("treb", 103, 0, 100, 0, 0x0003),
	// 	ParamInfo("bass", 104, 0, 100, 0, 0x0003),
	// 	ParamInfo("hvol", 105, 0,  50, 0, 0x0003),
	// 	ParamInfo("esns", 106, 0,   1, 0, 0x0000),
	// 	ParamInfo("msns", 107, 0,   1, 0, 0x0000),

	// 	ParamInfo("isns", 109, 0,   1, 0, 0x0000),

	// 	ParamInfo("pwdn", 111, 0,   1, 0, 0x0000),
	// 	ParamInfo("ins0", 112, 0,   1, 0, 0x0003),
	// 	ParamInfo("ins1", 113, 0,   1, 0, 0x0003),
	// 	ParamInfo("lthr", 114, 0,   1, 0, 0x0003),
	// 	ParamInfo("tcpu", 115, 0,   1, 0, 0x0003),
	// 	ParamInfo("surr", 116, 0,   1, 0, 0x0003),
	// 	ParamInfo("mled", 117, 0,   1, 0, 0x0000),

	// 	ParamInfo("snst", 120, 0,   1, 0, 0x0003),
	// 	ParamInfo("orea", 121, 0, 255, 0, 0x0000),
	// 	ParamInfo("ored", 122, 0, 255, 0, 0x0000),

	// 	ParamInfo("orky", 125, 0,   1, 0, 0x0000),
	// 	ParamInfo(),
	// };

	// this is the same as Whaler, but added options for volume and mic control afaik
	static const constexpr ParamInfo Orca_Rev_3[] = {
	
		ParamInfo("lrem",   2,   0,    1, 0, 0x0000),
		ParamInfo("powr",   3,   0,    1, 0, 0x0000),
		ParamInfo("wigg",   4,   0,    1, 0, 0x0000),

		ParamInfo("e2la",   6,   0,  255, 0, 0x0000),
		ParamInfo("e2ha",   7,   0,    1, 0, 0x0000),
		ParamInfo("e2rd",   8,   0,  255, 0, 0x0000),
		ParamInfo("e2dt",   9,   0,  255, 0, 0x0000),

		ParamInfo("dedi",  11,   0,    1, 0, 0x0008), // added in later macos
		ParamInfo("dflt",  12,   0,    1, 0, 0x0008),

		ParamInfo("spkp",  14,   0,    1, 0, 0x0003),
		ParamInfo("kcod",  15,   0,  254, 0, 0x0000),
		ParamInfo("save",  16,  85,  170, 0, 0x0000), // range updated in newer macos
		ParamInfo("sgsv",  17,   0,  254, 0, 0x0000),
		ParamInfo("adft",  18,   0,    1, 7, 0x0008),

		ParamInfo("over",  19,   0,    1, 2, 0x0003),
		ParamInfo("nmxo",  19,   0,  255, 0, 0x0000),

		ParamInfo("pass",  20,   0,  255, 0, 0x0000),
		ParamInfo("cont",  21,   0,   56, 2, 0x0003),
		ParamInfo("brgt",  22,   0,   40, 2, 0x0003),
		ParamInfo("hcon",  23,   0,  254, 2, 0x0003),
		ParamInfo("vcon",  24,   0,  254, 2, 0x0003),
		ParamInfo("rota",  25,   0,   63, 2, 0x0003),
		ParamInfo("para",  27,   0,  254, 2, 0x0007),

		ParamInfo("tvco",  28,   0,   63, 2, 0x0003),
		ParamInfo("bvco",  29,   0,   63, 2, 0x0003),
		ParamInfo("cmod",  30,   0,    5, 1, 0x0000),

		ParamInfo("hwid",  53,   0,  254, 4, 0x0003),
		ParamInfo("hpos",  54,   0,  254, 4, 0x0007),
		ParamInfo("vhgt",  55,   0,  254, 4, 0x0007),
		ParamInfo("vpos",  56,   0,  254, 4, 0x0007),
		ParamInfo("pinc",  57,   0,  254, 4, 0x0007),
		ParamInfo("keys",  58,   0,  254, 4, 0x0007),
		ParamInfo("rgan",  59,   0,  254, 1, 0x0000),
		ParamInfo("ggan",  60,   0,  254, 1, 0x0000),
		ParamInfo("bgan",  61,   0,  254, 1, 0x0000),
		ParamInfo("rg1 ",  62,   0,  254, 1, 0x0000),
		ParamInfo("gg1 ",  63,   0,  254, 1, 0x0000),
		ParamInfo("bg1 ",  64,   0,  254, 1, 0x0000),
		ParamInfo("rbrf",  65,   0,  127, 0, 0x0000), // removed in later macos
		ParamInfo("gbrf",  66,   0,  127, 0, 0x0000), // removed in later macos
		ParamInfo("bbrf",  67,   0,  127, 0, 0x0000), // removed in later macos
		ParamInfo("bow ",  68,   0,  254, 0, 0x0003), // removed in later macos
		ParamInfo("g2g2",  69,   0,   63, 0, 0x0000), // removed in later macos

		// 70 = High voltage
		ParamInfo("hvlt",  70, 154, 177, 0, 0x0000), // CUSTOM | range: 154-177 | default = 167

		ParamInfo("scor",  71,   0,  254, 0, 0x0003), // removed in later macos
		ParamInfo("ccor",  72,   0,  254, 0, 0x0003), // removed in later macos

		ParamInfo("sexy",  74,   0,   63, 0, 0x0003), // removed in later macos
		ParamInfo("hfoc",  75,   0,  254, 0, 0x0003), // removed in later macos

		ParamInfo("osk1",  85,   0,  255, 0, 0x0000), // added in later macos
		ParamInfo("osk2",  86,   0,  255, 0, 0x0000), // added in later macos
		ParamInfo("oskd",  87,   0,  255, 0, 0x0000), // added in later macos
		ParamInfo("rcur",  88,   0,  255, 0, 0x0000),
		ParamInfo("gcur",  89,   0,  255, 0, 0x0000),
		ParamInfo("bcur",  90,   0,  255, 0, 0x0000),
		ParamInfo("lran",  91,   0,    1, 0, 0x0008),
		ParamInfo("hran",  92,   0,    1, 0, 0x0008),
		ParamInfo("e2dl",  93,   0,  255, 0, 0x0000),
		ParamInfo("e2dh",  94,   0,  255, 0, 0x0000),
		ParamInfo("e2dd",  95,   0,  255, 0, 0x0000),

		ParamInfo("svol", 102,   0,   50, 0, 0x0003),
		ParamInfo("smvl", 102,   0,  255, 0, 0x0000), // added in later macos
		ParamInfo("treb", 103,   0,   50, 0, 0x0003),
		ParamInfo("bass", 104,   0,   50, 0, 0x0003),
		ParamInfo("hvol", 105,   0,   50, 0, 0x0003),
		ParamInfo("esns", 106,   0,    1, 0, 0x0000),
		ParamInfo("msns", 107,   0,    1, 0, 0x0000),

		ParamInfo("isns", 109,   0,    1, 0, 0x0000),

		ParamInfo("pwdn", 111,   0,    1, 0, 0x0000), // removed in later macos
		ParamInfo("ins0", 112,   0,    1, 0, 0x0003),
		ParamInfo("ins1", 113,   0,    1, 0, 0x0003),
		ParamInfo("lthr", 114,   0,    1, 0, 0x0003),
		ParamInfo("tcpu", 115,   0,    1, 0, 0x0003),
		ParamInfo("surr", 116,   0,    1, 0, 0x0003),
		ParamInfo("mled", 117,   0,    1, 0, 0x0000),

		ParamInfo("snst", 120,   0,    1, 0, 0x0003),
		ParamInfo("orea", 121,   0,  255, 0, 0x0000),
		ParamInfo("ored", 122,   0,  255, 0, 0x0000),

		ParamInfo("orky", 125,   0,    1, 0, 0x0000),
		ParamInfo(),
	};
}

