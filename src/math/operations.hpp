#pragma once

// Importation
#include <cmath>

#include "coord.hpp"
#include "nombre.hpp"

// Namespace
namespace math {

// Norme
template<class Int, size_t DEG>
auto norme(Vecteur<Int,DEG> const& vec) {
	Int somme = 0;
	for (Int v : vec) somme += (v * v);

	return std::sqrt(somme);
}

template<class Int, size_t DEG>
auto norme(Vecteur<Nombre<Int>,DEG> const& vec) {
	Nombre<Int> somme = 0;
	for (Nombre<Int> v : vec) somme += (v * v);

	if (somme.est_inf()) {
		return INFINI;
	} else {
		return std::sqrt(somme.val());
	}
}

template<class Int>
Int norme(Vecteur<Int,1> const& vec) {
	return vec[0];
}

// Produit scalaire
template<class Int, size_t DEG>
Int scalaire(Vecteur<Int,DEG> const& v1, Vecteur<Int,DEG> const& v2) {
	Int res = 0;

	for (int i = 0; i < DEG; ++i) {
		res += v1[i] * v2[i];
	}

	return res;
}

// Produit vectoriel
template<class Int>
Vecteur<Int,3> vectoriel(Vecteur<Int,3> const& v1, Vecteur<Int,3> const& v2) {
	Vecteur<Int,3> r;

	// Calculs
	r[0] = v1[1] * v2[2] - v1[2] * v2[1];
	r[1] = v1[2] * v2[0] - v1[0] * v2[2];
	r[2] = v1[0] * v2[1] - v1[1] * v2[0];

	return r;
}

} // math
