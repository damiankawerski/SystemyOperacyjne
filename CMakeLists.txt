cmake_minimum_required(VERSION 3.28)
project(Kolos)

set(CMAKE_CXX_STANDARD 14)

add_executable(Kolos
        Watki.c
        KolejkaKomunikaty.c
        SharedMemorySENDER.c
        SharedMemoryReceiver.c)
