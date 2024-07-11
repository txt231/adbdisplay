#pragma once

#include "../ParamInfo.h"

namespace Sousa
{

	ParamInfo Sousa_Rev_1[] = {
		ParamInfo('svol',  1, 0,  50, 3),
		ParamInfo('treb',  2, 0, 100, 3),
		ParamInfo('bass',  3, 0, 100, 3),
		ParamInfo('hvol',  4, 0,  50, 3),
		ParamInfo('isns',  5, 0,   1, 0),
		ParamInfo('msns',  6, 0,   1, 0),
		ParamInfo('hsns',  7, 0,   1, 0),
		ParamInfo('esns',  8, 0,   1, 0),
		ParamInfo('ins0', 11, 0,   1, 3),
		ParamInfo('ins1', 12, 0,   1, 3),
		ParamInfo('lthr', 13, 0,   1, 3),
		ParamInfo('tcpu', 14, 0,   1, 3),
		ParamInfo('pwig', 15, 0,   1, 0),
		ParamInfo('stro', 18, 0,   1, 3),
		ParamInfo('snst', 19, 0,   1, 3),
		ParamInfo('e2al', 20, 0, 255, 0),
		ParamInfo('e2ds', 21, 0, 255, 0),
		ParamInfo('kypd', 22, 0, 255, 0),
		ParamInfo(),
	};

}