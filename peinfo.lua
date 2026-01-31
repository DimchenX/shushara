local pefile = io.open(arg[-1], "rb")
local pedatas = pefile:read(1024)
pefile:close()

print()
local function dump(d)
local s=""
local r=0
  for i=1, #d  do
    s=s .. " " .. string.format("%02X",d[i])
    if i % 16 == 0 then
      print(string.format(" 0x%04X: " , i - 16) .. s)
      s = ""
    end
  end
  if #s > 0 then
    print(string.format(" 0x%04X: " , #d - (#d & 15)) .. s)
  end  
  return #d
end

print("\n Table size: ", dump({string.byte(pedatas,1,-1)}))

local pehd=string.unpack("< L",string.sub(pedatas,61,64))
print("\nPE HEADOFFSET :" ,pehd)

pedatas = string.sub(pedatas, pehd, pehd + 128)

print("\n -- Image File Header -- \n")
print(string.format("Machine arch         : 0x%.8X", string.unpack("< H", string.sub(pedatas, 6, 7))))
print(string.format("NumberOfSections     : 00%.8d", string.unpack("< H", string.sub(pedatas, 8, 9))))
print(string.format("TimeDateStamp        : 0x%.8X", string.unpack("< L", string.sub(pedatas, 10, 13))))
print(string.format("PointerToSymbolTable : 0x%.8X", string.unpack("< L", string.sub(pedatas, 14, 17))))
print(string.format("NumberOfSymbols      : 0x%.8X", string.unpack("< L", string.sub(pedatas, 18, 21))))
print(string.format("SizeOfOptionalHeader : 0x%.8X", string.unpack("< H", string.sub(pedatas, 22, 23))))
print(string.format("Characteristics      : 0x%.8X", string.unpack("< H", string.sub(pedatas, 24, 25))))

