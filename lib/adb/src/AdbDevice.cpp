
#include "AdbDevice.h"

void AdbDevice::SelfTest()
{
	AdbData<AdbReg3> Cmd(AdbReg3{
		.info = {
			.adbAddr = 0,
			._reserved1 = 0,
			.srq_enable = false,
			.exceptional_event = false,
			._reserved0 = 0
		},
		.devType = 0xFF,
	}); 
	
	Send(AdbOp(Talk, Reg_3), Cmd);
}

void AdbDevice::SetAddr(uint8_t addr)
{
	AdbData<AdbReg3> Cmd(AdbReg3 {
		.info = {
			.adbAddr = addr,

			._reserved1 = 0,
			.srq_enable = false,
			.exceptional_event = false,
			._reserved0 = 0,
		},
		.devType = 0xFE,
	}); 
	
	auto Result = Send(AdbOp(Talk, Reg_3), Cmd);
	
	if (Result == 0)
		m_Addr = addr;
}

int32_t AdbDevice::Enable()
{
	printf("[%s] 1 - Enter\n", __FUNCTION__);

	int32_t status;

	AdbData<AdbReg3> Cmd(AdbReg3{
		.info = {
			.adbAddr = m_Addr,
			._reserved1 = 0,
			.srq_enable = true,
			.exceptional_event = true,
			._reserved0 = 0,
		},

		.devType = 0x00,
	}); 
	
	status = Send(AdbOp(Listen, Reg_3), Cmd);
	if (status != 0)
		return status;
	
	status = m_Interface.Send(AdbOp(Talk, Reg_3), Cmd);
	if (status != 0)
		return status;
	

	printf("[Enable] got %02x%02x\n", Cmd.raw[0], Cmd.raw[1]);

	if (Cmd.data.info.srq_enable == false &&
		Cmd.data.info.exceptional_event == false)
		return -1;

	return 0;
}