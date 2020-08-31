cd "C:\Users\caioc\Desktop\Cheat!\Work Build\Release"
set atual=%date%
date 01-01-2014
"E:\Windows Kits\10\bin\x64\signtool.exe" sign /a /ac "VeriSign Class 3 Public Primary Certification Authority - G5.cer" /f "cert.pfx" /p "1" warface.dll
rename warface.dll ddraw.dll
PAUSE
date %atual%