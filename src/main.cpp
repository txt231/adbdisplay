
#include <Arduino.h>
#include <LibPrintf.h>

#include <Adb.h>
#include <AdbDisplayInterface.h>

static AdbInterface adb; 

static AdbDisplayInterface* pDisplay = nullptr;

void setup() 
{
	
	Serial.begin(115200);
	while (!Serial);
	
	adb.Init();
	_delay_ms(1000);

	ScanDeviceInfo Devices[16];
	auto Count = adb.ScanDevices(Devices);
	
	printf("Got [%i] devices\n", Count);

	for (auto i=0; i < Count; i++)
	{
		printf("Device [%i] = 0x%02x%02x\n", Devices[i].addr, Devices[i].reg.raw[0], Devices[i].reg.raw[1]);
		
		if (Devices[i].reg.data.devType == AdbDeviceType::Display)
		{
			if (pDisplay)
			{
				printf("\t Found multiple displays. usng first one!");
				continue;
			}
			printf("\t Found display!\n");
			pDisplay = new AdbDisplayInterface(adb, Devices[i].addr);
			
			// need to set address to be able to enable device!
			// this is part of adb negotation stuff
			pDisplay->SetAddr(Devices[i].addr);
		}
	}
	if (!pDisplay)
		return;
	

	printf("Enable %i\n", pDisplay->Detect());

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
	// 	if(pDisplay->GetValue(i, Val))
	// 		printf("[%i] = %i\n", i, Val);
	// }
	

	uint8_t GainOriginalVal[3] {209, 172, 179};
	// pDisplay->GetValueId("rgan", GainOriginalVal[0]);
	// pDisplay->GetValueId("ggan", GainOriginalVal[1]);
	// pDisplay->GetValueId("bgan", GainOriginalVal[2]);

	uint8_t CutOriginalVal[3] {121, 167, 140};
	// pDisplay->GetValueId("rg2 ", CutOriginalVal[0]);
	// pDisplay->GetValueId("gg2 ", CutOriginalVal[1]);
	// pDisplay->GetValueId("bg2 ", CutOriginalVal[2]);

	printf("RGB gain [%i, %i, %i]\n", GainOriginalVal[0], GainOriginalVal[1], GainOriginalVal[2]);
	printf("RGB cut [%i, %i, %i]\n", CutOriginalVal[0], CutOriginalVal[1], CutOriginalVal[2]);
	
	{
		uint8_t MaxVal = max(GainOriginalVal[0], max(GainOriginalVal[1], GainOriginalVal[2]));
		uint8_t AddVal = 254 - MaxVal;

		pDisplay->SetValueId("rgan", GainOriginalVal[0]+AddVal);
		pDisplay->SetValueId("ggan", GainOriginalVal[1]+AddVal);
		pDisplay->SetValueId("bgan", GainOriginalVal[2]+AddVal);
	}
	
	{

		uint8_t MaxVal = max(CutOriginalVal[0], max(CutOriginalVal[1], CutOriginalVal[2]));
		uint8_t AddVal = 254 - MaxVal;

		for(uint16_t i=AddVal/2; i <= AddVal; i++)
		{
			printf("%i\n", i);
			pDisplay->SetValueId("rg1 ", CutOriginalVal[0] + i);
			pDisplay->SetValueId("gg1 ", CutOriginalVal[1] + i);
			pDisplay->SetValueId("bg1 ", CutOriginalVal[2] + i);
			
			// _delay_ms(100);
		}
	}
	printf("bright done!\n");

	_delay_ms(1000*2);
	
	// pDisplay->SetValueId("rgan", GainOriginalVal[0]);
	// pDisplay->SetValueId("ggan", GainOriginalVal[1]);
	// pDisplay->SetValueId("bgan", GainOriginalVal[2]);

	// pDisplay->SetValueId("rg1 ", CutOriginalVal[0]);
	// pDisplay->SetValueId("gg1 ", CutOriginalVal[1]);
	// pDisplay->SetValueId("bg1 ", CutOriginalVal[2]);


	// to allow osd again
	pDisplay->SetValueId("lrem", 1);
	
	
}

void loop() {
  // put your main code here, to run repeatedly:
}
