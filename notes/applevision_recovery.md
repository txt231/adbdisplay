# Applevision recovery

This is for hammerhead devices.

seems to set some state value, read rgb gain and cut, then set state to something else, then write back rgb gain and cut + save.

***

## Codestuff

```c++
void AppleVision1710_Recovery()
{
	uint8_t Dflt;
	if(!pDisplay->GetValueId("dflt", Dflt))
		return;
	
	
	if(!pDisplay->SetValueId("cmod", 4))
		return;
	
	uint8_t RGan;
	uint8_t GGan;
	uint8_t BGan;

	uint8_t RCut;
	uint8_t GCut;
	uint8_t BCut;
	{
		if(!pDisplay->GetValueId("rgan", RGan))
			return;
		if(!pDisplay->GetValueId("ggan", GGan))
			return;
		if(!pDisplay->GetValueId("bgan", BGan))
			return;

		if(!pDisplay->GetValueId("rg1 ", RCut))
			return;
		if(!pDisplay->GetValueId("gg1 ", GCut))
			return;
		if(!pDisplay->GetValueId("bg1 ", BCut))
			return;
	}
	
	
	if(!pDisplay->SetValueId("cmod", 5))
		return;
	
	{
		if(!pDisplay->SetValueId("rgan", RGan))
			return;
		if(!pDisplay->SetValueId("ggan", GGan))
			return;
		if(!pDisplay->SetValueId("bgan", BGan))
			return;
		
		if(!pDisplay->SetValueId("rg1 ", RCut))
			return;
		if(!pDisplay->SetValueId("gg1 ", GCut))
			return;
		if(!pDisplay->SetValueId("bg1 ", BCut))
			return;
	}
	
	// [ 170, 85, 102 ]
	if(!pDisplay->SetValueId("save", 170))
		return;
	if(!pDisplay->SetValueId("save", 85))
		return;
	if(!pDisplay->SetValueId("save", 102))
		return;
}
```