#pragma once

// Importations
#include <vector>

#include "math/coord.hpp"
#include "math/forme.hpp"

// Namespace
namespace plateau {

// Classe
template<class Case>
class Plateau2D {
	public:
		// Constructeur
		Plateau2D(size_t lignes, size_t colonnes, Case defaut = Case()) : m_lignes(lignes), m_colonnes(colonnes),
			m_carte(lignes, std::vector<Case>(colonnes, defaut)), m_rectangle(colonnes, lignes) {}

		// Opérateurs
		std::vector<Case>& operator [] (int i) {
			return m_carte[i];
		}

		std::vector<Case> const& operator [] (int i) const {
			return m_carte[i];
		}

		Case& operator [] (math::Point<unsigned,2> const& pt) {
			return m_cartes[pt[0]][pt[1]];
		}

		Case const& operator [] (math::Point<unsigned,2> const& pt) const {
			return m_cartes[pt[0]][pt[1]];
		}

		// Méthodes
		bool contient(math::Point<unsigned,2> const& pt) const {
			return m_rectangle.contient(pt);
		}

		Case& get(math::Point<unsigned,2> const& pt) {
			return m_cartes[pt[0]][pt[1]];
		}

		Case const& get(math::Point<unsigned,2> const& pt) const {
			return m_cartes[pt[0]][pt[1]];
		}

		void set(math::Point<unsigned,2> const& pt, Case const& c) {
			m_cartes[pt[0]][pt[1]] = c;
		}

		// - accesseurs
		size_t nbLignes() const {
			return m_lignes;
		}

		size_t nbColonnes() const {
			return m_colonnes;
		}

	private:
		// Attributs
		size_t m_lignes, m_colonnes;
		std::vector<std::vector<Case>> m_carte;
		math::rectangle<unsigned> m_rectangle;
};

} // plateau
