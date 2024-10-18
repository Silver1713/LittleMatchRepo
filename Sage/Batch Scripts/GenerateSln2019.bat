@echo off

echo Generating Solutions for Visual Studio 2019..

mkdir ..\build
cd ..\build

cmake -G "Visual Studio 16 2019" 

cd ..

echo Solutions Generated, Access them in the build folder.
pause
