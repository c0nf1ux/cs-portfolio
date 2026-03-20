@echo off
"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" "8-2_Assignment.sln" /p:Configuration=Release /p:Platform=x86 /t:Rebuild /v:minimal
echo.
echo Build complete!
dir Release\*.exe
