# you can change cmake version if your version is lower than this,
cmake_minimum_required(VERSION 3.8)
project(WaveParser C)

set(CMAKE_C_STANDARD 11)

add_library(WaveParser
        base_def.h
        wave_reader.c wave_reader.h
        print_util.c print_util.h
        common_util.c common_util.h
        log.c log.h
        wave_common.c wave_common.h
        wave_writer.c wave_writer.h)

# comment the following line to build lib

link_libraries(WaveParser openal)

add_executable(WaveParser-bin test.c extenal/play.c extenal/play.h)
