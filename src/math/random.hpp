#pragma once

// Importations
#include <chrono>
#include <functional>
#include <random>
#include <type_traits>

#include "coord.hpp"
#include "meta.hpp"

// Namespace
namespace math {

// Métafonction
template<class I, I V1, I... VS>
struct produit : std::integral_constant<I, V1 * produit<I, VS...>::value> {};

template<class I, I V>
struct produit<I,V> : std::integral_constant<I,V> {};

// Générateur de points aléatoires !
template<class I, I... MAXS>
class GenerateurPoints {
	public:
		// Alias
		using maximums = meta::liste::vliste<size_t,MAXS...>;
		using distribution = typename std::conditional<
			std::is_integral<I>::value,
			std::uniform_int_distribution<I>,
			std::uniform_real_distribution<I>
		>::type;

		// Constructeur
		GenerateurPoints() : hash(meta::liste::max<maximums>::type::value),
			generateur(std::bind(
				distribution(0, meta::liste::pi<maximums>::type::value-1),
				std::mt19937(std::chrono::system_clock::now().time_since_epoch().count())
			)) {}

		// Opérateurs
		math::Point<I,sizeof...(MAXS)> operator () () const {
			return unhash(hash, generateur());
		}

	private:
		// Attributs
		std::hash<math::Point<unsigned,2>> hash;
		std::function<size_t()> generateur;
};

} // math
