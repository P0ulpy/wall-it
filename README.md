# wall-it



# Compilation guide

## Bootstrap workspace

*Windows*

Make sure you installed [Visual Studio](https://visualstudio.microsoft.com/) 

Then run the bootstrap script from **repo root directory**
```bat
.\scripts\bootstrap-workspace.bat
```

*GNU/Linux using apt*

Install necessary build tools and a C/C++ compiler
```sh
sudo apt-get update
sudo apt-get install build-essential tar curl zip unzip autoconf libtool g++ gcc
```

Then run the bootstrap script
```sh
./scripts/bootstrap-workspace.sh
```

Well done your repo is now ready to work with cmake and vcpkg !

## Compile the project

Cmake will atomatically detect your compiler and generator 

*Windows*
```sh
# For debug build
.\scripts\build-debug.bat
# For release build
.\scripts\build-release.bat
```

*Unix*
```bash
# For debug build
./scripts/build-debug.sh
# For release build
./scripts/build-release.sh
```

**Run your program**
You can now run the compiled program by looking into `out/Debug` or `out/Release`.
The out directory hierarchy will be different depending on your generator.

For exemple with Make generator in Debug mode run your program like that
```bash
# The executable name will change acording to the value set in add_executable(<name>, ...)
./out/Debug/cmake-vcpkg-template-app
```

**In case of issues while running vcpkg install**

Pay attention at this kind of message of vcpkg :
```
-- SFML currently requires the following libraries from the system package manager:
    libudev
    libx11
    libxrandr
    libxcursor
    opengl
You can intall them in your system using apt-get install libx11-dev libxrandr-dev libxcursor-dev libxi-dev libudev-dev libgl1-mesa-dev
```

Most of the time install issues with vcpkg are related to a dynamic library who are not installed in you system. Most of the time vcpkg explain directly how to install them. 