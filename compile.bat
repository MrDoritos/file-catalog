@echo off

set "console-gui=console-gui\"
set "includes= "
set "arg=-DGCC -o a.exe -ggdb"

::console-gui Submodule

set "console-gui-sourcePath=%console-gui%source\"
set "console-gui-headerPath=%console-gui%headers\"
set "sourcePath=%console-gui-sourcePath%"
set "headerPath=%console-gui-headerPath%"

set "includes=%includes% -I%headerPath%"
set "sources=%sourcePath%gameEngine.cpp %sourcePath%imath.cpp %sourcePath%lodepng.cpp %sourcePath%pixel.cpp %sourcePath%png.cpp %sourcePath%rigidbody.cpp %sourcePath%rigidbox.cpp"

::Moorepp Submodule
::l8r

@echo on
%userprofile%\Downloads\pocketcpp-0.7\pocketcpp\MinGW\bin\g++ %includes% %sources% %arg% main.cpp
if "%errorlevel%" NEQ "0" (
pause
)
@echo off
