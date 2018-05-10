#pragma once

// Importations
#include <limits>
#include <ostream>
#include <type_traits>

#include "infini.hpp"

// Classe
template<class Int, typename E = void>
class Nombre {
	private:
		// Attributs
		union {
			Int    m_val = 0;
			Infini m_inf;
		};

		bool m_est_inf = false;

	public:
		// Constructeur
		Nombre() {}
		Nombre(Int const& val)    { set(val); }
		Nombre(Infini const& inf) { set(inf); }

		// Opérateurs
		// - cast
		explicit operator bool () const {
			return m_est_inf ? (bool) m_inf : (bool) m_val;
		}

		bool operator ! () const {
			return m_est_inf ? !m_inf : !m_val;
		}

		explicit operator Int () const {
			return val();
		}

		// - comparaison
		friend bool operator < (Nombre const& nb1, Nombre const& nb2) {
			if (nb1.m_est_inf && nb2.m_est_inf) {
				return nb1.m_inf < nb2.m_inf;

			} else if (nb1.m_est_inf) {
				return nb1.m_inf.est_neg();

			} else if (nb2.m_est_inf) {
				return nb2.m_inf.est_pos();

			} else {
				return nb1.m_val < nb2.m_val;
			}
		}

		friend bool operator <= (Nombre const& nb1, Nombre const& nb2) {
			return !(nb1 > nb2);
		}

		friend bool operator == (Nombre const& nb1, Nombre const& nb2) {
			if (nb1.m_est_inf && nb2.m_est_inf) {
				return nb1.m_inf == nb2.m_inf;

			} else if (nb1.m_est_inf != nb2.m_est_inf) {
				return false;

			} else {
				return nb1.m_val == nb2.m_val;
			}
		}

		friend bool operator != (Nombre const& nb1, Nombre const& nb2) {
			return !(nb1 == nb2);
		}

		friend bool operator >= (Nombre const& nb1, Nombre const& nb2) {
			return !(nb1 < nb2);
		}

		friend bool operator > (Nombre const& nb1, Nombre const& nb2) {
			if (nb1.m_est_inf && nb2.m_est_inf) {
				return nb1.m_inf > nb2.m_inf;

			} else if (nb1.m_est_inf) {
				return nb1.m_inf.est_pos();

			} else if (nb2.m_est_inf) {
				return nb2.m_inf.est_neg();

			} else {
				return nb1.m_val > nb2.m_val;
			}
		}

		// - arithmétique
		Nombre& operator ++ () { if (!m_est_inf) ++m_val; return *this; }
		Nombre& operator -- () { if (!m_est_inf) --m_val; return *this; }

		Nombre operator ++ (int) const {
			Nombre tmp(*this);
			if (!m_est_inf) ++m_val;
			return tmp;
		}


		Nombre operator -- (int) const {
			Nombre tmp(*this);
			if (!m_est_inf) --m_val;
			return tmp;
		}

		Nombre operator - () const {
			return m_est_inf ? Nombre(-m_inf) : Nombre(-m_val);
		}

		friend Nombre operator + (Nombre nb1, Nombre const& nb2) { nb1 += nb2; return nb1; };
		friend Nombre operator - (Nombre nb1, Nombre const& nb2) { nb1 -= nb2; return nb1; };
		friend Nombre operator * (Nombre nb1, Nombre const& nb2) { nb1 *= nb2; return nb1; };
		friend Nombre operator / (Nombre nb1, Nombre const& nb2) { nb1 /= nb2; return nb1; };

		// - assignation
		Nombre& operator += (Nombre const& nb) {
			if (m_est_inf && nb.m_est_inf) {
				m_inf += nb.m_inf;

			} else if (m_est_inf) {
			} else if (nb.m_est_inf) {
				set(nb.m_inf);

			} else {
				m_val += nb.m_val;
			}

			return *this;
		}

		Nombre& operator -= (Nombre const& nb) {
			if (m_est_inf && nb.m_est_inf) {
				m_inf -= nb.m_inf;

			} else if (m_est_inf) {
			} else if (nb.m_est_inf) {
				set(-nb.m_inf);

			} else {
				m_val -= nb.m_val;
			}

			return *this;
		}

		Nombre& operator *= (Nombre const& nb) {
			if (m_est_inf && nb.m_est_inf) {
				m_inf *= nb.m_inf;

			} else if (m_est_inf) {
				if (nb.m_val < 0) m_inf = -m_inf;

			} else if (nb.m_est_inf) {
				set(m_val < 0 ? -nb.m_inf : nb.m_inf);

			} else {
				m_val *= nb.m_val;
			}

			return *this;
		}

		Nombre& operator /= (Nombre const& nb) {
			if (m_est_inf && nb.m_est_inf) {
				throw std::domain_error("cannot divide inf by inf");

			} else if (m_est_inf) {
				if (nb.m_val < 0) m_inf = -m_inf;
				else if (nb.m_val == 0) throw std::domain_error("cannot divide inf by 0");

			} else if (nb.m_est_inf) {
				set(0);

			} else {
				m_val /= nb.m_val;
			}

			return *this;
		}

		// - affichage
		friend std::ostream& operator << (std::ostream& stream, Nombre const& nb) {
			return nb.m_est_inf ? stream << nb.m_inf : stream << nb.m_val;
		}

		// Modateurs
		void set(Int const& val) {
			m_val = val;
			m_est_inf = false;
		}

		void set(Infini const& inf) {
			m_inf = std::numeric_limits<Int>::is_signed ? inf : INFINI;
			m_est_inf = true;
		}

		// Accesseur
		Int val() const {
			if (m_est_inf) {
				if (m_inf.est_pos()) {
					return std::numeric_limits<Int>::max();
				} else {
					return std::numeric_limits<Int>::min();
				}

			} else {
				return m_val;
			}
		}

		bool est_inf() const {
			return m_est_inf;
		}
};

template<class Int>
class Nombre<Int,typename std::enable_if<std::is_integral<Int>::value>::type> {
	private:
		// Attributs
		union {
			Int    m_val = 0;
			Infini m_inf;
		};

		bool m_est_inf = false;

	public:
		// Constructeur
		Nombre() {}
		Nombre(Int const& val)    { set(val); }
		Nombre(Infini const& inf) { set(inf); }

		// Opérateurs
		// - cast
		explicit operator bool () const {
			return m_est_inf ? (bool) m_inf : (bool) m_val;
		}

		bool operator ! () const {
			return m_est_inf ? !m_inf : !m_val;
		}

		explicit operator Int () const {
			return val();
		}

		// - comparaison
		friend bool operator < (Nombre const& nb1, Nombre const& nb2) {
			if (nb1.m_est_inf && nb2.m_est_inf) {
				return nb1.m_inf < nb2.m_inf;

			} else if (nb1.m_est_inf) {
				return nb1.m_inf.est_neg();

			} else if (nb2.m_est_inf) {
				return nb2.m_inf.est_pos();

			} else {
				return nb1.m_val < nb2.m_val;
			}
		}

		friend bool operator <= (Nombre const& nb1, Nombre const& nb2) {
			return !(nb1 > nb2);
		}

		friend bool operator == (Nombre const& nb1, Nombre const& nb2) {
			if (nb1.m_est_inf && nb2.m_est_inf) {
				return nb1.m_inf == nb2.m_inf;

			} else if (nb1.m_est_inf != nb2.m_est_inf) {
				return false;

			} else {
				return nb1.m_val == nb2.m_val;
			}
		}

		friend bool operator != (Nombre const& nb1, Nombre const& nb2) {
			return !(nb1 == nb2);
		}

		friend bool operator >= (Nombre const& nb1, Nombre const& nb2) {
			return !(nb1 < nb2);
		}

		friend bool operator > (Nombre const& nb1, Nombre const& nb2) {
			if (nb1.m_est_inf && nb2.m_est_inf) {
				return nb1.m_inf > nb2.m_inf;

			} else if (nb1.m_est_inf) {
				return nb1.m_inf.est_pos();

			} else if (nb2.m_est_inf) {
				return nb2.m_inf.est_neg();

			} else {
				return nb1.m_val > nb2.m_val;
			}
		}

		// - arithmétique
		Nombre& operator ++ () { if (!m_est_inf) ++m_val; return *this; }
		Nombre& operator -- () { if (!m_est_inf) --m_val; return *this; }

		Nombre operator ++ () const {
			Nombre tmp(*this);
			if (!m_est_inf) ++m_val;
			return tmp;
		}


		Nombre operator -- () const {
			Nombre tmp(*this);
			if (!m_est_inf) --m_val;
			return tmp;
		}

		Nombre operator - () const {
			return m_est_inf ? Nombre(-m_inf) : Nombre(-m_val);
		}

		Nombre operator ~ () const {
			return m_est_inf ? Nombre(0) : Nombre(~m_val);
		}

		friend Nombre operator + (Nombre nb1, Nombre const& nb2) { nb1 += nb2; return nb1; };
		friend Nombre operator - (Nombre nb1, Nombre const& nb2) { nb1 -= nb2; return nb1; };
		friend Nombre operator * (Nombre nb1, Nombre const& nb2) { nb1 *= nb2; return nb1; };
		friend Nombre operator / (Nombre nb1, Nombre const& nb2) { nb1 /= nb2; return nb1; };

		// - arithmétique binaire
		friend Nombre operator % (Nombre nb1, Nombre const& nb2) { nb1 %= nb2; return nb1; };
		friend Nombre operator & (Nombre nb1, Nombre const& nb2) { nb1 &= nb2; return nb1; };
		friend Nombre operator | (Nombre nb1, Nombre const& nb2) { nb1 |= nb2; return nb1; };
		friend Nombre operator ^ (Nombre nb1, Nombre const& nb2) { nb1 ^= nb2; return nb1; };
		friend Nombre operator << (Nombre nb1, Nombre const& nb2) { nb1 <<= nb2; return nb1; };
		friend Nombre operator >> (Nombre nb1, Nombre const& nb2) { nb1 >>= nb2; return nb1; };

		// - assignation
		Nombre& operator += (Nombre const& nb) {
			if (m_est_inf && nb.m_est_inf) {
				m_inf += nb.m_inf;

			} else if (m_est_inf) {
			} else if (nb.m_est_inf) {
				set(nb.m_inf);

			} else {
				m_val += nb.m_val;
			}

			return *this;
		}

		Nombre& operator -= (Nombre const& nb) {
			if (m_est_inf && nb.m_est_inf) {
				m_inf -= nb.m_inf;

			} else if (m_est_inf) {
			} else if (nb.m_est_inf) {
				set(-nb.m_inf);

			} else {
				m_val -= nb.m_val;
			}

			return *this;
		}

		Nombre& operator *= (Nombre const& nb) {
			if (m_est_inf && nb.m_est_inf) {
				m_inf *= nb.m_inf;

			} else if (m_est_inf) {
				if (nb.m_val < 0) m_inf = -m_inf;

			} else if (nb.m_est_inf) {
				set(m_val < 0 ? -nb.m_inf : nb.m_inf);

			} else {
				m_val *= nb.m_val;
			}

			return *this;
		}

		Nombre& operator /= (Nombre const& nb) {
			if (m_est_inf && nb.m_est_inf) {
				throw std::domain_error("cannot divide inf by inf");

			} else if (m_est_inf) {
				if (nb.m_val < 0) m_inf = -m_inf;
				else if (nb.m_val == 0) throw std::domain_error("cannot divide inf by 0");

			} else if (nb.m_est_inf) {
				set(0);

			} else {
				m_val /= nb.m_val;
			}

			return *this;
		}

		Nombre& operator %= (Nombre const& nb) {
			if (m_est_inf && nb.m_est_inf) {
				throw std::domain_error("cannot divide inf by inf");

			} else if (m_est_inf) {    // Division infinie
				if (nb.m_val > 0) set(0);
				else if (nb.m_val == 0) throw std::domain_error("cannot divide inf by 0");

			} else if (nb.m_est_inf) { // Division nulle

			} else {
				m_val %= nb.m_val;
			}

			return *this;
		};

		Nombre& operator &= (Nombre const& nb) {
			if (m_est_inf && nb.m_est_inf) {
			} else if (m_est_inf) {
				set(nb.m_val);

			} else if (nb.m_est_inf) {
			} else {
				m_val &= nb.m_val;
			}

			return *this;
		};

		Nombre& operator |= (Nombre const& nb) {
			if (m_est_inf && nb.m_est_inf) {
			} else if (m_est_inf) {
			} else if (nb.m_est_inf) {
				set(nb.m_inf);

			} else {
				m_val |= nb.m_val;
			}

			return *this;
		};

		Nombre& operator ^= (Nombre const& nb) {
			if (m_est_inf && nb.m_est_inf) {
				set(0);

			} else if (m_est_inf) {
				set(~nb.m_val);

			} else if (nb.m_est_inf) {
				m_val = ~m_val;

			} else {
				m_val ^= nb.m_val;
			}

			return *this;
		};

		Nombre& operator <<= (Nombre const& nb) {
			if (m_est_inf && nb.m_est_inf) {
				throw std::domain_error("cannot do inf << inf");

			} else if (m_est_inf) {
			} else if (nb.m_est_inf) {
				set(0);

			} else {
				m_val <<= nb.m_val;
			}

			return *this;
		};

		Nombre& operator >>= (Nombre const& nb) {
			if (m_est_inf && nb.m_est_inf) {
				throw std::domain_error("cannot do inf >> inf");

			} else if (m_est_inf) {
			} else if (nb.m_est_inf) {
				set(0);

			} else {
				m_val >>= nb.m_val;
			}

			return *this;
		};

		// - affichage
		friend std::ostream& operator << (std::ostream& stream, Nombre const& nb) {
			return nb.m_est_inf ? stream << nb.m_inf : stream << nb.m_val;
		}

		// Modateurs
		void set(Int const& val) {
			m_val = val;
			m_est_inf = false;
		}

		void set(Infini const& inf) {
			m_inf = std::numeric_limits<Int>::is_signed ? inf : INFINI;
			m_est_inf = true;
		}

		// Accesseur
		Int val() const {
			if (m_est_inf) {
				if (m_inf.est_pos()) {
					return std::numeric_limits<Int>::max();
				} else {
					return std::numeric_limits<Int>::min();
				}

			} else {
				return m_val;
			}
		}

		bool est_inf() const {
			return m_est_inf;
		}
};

namespace std {

// Numeric limits
template<class Int>
struct numeric_limits<Nombre<Int>> : numeric_limits<Int> {
	// Propriétés
	static constexpr bool is_specialized = true;

	static constexpr bool has_infinity = true;
	static constexpr Nombre<Int> infinity() { return Nombre<Int>(INFINI); }
};

// Type traits
template<class Int>
struct is_floating_point<Nombre<Int>> : is_floating_point<Int> {};

template<class Int>
struct is_integral<Nombre<Int>> : is_integral<Int> {};

template<class Int>
struct is_signed<Nombre<Int>> : is_signed<Int> {};

template<class Int>
struct is_unsigned<Nombre<Int>> : is_unsigned<Int> {};

} // std
