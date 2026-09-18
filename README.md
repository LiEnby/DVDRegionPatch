# DVD Region Patch

When the bad update hack released, i wanted to try it, 
i was a bit disappointed that i couldn't play DVDs outside my region though;

so i had a look for a solution, they all involved using JRunner to patch your SMC config or something;

thought " could probably do better " .. and well here it is "better" xS

add DVDRegionPatch.xex to any plugin entry in your launch.ini or JPRC.ini file.

# References:
This is my first time developing anything for the 360,
i referenced from the following were useful references for this;


**DashLaunch plugin example**:
 - https://github.com/InvoxiPlayGames/UsbdSecPatch/

**Function hooking**: 
 - https://gist.github.com/iMoD1998/4aa48d5c990535767a3fc3251efc0348
 - https://github.com/ClementDreptin/XexUtils
 - https://github.com/Ste1io/AuroraCrashPatcher/

**DVD XConfig**:
 - https://github.com/g91/XBLS/blob/master/Research/code/h/KernelExports.h#L401
 - https://github.com/Octal450/J-Runner-with-Extras/blob/master/J-Runner/Forms/SMCConfigEditor.cs#L86-L115

**Reverse Engineering**:
 - https://digiex.net/threads/xextool-6-3-download.9523/
 - https://github.com/emoose/idaxex
 
