[TOC]

# Milestones

* import/export tasklist (Major)
* concat splitted segemnts (Major)
* loading multiple input files /image sequence (Major)
* use API instead launching commandline binary (Major)

## TODOs

* function for verification of selected parameters (Minor)
* fix the preview to show correct frames for timestamps, avformat_get_stream_info() (Minor)
* support for aspect ratio in preview? (Minor)

# Build

## Debian

### Requirements

* bash
* build-essentials (gcc, g++, make, lib*,...)
* libwxgtk2.8-dev
* libwxbase2.8-dev
* libglu1-mesa-dev
* libasound2-dev
* libavformat-dev
* libavcodec-dev
* libavutil-dev
* libswscale-dev

### Compile

open a terminal
change into ffmpegyag directory
run `configure` (with --prefix=DIR if you want to install in a directory other than /usr/local)
```sh
./configure --prefix=/usr
# OR (if you want to use clang instead of gcc):
./configure --config-clang --prefix=/usr
```
Compile and install (may require root for installation)
```sh
make
sudo make install
```
remove ffmpegyag (run as root or uninstallation will fail)
```sh
sudo make uninstall
```
Creating a source package for redistribution
```sh
make tgz
```
Creating a debian binary package for redistribution
(configure with prefix /usr to prevent lintian errors)
(run as root for correct ownership of files)
```sh
./configure --prefix=/usr
# OR (if you want to use clang instead of gcc):
./configure --config-clang --prefix=/usr
sudo make deb
```

## Windows 7

### Requirements

* MinGW32 (GCC >= 4.5)
* wxWidgets MSW >= 2.8.12 build parameters:
  MONOLITHIC=1
  SHARED=0
  UNICODE=1
  BUILD=release
  USE_OPENGL=1

### Compile

open a command prompt (cmd)
change into ffmpegyag directory
run configure.cmd
run make
run make install

open a command prompt (cmd.exe)
add your MinGW to the system environment path (SET PATH=C:\MinGW\bin)
set environment variable for your wxWidgets (SET WXWIN=C:\wxMSW)
change into HakuNeko's build directory (CD .\build)
clean previous portable builds (mingw32-make.exe -f win32.make BUILD=portable clean)
compile HakuNeko as portable* application (mingw32-make.exe -f win32.make BUILD=portable)
portable: all settings are stored inside the applications root directory
HakuNeko_Portable.exe can be found in the .\bin\win32 directory
