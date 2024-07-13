
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

	for(auto i = 0; i < 0x80; i++)
	{
		_delay_ms(15);
		uint8_t Val;
		if(pDisplay->GetValue(i, Val))
			printf("[%i] = %i\n", i, Val);
	}
}

void loop() {
  // put your main code here, to run repeatedly:
}
