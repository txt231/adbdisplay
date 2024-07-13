#include "AdbDisplayInterface.h"

#include <Params.h>

int32_t AdbDisplayInterface::Enable()
{
	printf("[%s] 1 - Enter\n", __FUNCTION__);

	int32_t status = AdbDevice::Enable();
	if (status != 0)
		return status;
	
	// service utility sets this?
	// SetValueSafe(2, 0); // "lrem"
	return 0;
}


bool AdbDisplayInterface::SetReg2(uint8_t displayReigster)
{
	

	AdbData<DisplayReg1> Reg({
		._0 = 0,
		.displayReg = displayReigster,
	});
	
	auto Status = Send(AdbOp(Listen, Reg_1), Reg);
	if (Status != 0)
		return false;
	
	// delays by 1 macos tick, which according to docks is 1 frame, which is assumed to be 60 fps ~= 15ms
	_delay_ms(15);
	
	Status = Send(AdbOp(Talk, Reg_1), Reg);
	if (Status != 0)
		return false;

	// delays by 1 macos tick, which according to docks is 1 frame, which is assumed to be 60 fps ~= 15ms
	_delay_ms(15);
	
	// why doesnt it compare reg here?

	return true;
}

bool AdbDisplayInterface::Detect()
{
	printf("[%s] 1 - Enter\n", __FUNCTION__);

	Enable();
	
	// reset ptr in 0xff
	if(!SetValue(0xFF, 0xFF))
		return false;

	uint8_t Value1;
	if(!GetValue(0xFF, Value1))
		return false;
	// printf("[%s] %i - 0x%02x\n", __FUNCTION__, 2, Value1);


	uint8_t DisplayTypeId;
	if(!GetValue(0xFF, DisplayTypeId))
		return false;
	// printf("[%s] %i - Montype - 0x%02x\n", __FUNCTION__, 3, DisplayTypeId);

	m_Type = (DisplayType)DisplayTypeId;

	switch(m_Type)
	{
	case DisplayType::Telecaster:
	{
		m_Revision = 1;
		m_VersionUnk = 7;
	}
	case DisplayType::Sousa:
	{
		if(!GetValue(0xFF, m_Revision))
			return false;

		m_VersionUnk = 7;
		// earlier version did this to read versionunk, but later just sets it to 7?
		// earlier is probably real way, but is unessecary
		/* 
		if(m_Revision == 1)
		{
			uint8_t _1;
			uint8_t _2;
			uint8_t _3;
			uint8_t _4;
			if (!GetValue(0xFF, _1) ||
				!GetValue(0xFF, _2) ||
				!GetValue(0xFF, _3) ||
				!GetValue(0xFF, _4))
				return false;
			
		} 
		
		if(!GetValue(0xFF, m_VersionUnk))
			return false;
		*/
		
		break;
	}
	case DisplayType::Hammerhead:
	case DisplayType::Orca: // Whaler is identified as orca, but changed to whaler
	case DisplayType::WarriorEZ:
	case DisplayType::Manta:
	{
		if(!GetValue(0xFF, m_Revision))
			return false;
		// printf("[%s] %i - MonRev - 0x%02x\n", __FUNCTION__, 3, m_Revision);

		if(!GetValue(0xFF, m_VersionUnk))
			return false;
		// printf("[%s] %i - MonRevUnk - 0x%02x\n", __FUNCTION__, 3, m_VersionUnk);

				
		// detect if it is a Whaler (if it doesnt have AV)
		if (m_Type == DisplayType::Orca)
		{
			uint8_t MonitorAv;
			if(!GetValue(5, MonitorAv))
				return false;
			// printf("[%s] %i - monav - 0x%02x\n", __FUNCTION__, 3, MonitorAv);
			
			if (m_Revision < 2)
			{
				if (MonitorAv != 0)
					m_Type = DisplayType::Whaler;
			}
			else
			{
				if (MonitorAv != 1)
					m_Type = DisplayType::Whaler;
			}
		}
		break;
	}
	
	default:
		printf("Unknown monitor type %i\n", DisplayTypeId);
		return false;
	}
	

	switch(m_Type)
	{
	case DisplayType::Telecaster: 
		m_pParams = Telecaster_Params[m_Revision];
		break;
	case DisplayType::Sousa:
		m_pParams = Sousa_Params[m_Revision];
		break;
	case DisplayType::Hammerhead: // 1710
		m_pParams = Hammerhead_Params[m_Revision];
		break;
	case DisplayType::Orca: // 850AV
		m_pParams = Orca_Params[m_Revision];
		break;
	case DisplayType::Whaler: // 850
		m_pParams = Whaler_Params[m_Revision];
		break;
	case DisplayType::WarriorEZ: // 750
		m_pParams = WarriorEZ_Params[m_Revision];
		break;
	case DisplayType::Manta: 
		m_pParams = Manta_Params[m_Revision];
		break;
	}

	if(m_pParams == nullptr)
		printf("Params is null. is ifdef enabled, or is this a new device?\n");
	
	return m_pParams != nullptr;
	// return true;
	
	/*
	if(!SetReg2(0xFF))
		return false;

	AdbData<DisplayReg2> Reg({
		._0 = 0,
		.value = 0xFF,
	});

	status = Send(AdbOp(Listen, Reg_2), Reg);
	if (status != 0)
		return false;
	
	printf("[%s] 1 - 0x%02x%02x\n", __FUNCTION__, Reg.raw[0], Reg.raw[1]);

	// read value in reg 0xFF?
	{
		// set read register to 0xff
		status = Send(AdbOp(Listen, Reg_1), Reg);
		if (status != 0)
			return false;

		// read value in read register
		status = Send(AdbOp(Talk, Reg_2), Reg);
		if (status != 0)
			return false;
	}

	printf("[%s] 2 - 0x%02x%02x\n", __FUNCTION__, Reg.raw[0], Reg.raw[1]);
	
	// read previously returned reg?
	{
		// set read register to ??
		status = Send(AdbOp(Listen, Reg_1), Reg);
		if (status != 0)
			return false;

		// read value in read register
		status = Send(AdbOp(Talk, Reg_2), Reg);
		if (status != 0)
			return false;
	}
	_delay_ms(15);
	printf("[%s] 3 - 0x%02x%02x\n", __FUNCTION__, Reg.raw[0], Reg.raw[1]);
	
	if((Reg.data.value & 0xF0) != 0)
	{
		// set read register to ??
		status = Send(AdbOp(Listen, Reg_1), Reg);
		if (status != 0)
			return false;

		// read value in read register
		status = Send(AdbOp(Talk, Reg_2), Reg);
		if (status != 0)
			return false;
		
		
		_delay_ms(15);
		printf("[%s] 4 - 0x%02x%02x\n", __FUNCTION__, Reg.raw[0], Reg.raw[1]);
	}
	
	if ((Reg.data.value == 2) ||
		(Reg.data.value == 3) ||
		(Reg.data.value == 5))
		m_Type = (DisplayType)Reg.data.value;
	else
		m_Type = RawDisplayType::AppleVision1710;
	
	
	return true;
	*/
}

bool AdbDisplayInterface::GetValue(uint8_t displayRegister, uint8_t& value)
{
	AdbData<DisplayReg1> DataReg({
		._0 = 0,
		.displayReg = displayRegister,
	});
	
	auto Status = Send(AdbOp(Listen, Reg_1), DataReg);
	if (Status != 0)
		return false;

	_delay_ms(15*2);
	
	AdbData<DisplayReg2> ValueReg({
		._0 = 0x00,
		.value = displayRegister
	});
	Status = Send(AdbOp(Talk, Reg_2), ValueReg);
	if (Status != 0)
		return false;	
	
	_delay_ms(15*2);

	value = ValueReg.data.value;

	return true;
}
bool AdbDisplayInterface::SetValue(uint8_t displayRegister, uint8_t value)
{
	AdbData<DisplayReg1> DataReg({
		._0 = 0,
		.displayReg = displayRegister,
	});
	auto Status = Send(AdbOp(Listen, Reg_1), DataReg);
	if (Status != 0)
		return false;

	_delay_ms(15*2);
	
	AdbData<DisplayReg2> ValueReg({
		._0 = 0x00,
		.value = value
	});
	Status = Send(AdbOp(Listen, Reg_2), ValueReg);
	if (Status != 0)
		return false;

	_delay_ms(15*2);

	return true;
}

bool AdbDisplayInterface::GetValueSafe(uint8_t displayRegister, uint8_t& value)
{
	if(!SetReg2(displayRegister))
		return false;
	
	AdbData<DisplayReg2> Reg({
		._0 = 0x00,
		.value = displayRegister
	});
	
	auto Status = Send(AdbOp(Talk, Reg_2), Reg);
	if (Status != 0)
		return false;	
	
	_delay_ms(15*1);

	value = Reg.data.value;

	return true;
}
bool AdbDisplayInterface::SetValueSafe(uint8_t displayRegister, uint8_t value)
{
	if (!SetReg2(displayRegister))
		return false;
	
	AdbData<DisplayReg2> Reg({
		._0 = 0x00,
		.value = value
	});
	
	auto Status = Send(AdbOp(Listen, Reg_2), Reg);
	if (Status != 0)
		return false;
	
	Status = Send(AdbOp(Talk, Reg_0), Reg);
	if (Status != 0)
		return false;

	if (m_Type == DisplayType::Orca ||
		m_Type == DisplayType::Whaler)
		_delay_ms(15*2);
	else
		_delay_ms(15*4);

	return true;
}


bool AdbDisplayInterface::GetValueId(uint32_t fourCC, uint8_t& value)
{
	if (!m_pParams)
		return false;

	const ParamInfo* pParam = m_pParams;
	while(pParam->m_Id != 0)
	{
		if (pParam->m_Id != fourCC)
			continue;
		
		return GetValue(pParam->m_Reg, value);
	}
	
	return false;
}
bool AdbDisplayInterface::SetValueId(uint32_t fourCC, uint8_t value)
{
	if (!m_pParams)
		return false;

	const ParamInfo* pParam = m_pParams;
	while(pParam->m_Id != 0)
	{
		if (pParam->m_Id != fourCC)
			continue;
		
		if (value > pParam->m_Max)
			value = pParam->m_Max;
		
		return SetValue(pParam->m_Reg, value);
	}
	
	return false;
}

bool AdbDisplayInterface::DumpSettings1()
{
	
	{
		if(!SetValueId("oskd", 0))
			return false;
		
		uint8_t TestSettings[3] = {};
		for (uint16_t i=0; i < 0x100; i++)
		{
			uint8_t Value;
			if(!GetValueId("osk1", Value))
			{
				printf("[%i] = ?\n", i);
				continue;
			}
			
			if (i < sizeof(TestSettings))
				TestSettings[i] = Value;
			
			if (TestSettings[0] == 0xFF &&
				TestSettings[1] == 0xFF &&
				TestSettings[2] == 0xFF)
			{
				if (m_Type == DisplayType::Orca ||
					m_Type == DisplayType::Whaler)
					printf("Unable to communicate with the display.\n\nThe CRT/Video board is defective.\n");
				else
					printf("There is no communication link with the display!\n\nMake sure the jumper is installed on the Video/CRT board.\n");
		
				TestSettings[0] = 0;
				// return false;
			}
			

			// this is +0x201

			printf("[%i] = %i\n", i, Value);
		}
	}
	{

		if(!SetValueId("oskd", 1))
			return false;

		for (uint16_t i=0; i < 0x100; i++)
		{
			uint8_t Value;
			if(!GetValueId("osk2", Value))
			{
				printf("[%i] = ?\n", i);
				// printf("[%s] %i - %i\n", __FUNCTION__, 6, i);
				continue;
			}
			

			// this is + 0x300
			printf("[%i] = %i\n", i, Value);
		}
	
	}

	return true;
	/*
	uint8_t Regs1[] = {
		51, 49, 50,
	};
	uint8_t Regs850[] = {
		87, 85, 86,
	};
	
	uint8_t* pRegs = Regs850;
	if (m_RawType == RawDisplayType::AppleVision1710 ||
		m_RawType == RawDisplayType::_1 ||
		m_RawType == RawDisplayType::AppleVision750)
		pRegs = Regs1;

	// unsure if ghidra is messing up here , but return value checks seem reversed?
	
	{
		if(!SetReg2(pRegs[0]))
		{
			printf("[%s] %i\n", __FUNCTION__, 1);
			return false;
		}

		if(!SetValueSafe(pRegs[0], 1))
		{
			printf("[%s] %i\n", __FUNCTION__, 2);
			return false;
		}

		uint8_t TestSettings[3] = {};
		for (uint16_t i=0; i < 0x100; i++)
		{
			uint8_t Value;
			if(!GetValueSafe(pRegs[1], Value))
			{
				printf("[%i] = ?\n", i);
				// printf("[%s] %i - %i\n", __FUNCTION__, 3, i);
				continue;
			}
			
			if (i < sizeof(TestSettings))
				TestSettings[i] = Value;
			
			if (TestSettings[0] == 0xFF &&
				TestSettings[1] == 0xFF &&
				TestSettings[2] == 0xFF)
			{
				if (m_RawType == RawDisplayType::AppleVision850)
					printf("Unable to communicate with the display.\n\nThe CRT/Video board is defective.\n");
				else
					printf("There is no communication link with the display!\n\nMake sure the jumper is installed on the Video/CRT board.\n");
		
				TestSettings[0] = 0;
				// return false;
			}
			

			// this is +0x201

			printf("[%i] = %i\n", i, Value);
		}
	}
	{
		if(!SetReg2(pRegs[0]))
		{
			printf("[%s] %i\n", __FUNCTION__, 4);
			return false;
		}

		if(!SetValueSafe(pRegs[0], 0))
		{
			printf("[%s] %i\n", __FUNCTION__, 5);
			return false;
		}

		for (uint16_t i=0; i < 0x100; i++)
		{
			uint8_t Value;
			if(!GetValueSafe(pRegs[2], Value))
			{
				printf("[%i] = ?\n", i);
				// printf("[%s] %i - %i\n", __FUNCTION__, 6, i);
				continue;
			}
			

			// this is + 0x300
			printf("[%i] = %i\n", i, Value);
		}
	}
	*/
	
}


bool AdbDisplayInterface::DumpSettings2()
{

	if(!SetValueId("e2ha", 0))
		return false;

	for(uint8_t i=0; i < 0x80; i++)
	{
		if(!SetValueId("e2la", i))
			return false;
		
		uint8_t Value;
		if(!GetValueId("e2dt", Value))
			printf("[%i] = ?\n", i);
		else
			printf("[%i] = %i\n", i, Value);
	}
	
	return true;
}
bool AdbDisplayInterface::SaveSettings()
{
	if (m_Type == DisplayType::Orca ||
		m_Type == DisplayType::Whaler)
	{
		auto fUnkSave = [this]() -> bool
		{
			if(!SetValueId("pass", 0x22))
				return false;
			
			if(!SetValueSafe(13, 0x22))
				return false;
			
			_delay_ms(180*15);
			
			return true;
		};

		uint8_t Sequence[]{
			0x71, 0x65, 0x60, 0x62, 
			0x61, 0x63, 0x64, 0x44
		};

		for (uint8_t i=0; i < sizeof(Sequence); i++)
			SetValueId("sgsv", Sequence[i]);

		if (!fUnkSave())
			return false;
		
		// store rotation value at position 15 in osk. guess it isnt saved otherwise?
		uint8_t Rotation;
		GetValueId("rota", Rotation);
		SetValueId("oskd", 15);
		SetValueId("pass", 0xEE);
		SetValueId("osk1", Rotation);
	}
	else
	{
		uint8_t Sequence[] = {
			0xaa, 0x99, 0x99, 0x66,
		};
		
		for(uint8_t i=0; i < sizeof(Sequence); i++)
		{
			if(!SetValueId("save", Sequence[i]))
				return false;
		}
	}
	
	return true;
}