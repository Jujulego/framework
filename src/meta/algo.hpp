#pragma once

// Importations
#include <type_traits>

#include "for_each.hpp"
#include "operations.hpp"

// Namespace
namespace meta {

// Métafonctions
// - identité
template<class V>
struct identite {
	using type = V;
};

// - maximum
template<class V1, class V2>
struct max : std::conditional<(V1::value > V2::value), V1, V2> {};

// - minimum
template<class V1, class V2>
struct min : std::conditional<(V2::value > V1::value), V1, V2> {};

// Pour "metatableau"
namespace tableau {

// Métaalgos
// - maximum
template<class T, T... VS>
struct max : for_each<identite,meta::max,T,VS...> {};

// - minimum
template<class T, T... VS>
struct min : for_each<identite,meta::min,T,VS...> {};

// - sigma (somme de tous les elements)
template<class T, T... VS>
struct sigma : for_each<identite,add_,T,VS...> {};

// - pi (produit de tous les elements)
template<class T, T... VS>
struct pi : for_each<identite,mul_,T,VS...> {};

} // tableau

// Pour "métaliste"
namespace liste {

// Métaalgos
// - maximum
template<class L>
struct max : for_each<identite,meta::max,L> {};

// - minimum
template<class L>
struct min : for_each<identite,meta::min,L> {};

// - sigma (somme de tous les elements)
template<class L>
struct sigma : for_each<identite,add_,L> {};

// - pi (produit de tous les elements)
template<class L>
struct pi : for_each<identite,mul_,L> {};

} // liste
} // meta
