file(GLOB_RECURSE 
    WRAPPER 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp 
)

add_library(wrapper ${WRAPPER})