# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(PocketWX C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(PocketWX main.cpp ssd1306_i2c.cpp display.cpp wx_sensor_module.cpp hardware_utils.cpp bmep280.cpp logger.cpp menu/menu.cpp menu/menu_items.cpp)

pico_set_program_name(PocketWX "PocketWX")
pico_set_program_version(PocketWX "0.2")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(PocketWX 0)
pico_enable_stdio_usb(PocketWX 1)

# Add the standard library to the build
target_link_libraries(PocketWX
        pico_stdlib hardware_i2c)

# Add the standard include files to the build
target_include_directories(PocketWX PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(PocketWX)

