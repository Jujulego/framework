#pragma once

// Imporations
#include <type_traits>

// Namespace
namespace meta {

// Liste
template<class V, class L = void>
struct liste {
	// Alias
	using valeur = V;
	using type = typename V::value_type;

	using suivant = L;

	// Attributs
	static constexpr bool fin = false;
};

template<class V>
struct liste<V,void> {
	// Alias
	using valeur = V;
	using type = typename V::value_type;

	// Attributs
	static constexpr bool fin = true;
};

// Liste de valeurs
template<class T, T V, T... VALS>
struct vliste : liste<std::integral_constant<T,V>,vliste<T,VALS...>> {};

template<class T, T V>
struct vliste<T,V> : liste<std::integral_constant<T,V>> {};

// Opérations
// - count
template<class L, bool FIN = L::fin>
struct taille : std::integral_constant<typename L::type, taille<typename L::suivant, L::suivant::fin>::value + 1> {};

template<class L>
struct taille<L,true> : std::integral_constant<typename L::type, 1> {};

// - push_back
template<class L, class V, bool FIN = L::fin>
struct push_back {
	// Alias
	using type = liste<typename L::valeur, typename push_back<typename L::suivant, V, L::suivant::fin>::type>;
};

template<class L, class V>
struct push_back<L,V,true> {
	// Alias
	using type = liste<typename L::valeur, liste<V>>;
};

template<class L, typename L::type V>
struct vpush_back {
	using type = typename push_back<L,std::integral_constant<typename L::type,V>>::type;
};

// - push_front
template<class L, class V>
struct push_front {
	// Alias
	using type = liste<V,L>;
};

template<class L, typename L::type V>
struct vpush_front {
	// Alias
	using type = typename push_front<L,std::integral_constant<typename L::type,V>>::type;
};

} // meta
