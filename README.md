# Quartz
Quartz is a plugin based generic cross-platform application. It intends to be a platform for writing wide varity of plugins which need not be related. One of the design goals is to provide as many as plugin hooks without any assumptions about the plugins that will use the platform.

## Build System
Quartz uses a CMake based build system which uses cmake_lib (https://github.com/varunamachi/cmake_lib). Before running CMake a environment variable QUARTZ_ROOT should be set to the root of the Quartz directory.
The build system does not allow in-source builds, it is recommended that the build be done in $QUARTZ_ROOT/builds The generated binaries and headers in case of libraries are installed to $QUARTZ_ROOT/output directory. Any module can be built independently provided that the dependency modules are already built and their generated output is installed in $QUARTZ_ROOT/output.

## Building
Dependency - Qt 5.7+

On Linux:
```shell
export QT_ROOT=<path_to_qt_installation>/<qt_version>/<compiler_id>
#for example: 
#export QT_ROOT=/opt/Qt/Qt.5.7.0/5.7/gcc_64
cd scripts/linux
chmod u+x build.sh
./build.sh
```

On Windows:
```batch
set QT_ROOT=<path_to_qt_installation>/<qt_version>/<compiler_id>
rem -- for example:
rem -- set QT_ROOT=C:\Qt\Qt.5.7.0\5.7\mingw32_53
cd scripts\windows
build.bat
```

The binaries will be present at ```output/bin/Release```

## Platform modules
At this time Quartz has following modules:
- ```source/core```: Core service providers, plugin management and other untility classes
- ```source/base```: Classes defining basing UI structure and exposing platform adapters
- ```source/common```: Common UI classes in Qt5
- ```source/app```: The application
- ```plugin_base```: A static library to which plugins can link to, so that they dont have to implement common boilerplate

Apart from this the default plugins are located at ```plugins``` directory. At the moment following plugins are implemented:
- ```plugins/sample```: Plugin for testing and demonstrating the plugin system
- ```plugns/orek_client```: Plugin that enables Quartz to be a client to Orek service ( https://github.com/varunamachi/orekng )
- ```plugins/creator```: Work in progress for building a plugin that creates stub for developing other plugins


## Screenshot
On Linux:
![alt tag](https://raw.githubusercontent.com/varunamachi/quartz/master/extra/linux_screenshot.png)

On Windows:
![alt tag](https://raw.githubusercontent.com/varunamachi/quartz/master/extra/quartz_win10.png)
