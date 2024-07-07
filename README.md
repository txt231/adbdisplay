# ADBDDC

adbddc aims to be a bridge between apple adb connections used for some monitors and DDC which is a vesa standard.


Settings Ids and interfacing code mainly reverse engineered from "Display Service Utility" program.
I have not yet investigated monitor settings.


## USB and adbuino devices

While ddc can support usb over MCCS, and could possibly be doable with existing "adbuino" devices like QuokkADB, it is out of my scope.
More information should be available in the [ddcutil wiki](https://www.ddcutil.com/usb/)


# Credits 

This code is heavily inspired by:
- [tmk keyboard](https://github.com/tmk/tmk_keyboard/blob/master/tmk_core/protocol/adb.c) (Modified BSD (GPL compatible)) 
- [adbuino](https://github.com/akuker/adbuino) (GPLv3)

respect their licenses and wishes. I believe usage of GPLv3 would also make this gplv3.

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