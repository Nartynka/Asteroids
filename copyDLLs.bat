if exist bin\Win32\Debug\ (
	echo "Updating DLLs for Win32 Debug"
	del bin\Win32\Debug\*.dll
	ROBOCOPY ThirdParty\SDL2\lib\x86\   bin\Win32\Debug SDL2.dll 
	ROBOCOPY ThirdParty\SDL2_image\lib\x86\ bin\Win32\Debug SDL2_image.dll
	ROBOCOPY ThirdParty\SDL2_ttf\lib\x86 bin\Win32\Debug SDL2_ttf.dll
) 

if exist bin\Win32\Release\ (
	echo "Updating DLLs for Win32 Release"
	del bin\Win32\Release\*.dll
	ROBOCOPY ThirdParty\SDL2\lib\x86\   bin\Win32\Release SDL2.dll 
	ROBOCOPY ThirdParty\SDL2_image\lib\x86\ bin\Win32\Release SDL2_image.dll
	ROBOCOPY ThirdParty\SDL2_ttf\lib\x86 bin\Win32\Release SDL2_ttf.dll
) 

if exist bin\x64\Debug\ (
	echo "Updating DLLs for x64 Debug"
	del bin\x64\Debug\*.dll
	ROBOCOPY ThirdParty\SDL2\lib\x64\   bin\x64\Debug SDL2.dll 
	ROBOCOPY ThirdParty\SDL2_image\lib\x64\ bin\x64\Debug SDL2_image.dll
	ROBOCOPY ThirdParty\SDL2_ttf\lib\x64 bin\x64\Debug SDL2_ttf.dll
) 

if exist bin\x64\Release\ (
	echo "Updating DLLs for x64 Release"
	del bin\x64\Release\*.dll
	ROBOCOPY ThirdParty\SDL2\lib\x64\   bin\x64\Release SDL2.dll 
	ROBOCOPY ThirdParty\SDL2_image\lib\x64\ bin\x64\Release SDL2_image.dll
	ROBOCOPY ThirdParty\SDL2_ttf\lib\x64 bin\x64\Release SDL2_ttf.dll
) 