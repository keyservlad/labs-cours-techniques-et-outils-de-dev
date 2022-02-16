add_library(
	lib
	stuff.cpp
	stuff.h
	util.cpp
	util.h
)

target_include_directories(
	lib
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)
