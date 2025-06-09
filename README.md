# 2D_Physics_Engine

## How to build for Ubuntu 24.04 LTS

> **DISCLAIMER:** This README is a work in progress. The guides here might not fully work yet.

**Dependencies:**  
- SDL2  
- SDL2_ttf  
- SDL2_mixer  
- SDL2_image  

**Build steps:**
```sh
sudo apt install libsdl2-dev libsdl2-ttf-dev libsdl2-mixer-dev libsdl2-image-dev
cd build
cmake ..
make
```

**Run the program:**
```sh
./bin/Swordlord
```

---

## How to build for Windows 11

**Needed Software:**
- Git
- CMake ([download here](https://cmake.org/download/))
- SDL2, SDL2_ttf, SDL2_mixer, SDL2_image (via [vcpkg](https://github.com/microsoft/vcpkg) recommended)

**Install dependencies with vcpkg:**
```sh
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg install sdl2 sdl2-image sdl2-mixer sdl2-ttf nlohmann-json
```

**Or install SDL2 manually:**  
[SDL2 Releases](https://github.com/libsdl-org/SDL/releases)

**Build with CMake:**
```sh
cmake -B build -S . ^
  -DCMAKE_TOOLCHAIN_FILE="Your_Path/vcpkg/scripts/buildsystems/vcpkg.cmake" ^
  -DVCPKG_TARGET_TRIPLET=x64-windows

cmake --build build --config Release
```

**Run the program:**
```sh
cd sword_lord\2D-physics-engine\build\bin\Release
.\Swordlord.exe
```
