// {$Include includes\CleoIniFiles.h}
// vars 
goto @p
const DATATYPE = 0@, pMode = 1@, pLine = 2@, pStr = 3@, pStr_Buff = 4@, pEqual = 5@ // cleo_call's vars
const IniFilee = 6@, OpenFile = 7@, CloseFile = 8@, ReadLine = 9@, imageb = 10@, buffer = 11@
const ReturnValuee = 12@, pFileName = 13@, sscanf = 14@, pFile = 15@
const _integer = 2, _float = 4

// ini files system
:OpenIniFile
    0DD0: pFileName = get_label_addr @func
    0DD0: pMode = get_label_addr @mode
    0DD0: OpenFile = get_label_addr @_ZN8CFileMgr8OpenFileEPKcS1_
    0DD1: OpenFile = get_func_addr_by_cstr_name OpenFile
               
    set_register_value 0 value pFileName // teste.ini
    set_register_value 1 value pMode // "rt"
    context_call_func OpenFile
    0DD4: IniFilee = get_register_value 0

    0DD0: pFile = get_label_addr @File
    write_mem_addr pFile value IniFilee size 4 add_ib 0 protect 0
if IniFilee <> false // if file open
then
    0AB2: cleo_return 0
else
    end_thread
end

:File
hex
    00 (4)
end

:GetValueFromIni 
    ReadLineIni()

    switch DATATYPE
        case _integer
            0DD0: DATATYPE = get_label_addr @int
        case _float
            0DD0: DATATYPE = get_label_addr @float
    end

    0DD0: ReturnValuee = get_label_addr @value  // value = 4 bytes
    0DD0: pStr = get_label_addr @string
    0DD0: pStr_buff = get_label_addr @string_buff
    0DD0: pEqual = get_label_addr @equal
    0DD0: buffer = get_label_addr @buffer

    get_image_base imageb
    var sscanf: int, imageb: int // Fix error
    sscanf = 0x18D7B8 //v1.08 = 0x179670
    sscanf += imageb

    set_register_value 0 value buffer
    set_register_value 1 value pStr
    set_register_value 2 value pStr_buff
    set_register_value 3 value pEqual
    context_call_func sscanf // sscanf

    set_register_value 0 value buffer
    set_register_value 1 value DATATYPE
    set_register_value 2 value ReturnValuee
    context_call_func sscanf // sscanf

    DATATYPE = 0
    0DD8: ReturnValuee = read_mem_addr ReturnValuee size 4 add_ib 0
0AB2: cleo_return 1 ReturnValuee
 
:ReadLineIni
    0DD0: pFile = get_label_addr @File // android
    0DD8: IniFilee = read_mem_addr pFile size 4 add_ib 0
    0DD0: buffer = get_label_addr @buffer // android
    0DD0: ReadLine = get_label_addr @_ZN8CFileMgr8ReadLineEjPci
    0DD1: ReadLine = get_func_addr_by_cstr_name ReadLine
    set_register_value 0 value IniFilee
    set_register_value 1 value buffer
    set_register_value 2 value 512
    context_call_func ReadLine
    0DD8: ReadLine = read_mem_addr buffer size 1 add_ib 0
if and
 ReadLine <> 0xA // Line Feed 
 ReadLine <> 0x5B // [ 
 ReadLine <> 0x3B // ;
 ReadLine <> 0x23 // #
 //ReadLine <> 0x20 // space
jf @ReadLineIni
return

:CloseIni
    0DD0: pFile = get_label_addr @File
    0DD8: IniFilee = read_mem_addr pFile size 4 add_ib 0
    0DD0: CloseFile = get_label_addr @_ZN8CFileMgr9CloseFileEj
    0DD1: CloseFile = get_func_addr_by_cstr_name CloseFile
    set_register_value 0 value IniFilee
    context_call_func CloseFile
0AB2: cleo_return 0

:int
hex
    "%*s%*s%d" 00
end

:float
hex
    "%*s%*s%f" 00
end

:value
hex
    00(4)
end

:_ZN8CFileMgr8OpenFileEPKcS1_
hex
    "_ZN8CFileMgr8OpenFileEPKcS1_" 00 // "fopen" 00
end

:_ZN8CFileMgr8ReadLineEjPci //V2.00
hex
    "_ZN8CFileMgr8ReadLineEjPci" 00
end

:_ZN8CFileMgr9CloseFileEj //V2.00
hex
    "_ZN8CFileMgr9CloseFileEj" 00
end

:func
// script memory
hex
"configs/Ksets.ini" 00 // change this
end

:mode
hex
"rt" 00
end

:buffer //512 byte
hex
    00(512)
end

:string
hex
    "%s%s" 00
end

:equal
hex
    00 //for scan "="
end

:string_buff
hex
    00(512)
end

:p



     
      


