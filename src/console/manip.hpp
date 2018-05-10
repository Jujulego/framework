#pragma once

// Importations
#include <ostream>

#include "math/coord.hpp"

// -------------- BaseManip ------------
class BaseManip {
	public:
		// Destructeur
		virtual ~BaseManip() = default;

		// Méthodes
		virtual std::ostream& appliquer(std::ostream& stream) const = 0;
};

// Opérateur externe
std::ostream& operator << (std::ostream& stream, BaseManip const& manip);

// ------------- ClearManip ------------
class ClearManip : public BaseManip {
	public:
		// Méthodes
		virtual std::ostream& appliquer(std::ostream& stream) const override;
};

// ------------- CoordManip ------------
class CoordManip : public BaseManip {
	private:
		// Attributs
		math::Point<> m_point;

	public:
		// Constructeur
		CoordManip(math::Point<> const& p);
		CoordManip(int x = 0, int y = 0);

		// Opérateurs
		CoordManip  operator +  () const;
		CoordManip  operator -  () const;
		CoordManip  operator +  (math::Vecteur<> const& v) const;
		CoordManip  operator -  (math::Vecteur<> const& v) const;
		CoordManip& operator += (math::Vecteur<> const& v);
		CoordManip& operator -= (math::Vecteur<> const& v);

		// Méthodes
		virtual std::ostream& appliquer(std::ostream& stream) const override;

		// - accesseurs
		int& x();
		int const& x() const;

		int& y();
		int const& y() const;
};

// ------------- MouvManip -------------
class MouvManip : public BaseManip {
	private:
		// Attributs
		math::Vecteur<> m_vecteur;

	public:
		// Constructeur
		MouvManip(math::Vecteur<> const& v);
		MouvManip(int dx, int dy);

		// Opérateurs
		MouvManip  operator + () const;
		MouvManip  operator - () const;

		MouvManip  operator +  (math::Vecteur<> const& v) const;
		MouvManip  operator -  (math::Vecteur<> const& v) const;
		MouvManip& operator += (math::Vecteur<> const& v);
		MouvManip& operator -= (math::Vecteur<> const& v);

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
		int& dx();
		int const& dx() const;

		int& dy();
		int const& dy() const;
};

// Opérateur externe
MouvManip operator * (int const& k, MouvManip const& mm);

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
	static CoordManip x(1, 0);
	static CoordManip y(0, 1);
	inline CoordManip coord(int x, int y)     { return CoordManip(x, y); }
	inline CoordManip coord(math::Point<> pt) { return CoordManip(pt);   }

	// Basiques
	static EffLigneManip eff_ligne;  // Efface la ligne
	static SauveManip    sauve;      // Sauvegarde la position du curseur
	static RestoreManip  restore;    // Restore la dernière position sauvegardée
	static BuzzManip     buzz;       // Fait buzzer l'ordi

	// Mouv
	static MouvManip dx(1, 0);       // Décalage du curseur
	static MouvManip dy(0, 1);
	inline MouvManip mouv(int dx, int dy)    { return MouvManip(dx, dy); }
	inline MouvManip mouv(math::Vecteur<> v) { return MouvManip(v);      }
};
