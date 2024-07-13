#pragma once

#include <Adb.h>
#include <AdbDevice.h>


#include <ParamInfo.h>


enum DisplayType
{
	Telecaster, 
	Sousa,
	Hammerhead, // 1710
	Orca, // 850AV
	Whaler, // 850
	WarriorEZ, // 750
	Manta, 
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
	DisplayType m_Type;
	uint8_t m_Revision;
	uint8_t m_VersionUnk;

	const ParamInfo* m_pParams = nullptr;
	
private:

	int32_t Enable() override;

	bool SetReg2(uint8_t displayRegister);

public:
	bool Detect();
	
	bool GetValueSafe(const uint8_t displayRegister, uint8_t& value);
	bool SetValueSafe(const uint8_t displayRegister, const uint8_t value);
	bool GetValue(const uint8_t displayRegister, uint8_t& value);
	bool SetValue(const uint8_t displayRegister, const uint8_t value);

	bool GetValueId(const uint32_t fourCC, uint8_t& value);
	bool SetValueId(const uint32_t fourCC, const uint8_t value);

	inline bool GetValueId(const char* pCC, uint8_t& value)
	{
		return GetValueId(FourCC(pCC), value);
	}
	inline bool SetValueId(const char* pCC, const uint8_t value)
	{
		return SetValueId(FourCC(pCC), value);
	}
	
	bool DumpSettings1();
	bool DumpSettings2();

	bool SaveSettings();
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

