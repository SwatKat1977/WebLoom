# WebLoom

WebLoom is a modern C++ 17 html framework. 

## News  

- Important Information: The main repo is bumping is currently at V0.1.0 whilst the code is still in early development.
- Follow the [changelog](ChangeLog) for new features and bug fixes.

## Documentation

- [Getting Started](PLACEHOLDER)
- [Building On Linux](PLACEHOLDER)
- [Building On Windows](PLACEHOLDER)

## Dependencies

### SPD

Dependency : https://github.com/gabime/spdlog

Environment Variable : WEBLOOM_SDP_INC

### libMagic

#### Windows

Environment Variable : WEBLOOM_LIBMAGIC_INC, WEBLOOM_LIBMAGIC_LIB

* git clone https://github.com/microsoft/vcpkg.git
* cd vcpkg
* .\bootstrap-vcpkg.bat
* .\vcpkg install libmagic

The libMagic file is stored in a different place on Windows so you will need to
set WEBLOOM_LIBMAGIC_FILE. The location will be:

    {vcpkg path}\packages\libmagic_x64-windows\share\libmagic\misc\magic.mgc

## To build

To build WebLoom you need to have autoconf installed and then run the following commands:

* autoreconf --install
* ./configure --prefix=$(pwd)/build
* make

## For MacOs

make CXX=g++-14
