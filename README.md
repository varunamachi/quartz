# quartz
Quartz is a plugin based generic cross-platform application. It intends to be a platform for writing wide varity of plugins which need not be related. One of the design goals is to provide as many as plugin hooks without any assumptions about the plugins that will use the platform.

Quartz is in its initial stages and very much a work in progress. There is no guarantee that the code will build.

#Build System
Quartz uses a CMake based build system which uses cmake_lib (https://github.com/varunamachi/cmake_lib). Before running CMake a environment variable QUARTZ_ROOT should be set to the root of the Quartz directory.
The build system does not allow in-source builds, it is recommended that the build be done in $QUARTZ_ROOT/builds The generated binaries and headers in case of libraries are installed to $QUARTZ_ROOT/output directory. Any module can be built independently provided that the dependency modules are already built and their generated output is installed in $QUARTZ_ROOT/output.

#Building 
Dependency - Qt 5.6+

Right now Quartz is not in a state to build. But the build procedure is as follows (in Bash):
```shell
export QUARTZ_ROOT=<path_to_quartz_root>
cd $QUARTZ_ROOT/builds
mkdir -p quartz_full_build/debug
cd quartz_full_build/debug
cmake -G "Unix Makefile" -DCMKAE_BUILD_TYPE=Debug ../../../source
make -j$(nproc)
```

#Modules
At this time Quartz has following modules:
- quartz_core: Quartz's default plugin point providers
- quartz_common: Common UI classes in Qt5
- plugins: default plugins to be built with Quartz
- app: The application





