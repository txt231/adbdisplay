import io
import macresources
import ctypes
import struct

# Used in system 7
class SettingsEntry(ctypes.BigEndianStructure):
	_pack_ = 1
	_fields_ = [
		("typeId", ctypes.c_char*4),
		("reg", ctypes.c_uint16), #0x0004
		("min", ctypes.c_uint16), #0x0008
		("max", ctypes.c_uint16), #0x000c is this switched? maybe
		("_0x000a", ctypes.c_uint16), # 0x000A
		("flags", ctypes.c_uint16), # 0x000A
	] # 0x000E
	
	@property
	def typeName(self):
		return self.typeId.decode()
		return struct.pack(">I", self.typeId).decode()
 
	def cppName(self):
		return "\"%s\",% 4i,% 2i,% 4i, %i, 0x%04x" % (self.typeName, self.reg, self.min, self.max, self._0x000a, self.flags)
 
	def __str__(self) -> str:
		return "[%s] - %-3i | %i-%-03i | %i" % (self.typeName, self.reg, self.min, self.max, self.type)

	def __repr__(self) -> str:
		return self.__str__()

# Used in system 7
class SettingsHeader(ctypes.BigEndianStructure):
	_pack_ = 1
	_fields_ = [
		("_0x0000", ctypes.c_uint16),
		("_0x0002", ctypes.c_uint16),
		("settingsCount", ctypes.c_uint16),
	] # 0x0006
 
# Used in system 9
class SettingsEntry2(ctypes.BigEndianStructure):
	_pack_ = 1
	_fields_ = [
		("typeId", ctypes.c_char*4),
		("reg", ctypes.c_uint32), #0x0004
		("min", ctypes.c_uint32), #0x0008
		("max", ctypes.c_uint32), #0x000C is this switched? maybe
		("_0x0010", ctypes.c_uint32), #0x0010
		("flags", ctypes.c_uint32), #0x0014
	] # 0x0018
	
	@property
	def typeName(self):
		return self.typeId.decode()
		return struct.pack(">I", self.typeId).decode()
 
	def cppName(self):
		return "\"%s\",% 4i, %i,% 4i, %i, 0x%04x" % (self.typeName, self.reg, self.min, self.max, self._0x0010, self.flags)
 
	def __str__(self) -> str:
		return "[%s] - %-3i | %i-%-03i | %i" % (self.typeName, self.reg, self.min, self.max, self.type)

	def __repr__(self) -> str:
		return self.__str__()
# used in system 9
class SettingsHeader2(ctypes.BigEndianStructure):
	_pack_ = 1
	_fields_ = [
		("_0x0000", ctypes.c_uint16), # 0x0000
		("_0x0002", ctypes.c_uint32), 
		("_0x0006", ctypes.c_uint32),
		("_0x000a", ctypes.c_uint32),
		("_0x000e", ctypes.c_uint32),
		("_0x0012", ctypes.c_uint32),
		("_0x0016", ctypes.c_uint32),
		("_0x001a", ctypes.c_uint32),
		("settingsCount", ctypes.c_uint32), # 0x0016
	]
	

def dump(path, newFormat =False):
    
	File = list(macresources.parse_rez_code(open(path, "rb").read()))


	SettingsFiles = [x for x in File if x.type == b"ladt"]

	if len(SettingsFiles) == 0:
		return
	
	SettingsFiles = sorted(SettingsFiles, key=lambda x: x.id)

	for Settings in SettingsFiles:
		DisplayType = Settings.id // 100
		DisplayRevision = Settings.id % 100
		
		print()
		# print(Settings.name)
		# print(f"\t{DisplayType=}")
		# print(f"\t{DisplayRevision=}")

		Reader = io.BytesIO(Settings.data)
		
		Header = None
		Entries = []
	
		if newFormat:
			Header = SettingsHeader2.from_buffer_copy(Reader.read(ctypes.sizeof(SettingsHeader2)))
			Entries = [SettingsEntry2.from_buffer_copy(Reader.read(ctypes.sizeof(SettingsEntry2))) for _ in range(Header.settingsCount)]
		else:
			Header = SettingsHeader.from_buffer_copy(Reader.read(ctypes.sizeof(SettingsHeader)))
			Entries = [SettingsEntry.from_buffer_copy(Reader.read(ctypes.sizeof(SettingsEntry))) for _ in range(Header.settingsCount)]

		Entries = sorted(Entries, key=lambda x: x.reg)

		# for Ent in Entries:
		# 	print(f"\t\t{Ent}")
   
   
		CppName = Settings.name.replace(" ", "_")
		CppData = "ParamInfo %s[] = {\n" % (CppName)
		for Ent in Entries:
			CppData += "\tParamInfo(%s),\n" % Ent.cppName()

		CppData += "\tParamInfo(),\n" # add end
		CppData += "};\n"

		print(CppData)


		

# dump("/home/txt/Documents/RE/apple/data/data/System Folder/Extensions/°AppleVision.rdump", False)
dump("/home/txt/Documents/RE/apple/data/macos9_data/System Folder/Extensions/Apple Monitor Plugins.rdump", True)