// Importations
#include <vector>

#include "plateau/2d.hpp"

#include "othellier.hpp"
#include "pion.hpp"

// Constantes
const Othellier::vecteur_type Othellier::DIRECTIONS[] = {
	plateau::Plateau2D<Pion>::HAUT,
	plateau::Plateau2D<Pion>::HAUT + plateau::Plateau2D<Pion>::GAUCHE,
	plateau::Plateau2D<Pion>::GAUCHE,
	plateau::Plateau2D<Pion>::BAS + plateau::Plateau2D<Pion>::GAUCHE,
	plateau::Plateau2D<Pion>::BAS,
	plateau::Plateau2D<Pion>::BAS + plateau::Plateau2D<Pion>::DROITE,
	plateau::Plateau2D<Pion>::DROITE,
	plateau::Plateau2D<Pion>::HAUT + plateau::Plateau2D<Pion>::DROITE,
};

// Constructeur
Othellier::Othellier() : plateau::Plateau2D<Pion>(8, 8) {
	// Pions de départ
	m_carte[3][4] = Pion(Pion::NOIR);
	m_carte[4][3] = Pion(Pion::NOIR);
	m_carte[3][3] = Pion(Pion::BLANC);
	m_carte[4][4] = Pion(Pion::BLANC);
};

// Méthodes
bool Othellier::vide(Othellier::point_type const& pt) const {
	return get(pt)->couleur() != Pion::VIDE;
}

unsigned Othellier::poser(Othellier::point_type const& pt, Pion const& pion) {
	// Check position vide
	if (vide(pt)) return 0;

	// Position valide ?
	std::vector<vecteur_type> dirs;
	for (auto dir : DIRECTIONS) {
		auto pos = pt + dir;
		if (!get(pos)->ennemi(pion)) {
			continue;
		}

		for (pos += dir; contient(pos); pos += dir) {
			if (!get(pos)->ami(pion)) {
				dirs.push_back(dir);
				break;

			} else if (get(pos)->vide()) {
				break;
			}
		}
	}

	if (dirs.size() == 0) {
		return 0;
	}

	// Changements
	unsigned nb = 0;
	for (auto dir : dirs) {
		for (auto pos = pt + dir; contient(pos); pos += dir) {
			if (get(pos)->ennemi(pion)) {
				nb++;
				get(pos)->changer();

			} else {
				break;
			}
		}
	}

	return nb;
}
