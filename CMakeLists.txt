cmake_minimum_required(VERSION 3.8)
project("CANBusSimulator")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CANBusSimulator main.cpp CANMessage.cpp CANMessage.h CANNode.h CANBus.cpp CANBus.h EngineECU.h EngineECU.cpp ABSNode.cpp ABSNode.h Dashboard.h Dashboard.cpp)