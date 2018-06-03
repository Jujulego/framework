#pragma once

// Importations
#include <type_traits>

// Namespace
namespace meta {

// Métafonctions
template<class V1>
struct neg_ {
	// Alias
	using type = std::integral_constant<typename V1::value_type, -V1::value>;
};

template<class V1>
struct not_ {
	// Alias
	using type = std::integral_constant<typename V1::value_type, ~V1::value>;
};

template<class V1, class V2>
struct add_ {
	// Alias
	using type = std::integral_constant<typename V1::value_type, V1::value + V2::value>;
};

template<class V1, class V2>
struct sub_ {
	// Alias
	using type = std::integral_constant<typename V1::value_type, V1::value - V2::value>;
};

template<class V1, class V2>
struct mul_ {
	// Alias
	using type = std::integral_constant<typename V1::value_type, V1::value * V2::value>;
};

template<class V1, class V2>
struct div_ {
	// Alias
	using type = std::integral_constant<typename V1::value_type, V1::value / V2::value>;
};

template<class V1, class V2>
struct and_ {
	// Alias
	using type = std::integral_constant<typename V1::value_type, V1::value & V2::value>;
};

template<class V1, class V2>
struct or_ {
	// Alias
	using type = std::integral_constant<typename V1::value_type, V1::value | V2::value>;
};

template<class V1, class V2>
struct xor_ {
	// Alias
	using type = std::integral_constant<typename V1::value_type, V1::value ^ V2::value>;
};

} // meta
