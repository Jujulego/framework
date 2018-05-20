#
# Dossiers
#
add_subdirectory(math)
add_subdirectory(console)

#
# Executable run
#
add_executable(run
	main.cpp

	# Console
#	console/asciiart.cpp
#	console/asciiart.hpp
#	console/chars.cpp
#	console/chars.hpp
#	console/console.cpp
#	console/console.hpp
#	console/manip.cpp
#	console/manip.hpp
#	console/menu.hpp
#	console/menu.cpp
#	console/posstream.hpp
#	console/style.cpp
#	console/style.hpp

	# Math
#	math/coord.hpp
#	math/infini.cpp
#	math/infini.hpp
#	math/matrice.hpp
#	math/nombre.hpp
#	math/operations.hpp
#	math/polynome.hpp
#	math/range.hpp
)

target_link_libraries(run math console)
