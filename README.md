# BODA ATTACHMENT BASE
A Raspberry Pi Pico (rp2040) based project to coincide with the Boda capstone project. 

# Description
The Boda is a robotic arm that has interchangeable attachments that can be designed for a users use-case. The attachments are based on an rp2040 (Raspberry Pi Pico) that has been programmed using this repo.
The repo includes a pre-formatted framework which contains the functionality to communicate with a Boda base arm and 

# System Requirements
- cmake
- Pi Pico C/C++ SDK

**Windows/iMac**

VSCode and A valid instance of WSL/WSL2; development used WSL2: Ubuntu

# Build Instructions
1. Complete the Getting started with Raspberry Pi Pico to properly download and install the rp2040 C/C++ SDK (if not installed) :

   https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf?_gl=1*r2v8m9*_ga*MTcxOTc2MzgwNi4xNzA3MjYzODA5*_ga_22FD70LWDS*MTcwNzYwOTU4Mi4xLjAuMTcwNzYwOTU4Mi4wLjAuMA..

2. Clone Git Repo to a local folder.

3. In the top level project directory, edit the `CMakeLists.txt` locate line 3:
```
set(PICO_SDK_PATH "/{FILE_PATH}/pico-sdk")
```
&emsp; and change the file path where the locally installed `pico-sdk` folder is located.

4. In the VSCode Terminal, create a build directory:
```
mkdir build
```

5. Enter the build directory:
```
cd build
```

6. Generate the Build files using cmake by running:
```
cmake .. 
```

7. Generate `main.uf2` to upload to the Raspberry Pi Pico:
```
make
```

8. Connect Pi Pico in bootsel mode by holding the `BOOTSEL` button while inserting the USB.
9. Drag resulting `main.uf2` file in the build directory into pi pico's drive to load it.

# Development Instructions:
