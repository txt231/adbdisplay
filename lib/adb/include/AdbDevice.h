#pragma once


#include "adb.h"


enum AdbDeviceType
{
	Display = 0xc0,
};

class AdbDevice
{
public:
	AdbDevice(AdbInterface& interface, uint8_t addr)
		: m_Interface(interface)
		, m_Addr(addr)
	{}
	
protected:
	AdbInterface& m_Interface;	
	uint8_t m_Addr;
	
public:
	inline int32_t Send(AdbOp op)
	{
		return m_Interface.Send(AdbOp(m_Addr, op.cmd, op.reg));
	}

	template <typename T>
	inline int32_t Send(AdbOp op, AdbData<T>& data)
	{
		return m_Interface.Send(AdbOp(m_Addr, op.cmd, op.reg), data);
	}
	
	
	virtual int32_t Enable();
	
	void SelfTest();
	void SetAddr(uint8_t addr);

};