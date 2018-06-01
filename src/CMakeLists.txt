#
# Dossiers
#
add_subdirectory(math)
add_subdirectory(console)

add_subdirectory(demineur)

#
# Executable run
#
add_executable(run
	main.cpp

	module.hpp
	modules.hpp
	modules.cpp
)

target_link_libraries(run math console)

if (UNIX)
	target_link_libraries(run dl)
endif()
