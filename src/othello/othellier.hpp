#pragma once

// Importations
#include "plateau/2d.hpp"
#include "pion.hpp"

// Classe
class Othellier : public plateau::Plateau2D<Pion> {
	public:
		// Alias
		using point_type = typename plateau::Plateau2D<Pion>::point_type;
		using vecteur_type = typename plateau::Plateau2D<Pion>::vecteur_type;

		// Constantes
		static const vecteur_type DIRECTIONS[];

		// Constructeur
		Othellier();

		// Méthodes
		bool vide(point_type const& pt) const;
		unsigned poser(point_type const& pt, Pion const& pion);
};
