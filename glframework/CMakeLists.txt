file(GLOB_RECURSE GLFRAMEWORK ./*.cpp ./*.hpp)

add_library(GLFramework ${GLFRAMEWORK} "core.h")