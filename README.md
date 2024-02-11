1. Complete the Getting started with Raspberry Pi Pico :

   https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf?_gl=1*r2v8m9*_ga*MTcxOTc2MzgwNi4xNzA3MjYzODA5*_ga_22FD70LWDS*MTcwNzYwOTU4Mi4xLjAuMTcwNzYwOTU4Mi4wLjAuMA..
  
3. Clone Git Repo
  
5. in ./CMakeLists.txt line 3, set PICO_SDK_PATH to the file path where locally installed pico_sdk is located. 
  
7. mkdir build
   
9. cd build
   
11.  cmake ..
   
13. make
   
15. Connect Pi Pico in bootsel mode 
   
17. drag resulting .uf2 file in build to pi pico drive to load it.
