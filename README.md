# WebLoom

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

## To build with Mac

make CXX=g++-14
