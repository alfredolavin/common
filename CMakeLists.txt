cmake_minimum_required(VERSION 3.26)

set(PROG_TYPE usbasp)


# Variables regarding the AVR chip
set(MCU   attiny85)
set(F_CPU 8000000)
set(BAUD  9600)
add_definitions(-DF_CPU=${F_CPU})

# program names
set(AVRCPP   avr-g++)
set(AVRC     avr-gcc)
set(AVRSTRIP avr-strip)
set(OBJCOPY  avr-objcopy)
set(OBJDUMP  avr-objdump)
set(AVRSIZE  avr-size)
set(AVRDUDE  avrdude)

# Sets the compiler
# Needs to come before the project function
set(CMAKE_SYSTEM_NAME  Generic)
set(CMAKE_CXX_COMPILER ${AVRCPP})
set(CMAKE_C_COMPILER   ${AVRC})
set(CMAKE_ASM_COMPILER   ${AVRC})

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME ProjectName)   
string(REPLACE " " "_" ProjectId ${ProjectName})
project (${ProjectName} C CXX ASM)

# Important project paths
set(BASE_PATH    "${${PROJECT_NAME}_SOURCE_DIR}")
set(INC_PATH     "${BASE_PATH}/eduardino")
set(SRC_PATH     "${BASE_PATH}")
set(LIB_DIR_PATH "${BASE_PATH}/eduardino")

# Files to be compiled
file(GLOB_RECURSE SRC_FILES	FOLLOW_SYMLINKS "${SRC_PATH}/*.cpp"
										"${SRC_PATH}/*.cpp"
                    "${SRC_PATH}/*.cc"
                    "${SRC_PATH}/*.c"
                    "${SRC_PATH}/*.cxx"
                    "${SRC_PATH}/*.S"
                    "${SRC_PATH}/*.s"
                    "${SRC_PATH}/*.sx"
                    "${SRC_PATH}/*.asm")
list(FILTER SRC_FILES EXCLUDE REGEX "${PROJECT_SOURCE_DIR}/build/.*" )

set(LIB_SRC_FILES)
set(LIB_INC_PATH)
file(GLOB_RECURSE LIBRARIES "${LIB_DIR_PATH}/**")
foreach(subdir ${LIBRARIES})
    file(GLOB lib_files "${subdir}*.cpp"
												"${subdir}/*.cpp"
                        "${subdir}/*.cc"
                        "${subdir}/*.c"
                        "${subdir}/*.cxx"
                        "${subdir}/*.S"
                        "${subdir}/*.s"
                        "${subdir}/*.sx"
                        "${subdir}/*.asm")
    if(IS_DIRECTORY ${subdir})
        list(APPEND LIB_INC_PATH  "${subdir}")
    endif()
    list(APPEND LIB_SRC_FILES "${lib_files}")
endforeach()

# Compiler flags
set(CSTANDARD "-std=gnu99")
set(CDEBUG    " -g -ggdb")
set(CWARN     "-Wall -Wstrict-prototypes -Wl,--gc-sections -Wl,--relax")
set(CTUNING   "-funsigned-char -funsigned-bitfields -fshort-enums -ffunction-sections -fdata-sections -g3 -Os -fno-exceptions -std=gnu++23 -fpermissive")
set(COPT      "-Os -lm -lprintf_flt")
set(CMCU      "-mmcu=${MCU}")
set(CDEFS     "-DF_CPU=${F_CPU} -DBAUD=${BAUD}")

set(CFLAGS   "${CMCU} ${CDEBUG} ${CDEFS} ${COPT} ${CWARN} ${CSTANDARD} ${CTUNING}")
set(CXXFLAGS "${CMCU} ${CDEBUG} ${CDEFS} ${COPT} ${CTUNING}")

set(CMAKE_C_FLAGS   "${CFLAGS}")
set(CMAKE_CXX_FLAGS "${CXXFLAGS}")
set(CMAKE_ASM_FLAGS   "${CFLAGS}")

# Project setup
include_directories(${INC_PATH} ${LIB_INC_PATH})
add_executable(${PROJECT_NAME} ${SRC_FILES} ${LIB_SRC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.elf")

# Compiling targets
add_custom_target(strip ${AVRSTRIP} "${PROJECT_NAME}.elf" DEPENDS ${PROJECT_NAME}.elf)
add_custom_target(hex ALL ${OBJCOPY} -R .eeprom -O ihex "${PROJECT_NAME}.elf" "${PROJECT_NAME}.hex"  DEPENDS ${PROJECT_NAME}.elf)
add_custom_target(eeprom ${OBJCOPY} -j .eeprom --change-section-lma .eeprom=0 -O ihex "${PROJECT_NAME}.elf" "${PROJECT_NAME}.eeprom"  DEPENDS ${PROJECT_NAME}.elf)
add_custom_target(listing ALL ${OBJDUMP} -x "${PROJECT_NAME}.elf" > "${PROJECT_NAME}.map" DEPENDS ${PROJECT_NAME}.elf)
add_custom_target(map ALL ${OBJDUMP} -h --source --no-show-raw-insn --visualize-jumps=extended-color --wide --demangle --disassembler-color=extended-color -S "${PROJECT_NAME}.elf" | ansi2html.sh > "${PROJECT_NAME}.lss.html"  DEPENDS ${PROJECT_NAME}.elf)
add_custom_target(size ALL ${AVRSIZE} --format=berkeley -t "${PROJECT_NAME}.elf"  DEPENDS ${PROJECT_NAME}.elf)
add_custom_target(flash ${AVRDUDE} -c ${PROG_TYPE} -p ${MCU} -U flash:w:${PROJECT_NAME}.hex DEPENDS ${PROJECT_NAME}.elf)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_NAME}.hex;${PROJECT_NAME}.eeprom;${PROJECT_NAME}.lst")
