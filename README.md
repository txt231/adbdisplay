# ADB Display

A project to explore apple adb protocol for apple displays.

My end goal is to probably do a DDC to ADB converter, to allow for a better vga connection.
**At current state its just code to explore and test adb to a display**

Most of the registers/addresses that relates to actual monitor settings are only available when the display is turned on. 

In my case all settings registers return 0xFF. My guess for this is because it is probably only supposed to be available in mac modes. My theory is that sense pins on connector needs to be set right, or RGBHV signal need to be recognized as a macintosh. 

***

Default pin in this case is pin 8, as i had issues with pin 3 on an arduino uno.
Connected with a pullup resistor as described in other adb projects.



## ADB

ADB interaction with display is mainly taken from `Display Service Utility`. 

AppleVision/Apple Monitor Plugins binary contains settings information as `ladt` resources. A script for reading these resources is in `dump_settings.py`. 
This binary contains a bit better way to query monitor type and revision, but is hard to navigate by its heavy use of components and the `ComponentDispatch` syscall.


## Models

To reduce space used on the microcontroller, some settings tables been put behind ifdefs 

| Codename 		| Model 			|
| - 			| - 				|
| Telecaster 	| 	 				|
| Sousa 		|  					|
| Hammerhead 	| AppleVision 1710 	|
| Orca 			| AppleVision 850AV |
| Whaler 		| AppleVision 850 	|
| WarriorEZ 	| AppleVision 750 	|
| Manta		 	| 	 				|


# Credits

- `macemu/SheepShaver` for dynamic testing of apple adb interactions (Display service utility). AppleVision extension/Monitor plugins extension doesnt work.
- `m68k_mac_reversing_tools`


ADB code and project structure is credited to:
- [tmk keyboard](https://github.com/tmk/tmk_keyboard/blob/master/tmk_core/protocol/adb.c) | adb reading code
- [adbuino](https://github.com/akuker/adbuino) | adb code and project structure
- [stm32-adb2usb](https://github.com/szymonlopaciuk/stm32-adb2usb/blob/main/src/adb_structures.h) | for adb bitfield structures

```
The following copyright notice should be included with distributions of 
this source code:
    Copyright 2021-2023 Tony Kuker
    Copyright 2022-2023 Rabbit Hole Computing LLC
    Copyright 2020 Difegue
    Copyright 2015 Rob Braun
    Copyright 2011 Jun WAKO <wakojun@gmail.com>
    Copyright 2013 Shay Green <gblargg@gmail.com>
```