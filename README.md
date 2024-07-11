# ADB Display

A project to explore apple adb protocol for apple displays.

My end goal is to probably do a DDC to ADB converter, to allow for a proper vga connection.
**At current state its just code to explore and test adb**j

***

Adb interaction mainly reverse engineered from Display Service Utility. 
AppleVision binary contains settings information as `ladt` resources, and a bit better way to query monitor type and revision. 

## DDC

I hope to get DDC vcp values mapped to adb values.
DDC communitcates over i2c.

### Usb devices

While ddc can support usb over MCCS, and could possibly be doable with existing "adbuino" devices like QuokkADB, but is out of my scope.
More information should be available in the [ddcutil wiki](https://www.ddcutil.com/usb/)


# Credits

- `macemu/SheepShaver` for dynamic testing of apple adb interactions (Display service utility)


ADB code and project structure is credited to:
- [tmk keyboard](https://github.com/tmk/tmk_keyboard/blob/master/tmk_core/protocol/adb.c) (Modified BSD (GPL compatible)) 
- [adbuino](https://github.com/akuker/adbuino) (GPLv3)

respect their licenses and wishes. I believe usage of GPLv3 would also make this GPLv3.

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