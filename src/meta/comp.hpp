#pragma once

// Importations
#include <type_traits>

#include "int.hpp"

// Namespace
namespace meta {

// Métafonctions
template<class V1, class V2>
struct inf {
	// Alias
	using type = std::integral_constant<bool, (V2::value > V1::value)>;
};

template<class V1, class V2>
struct inf_egal {
	// Alias
	using type = std::integral_constant<bool, (V1::value <= V2::value)>;
};

template<class V1, class V2>
struct egal {
	// Alias
	using type = std::integral_constant<bool, (V1::value == V2::value)>;
};

template<class V1, class V2>
struct diff {
	// Alias
	using type = std::integral_constant<bool, (V1::value != V2::value)>;
};

template<class V1, class V2>
struct sup_egal {
	// Alias
	using type = std::integral_constant<bool, (V1::value >= V2::value)>;
};

template<class V1, class V2>
struct sup {
	// Alias
	using type = std::integral_constant<bool, (V1::value > V2::value)>;
};

} // meta
