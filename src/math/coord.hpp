#pragma once

// Importations
#include <algorithm>
#include <array>
#include <cstddef>
#include <functional>
#include <ostream>

#include "nombre.hpp"

// Classe
template<class Int, size_t DEG, size_t PT>
class Coord {
	static_assert(PT < 2, "Vecteur (PT = 0) ou Point (PT = 1)");

	public:
		// Alias
		using value_type      = Int;
		using reference       = Int&;
		using const_reference = Int const&;
		using pointer         = Int*;
		using const_pointer   = Int const*;
		using iterator        = typename std::array<Int,DEG>::iterator;
		using const_iterator  = typename std::array<Int,DEG>::const_iterator;
		using size_type       = size_t;
		using difference_type = std::ptrdiff_t;

		// Constructeur
		Coord() = default;
		Coord(Coord const& c) : m_coords(c.m_coords) {};
		Coord(std::array<Int,DEG> const& coords) : m_coords(coords) {};

		// Opérateurs
		// - cast
		explicit operator bool () const {
			for (size_t i = 0; i < DEG; ++i) {
				if (m_coords[i] != 0) {
					return true;
				}
			}

			return false;
		}

		bool operator ! () const {
			for (size_t i = 0; i < DEG; ++i) {
				if (m_coords[i] != 0) {
					return false;
				}
			}

			return true;
		}

		// - accesseurs
		Int& operator [] (size_t i) {
			return m_coords[i];
		}

		Int const& operator [] (size_t i) const {
			return m_coords[i];
		}

		// - comparaison
		bool operator == (Coord const& c) const {
			return std::equal(begin(), end(), c.begin());
		}

		bool operator != (Coord const& c) const {
			return !std::equal(begin(), end(), c.begin());
		}

		// - arithmétique
		Coord operator - () const {
			Coord r;

			for (int i = 0; i < DEG; ++i) {
				r[i] = -m_coords[i];
			}

			return 0;
		}

		Coord& operator += (Coord<Int,DEG,0> const& v) {
			for (int i = 0; i < DEG; ++i) {
				m_coords[i] += v[i];
			}

			return *this;
		}

		Coord& operator -= (Coord<Int,DEG,0> const& v) {
			for (int i = 0; i < DEG; ++i) {
				m_coords[i] -= v[i];
			}

			return *this;
		}

		// Méthodes
		size_type size() const {
			return DEG;
		}

		// Itérateurs
		iterator begin() { return m_coords.begin(); }
		iterator end()   { return m_coords.end();   }

		const_iterator begin() const { return m_coords.cbegin(); }
		const_iterator end()   const { return m_coords.cend();   }

	private:
		// Attributs
		std::array<Int,DEG> m_coords;
};

template<class Int, size_t DEG>
class Coord<Int,DEG,0> {
	public:
		// Alias
		using value_type      = Int;
		using reference       = Int&;
		using const_reference = Int const&;
		using pointer         = Int*;
		using const_pointer   = Int const*;
		using iterator        = typename std::array<Int,DEG>::iterator;
		using const_iterator  = typename std::array<Int,DEG>::const_iterator;
		using size_type       = size_t;
		using difference_type = std::ptrdiff_t;

		// Constructeur
		Coord() = default;
		Coord(Coord const& c) : m_coords(c.m_coords) {};
		Coord(std::array<Int,DEG> const& coords) : m_coords(coords) {};

		template<class... I>
		Coord(I const&... coords) : m_coords({coords...}) {};

		// Opérateurs
		// - accesseurs
		Int& operator [] (size_t i) {
			return m_coords[i];
		}

		Int const& operator [] (size_t i) const {
			return m_coords[i];
		}

		// - comparaison
		bool operator == (Coord const& c) const {
			for (int i = 0; i < DEG; ++i) {
				if (m_coords[i] != c[i]) return false;
			}

			return true;
		}

		bool operator != (Coord const& c) const {
			for (int i = 0; i < DEG; ++i) {
				if (m_coords[i] == c[i]) return false;
			}

			return true;
		}

		// - arithmétique
		Coord operator - () const {
			Coord r;

			for (int i = 0; i < DEG; ++i) {
				r[i] = -m_coords[i];
			}

			return 0;
		}

		Coord& operator += (Coord<Int,DEG,0> const& v) {
			for (int i = 0; i < DEG; ++i) {
				m_coords[i] += v[i];
			}

			return *this;
		}

		Coord& operator -= (Coord<Int,DEG,0> const& v) {
			for (int i = 0; i < DEG; ++i) {
				m_coords[i] -= v[i];
			}

			return *this;
		}

		Coord& operator *= (Int const& v) {
			for (int i = 0; i < DEG; ++i) {
				m_coords[i] *= v;
			}

			return *this;
		}

		Coord& operator /= (Int const& v) {
			for (int i = 0; i < DEG; ++i) {
				m_coords[i] /= v;
			}

			return *this;
		}

		// Méthodes
		size_type size() const {
			return DEG;
		}

		// Itérateurs
		iterator begin() { return m_coords.begin(); }
		iterator end()   { return m_coords.end();   }

		const_iterator begin() const { return m_coords.cbegin(); }
		const_iterator end()   const { return m_coords.cend();   }

	private:
		// Attributs
		std::array<Int,DEG> m_coords;
};

// Opérateurs externes
// - arithmétique
template<class Int, size_t DEG, size_t PT1, size_t PT2>
Coord<Int,DEG,PT1+PT2> operator + (Coord<Int,DEG,PT1> const& c1, Coord<Int,DEG,PT2> const& c2) {
	static_assert(PT1 + PT2, "Impossible d'ajouter un point à un point");
	Coord<Int,DEG,PT1+PT2> r;

	for (size_t i = 0; i < DEG; ++i) {
		r[i] = c1[i] + c2[i];
	}

	return r;
}

template<class Int, size_t DEG, size_t PT1, size_t PT2>
Coord<Int,DEG,PT1-PT2> operator - (Coord<Int,DEG,PT1> const& c1, Coord<Int,DEG,PT2> const& c2) {
	static_assert(PT2 <= PT1, "Impossible de soustraire un point à un vecteur");
	Coord<Int,DEG,PT1-PT2> r;

	for (size_t i = 0; i < DEG; ++i) {
		r[i] = c1[i] - c2[i];
	}

	return r;
}

template<class Int, size_t DEG>
Coord<Int,DEG,0> operator * (Int const& v, Coord<Int,DEG,0> c) {
	c *= v;
	return c;
}

template<class Int, size_t DEG>
Coord<Int,DEG,0> operator * (Coord<Int,DEG,0> c, Int const& v) {
	c *= v;
	return c;
}

template<class Int, size_t DEG>
Coord<Int,DEG,0> operator / (Coord<Int,DEG,0> c, Int const& v) {
	c /= v;
	return c;
}

// - affichage
template<class Int, size_t DEG, size_t PT>
std::ostream& operator << (std::ostream& stream, Coord<Int,DEG,PT> const& c) {
	stream << "(";

	for (size_t i = 0; i < DEG; ++i) {
		stream << c[i];
		if (i != DEG - 1) stream << ", ";
	}

	return stream << ")";
}

// Alias
template<class Int, size_t DEG = 2>
using Point = Coord<Int,DEG,1>;

template<class Int, size_t DEG = 2>
using Vecteur = Coord<Int,DEG,0>;


namespace std {

// Hash & Less
template<class Int, size_t DEG, size_t PT>
class hash<Coord<Int,DEG,PT>> {
	public:
		// Constructeur
		hash(array<size_t,DEG-1> const& fact) : m_fact(fact) {
			m_mins.fill(0);
		}

		hash(array<size_t,DEG-1> const& fact, array<size_t,DEG> const& mins) : m_fact(fact), m_mins(mins) {};

		// Opérateur d'appel
		size_t operator () (Coord<Int,DEG,PT> const& c) const {
			size_t h = c[0] + m_mins[0];

			for (size_t i = 0; i < DEG-1; ++i) {
				h *= m_fact[i];
				h += c[i+1] + m_mins[i+1];
			}

			return h;
		}

		// Accesseurs
		size_t const& fact(size_t const& i) const {
			return m_fact[i];
		}

		size_t const& mins(size_t const& i) const {
			return m_mins[i];
		}

	private:
		// Attributs
		array<size_t,DEG-1> m_fact;
		array<size_t,DEG>   m_mins;
};

template<class Int, size_t DEG, size_t PT>
class hash<Coord<Nombre<Int>,DEG,PT>> {
	public:
		// Constructeur
		hash(array<size_t,DEG-1> const& fact) : m_fact(fact) {
			m_mins.fill(0);
		}

		hash(array<size_t,DEG-1> const& fact, array<size_t,DEG> const& mins) : m_fact(fact), m_mins(mins) {};

		// Opérateur d'appel
		size_t operator () (Coord<Nombre<Int>,DEG,PT> const& c) const {
			size_t h = c[0].val() + m_mins[0];

			for (size_t i = 0; i < DEG-1; ++i) {
				h *= m_fact[i];
				h += c[i+1].val() + m_mins[i+1];
			}

			return h;
		}

		// Accesseurs
		size_t const& fact(size_t const& i) const {
			return m_fact[i];
		}

		size_t const& mins(size_t const& i) const {
			return m_mins[i];
		}

	private:
		// Attributs
		array<size_t,DEG-1> m_fact;
		array<size_t,DEG>   m_mins;
};

template<class Int, size_t DEG, size_t PT>
struct less<Coord<Int,DEG,PT>> { // Ordre arbitraire
	// Opérateur d'appel
	bool operator () (Coord<Int,DEG,PT> const& c1, Coord<Int,DEG,PT> const& c2) const {
		for (size_t i = 0; i < DEG; ++i) {
			if (c1[i] < c2[i]) return true;
			if (c1[i] > c2[i]) return false;
		}

		return false;
	}
};

}

// unhash
template<class Int, size_t DEG, size_t PT>
Coord<Int,DEG,PT> unhash(std::hash<Coord<Int,DEG,PT>> const& hash, size_t h) {
	static_assert(std::is_integral<Int>::value, "unhash defini seulement pour les entiers");
	Coord<Int,DEG,PT> r;

	for (size_t i = DEG -2; i >= 0; --i) {
		r[i+1] = (h % hash.fact(i)) - hash.mins(i+1);
		h /= hash.fact(i);
	}

	r[0] = h - hash.mins(0);

	return r;
}
