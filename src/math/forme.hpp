#pragma once

// Importations
#include <algorithm>
#include <cmath>

#include "coord.hpp"

// Namespace
namespace math {

// Classe de base
template<class Int, size_t DEG>
class Forme {
	public:
		// Destructeur virtuel
		virtual ~Forme() = default;

		// Méthodes abstraites
		virtual bool contient(Point<Int,DEG> const& pt) const = 0;
};

// Classes
template<class Int, size_t DEG>
class DeuxPoints : public Forme<Int,DEG> {
	/**
	 * Teste la présence d'un point dans un objet régulier défini par 2 points (toutes dimension confondues)
	 * Les valeurs maximums sont ignorées
	 *
	 * ex : le rectangle (2D) ou le pavé droit (3D) etc ...
	 */

	protected:
		// Attributs
		Point<Int,DEG> m_pt1, m_pt2;

	public:
		// Constructeurs
		DeuxPoints(Point<Int,DEG> const& pt1, Point<Int,DEG> const& pt2) : m_pt1(pt1), m_pt2(pt2) {}
		DeuxPoints(Point<Int,DEG> const& pt, Vecteur<Int,DEG> const& v) : DeuxPoints(pt, pt + v) {}
		DeuxPoints(Vecteur<Int,DEG> const& v) : DeuxPoints(Point<Int,DEG>(), v) {}

		// Méthodes
		virtual bool contient(Point<Int,DEG> const& pt) const override {
			for (size_t i = 0; i < DEG; ++i) {
				if (pt[i] >= std::max(m_pt1[i], m_pt2[i]) || pt[i] < std::min(m_pt1[i], m_pt2[i])) {
					return false;
				}
			}

			return true;
		}
};

template<class Int>
class Rectangle : public DeuxPoints<Int,2> {
	public:
		// Constructeurs
		Rectangle(Point<Int,2> const& pt1, Point<Int,2> const& pt2) : DeuxPoints<Int,2>(pt1, pt2) {}
		Rectangle(Point<Int,2> const& pt, Vecteur<Int,2> const& v) : DeuxPoints<Int,2>(pt, pt + v) {}
		Rectangle(Vecteur<Int,2> const& v) : DeuxPoints<Int,2>(Point<Int,2>({0, 0}), v) {}
		Rectangle(Int const& tx, Int const& ty) : Rectangle(Vecteur<Int,2>({tx, ty})) {}

		// Méthodes bonus ;)
		Int tx() const {
			return std::abs((DeuxPoints<Int,2>::m_pt1 - DeuxPoints<Int,2>::m_pt2)[0]);
		}

		Int ty() const {
			return std::abs((DeuxPoints<Int,2>::m_pt1 - DeuxPoints<Int,2>::m_pt2)[1]);
		}

		Int perimetre() const {
			return 2*(tx() + ty());
		}

		Int aire() const {
			return tx() * ty();
		}
};

template<class Int>
class PaveDroit : public DeuxPoints<Int,3> {
	public:
		// Constructeurs
		PaveDroit(Point<Int,3> const& pt1, Point<Int,3> const& pt2) : DeuxPoints<Int,3>(pt1, pt2) {}
		PaveDroit(Point<Int,3> const& pt, Vecteur<Int,3> const& v) : DeuxPoints<Int,3>(pt, pt + v) {}
		PaveDroit(Vecteur<Int,3> const& v) : DeuxPoints<Int,3>(Point<Int,3>(), v) {}

		// Méthodes bonus ;)
		Int tx() const {
			return std::abs((DeuxPoints<Int,3>::m_pt1 - DeuxPoints<Int,3>::m_pt2)[0]);
		}

		Int ty() const {
			return std::abs((DeuxPoints<Int,3>::m_pt1 - DeuxPoints<Int,3>::m_pt2)[1]);
		}

		Int tz() const {
			return std::abs((DeuxPoints<Int,3>::m_pt1 - DeuxPoints<Int,3>::m_pt2)[2]);
		}

		Int surface() const {
			return 2 * (tx() * ty() + ty() * tz() + tz() * tx());
		}

		Int volume() const {
			return tx() * ty() * tz();
		}
};

} // math
