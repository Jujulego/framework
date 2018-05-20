#
# Librairies
#
add_library(console SHARED
	asciiart.cpp
	asciiart.hpp
	chars.cpp
	chars.hpp
	console.cpp
	console.hpp
	manip.cpp
	manip.hpp
	menu.cpp
	menu.hpp
	posstream.hpp
	style.cpp
	style.hpp
)

target_link_libraries(console math)
