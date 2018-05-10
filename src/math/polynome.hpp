#pragma once

// Importations
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <ostream>
#include <type_traits>

// Namespace
namespace math {

// Template
template<class Int, size_t DEG>
class Polynome {
	static_assert(DEG > 0, "Le degrés doit être non nul");

	public:
		// Alias
		using value_type      = Int;
		using reference       = Int&;
		using const_reference = Int const&;
		using pointer         = Int*;
		using const_pointer   = Int const*;
		using iterator        = typename std::array<Int,DEG+1>::iterator;
		using const_iterator  = typename std::array<Int,DEG+1>::const_iterator;
		using size_type       = size_t;
		using difference_type = std::ptrdiff_t;

		// Constructeur
		Polynome() {
			// Initialisation
			for (size_t i = 0; i <= DEG; ++i) {
				m_facteurs[i] = 0;
			}
		}

		Polynome(Polynome const& p) : m_facteurs(p.m_facteurs) {}
		Polynome(std::array<Int,DEG+1> const& facteurs) : m_facteurs(facteurs) {}

		template<size_t DEG2>
		Polynome(typename std::enable_if<DEG2 < DEG,Polynome<Int,DEG2> const&>::type p) {
			for (size_t i = 0; i <= DEG2; ++i) {
				m_facteurs[i] = p[i];
			}
		}

		template<size_t DEG2>
		Polynome(typename std::enable_if<DEG2 < DEG,std::array<Int,DEG2+1> const&>::type facteurs) {
			for (size_t i = 0; i <= DEG2; ++i) {
				m_facteurs[i] = facteurs[i];
			}
		}

		// Opérateurs
		// - cast
		explicit operator bool () const {
			for (size_t i = 0; i <= DEG; ++i) {
				if (m_facteurs[i] != 0) {
					return true;
				}
			}

			return false;
		}

		bool operator ! () const {
			for (size_t i = 0; i <= DEG; ++i) {
				if (m_facteurs[i] != 0) {
					return false;
				}
			}

			return true;
		}

		// - accesseurs
		Int& operator [] (size_t i) {
			return m_facteurs[i];
		}

		Int const& operator [] (size_t i) const {
			return m_facteurs[i];
		}

		// - comparaison
		bool operator == (Polynome const& p) const {
			return std::equal(begin(), end(), p.begin());
		}

		bool operator != (Polynome const& p) const {
			return !std::equal(begin(), end(), p.begin());
		}

		// - arithmétique
		Polynome operator - () const {
			Polynome r;

			for (size_t i = 0; i <= DEG; ++i) {
				r[i] = -m_facteurs[i];
			}

			return r;
		}

		Polynome& operator ++ () { ++m_facteurs[0]; return *this; }
		Polynome& operator -- () { --m_facteurs[0]; return *this; }

		Polynome operator ++ (int) const {
			Polynome tmp(*this);
			++m_facteurs[0];
			return tmp;
		}

		Polynome operator -- (int) const {
			Polynome tmp(*this);
			--m_facteurs[0];
			return tmp;
		}

		friend Polynome operator + (Polynome p, Int val) { p += val; return p; }
		friend Polynome operator - (Polynome p, Int val) { p -= val; return p; }
		friend Polynome operator * (Polynome p, Int val) { p *= val; return p; }
		friend Polynome operator / (Polynome p, Int val) { p /= val; return p; }

		// - assignation
		Polynome& operator += (Int val) {
			m_facteurs[0] += val;
			return *this;
		}

		Polynome& operator -= (Int val) {
			m_facteurs[0] -= val;
			return *this;
		}

		Polynome& operator *= (Int val) {
			for (size_t i = 0; i <= DEG; ++i) {
				m_facteurs[i] *= val;
			}

			return *this;
		}

		Polynome& operator /= (Int val) {
			for (size_t i = 0; i <= DEG; ++i) {
				m_facteurs[i] /= val;
			}

			return *this;
		}

		template<size_t DEG2>
		typename std::enable_if<DEG2 <= DEG,Polynome&>::type operator += (Polynome<Int,DEG2> const& p) {
			for (size_t i = 0; i <= DEG2; ++i) {
				m_facteurs[i] += p[i];
			}

			return *this;
		}

		template<size_t DEG2>
		typename std::enable_if<DEG2 <= DEG,Polynome&>::type operator -= (Polynome<Int,DEG2> const& p) {
			for (size_t i = 0; i <= DEG2; ++i) {
				m_facteurs[i] -= p[i];
			}

			return *this;
		}

		template<size_t DEG2>
		typename std::enable_if<DEG2 <= DEG,Polynome&>::type operator /= (Polynome<Int,DEG2> const& p);

		template<size_t DEG2>
		typename std::enable_if<DEG2 <= DEG,Polynome&>::type operator %= (Polynome<Int,DEG2> const& p);

		// Méthodes
		size_t degres() const {
			size_t deg = DEG;

			while (m_facteurs[deg] == 0) {
				--deg;
			}

			return deg;
		}

		size_type size() const {
			return DEG+1;
		}

		Int appliquer(Int val) const {
			Int r = m_facteur[0];

			for (size_t i = 1; i <= DEG; ++i) {
				r += m_facteurs[i] * std::pow(val, (Int) i);
			}

			return r;
		}

		// Itérateurs
		iterator begin() { return m_facteurs.begin(); }
		iterator end()   { return m_facteurs.end();   }

		const_iterator begin() const { return m_facteurs.cbegin(); }
		const_iterator end()   const { return m_facteurs.cend();   }

	private:
		// Attributs
		std::array<Int,DEG+1> m_facteurs;
};

// Opérations
template<size_t D, class Int, size_t DEG>
Polynome<Int,DEG+D> shift_right(Polynome<Int,DEG> const& p, size_t d) {
	assert(p.degres() + d <= DEG+D); //, "Valeur de d supérieure à celle annoncée");
	Polynome<Int,DEG+D> r;

	for (size_t i = 0; i <= DEG; ++i) {
		r[i+d] = p[i];
	}

	return r;
}

// Opérateurs
template<class Int, size_t DEG> template<size_t DEG2>
typename std::enable_if<DEG2 <= DEG,Polynome<Int,DEG>&>::type Polynome<Int,DEG>::operator /= (Polynome<Int,DEG2> const& p) {
	// Copie de this
	Polynome<Int,DEG> n(*this);

	// Mise à zéro
	for (size_t i = 0; i <= DEG; ++i) {
		m_facteurs[i] = 0;
	}

	// Calcul !
	while (n.degres() >= p.degres()) {
		// Décalage du diviseur
		size_t deg = n.degres();
		size_t decal = deg - p.degres();
		Polynome<Int,DEG> d = shift_right<DEG-DEG2>(p, decal);

		// Division
		m_facteurs[decal] = n[deg] / d[deg];
		d *= m_facteurs[decal];
		n -= d;
	}

	return *this;
}

template<class Int, size_t DEG> template<size_t DEG2>
typename std::enable_if<DEG2 <= DEG,Polynome<Int,DEG>&>::type Polynome<Int,DEG>::operator %= (Polynome<Int,DEG2> const& p) {
	// Calcul !
	while (degres() >= p.degres()) {
		// Décalage du diviseur
		size_t deg = degres();
		size_t decal = deg - p.degres();
		Polynome<Int,DEG> d = shift_right<DEG-DEG2>(p, decal);

		// Division
		d *= m_facteurs[deg] / d[deg];
		(*this) -= d;
	}

	return *this;
}

} // math

// Opérateurs externes
// - arithmétique
template<class Int, size_t D1, size_t D2>
typename std::enable_if<(D1 > D2),math::Polynome<Int,D1>>::type operator + (math::Polynome<Int,D1> const& p1, math::Polynome<Int,D2> const& p2) {
	math::Polynome<Int,D1> r(p1);
	r += p2;

	return r;
}

template<class Int, size_t D1, size_t D2>
typename std::enable_if<(D1 <= D2),math::Polynome<Int,D2>>::type operator + (math::Polynome<Int,D1> const& p1, math::Polynome<Int,D2> const& p2) {
	math::Polynome<Int,D2> r(p2);
	r += p1;

	return r;
}

template<class Int, size_t D1, size_t D2>
typename std::enable_if<(D1 > D2),math::Polynome<Int,D1>>::type operator - (math::Polynome<Int,D1> const& p1, math::Polynome<Int,D2> const& p2) {
	math::Polynome<Int,D1> r(p1);
	r -= p2;

	return r;
}

template<class Int, size_t D1, size_t D2>
typename std::enable_if<(D1 <= D2),math::Polynome<Int,D2>>::type operator - (math::Polynome<Int,D1> const& p1, math::Polynome<Int,D2> const& p2) {
	math::Polynome<Int,D2> r(p2);
	r -= p1;

	return r;
}

template<class Int, size_t D1, size_t D2>
math::Polynome<Int,D1+D2> operator * (math::Polynome<Int,D1> const& p1, math::Polynome<Int,D2> const& p2) {
	math::Polynome<Int,D1+D2> r;

	for (size_t i = 0; i <= D1; ++i) {
		for (size_t j = 0; j <= D2; ++j) {
			r[i+j] += p1[i] * p2[j];
		}
	}

	return r;
}

template<class Int, size_t D1, size_t D2>
typename std::enable_if<D2 < D1,math::Polynome<Int,D1-D2>>::type operator / (math::Polynome<Int,D1> n, math::Polynome<Int,D2> const& p) {
	// Initialisation quotient
	math::Polynome<Int,D1-D2> q;

	// Calcul !
	while (n.degres() >= p.degres()) {
		// Décalage du diviseur
		size_t deg = n.degres();
		size_t decal = deg - p.degres();
		math::Polynome<Int,D1> d = math::shift_right<D1-D2>(p, decal);

		// Division
		q[decal] = n[deg] / d[deg];
		d *= q[decal];
		n -= d;
	}

	return q;
}

template<class Int, size_t D1, size_t D2>
typename std::enable_if<D2 < D1,math::Polynome<Int,D1>>::type operator % (math::Polynome<Int,D1> n, math::Polynome<Int,D2> const& p) {
	// Calcul !
	while (n.degres() >= p.degres()) {
		// Décalage du diviseur
		size_t deg = n.degres();
		size_t decal = deg - p.degres();
		math::Polynome<Int,D1> d = math::shift_right<D1-D2>(p, decal);

		// Division
		d *= n[deg] / d[deg];
		n -= d;
	}

	return n;
}

// - affichage
template<class Int, size_t DEG>
std::ostream& operator << (std::ostream& stream, math::Polynome<Int,DEG> const& p) {
	// Cas du polynome nul
	if (!p) {
		return stream << "0";
	}

	// Affichage
	bool prev = false;

	for (size_t i = 0; i <= DEG; ++i) {
		Int fact = p[i];

		if (fact != 0) {
			// "plus"
			if (prev) {
				if (fact > 0) stream << "+";
			} else {
				prev = true;
			}

			// facteur
			if (fact != 1 || (fact == 1 && i == 0)) {
				stream << fact;
			}

			// "fois"
			if (fact != 1 && i > 0) {
				stream << "*";
			}

			// "variable"
			if (i > 0) {
				stream << "x";
			}

			// puissance
			if (i > 1) {
				stream << "^" << i;
			}
		}
	}

	return stream;
}
