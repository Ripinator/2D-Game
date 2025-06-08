# 2D_Physics_engine

## How to build for LTS Ubuntu 24.04

### DISCLAIMER: This README is a work in progress the guides in here might not fully work yet

install the SDL2 library along with SDL2.ttf, SDL2.Mixer, SDL2.image

move to the build folder

run the command cmake ..

run the command make

execute the program with this ./bin/Swordlord


## How to build for Windows 11

#### Needed Software

install git
install the SDL2 library along with SDL2.ttf, SDL2.Mixer, SDL2.image

CMake
https://cmake.org/download/


I would recommend vcpkg

git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg install sdl2 sdl2-image sdl2-mixer sdl2-ttf
.\vcpkg install nlohmann-json


If you dont want to use vcpkg you can also install SDL2 manually from here
https://github.com/libsdl-org/SDL/releases


run the command

cmake -B build -S . `
>>   -DCMAKE_TOOLCHAIN_FILE=">Your_Path/vcpkg/scripts/buildsystems/vcpkg.cmake" `
>>   -DVCPKG_TARGET_TRIPLET=x64-windows



run the command

cmake --build build --config Release



run the command

cd sword_lord\2D-pysics-engine\build\bin\Release

run the program with

.\Swordlord.exe
