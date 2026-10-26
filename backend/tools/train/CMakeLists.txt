cmake_minimum_required(VERSION 3.18)
project(nc_train CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

find_package(Torch REQUIRED)
find_package(nlohmann_json 3 REQUIRED)
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/../../src)

# the ML module, compiled once; we add files here as we build them
add_library(nc_ml STATIC
  ${SRC}/ml/Dataset.cpp
  ${SRC}/ml/Model.cpp
  ${SRC}/ml/Metrics.cpp
  ${SRC}/ml/Trainer.cpp)
target_include_directories(nc_ml PUBLIC ${SRC})
target_link_libraries(nc_ml PUBLIC "${TORCH_LIBRARIES}" nlohmann_json::nlohmann_json)


foreach(t test_dataset test_standardize test_tensors test_model test_metrics test_train test_save)
  add_executable(${t} ${t}.cpp)
  target_link_libraries(${t} PRIVATE nc_ml)
endforeach()