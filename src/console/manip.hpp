#pragma once

// Importations
#include <ostream>

#include "math/coord.hpp"

// Namespace
namespace console {

// -------------- BaseManip ------------
class BaseManip {
	public:
		// Destructeur
		virtual ~BaseManip() = default;

		// Méthodes
		virtual std::ostream& appliquer(std::ostream& stream) const = 0;
};

// ------------- ClearManip ------------
class ClearManip : public BaseManip {
	public:
		// Méthodes
		virtual std::ostream& appliquer(std::ostream& stream) const override;
};

// ------------- MouvManip -------------
class MouvManip : public BaseManip {
	private:
		// Attributs
		math::Vecteur<int,2> m_vecteur;

	public:
		// Constructeur
		MouvManip(math::Vecteur<int,2> const& v);
		MouvManip(int dx, int dy);

		// Opérateurs
		MouvManip  operator + () const;
		MouvManip  operator - () const;

		MouvManip  operator +  (math::Vecteur<int,2> const& v) const;
		MouvManip  operator -  (math::Vecteur<int,2> const& v) const;
		MouvManip& operator += (math::Vecteur<int,2> const& v);
		MouvManip& operator -= (math::Vecteur<int,2> const& v);

		MouvManip  operator +  (MouvManip const& mm) const;
		MouvManip  operator -  (MouvManip const& mm) const;
		MouvManip& operator += (MouvManip const& mm);
		MouvManip& operator -= (MouvManip const& mm);

		MouvManip  operator *  (int k) const;
		MouvManip  operator /  (int k) const;
		MouvManip& operator *= (int k);
		MouvManip& operator /= (int k);

		// Méthodes
		virtual std::ostream& appliquer(std::ostream& stream) const override;

		// - accesseurs
		math::Vecteur<int,2>& vecteur();
		math::Vecteur<int,2> const& vecteur() const;

		int& dx();
		int const& dx() const;

		int& dy();
		int const& dy() const;
};

// ------------- CoordManip ------------
class CoordManip : public BaseManip {
	private:
		// Attributs
		math::Point<size_t,2> m_point;

	public:
		// Constructeur
		CoordManip(math::Point<size_t,2> const& p);
		CoordManip(size_t x = 0, size_t y = 0);

		// Opérateurs
		CoordManip  operator +  () const;
		CoordManip  operator -  () const;
		CoordManip  operator +  (math::Vecteur<int,2> const& v) const;
		CoordManip  operator -  (math::Vecteur<int,2> const& v) const;
		CoordManip& operator += (math::Vecteur<int,2> const& v);
		CoordManip& operator -= (math::Vecteur<int,2> const& v);
		CoordManip  operator +  (MouvManip const& mm) const;
		CoordManip  operator -  (MouvManip const& mm) const;
		CoordManip& operator += (MouvManip const& mm);
		CoordManip& operator -= (MouvManip const& mm);

		// Méthodes
		virtual std::ostream& appliquer(std::ostream& stream) const override;

		// - accesseurs
		math::Point<size_t,2>& point();
		math::Point<size_t,2> const& point() const;

		size_t& x();
		size_t const& x() const;

		size_t& y();
		size_t const& y() const;
};

// ----------- EffLigneManip -----------
class EffLigneManip : public BaseManip {
	public:
		// Méthodes
		virtual std::ostream& appliquer(std::ostream& stream) const override;
};

// ------------ SauveManip -------------
class SauveManip : public BaseManip {
	public:
		// Méthodes
		virtual std::ostream& appliquer(std::ostream& stream) const override;
};

// ----------- RestoreManip ------------
class RestoreManip : public BaseManip {
	public:
		// Méthodes
		virtual std::ostream& appliquer(std::ostream& stream) const override;
};

// ------------- BuzzManip -------------
class BuzzManip : public BaseManip {
	public:
		// Méthodes
		virtual std::ostream& appliquer(std::ostream& stream) const override;
};

// Instances
namespace manip {
	// Basiques
	static ClearManip clear;         // Efface l'écran

	// Coords
	static CoordManip origine(0, 0); // Le point en haut à gauche
	inline CoordManip coord(int x, int y)     { return CoordManip(x, y); }
	inline CoordManip coord(math::Point<size_t,2> pt) { return CoordManip(pt);   }

	// Basiques
	static EffLigneManip eff_ligne;  // Efface la ligne
	static SauveManip    sauve;      // Sauvegarde la position du curseur
	static RestoreManip  restore;    // Restore la dernière position sauvegardée
	static BuzzManip     buzz;       // Fait buzzer l'ordi

	// Mouv
	static MouvManip dx(1, 0);       // Décalage du curseur
	static MouvManip dy(0, 1);
	inline MouvManip mouv(int dx, int dy)    { return MouvManip(dx, dy); }
	inline MouvManip mouv(math::Vecteur<int,2> v) { return MouvManip(v);      }
} // manip

} // console

// Opérateurs externes
std::ostream& operator << (std::ostream& stream, console::BaseManip const& manip);
console::MouvManip operator * (int const& k, console::MouvManip const& mm);
