# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/TIRTHA/esp/esp-idf/components/bootloader/subproject"
  "D:/IOT-and-Robotics/IOT-and-Robotics/ESP-IDF/usb_host_lib/build/bootloader"
  "D:/IOT-and-Robotics/IOT-and-Robotics/ESP-IDF/usb_host_lib/build/bootloader-prefix"
  "D:/IOT-and-Robotics/IOT-and-Robotics/ESP-IDF/usb_host_lib/build/bootloader-prefix/tmp"
  "D:/IOT-and-Robotics/IOT-and-Robotics/ESP-IDF/usb_host_lib/build/bootloader-prefix/src/bootloader-stamp"
  "D:/IOT-and-Robotics/IOT-and-Robotics/ESP-IDF/usb_host_lib/build/bootloader-prefix/src"
  "D:/IOT-and-Robotics/IOT-and-Robotics/ESP-IDF/usb_host_lib/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/IOT-and-Robotics/IOT-and-Robotics/ESP-IDF/usb_host_lib/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/IOT-and-Robotics/IOT-and-Robotics/ESP-IDF/usb_host_lib/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
