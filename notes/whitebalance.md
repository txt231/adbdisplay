# White balance

The AppleVision system extension on system 7 has a function that does the automatic white balance, probably displaying some colors.

Heavy use of FP68K syscall, which does floating point arithmetic. annoying in its current state.

***


```c++

void WriteCutoff(uint8_t* pVals)
{
	write("rg1 ", pVals[0]);
	write("gg1 ", pVals[1]);
	write("bg1 ", pVals[2]);
}

void ReadRGBCur(uint8_t* pVals)
{
	read("rcur", pVals[0]);
	read("gcur", pVals[1]);
	read("bcur", pVals[2]);
}


void WB()
{
	// backup initial brightess & contrast
	// contrast = ?
	// brightness /= 2
	
	// TODO: some more float stuff around here

	uint8_t RGBCutoff[3]  { 0 };
	WriteCutoff(RGBCutoff);
	delay();

	uint8_t InitialRGBCur[3] { 0 };
	ReadRGBCur(InitialRGBCur);

	uint8_t CutoffVals[3] { 0 };
	uint8_t RGBVals[3] { 0 };
	
	for(uint8_t Step = 254/2; Step != 0; Step /= 2)
	{
		delay();

		ReadRGBCur(RGBVals);
		
		// overflow?
		// Step each rgb value 
		for(auto i=0; i < 3; i++)
		{
			if (InitialRGBCur[i] + 2 <= RGBVals[i])
				CutoffVals[i] -= Step;
			else if (InitialRGBCur[i] + 2 >= RGBVals[i])
				CutoffVals[i] += Step;
		}
		
		WriteCutoff(CutoffVals);
	}

	CutoffVals[0] -= 8;
	CutoffVals[1] -= 8;
	CutoffVals[2] -= 8;
	WriteCutoff(CutoffVals);
	
	// does something similar with more float maths
	// TODO: fix floats or sit down and do it manually 
	

	// restore initial brightness and contrast
}

```
