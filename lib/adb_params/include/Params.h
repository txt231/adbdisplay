#pragma once


#ifdef ADB_DISPLAY_TELECASTER
#include "ParamData/Telecaster.h"
#endif

#ifdef ADB_DISPLAY_SOUSA
#include "ParamData/Sousa.h"
#endif
#ifdef ADB_DISPLAY_HAMMERHEAD
#include "ParamData/Hammerhead.h"
#endif
#ifdef ADB_DISPLAY_ORCA
#include "ParamData/Orca.h"
#endif
#ifdef ADB_DISPLAY_WHALER
#include "ParamData/Whaler.h"
#endif
#ifdef ADB_DISPLAY_WARRIOREZ
#include "ParamData/WarriorEZ.h"
#endif
#ifdef ADB_DISPLAY_MANTA
#include "ParamData/Manta.h"
#endif

static const constexpr ParamInfo* Telecaster_Params[] {
#ifdef ADB_DISPLAY_TELECASTER
	nullptr,
	Params::Telecaster::Telecaster_Rev_1,
#else
	nullptr,
	nullptr,
#endif
};

static const constexpr ParamInfo* Sousa_Params[] {
#ifdef ADB_DISPLAY_SOUSA
	nullptr,
	Params::Sousa::Sousa_Rev_1,
#else
	nullptr,
	nullptr,
#endif
};

// AppleVision 1710
static const constexpr ParamInfo* Hammerhead_Params[] {
#ifdef ADB_DISPLAY_HAMMERHEAD
	nullptr,
	nullptr,
	nullptr,
	Params::Hammerhead::Hammerhead_Rev_3,
	Params::Hammerhead::Hammerhead_Rev_4,
#else
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
#endif
};

// AppleVision/ColorSync 850AV
static const constexpr ParamInfo* Orca_Params[] {
#ifdef ADB_DISPLAY_ORCA
	nullptr,
	nullptr, //Params::Orca::Orca_Rev_1,
	nullptr, //Params::Orca::Orca_Rev_2,
	Params::Orca::Orca_Rev_3
#else
	nullptr,
	nullptr,
	nullptr,
	nullptr,
#endif
};

// AppleVision/ColorSync 850
static const constexpr ParamInfo* Whaler_Params[] {
#ifdef ADB_DISPLAY_WHALER
	nullptr,
	nullptr, //Params::Whaler::Whaler_Rev_1,
	nullptr, //Params::Whaler::Whaler_Rev_2,
	Params::Whaler::Whaler_Rev_3,
#else
	nullptr,
	nullptr,
	nullptr,
	nullptr,
#endif
};

// AppleVision/ColorSync 750
static const constexpr ParamInfo* WarriorEZ_Params[] {
#ifdef ADB_DISPLAY_WARRIOREZ
	nullptr,
	Params::WarriorEZ::WarriorEZ_Rev_1,
#else
	nullptr,
	nullptr,
#endif
};

static const constexpr ParamInfo* Manta_Params[] {
#ifdef ADB_DISPLAY_MANTA
	nullptr,
	Params::Manta::Manta_Rev_1,
	Params::Manta::Manta_Rev_2,
#else
	nullptr,
	nullptr,
	nullptr,
#endif
};


// macos 9 has a bunch of parameters for "Moby MCS", and "Scruffy MCS"
// Im guessing MCS = Monitor Control System?