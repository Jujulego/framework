#pragma once

// Imporations
#include <type_traits>

// Namespace
namespace meta {

// Get
template<size_t I, class T, T V, T... Vals>
struct get : std::conditional<I == 0, std::integral_constant<T,V>, get<I-1,T,Vals...>>::type {};

template<size_t I, class T, T V>
struct get<I,T,V> : std::integral_constant<T,V> {
	// Assertion
	static_assert(I == 0, "Index trop grand");
};

} // meta

