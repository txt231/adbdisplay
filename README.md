# ADB Display

A project to explore ADB(Apple Data Bus) protocol for some apple displays.

My end goal is to probably do a DDC to ADB converter, to allow for a better vga connection.
**At current state its just code to explore and test adb to a display**

**check what the code is run before you run it!**

Most of the registers/addresses that relates to actual monitor settings are only available when the display is turned on. But Some registers like power state, revision, copyright notice, etc. is readable when monitor is turned off.

To read and write settings over ADB, param `lrem` needs to be set to 0. This is done in the `Detect` function. It also seems to disable OSD until 1 is written to it again. 
Also note that writing settings doesnt seem to apply on certain resolutions. Im guessing it needs to be saved first. (might be display dependent) 

After writing a register, the display does not save, and previous values will be restored on reboot.
Im guessing save sequence refers to specific settings?

`DumpSettings1` and `DumpSettings2` should dump some pieces of data that is in a parameter file used in service utility. 

***

Default pin in this case is pin 8, as i had issues with pin 3 on an arduino uno.
Connected with a pullup resistor as described in other adb projects.



## ADB Interaction

ADB interaction with display is mainly taken from `Display Service Utility`. 

AppleVision/Apple Monitor Plugins binary contains settings information as `ladt` resources. A script for reading these resources is in `dump_settings.py`. 
This binary contains a bit better way to query monitor type and revision, but is annoying to navigate by its heavy use of components and the `ComponentDispatch` syscall.


## Models

To reduce space used on the microcontroller, some settings tables been put behind ifdefs (check `lib/adb_params/include/Params.h` and `platformio.ini`)


NOTE: This table is not confirmed. 
| Codename 		| Model 				|
| - 			| - 					|
| Telecaster 	| 	 					|
| Sousa 		|  						|
| Hammerhead 	| (AppleVision 1710)	|
| Orca 			| AppleVision 850AV 	|
| Whaler 		| AppleVision 850 		|
| WarriorEZ 	| (AppleVision 750)		|
| Manta		 	| 	 					|


# Credits

- `macemu/SheepShaver` for dynamic testing of apple adb interactions (Display service utility). AppleVision extension/Monitor plugins extension doesnt work.
- `m68k_mac_reversing_tools`


ADB code and project structure is credited to:
- [tmk keyboard](https://github.com/tmk/tmk_keyboard/blob/master/tmk_core/protocol/adb.c) | adb reading code
- [adbuino](https://github.com/akuker/adbuino) | adb code and project structure
- [stm32-adb2usb](https://github.com/szymonlopaciuk/stm32-adb2usb/blob/main/src/adb_structures.h) | for adb bitfield structure
