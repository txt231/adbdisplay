#pragma once

#include "ParamData/Telecaster.h"
#include "ParamData/Sousa.h"
#include "ParamData/Hammerhead.h"
#include "ParamData/Orca.h"
#include "ParamData/Whaler.h"

ParamInfo* Telecaster_Params[] {
	nullptr,
	Telecaster::Telecaster_Rev_1,
};

ParamInfo* Sousa_Params[] {
	nullptr,
	Sousa::Sousa_Rev_1,
};

ParamInfo* Hammerhead_Params[] {
	nullptr,
	nullptr,
	nullptr,
	Hammerhead::Hammerhead_Rev_3,
	Hammerhead::Hammerhead_Rev_4,
};

// AppleVision/ColorSync 850AV
ParamInfo* Orca_Params[] {
	nullptr,
	Orca::Orca_Rev_1,
	Orca::Orca_Rev_2,
	Orca::Orca_Rev_3
};

// AppleVision/ColorSync 850
ParamInfo* Whaler_Params[] {
	nullptr,
	Whaler::Whaler_Rev_1,
	Whaler::Whaler_Rev_2,
	Whaler::Whaler_Rev_3,
};