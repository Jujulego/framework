#
# Module
#
add_library(othello MODULE
	module.cpp
	pion.cpp
	pion.hpp
	othellier.cpp
	othellier.hpp
)

target_link_libraries(othello math console)
