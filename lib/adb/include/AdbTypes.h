#pragma once

#include <stdint.h>

#pragma pack(push, 1)

enum AdbRegister
	: uint8_t 
{
	Reg_0,
	Reg_1, // monitor data address/idx
	Reg_2, // monitor data
	Reg_3, // Device ID
};

enum AdbCommand
	: uint8_t
{
	Reset,
	Flush,
	Listen, // write reg
	Talk, // read reg
};

struct AdbDeviceInfo
{
	uint8_t adbAddr : 4; // 0 - 3
	uint8_t _reserved1 : 1; // 4 | must be 0
	uint8_t srq_enable : 1; // 5
	uint8_t exceptional_event : 1; // 6 device specific 
	uint8_t _reserved0 : 1; // 7
};

// assume this is big endian?
struct AdbReg3
{
	AdbDeviceInfo info; //0x0000
	// union
	// {
		uint8_t devType; //0x0001 
	// 	uint8_t cmd; //0x0001
	// };
};


template <typename T>
class AdbData
{
public:
	AdbData() 
	{}
	inline constexpr AdbData(const T data)
		: data(data)
	{}
	// inline AdbData(T& data)
	// 	: data(data)
	// {}

	union 
	{
		uint8_t raw[8];
		T data; 
	};
	

	inline void Zero()
	{
		for(uint8_t i=0; i < sizeof(T); i++)
			raw[i] = 0;
	}

	inline constexpr uint8_t size()
	{
		return sizeof(T);
	}
};


class AdbOp
{
public:	
	constexpr AdbOp(const AdbCommand cmd, const AdbRegister reg)
		: reg{reg}
		, cmd{cmd}
		, addr{0}
	{}

	constexpr AdbOp(const uint8_t addr, const AdbCommand cmd, const AdbRegister reg)
		: reg{reg}
		, cmd{cmd}
		, addr{addr}
	{}

	union 
	{
		uint8_t raw;
		struct
		{
			// uint8_t reg : 2; // AdbRegister
			// uint8_t cmd : 2; // AdbCommand
			AdbRegister reg : 2;	
			AdbCommand cmd : 2;
			uint8_t addr : 4;
		};
	};
};


#pragma pack(pop)