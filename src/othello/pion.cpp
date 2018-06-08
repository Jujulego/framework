// Importations
#include "pion.hpp"

// Constructeur
Pion::Pion(Pion::Couleur couleur) : m_couleur(couleur) {}

// Méthodes
void Pion::changer() {
	switch (m_couleur) {
	case BLANC:
		m_couleur = NOIR;
		break;

	case NOIR:
		m_couleur = BLANC;
		break;

	case VIDE:
		break;
	}
}

bool Pion::vide() const {
	return m_couleur == VIDE;
}

bool Pion::ami(Pion const& pion) const {
	return pion.m_couleur == m_couleur;
}

bool Pion::ennemi(Pion const& pion) const {
	switch (m_couleur) {
	case BLANC:
		return pion.m_couleur == NOIR;

	case NOIR:
		return pion.m_couleur == BLANC;

	case VIDE:
		return false;
	}
}

// - accesseurs
Pion::Couleur& Pion::couleur() {
	return m_couleur;
}

Pion::Couleur const& Pion::couleur() const {
	return m_couleur;
}
