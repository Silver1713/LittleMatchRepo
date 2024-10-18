@echo off

echo Generating Solutions for Visual Studio 2022..
rmdir /s /q ..\build
mkdir ..\build
cd ..\build

cmake -G "Visual Studio 17 2022" ..

cd ..

echo Solutions Generated, Access them in the build folder.
pause
