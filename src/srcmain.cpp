#include <platform.h>

#include <Adb.h>
#include <AdbDisplayInterface.h>

static AdbInterface adb; 

static AdbDisplayInterface* pDisplay = nullptr;

void SetTempHighVoltage(uint8_t vlt=164)
{
	if (!pDisplay)
		return;
	
	pDisplay->SetValueId("pass", 70 + 43);
	
	pDisplay->SetValueId("hvlt", vlt);
}

void SetTempG2(uint8_t vlt=108)
{
	if(!pDisplay)
		return;
	
	printf("log G2 pass : %i\n", pDisplay->SetValueId("pass", 69 + 43));
	
	printf("log g2 val %i\n", pDisplay->SetValueId("g2g2", vlt));

	if (false)
		printf("log G2 save : %i\n", pDisplay->SetValueId("sgsv", 69 + 43));
}

bool start()
{
	if(pDisplay)
	{
		printf("log Already started!\n");
		return true;
	}

	adb.Init();
	adb_delay_ms(500);

	ScanDeviceInfo Devices[16];
	auto Count = adb.ScanDevices(Devices);
	
	printf("log Got [%i] devices\n", Count);

	for (auto i=0; i < Count; i++)
	{
		printf("log Device [%i] = 0x%02x%02x\n", Devices[i].addr, Devices[i].reg.raw[0], Devices[i].reg.raw[1]);
		
		if (Devices[i].reg.data.devType == AdbDeviceType::Display)
		{
			if (pDisplay)
			{
				printf("log \t Found multiple displays. usng first one!\n");
				continue;
			}
			printf("log \t Found display!\n");
			pDisplay = new AdbDisplayInterface(adb, Devices[i].addr);
			
			// need to set address to be able to enable device!
			// this is part of adb negotation stuff
			pDisplay->SetAddr(Devices[i].addr);
		}
	}

	if (pDisplay == nullptr)
		return false;
	
	return pDisplay->Detect();
}

void handleLine(const char* pLine, uint32_t len)
{
	printf("log Handle lIne [%s]\n", pLine);

	// for(uint32_t i=0; i < len; i++)
	// 	printf("log chr %d = %d (%c)\n", i, (uint32_t)pLine[i], pLine[i]);

	if (strncmp(pLine, "start", 5) == 0)
	{
		start();
	}
	else if (strncmp(pLine, "set", 3) == 0)
	{
		const char* pSpace = strchr(pLine + 4, ' ');
		if(!pSpace)
		{
			printf("log error parsing line [%s]\n", pLine);
			return;
		}

		uint32_t ValId = FourCC(pLine + 4);

		int Value = atoi(pSpace + 1);
		uint32_t ValData = Value & 0xFF; 
		if ((ValData ^ 0x55) != ((Value >> 8) & 0xFF))
		{
			printf("log set checksum failed!\n");
			return;
		}
		
		printf("log Setting[%lx] = %lu\n", (long)ValId, (long)ValData);
		
		if(pDisplay)
		{
			pDisplay->SetValueId("lrem", 0);

			pDisplay->SetValueId(ValId, ValData & 0xFF);
			
			uint8_t ConfirmVal;
			if (pDisplay->GetValueId(ValId, ConfirmVal))
				printf("val %c%c%c%c %lu\n", 
					pLine[4],
					pLine[5],
					pLine[6],
					pLine[7],
		   			(long)((ConfirmVal) | ((ConfirmVal ^ 0x55)<< 8))
				);

			pDisplay->SetValueId("lrem", 1);
		}
	}
	else if (strncmp(pLine, "get", 3) == 0)
	{
		uint32_t ValId = FourCC(pLine + 4);

		printf("log Gettin[%c%c%c%c] = 0x%lx\n",
				pLine[4],
				pLine[5],
				pLine[6],
				pLine[7],
		 		(long)ValId
				);

		if(pDisplay)
		{
			pDisplay->SetValueId("lrem", 0);

			uint8_t ConfirmVal;
			if (pDisplay->GetValueId(ValId, ConfirmVal))
				printf("val %c%c%c%c %lu\n", 
					pLine[4],
					pLine[5],
					pLine[6],
					pLine[7],
		   			(long)((ConfirmVal) | ((ConfirmVal ^ 0x55) << 8))
				);
				
			pDisplay->SetValueId("lrem", 1);
		}
	}
	else if (strncmp(pLine, "save", 4) == 0)
	{
		uint32_t ValId = FourCC(pLine + 5);
		printf("log Save [%s] [%c%c%c%c]\n", pLine, pLine[5], pLine[6], pLine[7], pLine[8]);
	}
	else
	{
		printf("log Invalid Line [%s]\n", pLine);
	}
	
}

bool serial_update()
{
	static char LineBuffer[1024];
	static uint32_t LineBufPos = 0;

	if (!serial_rx_avail())
		return false;
	
	char ch = 0; 
	if (serial_rx_read((uint8_t*)&ch, sizeof(ch)) == 0)
		return false;
	
	if (ch == '\n')
	{
		LineBuffer[LineBufPos] = 0;
		handleLine(LineBuffer, LineBufPos);
		
		LineBufPos = 0;
		return true;
	}
	
	LineBuffer[LineBufPos++] = ch;
		
	return true;
}

int main() 
{
	
	platform_init();
	bool Enable = start();	

	printf("log Enable %i\n", Enable);
	// pDisplay->SetValueId("lrem", 0);

	// printf("Setting geometry mode!\n");
	

	// printf("DumPSettings1 %i\n", pDisplay->DumpSettings1());
	
	// pDisplay->SetValue(20, 113);
	// pDisplay->SetValue(17, 113);

	// printf("Setting pos!\n");
	// {
	// 	for (auto i=25; i < 64; i++)
	// 	{
	// 		printf("%i\n", i);
	// 		pDisplay->SetValue(56, i);
	// 		_delay_ms(200);
	// 	}
	// }
	// printf("Finished\n");

	// for(auto i = 0; i < 129; i++)
	// {
	// 	_delay_ms(15);
	// 	uint8_t Val;
	// 	if (pDisplay->GetValue(i, Val))
	// 		printf("log [%i] = %i\n", i, Val);
	// }
	

	// uint8_t GainOriginalVal[3] {209, 172, 179};
	// pDisplay->GetValueId("rgan", GainOriginalVal[0]);
	// pDisplay->GetValueId("ggan", GainOriginalVal[1]);
	// pDisplay->GetValueId("bgan", GainOriginalVal[2]);
	// uint8_t CutOriginalVal[3] {121, 167, 140};
	// pDisplay->GetValueId("rg2 ", CutOriginalVal[0]);
	// pDisplay->GetValueId("gg2 ", CutOriginalVal[1]);
	// pDisplay->GetValueId("bg2 ", CutOriginalVal[2]);

	// printf("RGB gain [%i, %i, %i]\n", GainOriginalVal[0], GainOriginalVal[1], GainOriginalVal[2]);
	// printf("RGB cut [%i, %i, %i]\n", CutOriginalVal[0], CutOriginalVal[1], CutOriginalVal[2]);
	
	// {
	// 	// uint8_t MaxVal = max(GainOriginalVal[0], max(GainOriginalVal[1], GainOriginalVal[2]));
	// 	// uint8_t AddVal = 254 - MaxVal;
	// 	uint8_t AddVal = 0;

	// 	pDisplay->SetValueId("rgan", GainOriginalVal[0]+AddVal);
	// 	pDisplay->SetValueId("ggan", GainOriginalVal[1]+AddVal);
	// 	pDisplay->SetValueId("bgan", GainOriginalVal[2]+AddVal);
	// }
	
	// {

	// 	uint8_t MaxVal = max(CutOriginalVal[0], max(CutOriginalVal[1], CutOriginalVal[2]));
	// 	uint8_t AddVal = 254 - MaxVal;

	// 	uint8_t i = AddVal;
	// 	{
	// 		printf("%i\n", i);
	// 		pDisplay->SetValueId("rg1 ", CutOriginalVal[0] + i);
	// 		pDisplay->SetValueId("gg1 ", CutOriginalVal[1] + i);
	// 		pDisplay->SetValueId("bg1 ", CutOriginalVal[2] + i);
	// 		// _delay_ms(100);
	// }
	// printf("bright done!\n");
	// _delay_ms(1000*2);
	
	// pDisplay->SetValueId("rgan", GainOriginalVal[0]);
	// pDisplay->SetValueId("ggan", GainOriginalVal[1]);
	// pDisplay->SetValueId("bgan", GainOriginalVal[2]);

	// pDisplay->SetValueId("rg1 ", CutOriginalVal[0]);
	// pDisplay->SetValueId("gg1 ", CutOriginalVal[1]);
	// pDisplay->SetValueId("bg1 ", CutOriginalVal[2]);
	
	// SetTempG2(140);
	// SetTempG2(160);
	// SetTempG2(155);
	// SetTempG2(152); // final
	
	// _delay_ms(100);
	// SetTempG2(158);
	
	// printf("hv done!\n");
	// _delay_ms(1000*5);
	
	// printf("Reset!");	
	// SetTempG2();

	// to allow osd again
	if(pDisplay)
		pDisplay->SetValueId("lrem", 1);
	
	
	while (true)
	{
		serial_update();
	}
}

// Arduino support
void setup()
{
	main();
}
void loop()
{}