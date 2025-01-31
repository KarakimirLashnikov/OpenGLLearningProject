file(GLOB_RECURSE 
	APPLICATION 
	"./*.cpp"
	"./*.hpp"
	"./camera/*.cpp"
	"./camera/*.hpp"
)
add_library(app ${APPLICATION})