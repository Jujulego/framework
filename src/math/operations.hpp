#pragma once

// Importation
#include <cmath>

#include "coord.hpp"
#include "nombre.hpp"

// Namespace
namespace math {

// Norme
template<class Int, size_t DEG>
auto norme(Vecteur<DEG,Int> const& vec) {
	Int somme = 0;
	for (Int v : vec) somme += (v * v);

	return std::sqrt(somme);
}

template<class Int, size_t DEG>
auto norme(Vecteur<DEG,Nombre<Int>> const& vec) {
	Nombre<Int> somme = 0;
	for (Nombre<Int> v : vec) somme += (v * v);

	if (somme.est_inf()) {
		return INFINI;
	} else {
		return std::sqrt(somme.val());
	}
}

template<class Int>
Int norme(Vecteur<1,Int> const& vec) {
	return vec[0];
}

// Produit scalaire
template<class Int, size_t DEG>
Int scalaire(Vecteur<DEG,Int> const& v1, Vecteur<DEG,Int> const& v2) {
	Int res = 0;

	for (int i = 0; i < DEG; ++i) {
		res += v1[i] * v2[i];
	}

	return res;
}

// Produit vectoriel
template<class Int>
Vecteur<3,Int> vectoriel(Vecteur<3,Int> const& v1, Vecteur<3,Int> const& v2) {
	Vecteur<3,Int> r;

	// Calculs
	r[0] = v1[1] * v2[2] - v1[2] * v2[1];
	r[1] = v1[2] * v2[0] - v1[0] * v2[2];
	r[2] = v1[0] * v2[1] - v1[1] * v2[0];

	return r;
}

} // math
