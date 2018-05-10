// Importations
#include <iomanip>
#include <iostream>

#include "math/coord.hpp"
#include "math/matrice.hpp"
#include "math/nombre.hpp"
#include "math/operations.hpp"
#include "math/polynome.hpp"
#include "math/range.hpp"

// Prototype
template<class Int,size_t L,size_t C>
void aff_matrice(math::Matrice<Int,L,C> const& mat, size_t larg = 4);

// Main
int main() {
	math::Polynome<int,3> p1({-42, 0, -12, 1});
	math::Polynome<int,1> p2({-3, 1});
	auto q = p1 / p2;
	auto r = p1 % p2;

	std::cout << q << std::endl;
	std::cout << r << std::endl;

	return 0;
}

// Fonctions
template<class Int,size_t L,size_t C>
void aff_matrice(math::Matrice<Int,L,C> const& mat, size_t larg) {
	std::cout << std::setfill(' ');

	for (auto c : math::range(mat.size())) {
		std::cout << std::setw(larg) << mat[c] << " ";

		if (c[1]+1 == mat.nb_col()) {
			std::cout << std::endl;
		}
	}
}
