1. Clone Git Repo
2. in ./CMakeLists.txt line 3, set PICO_SDK_PATH to the file path where locally installed pico_sdk is located. 
3. mkdir build
4. cd build
5. cmake ..
6. make
7. Connect Pi Pico in bootsel mode 
8. drag resulting .uf2 file in build to pi pico drive to load it.