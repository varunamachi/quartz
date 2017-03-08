set INVOKE_DIR=%cd%
pushd ..
pushd ..

set QZ_PATH=%cd%
set QUARTZ_ROOT=%QZ_PATH:\=/%
echo "Using QUARTZ_ROOT => %QUARTZ_ROOT%"

echo "Using Qt Root: %QT_ROOT%"
set QT_CMAKE_PATH=%QT_ROOT%\lib\cmake

set BUILD_DIR="__quartz_release"
cd "%QUARTZ_ROOT%/build"
if exist %BUILD_DIR% rd /q /s %BUILD_DIR%
mkdir %BUILD_DIR%
cd %BUILD_DIR%

cmake -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=%QT_CMAKE_PATH% -DCMAKE_BUILD_TYPE=Release "%QUARTZ_ROOT%"
if %ERRORLEVEL% NEQ 0 goto error
mingw32-make -j4 install

cd %INVOKE_DIR%

goto end

:error
cd %INVOKE_DIR%
EXIT /B %ERRORLEVEL%

:end
endlocal