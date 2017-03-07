# Quartz
Quartz is a plugin based generic cross-platform application. It intends to be a platform for writing wide varity of plugins which need not be related. One of the design goals is to provide as many as plugin hooks without any assumptions about the plugins that will use the platform.

Quartz is in its initial stages and very much a work in progress. There is no guarantee that the code will build.

## Build System
Quartz uses a CMake based build system which uses cmake_lib (https://github.com/varunamachi/cmake_lib). Before running CMake a environment variable QUARTZ_ROOT should be set to the root of the Quartz directory.
The build system does not allow in-source builds, it is recommended that the build be done in $QUARTZ_ROOT/builds The generated binaries and headers in case of libraries are installed to $QUARTZ_ROOT/output directory. Any module can be built independently provided that the dependency modules are already built and their generated output is installed in $QUARTZ_ROOT/output.

## Building
Dependency - Qt 5.7+

 But the build procedure for debug build on Linux is as follows (in Bash):
```shell
export QUARTZ_ROOT=<path_to_quartz_root>
cd $QUARTZ_ROOT/builds
mkdir -p quartz_full_build/debug
cd quartz_full_build/debug
cmake -G "Unix Makefile" -DCMKAE_BUILD_TYPE=Debug ../../../source
make -j$(nproc)
```

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







