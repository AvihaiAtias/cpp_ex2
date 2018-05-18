cmake_minimum_required(VERSION 3.10)
project(ex2)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex2 main.cpp TransportSystem.cpp TransportSystem.h Validations.cpp Validations.cpp Validations.h IOmanager.cpp IOmanager.h Exceptions.h Vehicle.cpp Vehicle.h Bus.h Tram.h Sprinter.h Rail.h Station.cpp Station.h)