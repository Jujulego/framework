#pragma once

// Importations
#include <algorithm>
#include <array>
#include <cstddef>
#include <functional>
#include <ostream>

#include "nombre.hpp"

// Namespace
namespace math {

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
		Coord() {
			for (size_t i = 0; i < DEG; ++i) {
				m_coords[i] = 0;
			}
		}

		Coord(Coord const& c) : m_coords(c.m_coords) {}
		Coord(std::array<Int,DEG> const& coords) : m_coords(coords) {}

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
		Coord operator + () const {
			Coord r;

			for (size_t i = 0; i < DEG; ++i) {
				r[i] = +m_coords[i];
			}

			return r;
		}

		Coord operator - () const {
			Coord r;

			for (size_t i = 0; i < DEG; ++i) {
				r[i] = -m_coords[i];
			}

			return r;
		}

		template<class I>
		Coord& operator += (Coord<I,DEG,0> const& v) {
			for (size_t i = 0; i < DEG; ++i) {
				m_coords[i] += v[i];
			}

			return *this;
		}

		template<class I>
		Coord& operator -= (Coord<I,DEG,0> const& v) {
			for (size_t i = 0; i < DEG; ++i) {
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
			for (size_t i = 0; i < DEG; ++i) {
				if (m_coords[i] != c[i]) return false;
			}

			return true;
		}

		bool operator != (Coord const& c) const {
			for (size_t i = 0; i < DEG; ++i) {
				if (m_coords[i] == c[i]) return false;
			}

			return true;
		}

		// - arithmétique
		Coord operator + () const {
			Coord r;

			for (size_t i = 0; i < DEG; ++i) {
				r[i] = +m_coords[i];
			}

			return r;
		}

		Coord operator - () const {
			Coord r;

			for (size_t i = 0; i < DEG; ++i) {
				r[i] = -m_coords[i];
			}

			return r;
		}

		template<class I>
		Coord& operator += (Coord<I,DEG,0> const& v) {
			for (size_t i = 0; i < DEG; ++i) {
				m_coords[i] += v[i];
			}

			return *this;
		}

		template<class I>
		Coord& operator -= (Coord<I,DEG,0> const& v) {
			for (size_t i = 0; i < DEG; ++i) {
				m_coords[i] -= v[i];
			}

			return *this;
		}

		template<class I>
		Coord& operator *= (I const& v) {
			for (size_t i = 0; i < DEG; ++i) {
				m_coords[i] *= v;
			}

			return *this;
		}

		template<class I>
		Coord& operator /= (I const& v) {
			for (size_t i = 0; i < DEG; ++i) {
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

} // math

// Opérateurs externes
// - arithmétique
template<class I1, class I2, size_t DEG, size_t PT1, size_t PT2>
math::Coord<I1,DEG,PT1+PT2> operator + (math::Coord<I1,DEG,PT1> const& c1, math::Coord<I2,DEG,PT2> const& c2) {
	static_assert(PT1 + PT2 < 2, "Impossible d'ajouter un point à un point");
	math::Coord<I1,DEG,PT1+PT2> r;

	for (size_t i = 0; i < DEG; ++i) {
		r[i] = c1[i] + c2[i];
	}

	return r;
}

template<class I1, class I2, size_t DEG, size_t PT1, size_t PT2>
math::Coord<I1,DEG,PT1-PT2> operator - (math::Coord<I1,DEG,PT1> const& c1, math::Coord<I2,DEG,PT2> const& c2) {
	static_assert(PT2 <= PT1, "Impossible de soustraire un point à un vecteur");
	math::Coord<I1,DEG,PT1-PT2> r;

	for (size_t i = 0; i < DEG; ++i) {
		r[i] = c1[i] - c2[i];
	}

	return r;
}

template<class Int, class I, size_t DEG>
math::Coord<Int,DEG,0> operator * (I const& v, math::Coord<Int,DEG,0> c) {
	c *= v;
	return c;
}

template<class Int, class I, size_t DEG>
math::Coord<Int,DEG,0> operator * (math::Coord<Int,DEG,0> c, I const& v) {
	c *= v;
	return c;
}

template<class Int, class I, size_t DEG>
math::Coord<Int,DEG,0> operator / (math::Coord<Int,DEG,0> c, I const& v) {
	c /= v;
	return c;
}

// - affichage
template<class Int, size_t DEG, size_t PT>
std::ostream& operator << (std::ostream& stream, math::Coord<Int,DEG,PT> const& c) {
	stream << "(";

	for (size_t i = 0; i < DEG; ++i) {
		stream << c[i];
		if (i != DEG - 1) stream << ", ";
	}

	return stream << ")";
}

namespace math {

// Alias
// - point
template<class Int, size_t DEG>
using Point = Coord<Int,DEG,1>;

// - vecteur
template<class Int, size_t DEG>
using Vecteur = Coord<Int,DEG,0>;

} // math

namespace std {

// Hash & Less
template<class Int, size_t DEG, size_t PT>
class hash<math::Coord<Int,DEG,PT>> {
	public:
		// Constructeur
		hash(size_t fact) : m_fact(fact) {
			m_mins.fill(0);
		}

		hash(size_t fact, array<size_t,DEG> const& mins) : m_fact(fact), m_mins(mins) {};

		// Opérateur d'appel
		size_t operator () (math::Coord<Int,DEG,PT> const& c) const {
			size_t h = c[0] + m_mins[0];

			for (size_t i = 0; i < DEG-1; ++i) {
				h *= m_fact;
				h += c[i+1] + m_mins[i+1];
			}

			return h;
		}

		// Accesseurs
		size_t const& fact() const {
			return m_fact;
		}

		size_t const& mins(size_t const& i) const {
			return m_mins[i];
		}

	private:
		// Attributs
		size_t m_fact;
		array<size_t,DEG> m_mins;
};

template<class Int, size_t DEG, size_t PT>
class hash<math::Coord<math::Nombre<Int>,DEG,PT>> {
	public:
		// Constructeur
		hash(size_t fact) : m_fact(fact) {
			m_mins.fill(0);
		}

		hash(size_t fact, array<size_t,DEG> const& mins) : m_fact(fact), m_mins(mins) {};

		// Opérateur d'appel
		size_t operator () (math::Coord<math::Nombre<Int>,DEG,PT> const& c) const {
			size_t h = c[0].val() + m_mins[0];

			for (size_t i = 1; i < DEG; ++i) {
				h *= m_fact;
				h += c[i].val() + m_mins[i];
			}

			return h;
		}

		// Accesseurs
		size_t const& fact() const {
			return m_fact;
		}

		size_t const& mins(size_t const& i) const {
			return m_mins[i];
		}

	private:
		// Attributs
		size_t m_fact;
		array<size_t,DEG> m_mins;
};

template<class Int, size_t DEG, size_t PT>
struct less<math::Coord<Int,DEG,PT>> { // Ordre arbitraire
	// Opérateur d'appel
	bool operator () (math::Coord<Int,DEG,PT> const& c1, math::Coord<Int,DEG,PT> const& c2) const {
		for (size_t i = 0; i < DEG; ++i) {
			if (c1[i] < c2[i]) return true;
			if (c1[i] > c2[i]) return false;
		}

		return false;
	}
};

}

namespace math {

// unhash
template<class Int, size_t DEG, size_t PT>
Coord<Int,DEG,PT> unhash(std::hash<Coord<Int,DEG,PT>> const& hash, size_t h) {
	static_assert(std::is_integral<Int>::value, "unhash defini seulement pour les entiers");
	Coord<Int,DEG,PT> r;

	for (size_t i = DEG -2; i+1 > 0; --i) {
		r[i+1] = (h % hash.fact()) - hash.mins(i+1);
		h /= hash.fact();
	}

	r[0] = h - hash.mins(0);

	return r;
}

} // math
