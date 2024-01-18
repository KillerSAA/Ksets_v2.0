
int gMobMenu, i
float x, y

:GetTargetBlipCoords
    Memory.GetLabelPointer(gMobMenu, @gMobileMenu)
    Memory.GetFuncPointerByCstrName(gMobMenu, gMobMenu)
    Memory.GetLabelPointer(i, @ms_RadarTrace)
    Memory.GetFuncPointerByCstrName(i, i)
    gMobMenu += 0x48
    Memory.Read(gMobMenu, gMobMenu, 2, False)
    gMobMenu *= 0x28
    gMobMenu += i
    gMobMenu += 8
    Memory.Read(x, gMobMenu, 4, False) // X 
    gMobMenu += 4
    Memory.Read(y, gMobMenu, 4, False) // Y
return                                                   

:gMobileMenu
hex
 "gMobileMenu" 00
end

:ms_RadarTrace
hex
 "_ZN6CRadar13ms_RadarTraceE" 00
end