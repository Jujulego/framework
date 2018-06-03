#pragma once

// Importations
#include <type_traits>

#include "int.hpp"

// Namespace
namespace meta {

// Métafonction
template<size_t VAL>
struct factorielle {
	// Alias
	using type = size_<VAL * factorielle<VAL-1>::type::value>;
};

template<>
struct factorielle<1> {
	// Alias
	using type = size_<1>;
};

} // meta
