import io
import macresources
import ctypes
import struct

class SettingsEntry(ctypes.BigEndianStructure):
	_pack_ = 1
	_fields_ = [
		("typeId", ctypes.c_char*4),
		("reg", ctypes.c_uint16),
		("_0x0006", ctypes.c_uint16),
		("max", ctypes.c_uint16), # is this switched? maybe
		("min", ctypes.c_uint16),
		("type", ctypes.c_uint16),
	] # 0x000E
	
	@property
	def typeName(self):
		return self.typeId.decode()
		return struct.pack(">I", self.typeId).decode()
 
	def cppName(self):
		return "'%s', % 4i, %i, % 4i, %i" % (self.typeName, self.reg, self.min, self.max, self.type)
 
	def __str__(self) -> str:
		return "[%s] - %-3i | %i-%-03i | %i" % (self.typeName, self.reg, self.min, self.max, self.type)

	def __repr__(self) -> str:
		return self.__str__()

class SettingsHeader(ctypes.BigEndianStructure):
	_pack_ = 1
	_fields_ = [
		("_0x0000", ctypes.c_uint16),
		("_0x0002", ctypes.c_uint16),
		("settingsCount", ctypes.c_uint16),
	]


def dump(path):
    
	File = list(macresources.parse_rez_code(open(path, "rb").read()))


	SettingsFiles = [x for x in File if x.type == b"ladt"]

	if len(SettingsFiles) == 0:
		return
	
	SettingsFiles = sorted(SettingsFiles, key=lambda x: x.id)

	for Settings in SettingsFiles:
		DisplayType = Settings.id // 100
		DisplayRevision = Settings.id % 100
		
		print()
		print(Settings.name)
		print(f"\t{DisplayType=}")
		print(f"\t{DisplayRevision=}")

		Reader = io.BytesIO(Settings.data)
	
		Header = SettingsHeader.from_buffer_copy(Reader.read(ctypes.sizeof(SettingsHeader)))

		Entries = [SettingsEntry.from_buffer_copy(Reader.read(ctypes.sizeof(SettingsEntry))) for _ in range(Header.settingsCount)]

		Entries = sorted(Entries, key=lambda x: x.reg)

		for Ent in Entries:
			print(f"\t\t{Ent}")
   
   
		CppName = Settings.name.replace(" ", "_")
		CppData = "ParamInfo %s[] = {\n" % (CppName)
		for Ent in Entries:
			CppData += "\tParamInfo(%s),\n" % Ent.cppName()

		CppData += "\tParamInfo(),\n" # add end
		CppData += "};\n"

		print(CppData)


		

dump("/home/txt/Documents/RE/apple/data/data/System Folder/Extensions/°AppleVision.rdump")