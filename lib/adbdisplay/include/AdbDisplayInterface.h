#pragma once

#include <adb.h>
#include <AdbDevice.h>


enum DisplayType
{
	_0,
	_1,
	AppleVision1710,
	AppleVision850,
	_4,
	AppleVision750,
};


enum DispReg_Shared
	: uint8_t
{
	_2 = 2,
};


struct DisplayReg1 
{
	uint8_t _0; //0x0000
	uint8_t displayReg; //0x0001
};
struct DisplayReg2
{
	uint8_t _0; //0x0000
	uint8_t value; //0x0001
};

class AdbDisplayInterface
	: public AdbDevice
{
public:
	AdbDisplayInterface(AdbInterface& interface, uint8_t addr)
		: AdbDevice(interface, addr)
	{}

	// TODO: assign to a specific adb id.
	// probably wont care too much about it sinec i will only use it with 1 device anyway
	// AdbDisplayInterface(AdbInterface& interface, uint8_t addr)
	// 	: m_Interface(interface)
	// {}

protected:
	DisplayType m_Type = DisplayType::_0;
	
private:

	int32_t Enable() override;

	bool SetReg2(uint8_t displayRegister);

public:
	bool Detect();
	
	bool GetValue(uint8_t displayRegister, uint8_t& value);
	bool SetValue(uint8_t displayRegister, uint8_t value);

};


/*
template <uint8_t reg>
class DispReg
{
public:
	inline DispReg(AdbDisplayInterface& iface)
		: m_If(iface)
	{}

	AdbDisplayInterface& m_If;

	uint8_t& operator ()
	{
		uint8_t val;
		if (!m_If.GetVal(reg, val))
			return 0;
		return val;
	
	operator uint8_t()
	{
		uint8_t val;
		if (!m_If.GetVal(reg, val))
			return 0;
		return val;
	}
	
	bool operator =(uint8_t val)
	{
		return m_If.SetValue(0, reg, val);
	}
};
*/

