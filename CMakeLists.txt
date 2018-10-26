cmake_minimum_required(VERSION 3.9)
project(WaveParser C)

set(CMAKE_C_STANDARD 11)

add_library(WaveParser
        base_def.h
        wave_reader.c wave_reader.h
        print_util.c print_util.h
        common_util.c common_util.h
        log.c log.h
        wave_common.c wave_common.h
        )

link_libraries(WaveParser asound)

add_executable(WaveParser-bin test.c extenal/play.c extenal/play.h)