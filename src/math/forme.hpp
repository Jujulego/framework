#pragma once

// Importations
#include <algorithm>
#include <cmath>

#include "constantes.hpp"
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

		// - accesseurs
		Vecteur<Int,DEG> vecteur() const {
			return m_pt2 - m_pt1;
		}

		Point<Int,DEG> const& pt1() const {
			return m_pt1;
		}

		Point<Int,DEG> const& pt2() const {
			return m_pt2;
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
			return std::abs(DeuxPoints<Int,2>::vecteur()[0]);
		}

		Int ty() const {
			return std::abs(DeuxPoints<Int,2>::vecteur()[1]);
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
			return std::abs(DeuxPoints<Int,3>::vecteur()[0]);
		}

		Int ty() const {
			return std::abs(DeuxPoints<Int,3>::vecteur()[1]);
		}

		Int tz() const {
			return std::abs(DeuxPoints<Int,3>::vecteur()[2]);
		}

		Int surface() const {
			return 2 * (tx() * ty() + ty() * tz() + tz() * tx());
		}

		Int volume() const {
			return tx() * ty() * tz();
		}
};

template<class Int, size_t DEG>
class PointRayon : public Forme<Int,DEG> {
	protected:
		// Attributs
		Point<Int,DEG> m_centre;
		Int m_rayon;

	public:
		// Constructeur
		PointRayon(Int const& rayon) : m_rayon(rayon) {}
		PointRayon(Point<Int,DEG> const& centre, Int const& rayon) : m_centre(m_centre), m_rayon(rayon) {}

		// Méthodes
		virtual bool contient(Point<Int,DEG> const& pt) const override {
			auto v = pt - centre;
			Int somme = 0;

			for (size_t i = 0; i < DEG; ++i) {
				somme += v[i] * v[i];
			}

			return somme <= (rayon * rayon);
		}

		// - accesseurs
		Point<Int,DEG> const& centre() const {
			return m_centre;
		}

		Int const& rayon() const {
			return m_rayon;
		}
};

template<class Int>
class Disque : public PointRayon<Int,2> {
	public:
		// Constructeur
		Disque(Int const& rayon) : PointRayon<Int,2>(rayon) {}
		Disque(Point<Int,2> const& centre, Int const& rayon) : PointRayon<Int,2>(centre, rayon) {}

		// Méthodes
		auto perimetre() const {
			return 2 * PI * PointRayon<Int,2>::m_rayon;
		}

		auto aire() const {
			return PI * PointRayon<Int,2>::m_rayon * PointRayon<Int,2>::m_rayon;
		}
};

template<class Int>
class Cercle : public Disque<Int> {
	public:
		// Constructeur
		Cercle(Int const& rayon) : Disque<Int>(rayon) {}
		Cercle(Point<Int,2> const& centre, Int const& rayon) : Disque<Int>(centre, rayon) {}

		// Méthodes
		virtual bool contient(Point<Int,2> const& pt) const override {
			auto v = pt - Disque<Int>::m_centre;
			return (v[0] * v[0] + v[1] * v[1]) == (Disque<Int>::m_rayon * Disque<Int>::m_rayon);
		}
};

template<class Int>
class Boule : public PointRayon<Int,3> {
	public:
		// Constructeur
		Boule(Int const& rayon) : PointRayon<Int,3>(rayon) {}
		Boule(Point<Int,3> const& centre, Int const& rayon) : PointRayon<Int,3>(centre, rayon) {}

		// Méthodes
		auto surface() const {
			return 4 * PI * PointRayon<Int,3>::m_rayon * PointRayon<Int,3>::m_rayon;
		}

		auto volume() const {
			return 4/3 * PI * PointRayon<Int,3>::m_rayon * PointRayon<Int,3>::m_rayon * PointRayon<Int,3>::m_rayon;
		}
};

template<class Int>
class Sphere : public Boule<Int> {
	public:
		// Constructeur
		Sphere(Int const& rayon) : Boule<Int>(rayon) {}
		Sphere(Point<Int,3> const& centre, Int const& rayon) : Boule<Int>(centre, rayon) {}

		// Méthodes
		virtual bool contient(Point<Int,3> const& pt) const override {
			auto v = pt - Boule<Int>::m_centre;
			return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]) == (Boule<Int>::m_rayon * Boule<Int>::m_rayon);
		}
};

} // math
