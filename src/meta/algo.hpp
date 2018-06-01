#pragma once

// Importations
#include <type_traits>

#include "comp.hpp"
#include "for_each.hpp"
#include "meta/math.hpp"

// Namespace
namespace meta {

// Métafonctions
// - identité
template<class V>
struct ident {
	using type = V;
};

// - maximum
template<class T, T V1, T... VS>
struct max : max<T, V1, max<T, VS...>::value> {};

template<class T, T V1, T V2>
struct max<T, V1, V2> : std::conditional<(V1 > V2),
	std::integral_constant<T,V1>,
	std::integral_constant<T,V2>
>::type {};

// - minimum
template<class T, T V1, T... VS>
struct min : min<T, V1, min<T, VS...>::value> {};

template<class T, T V1, T V2>
struct min<T, V1, V2> : std::conditional<(V2 > V1),
	std::integral_constant<T,V1>,
	std::integral_constant<T,V2>
>::type {};

} // meta
