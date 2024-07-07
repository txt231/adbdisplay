#include "AdbDisplayInterface.h"

int32_t AdbDisplayInterface::Enable()
{
	printf("[%s] 1 - Enter\n", __FUNCTION__);

	int32_t status = AdbDevice::Enable();
	if (status != 0)
		return status;
	
	SetValue(DispReg_Shared::_2, 0);
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

bool AdbDisplayInterface::SetValue(uint8_t displayRegister, uint8_t value)
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

	if (m_Type == DisplayType::AppleVision850 ||
		m_Type == DisplayType::_4)
		_delay_ms(15*2);
	else
		_delay_ms(15*4);

	return true;
}

bool AdbDisplayInterface::Detect()
{
	printf("[%s] 1 - Enter\n", __FUNCTION__);

	int32_t status;
	
	Enable();
	
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
		m_Type = DisplayType::AppleVision1710;

	printf("[%s] montor type %i\n", __FUNCTION__, m_Type);
	
	return true;
}