cmake_minimum_required(VERSION 3.5.0)
project(clustering)
include_directories(include)

#Set debug flag
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pthread")

#Can manually add the sources using the set command as follows:
set(SOURCES preprocess.cpp ) 
list(APPEND SOURCES cpp/parser.cpp)
list(APPEND SOURCES cpp/util.cpp)
list(APPEND SOURCES cpp/graph.cpp)
list(APPEND SOURCES cpp/mat.cpp)
list(APPEND SOURCES cpp/dataset_base.cpp)
list(APPEND SOURCES cpp/similarity_base.cpp)
list(APPEND SOURCES cpp/folder.cpp)

#datasets
list(APPEND SOURCES cpp/datasets/ml10m100k.cpp)
list(APPEND SOURCES cpp/datasets/ml2k.cpp)
list(APPEND SOURCES cpp/datasets/ml100k.cpp)
list(APPEND SOURCES cpp/datasets/comoda.cpp)
list(APPEND SOURCES cpp/datasets/netflix.cpp)

#similarities
list(APPEND SOURCES cpp/similarities/nmsd.cpp)
list(APPEND SOURCES cpp/similarities/cosine.cpp)
list(APPEND SOURCES cpp/similarities/correlation.cpp)
list(APPEND SOURCES cpp/similarities/euclidean.cpp)
list(APPEND SOURCES cpp/similarities/loglikelihood.cpp)

#However, the file(GLOB...) allows for wildcard additions:
#file(GLOB_RECURSE SOURCES "cpp/*.cpp")

add_executable(clustering ${SOURCES})

#Set name of executable
set_target_properties(clustering PROPERTIES OUTPUT_NAME preprocess.out PREFIX "")

target_compile_features(clustering PRIVATE cxx_range_for)