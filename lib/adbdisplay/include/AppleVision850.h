#pragma once


enum DispReg_850
{
	Rotation = 25,

	HorizWidth = 53,
	HorizPos = 54,
	VertWidth = 55,
	VertPos = 56,
	Pincushion = 57,
	Keystone = 58,

	HighVoltage = 70,

	HFocus = 75,
};

/*


(2, 0, 0, ""), # written = 2



# reg, min, max, name
monitor_settings_850 = [




    (7, 0, 0, ""), # TODO:


    (6, 0, 0x80, "ROM_PTR"),  # set ptr
    (9, 0, 0, "ROM_DATA"), # set ptr, then read data. hashed and used for verification?

    (11, 0, 0, "INSTR"), # written to as a sequence to save?


    (17, 0, 0, ""), # TODO: focus related?

    (20, 0, 0, ""), # TODO: set to 0xEE?

    (25, 2, 63, "Rotation"),


    (41, 0, 0, ""), # TODO: focus related?
    (42, 0, 0, ""), # TODO: focus related?
    (43, 0, 0, ""), # TODO: focus related?


    (49, 0, 0, "DATA_IO_BANK1_NEXT"), # reads/writes next data
    (50, 0, 0, "DATA_IO_BANK2_NEXT"), # reads/writes next data
    (51, 0, 0, "DATA_SET_BANK"), # set to 1 to read bank 1, set to 0 to read. for writing this is set to address



    (53, 2, 254, "Horizontal Width"),
    (54, 45, 217, "Horizontal Position"),
    (55, 2, 222, "Vertical Height"),
    (56, 10, 240, "Vertical Position"),
    (57, 2, 254, "Pincushion"),
    (58, 2, 254, "Keystone"),


    (70, 154, 177, "High Voltage"),

    (75, 3, 254, "H-Focus"),


    (85, 2, 63, ""), #TODO: rotation? written to when saving


    (87, 0, 0, ""), # TODO: another data access thing? written to as 15 wen saving. maybe some write enable?

    (113, 0, 0, ""), # TODO:


    (255, 0, 0, "TYPE_POS"), # returns register where monitor type is stored? something like that
]

*/