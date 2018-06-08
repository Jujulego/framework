#pragma once

// Importations
#include <vector>

#include "math/coord.hpp"
#include "math/forme.hpp"

// Namespace
namespace plateau {

// Classe
template<class Objet>
class Plateau2D {
	public:
		// Alias
		using point_type = math::Point<unsigned,2>;
		using vecteur_type = math::Vecteur<int,2>;

		// Constantes
		static const vecteur_type HAUT;
		static const vecteur_type BAS;
		static const vecteur_type GAUCHE;
		static const vecteur_type DROITE;
		static const vecteur_type DIRECTIONS[];

		// Classe
		class case_iterator {
			public:
				// Constructeur
				case_iterator(Plateau2D* plateau, point_type const& pos)
					: m_pos(pos), m_plateau(plateau) {}

				// Opérateurs
				// - déférenciation
				Objet& operator *  () const { return (*m_plateau)[m_pos[1]][m_pos[0]]; }
				Objet* operator -> () const { return (m_plateau->m_carte[m_pos[1]].begin() + m_pos[0]).operator -> (); }

				// - assignation
				case_iterator& operator += (vecteur_type const& v) { m_pos += v; return *this; }
				case_iterator& operator -= (vecteur_type const& v) { m_pos -= v; return *this; }

				// - arithmétique
				case_iterator operator + (vecteur_type const& v) const { return case_iterator(m_plateau, m_pos + v); }
				case_iterator operator - (vecteur_type const& v) const { return case_iterator(m_plateau, m_pos - v); }

				vecteur_type operator - (case_iterator const& cit) const {
					return m_pos - cit.m_pos;
				}

				// Méthodes
				bool valide() const {
					return m_plateau->m_rectangle.contient(m_pos);
				}

				std::vector<case_iterator> cases_adjacentes() const {
					std::vector<case_iterator> adja;

					for (auto dir : DIRECTIONS) {
						auto pos = m_pos + dir;

						if (m_rectangle.contient(pos)) {
							adja.push_back(case_iterator(m_plateau, pos));
						}
					}

					return adja;
				}

				// - accesseurs
				point_type& position() {
					return m_pos;
				}

				point_type const& position() const {
					return m_pos;
				}

				Plateau2D& plateau() const {
					return *m_plateau;
				}

			private:
				// Attributs
				point_type m_pos;
				Plateau2D* m_plateau;
		};

		class case_const_iterator {
			public:
				// Constructeurs
				case_const_iterator(Plateau2D const* plateau, point_type const& pos)
					: m_pos(pos), m_plateau(plateau) {}

				case_const_iterator(case_iterator const& cit)
					: m_pos(cit.m_pos), m_plateau(cit.m_plateau) {}

				// Opérateurs
				// - déférenciation
				Objet const& operator *  () const { return (*m_plateau)[m_pos[1]][m_pos[0]]; }
				Objet const* operator -> () const { return (m_plateau->m_carte[m_pos[1]].begin() + m_pos[0]).operator -> (); }

				// - assignation
				case_const_iterator& operator += (vecteur_type const& v) { m_pos += v; return *this; }
				case_const_iterator& operator -= (vecteur_type const& v) { m_pos -= v; return *this; }

				// - arithmétique
				case_const_iterator operator + (vecteur_type const& v) const { return case_iterator(m_plateau, m_pos + v); }
				case_const_iterator operator - (vecteur_type const& v) const { return case_iterator(m_plateau, m_pos - v); }

				vecteur_type operator - (case_const_iterator const& cit) const {
					return m_pos - cit.m_pos;
				}

				// Méthodes
				bool valide() const {
					return m_plateau->m_rectangle.contient(m_pos);
				}

				std::vector<case_const_iterator> cases_adjacentes() const {
					std::vector<case_const_iterator> adja;

					for (auto dir : DIRECTIONS) {
						auto pos = m_pos + dir;

						if (m_rectangle.contient(pos)) {
							adja.push_back(case_const_iterator(m_plateau, pos));
						}
					}

					return adja;
				}

				// - accesseurs
				point_type& position() {
					return m_pos;
				}

				point_type const& position() const {
					return m_pos;
				}

				Plateau2D const& plateau() const {
					return *m_plateau;
				}

			private:
				// Attributs
				point_type m_pos;
				Plateau2D const* m_plateau;
		};

		// Constructeur
		Plateau2D(size_t lignes, size_t colonnes, Objet defaut = Objet()) : m_lignes(lignes), m_colonnes(colonnes),
			m_rectangle(colonnes, lignes), m_carte(lignes, std::vector<Objet>(colonnes, defaut)) {}

		// Opérateurs
		std::vector<Objet>& operator [] (int i) {
			return m_carte[i];
		}

		std::vector<Objet> const& operator [] (int i) const {
			return m_carte[i];
		}

		Objet& operator [] (point_type const& pt) {
			return m_carte[pt[0]][pt[1]];
		}

		Objet const& operator [] (point_type const& pt) const {
			return m_carte[pt[0]][pt[1]];
		}

		// Méthodes
		bool contient(math::Point<unsigned,2> const& pt) const {
			return m_rectangle.contient(pt);
		}

		case_iterator get(math::Point<unsigned,2> const& pt) {
			return case_iterator(this, pt);
		}

		case_const_iterator get(math::Point<unsigned,2> const& pt) const {
			return case_const_iterator(this, pt);
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
		math::Rectangle<unsigned> m_rectangle;

	protected:
		std::vector<std::vector<Objet>> m_carte;
};

// Variables statiques
template<class Objet> const typename Plateau2D<Objet>::vecteur_type Plateau2D<Objet>::HAUT({   0, -1});
template<class Objet> const typename Plateau2D<Objet>::vecteur_type Plateau2D<Objet>::BAS({    0,  1});
template<class Objet> const typename Plateau2D<Objet>::vecteur_type Plateau2D<Objet>::GAUCHE({ 1,  0});
template<class Objet> const typename Plateau2D<Objet>::vecteur_type Plateau2D<Objet>::DROITE({-1,  0});

template<class Objet>
const typename Plateau2D<Objet>::vecteur_type Plateau2D<Objet>::DIRECTIONS[] = {
	Plateau2D<Objet>::HAUT,
	Plateau2D<Objet>::BAS,
	Plateau2D<Objet>::GAUCHE,
	Plateau2D<Objet>::DROITE
};

} // plateau
