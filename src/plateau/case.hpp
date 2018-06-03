#pragma once

// Importations
#include "math/coord.hpp"

// Namespace
namespace plateau {

// Classe
template<size_t DEG>
class Case {
	public:
		// Alias
		using point_type = math::Point<unsigned,2>;
		using vecteur_type = math::Vecteur<int,2>;

		// Constructeur
		Case() : Case(point_type()) {}
		Case(point_type pt) : m_point(pt) {}

	private:
		// Attributs
		Pt m_point;
};

} // plateau
