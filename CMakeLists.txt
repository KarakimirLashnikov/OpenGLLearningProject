# CMakeList.txt: OpenGLCmakeProject 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
# 
project ("OpenGLCmakeProject")
set (CMAKE_CXX_STANDARD 20)

add_definitions(-DDEBUG)
# 查找目录
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/
	include/
	dependency/include/
)

file(GLOB ASSETS "./assets")
file(COPY ${ASSETS} DESTINATION ${CMAKIE_BINARY_DIR}/)

link_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/dependency/lib
)

add_subdirectory(wrapper)
add_subdirectory(application)
add_subdirectory(glframework)

# 将源代码添加到此项目的可执行文件。
add_executable (
	OpenGLCmakeProject 
	"src/OpenGLCmakeProject.cpp" 
	"src/glad.c"
)

# 链接库
target_link_libraries(
	OpenGLCmakeProject 
	opengl32
	glfw3.lib
	soil2-debug.lib
	wrapper
	app
	GLFramework
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OpenGLCmakeProject PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
