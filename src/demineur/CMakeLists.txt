#
# Module
#
add_library(demineur MODULE
	module.cpp
	terrain.hpp
)

target_link_libraries(demineur math console)
