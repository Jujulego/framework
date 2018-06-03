#pragma once

// Imporations
#include <array>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <vector>

#include "coord.hpp"
#include "meta.hpp"

// Namespace
namespace math {

// Classe
template<class Int, size_t LIG, size_t COL = LIG> // Matrice carrée par défaut
class Matrice {                                   // Matrice<Int,0,0> => matrice dynamique (vecteur) taille déterminée à l'execution
	static_assert(LIG > 0, "Doit avoir un nombre non nul de lignes");
	static_assert(COL > 0, "Doit avoir un nombre non nul de colonnes");
	/**
	 * Décrit une matrice à allocation fixe
	 */

	public:
		// Alias
		using value_type      = Int;
		using reference       = Int&;
		using const_reference = Int const&;
		using pointer         = Int*;
		using const_pointer   = Int const*;
		using iterator        = typename std::array<Int, LIG * COL>::iterator;
		using const_iterator  = typename std::array<Int, LIG * COL>::const_iterator;
		using size_type       = size_t;
		using difference_type = ptrdiff_t;

		// Sous-classes
		class column_iterator {
			/**
			 * Permet d'iterer les valeurs par colones
			 */

			public:
				// Alias
				using value_type        = Matrice::value_type;
				using reference         = Matrice::reference;
				using difference_type   = Matrice::difference_type;
				using iterator_category = std::random_access_iterator_tag;

				// Constructeurs
				column_iterator() = default;
				column_iterator(iterator const& it) : m_it(it) {};

				// Opérateurs
				// - déférenciation
				reference operator *  () const { return *m_it; }
				pointer   operator -> () const { return m_it.operator ->(); }
				reference operator [] (Matrice::size_type v) const { return m_it[v]; }

				// - comparaison
				bool operator <  (column_iterator const& cit) const { return m_it <  cit.m_it; };
				bool operator <= (column_iterator const& cit) const { return m_it <= cit.m_it; };
				bool operator == (column_iterator const& cit) const { return m_it == cit.m_it; };
				bool operator != (column_iterator const& cit) const { return m_it != cit.m_it; };
				bool operator >= (column_iterator const& cit) const { return m_it >= cit.m_it; };
				bool operator >  (column_iterator const& cit) const { return m_it >  cit.m_it; };

				// - incrémentation & décrémentation
				column_iterator& operator ++ () { m_it += COL; return *this; }
				column_iterator& operator -- () { m_it -= COL; return *this; }

				column_iterator operator ++ (int) {
					column_iterator tmp(*this);
					++(*this);
					return tmp;
				}

				column_iterator operator -- (int) {
					column_iterator tmp(*this);
					--(*this);
					return tmp;
				}

				// - assignation
				column_iterator& operator += (Matrice::size_type v) { m_it += v * COL; return *this; }
				column_iterator& operator -= (Matrice::size_type v) { m_it -= v * COL; return *this; }

				// - arithmétique
				column_iterator operator + (Matrice::size_type v) const { column_iterator r(*this); r += v; return r; };
				column_iterator operator - (Matrice::size_type v) const { column_iterator r(*this); r -= v; return r; };

				friend column_iterator operator + (Matrice::size_type v, column_iterator const& it) {
					column_iterator r(it);
					r += v;
					return r;
				};

				difference_type operator - (column_iterator cit) const {
					return (m_it - cit.m_it) / COL;
				};

			private:
				// Attributs
				iterator m_it;
		};

		class const_column_iterator {
			/**
			 * Version de column_iterator renvoyant des reférences constantes
			 */

			public:
				// Alias
				using value_type        = Matrice::value_type;
				using reference         = Matrice::const_reference;
				using difference_type   = Matrice::difference_type;
				using iterator_category = std::random_access_iterator_tag;

				// Constructeurs
				const_column_iterator() = default;
				const_column_iterator(const_iterator const& it) : m_it(it) {};
				const_column_iterator(column_iterator const& cit) : m_it(cit.m_it) {};

				// Opérateurs
				// - déférenciation
				reference operator *  () const { return *m_it; }
				pointer   operator -> () const { return m_it.operator ->(); }
				reference operator [] (Matrice::size_type v) const { return m_it[v]; }

				// - comparaison
				bool operator <  (const_column_iterator const& cit) const { return m_it <  cit.m_it; };
				bool operator <= (const_column_iterator const& cit) const { return m_it <= cit.m_it; };
				bool operator == (const_column_iterator const& cit) const { return m_it == cit.m_it; };
				bool operator != (const_column_iterator const& cit) const { return m_it != cit.m_it; };
				bool operator >= (const_column_iterator const& cit) const { return m_it >= cit.m_it; };
				bool operator >  (const_column_iterator const& cit) const { return m_it >  cit.m_it; };

				// - incrémentation & décrémentation
				const_column_iterator& operator ++ () { m_it += COL; return *this; }
				const_column_iterator& operator -- () { m_it -= COL; return *this; }

				const_column_iterator operator ++ (int) {
					const_column_iterator tmp(*this);
					++(*this);
					return tmp;
				}

				const_column_iterator operator -- (int) {
					const_column_iterator tmp(*this);
					--(*this);
					return tmp;
				}

				// - assignation
				const_column_iterator& operator += (Matrice::size_type v) { m_it += v * COL; return *this; }
				const_column_iterator& operator -= (Matrice::size_type v) { m_it -= v * COL; return *this; }

				// - arithmétique
				const_column_iterator operator + (Matrice::size_type v) const { const_column_iterator r(*this); r += v; return r; };
				const_column_iterator operator - (Matrice::size_type v) const { const_column_iterator r(*this); r -= v; return r; };

				friend const_column_iterator operator + (Matrice::size_type v, const_column_iterator const& it) {
					const_column_iterator r(it);
					r += v;
					return r;
				};

				difference_type operator - (const_column_iterator cit) const {
					return (m_it - cit.m_it) / COL;
				};

			private:
				// Attributs
				const_iterator m_it;
		};

		template<class It, class CIt, size_t N>
		class part {
			/**
			 * Permet de représenté une ligne / une colonne de la matrice
			 * It  : type d'itérateur
			 * CIt : type d'itérateur à références constantes
			 * N   : taille de la ligne/colonne
			 */

			public:
				// Alias
				using value_type       = Matrice::value_type;
				using reference        = Matrice::reference;
				using const_reference  = Matrice::const_reference;
				using iterator         = It;
				using const_iterator   = CIt;
				using size_type        = Matrice::size_type;
				using difference_type  = Matrice::difference_type;

				// Constructeur
				part(It const& deb) : m_deb(deb) {};

				// Opérateurs
				// - accès éléments
				reference operator [] (size_type const& i) {
					return *(m_deb + i);
				}

				const_reference operator [] (size_type const& i) const {
					return *(const_iterator(m_deb) + i);
				}

				// Méthodes
				size_type size() const {
					return N;
				}

				void fill(Int const& v) {
					for (int i = 0; i < size(); ++i) (*this)[i] = v;
				}

				// Itérateurs
				iterator begin() { return m_deb; }
				iterator end()   { return m_deb + N; }

				const_iterator begin() const { return const_iterator(m_deb); }
				const_iterator end()   const { return const_iterator(m_deb + N); }

			private:
				// Attributs
				It m_deb;
		};

		template<class CIt, size_t N>
		class const_part {
			/**
			 * Version de part à références constantes uniquement
			 * CIt : type d'itérateur à références constantes
			 * N   : taille de la ligne/colonne
			 */

			public:
				// Alias
				using value_type       = Matrice::value_type;
				using const_reference  = Matrice::const_reference;
				using const_iterator   = CIt;
				using size_type        = Matrice::size_type;
				using difference_type  = Matrice::difference_type;

				// Constructeurs
				template<class It>
				const_part(part<It,CIt,N> const& p) : m_deb(p.m_deb) {};
				const_part(CIt const& deb) : m_deb(deb) {};

				// Opérateurs
				// - accès éléments
				const_reference operator [] (size_type const& c) const {
					return *(m_deb + c);
				}

				// Méthodes
				size_type size() const {
					return N;
				}

				// Itérateurs
				const_iterator begin() const { return m_deb; }
				const_iterator end()   const { return m_deb + N; }

			private:
				// Attributs
				CIt m_deb;
		};

		// Constructeur
		Matrice() : hash(meta::max<meta::size_<LIG>,meta::size_<COL>>::type::value) {
			for (unsigned i = 0; i < LIG*COL; ++i) {
				m_matrice[i] = 0;
			}
		}
		Matrice(std::array<Int,LIG * COL> const& matrice) : hash(meta::max<meta::size_<LIG>,meta::size_<COL>>::type::value), m_matrice(matrice) {}

		// Opérateurs
		// - accès élément
		reference operator [] (Point<unsigned,2> const& c) { // (lig, col)
			return m_matrice[hash(c)];
		}

		const_reference operator [] (Point<unsigned,2> const& c) const { // (lig, col)
			return m_matrice[hash(c)];
		}

		// - arithmétique
		Matrice operator - () const {
			Matrice r;

			for (int i = 0; i < size(); ++i) {
				r.m_matrice[i] = -m_matrice[i];
			}

			return r;
		}

		Matrice operator + (Matrice m) const { m += (*this); return m; }
		Matrice operator - (Matrice m) const { m -= (*this); return m; }

		Matrice operator + (Matrice<Int,0,0> const& m) const { Matrice r(*this); r += m; return r; }
		Matrice operator - (Matrice<Int,0,0> const& m) const { Matrice r(*this); r -= m; return r; }

		Matrice operator / (Int const& lambda) const { Matrice r(*this); r /= lambda; return r; }
		Matrice operator * (Int const& lambda) const { Matrice r(*this); r *= lambda; return r; }
		friend Matrice operator * (Int const& lambda, Matrice m) { m *= lambda; return m; }

		// - assignation
		Matrice& operator += (Matrice const& m) {
			for (int i = 0; i < size(); ++i) {
				m_matrice[i] += m.m_matrice[i];
			}

			return *this;
		}

		Matrice& operator += (Matrice<Int,0,0> const& m) {
			if (nb_lig() != m.nb_lig() || nb_col() != m.nb_col()) throw std::domain_error("Impossible d'ajouter 2 matrices de tailles différentes");

			for (int l = 0; l < LIG; ++l) {
				for (int c = 0; c < COL; ++c) {
					m_matrice[hash({l, c})] += m[{l, c}];
				}
			}

			return *this;
		}

		Matrice& operator -= (Matrice const& m) {
			for (int i = 0; i < size(); ++i) {
				m_matrice[i] -= m.m_matrice[i];
			}

			return *this;
		}

		Matrice& operator -= (Matrice<Int,0,0> const& m) {
			if (nb_lig() != m.nb_lig() || nb_col() != m.nb_col()) throw std::domain_error("Impossible de soustraire 2 matrices de tailles différentes");

			for (int l = 0; l < LIG; ++l) {
				for (int c = 0; c < COL; ++c) {
					m_matrice[hash({l, c})] -= m[{l, c}];
				}
			}

			return *this;
		}

		Matrice& operator *= (Int const& lambda) {
			for (Int& v : *this) {
				v *= lambda;
			}

			return *this;
		}

		Matrice& operator /= (Int const& lambda) {
			for (Int& v : *this) {
				v /= lambda;
			}

			return *this;
		}

		// Méthodes
		Vecteur<unsigned,2> size() const {
			return Vecteur<unsigned,2>({LIG, COL});
		}

		size_type nb_lig() const {
			return LIG;
		}

		size_type nb_col() const {
			return COL;
		}

		void fill(Int const& val) {
			for (int i = 0; i < size(); ++i) m_matrice[i] = val;
		}

		auto colonne(size_type c) {
			return part<column_iterator,const_column_iterator,LIG>(column_iterator(begin() + c));
		}

		auto colonne(size_type c) const {
			return const_part<const_column_iterator,LIG>(const_column_iterator(begin() + c));
		}

		auto colonnes() {
			std::vector<part<column_iterator,const_column_iterator,LIG>> colonnes(COL);

			for (int c = 0; c < COL; ++c) {
				colonnes[c] = colonne(c);
			}

			return colonnes;
		}

		auto colonnes() const {
			std::vector<const_part<const_column_iterator,LIG>> colonnes(COL);

			for (int c = 0; c < COL; ++c) {
				colonnes[c] = colonne(c);
			}

			return colonnes;
		}

		auto ligne(size_type l) {
			return part<iterator,const_iterator,COL>(begin() + (l * COL));
		}

		auto ligne(size_type l) const {
			return const_part<const_iterator,COL>(begin() + (l * COL));
		}

		auto lignes() {
			std::vector<part<iterator,const_iterator,COL>> lignes(LIG);

			for (int l = 0; l < LIG; ++l) {
				lignes[l] = ligne(l);
			}

			return lignes;
		}

		auto lignes() const {
			std::vector<const_part<const_iterator,COL>> lignes(LIG);

			for (int l = 0; l < LIG; ++l) {
				lignes[l] = ligne(l);
			}

			return lignes;
		}

		// Itérateurs
		iterator begin() { return m_matrice.begin(); }
		iterator end()   { return m_matrice.end(); }

		const_iterator begin() const { return m_matrice.cbegin(); }
		const_iterator end()   const { return m_matrice.cend(); }

	private:
		// Attributs
		std::hash<Point<unsigned,2>> hash;
		std::array<Int,LIG * COL> m_matrice;
};

template<class Int>
class Matrice<Int,0,0> {
	/**
	 * Version de Matrice à allocation dynamique
	 */
	public:
		// Alias
		using value_type      = Int;
		using reference       = Int&;
		using const_reference = Int const&;
		using pointer         = Int*;
		using const_pointer   = Int const*;
		using iterator        = typename std::vector<Int>::iterator;
		using const_iterator  = typename std::vector<Int>::const_iterator;
		using size_type       = size_t;
		using difference_type = ptrdiff_t;

		// Sous-classes
		class column_iterator {
			public:
				// Alias
				using value_type        = Matrice::value_type;
				using reference         = Matrice::reference;
				using difference_type   = Matrice::difference_type;
				using iterator_category = std::random_access_iterator_tag;

				// Constructeurs
				column_iterator() = default;
				column_iterator(iterator const& it, size_type col) : m_it(it), COL(col) {};

				// Opérateurs
				// - déférenciation
				reference operator *  () const { return *m_it; }
				pointer   operator -> () const { return m_it.operator ->(); }
				reference operator [] (Matrice::size_type v) const { return m_it[v]; }

				// - comparaison
				bool operator <  (column_iterator const& cit) const { return m_it <  cit.m_it; };
				bool operator <= (column_iterator const& cit) const { return m_it <= cit.m_it; };
				bool operator == (column_iterator const& cit) const { return m_it == cit.m_it; };
				bool operator != (column_iterator const& cit) const { return m_it != cit.m_it; };
				bool operator >= (column_iterator const& cit) const { return m_it >= cit.m_it; };
				bool operator >  (column_iterator const& cit) const { return m_it >  cit.m_it; };

				// - incrémentation & décrémentation
				column_iterator& operator ++ () { m_it += COL; return *this; }
				column_iterator& operator -- () { m_it -= COL; return *this; }

				column_iterator operator ++ (int) {
					column_iterator tmp(*this);
					++(*this);
					return tmp;
				}

				column_iterator operator -- (int) {
					column_iterator tmp(*this);
					--(*this);
					return tmp;
				}

				// - assignation
				column_iterator& operator += (Matrice::size_type v) { m_it += v * COL; return *this; }
				column_iterator& operator -= (Matrice::size_type v) { m_it -= v * COL; return *this; }

				// - arithmétique
				column_iterator operator + (Matrice::size_type v) const { column_iterator r(*this); r += v; return r; };
				column_iterator operator - (Matrice::size_type v) const { column_iterator r(*this); r -= v; return r; };

				friend column_iterator operator + (Matrice::size_type v, column_iterator const& it) {
					column_iterator r(it);
					r += v;
					return r;
				};

				difference_type operator - (column_iterator cit) const {
					return (m_it - cit.m_it) / COL;
				};

			private:
				// Attributs
				iterator m_it;
				size_type COL;
		};

		class const_column_iterator {
			public:
				// Alias
				using value_type        = Matrice::value_type;
				using reference         = Matrice::const_reference;
				using difference_type   = Matrice::difference_type;
				using iterator_category = std::random_access_iterator_tag;

				// Constructeurs
				const_column_iterator() = default;
				const_column_iterator(column_iterator const& cit) : m_it(cit.m_it), COL(cit.COL) {};
				const_column_iterator(const_iterator const& it, size_type col) : m_it(it), COL(col) {};

				// Opérateurs
				// - déférenciation
				reference operator *  () const { return *m_it; }
				pointer   operator -> () const { return m_it.operator ->(); }
				reference operator [] (Matrice::size_type v) const { return m_it[v]; }

				// - comparaison
				bool operator <  (const_column_iterator const& cit) const { return m_it <  cit.m_it; };
				bool operator <= (const_column_iterator const& cit) const { return m_it <= cit.m_it; };
				bool operator == (const_column_iterator const& cit) const { return m_it == cit.m_it; };
				bool operator != (const_column_iterator const& cit) const { return m_it != cit.m_it; };
				bool operator >= (const_column_iterator const& cit) const { return m_it >= cit.m_it; };
				bool operator >  (const_column_iterator const& cit) const { return m_it >  cit.m_it; };

				// - incrémentation & décrémentation
				const_column_iterator& operator ++ () { m_it += COL; return *this; }
				const_column_iterator& operator -- () { m_it -= COL; return *this; }

				const_column_iterator operator ++ (int) {
					const_column_iterator tmp(*this);
					++(*this);
					return tmp;
				}

				const_column_iterator operator -- (int) {
					const_column_iterator tmp(*this);
					--(*this);
					return tmp;
				}

				// - assignation
				const_column_iterator& operator += (Matrice::size_type v) { m_it += v * COL; return *this; }
				const_column_iterator& operator -= (Matrice::size_type v) { m_it -= v * COL; return *this; }

				// - arithmétique
				const_column_iterator operator + (Matrice::size_type v) const { const_column_iterator r(*this); r += v; return r; };
				const_column_iterator operator - (Matrice::size_type v) const { const_column_iterator r(*this); r -= v; return r; };

				friend const_column_iterator operator + (Matrice::size_type v, const_column_iterator const& it) {
					const_column_iterator r(it);
					r += v;
					return r;
				};

				difference_type operator - (const_column_iterator cit) const {
					return (m_it - cit.m_it) / COL;
				};

			private:
				// Attributs
				const_iterator m_it;
				size_type COL;
		};

		template<class It, class CIt>
		class part {
			public:
				// Alias
				using value_type       = Matrice::value_type;
				using reference        = Matrice::reference;
				using const_reference  = Matrice::const_reference;
				using iterator         = It;
				using const_iterator   = CIt;
				using size_type        = Matrice::size_type;
				using difference_type  = Matrice::difference_type;

				// Constructeur
				part(It const& deb, size_type n) : m_deb(deb), N(n) {};

				// Opérateurs
				// - accès éléments
				reference operator [] (size_type const& i) {
					return *(m_deb + i);
				}

				const_reference operator [] (size_type const& i) const {
					return *(const_iterator(m_deb) + i);
				}

				// Méthodes
				size_type size() const {
					return N;
				}

				void fill(Int const& v) {
					for (int i = 0; i < size(); ++i) (*this)[i] = v;
				}

				// Itérateurs
				iterator begin() { return m_deb; }
				iterator end()   { return m_deb + N; }

				const_iterator begin() const { return const_iterator(m_deb); }
				const_iterator end()   const { return const_iterator(m_deb + N); }

			private:
				// Attributs
				It m_deb;
				size_type N;
		};

		template<class CIt>
		class const_part {
			public:
				// Alias
				using value_type       = Matrice::value_type;
				using const_reference  = Matrice::const_reference;
				using const_iterator   = CIt;
				using size_type        = Matrice::size_type;
				using difference_type  = Matrice::difference_type;

				// Constructeurs
				template<class It>
				const_part(part<It,CIt> const& p) : m_deb(p.m_deb), N(p.N) {};
				const_part(CIt const& deb, size_type n) : m_deb(deb), N(n) {};

				// Opérateurs
				// - accès éléments
				const_reference operator [] (size_type const& c) const {
					return *(m_deb + c);
				}

				// Méthodes
				size_type size() const {
					return N;
				}

				// Itérateurs
				const_iterator begin() const { return m_deb; }
				const_iterator end()   const { return m_deb + N; }

			private:
				// Attributs
				CIt m_deb;
				size_type N;
		};

		// Constructeur
		Matrice(size_type lig)                : LIG(lig), COL(lig), hash(std::max(lig, lig)), m_matrice(lig * lig) {};
		Matrice(size_type lig, size_type col) : LIG(lig), COL(col), hash(std::max(lig, col)), m_matrice(lig * col) {};

		Matrice(std::vector<std::vector<Int>> const& matrice)
			: LIG(matrice.size()), COL(matrice.front().size()),
			  hash({matrice.size()}), m_matrice(matrice.size() * matrice.front().size()) {

			for (int l = 0; l < LIG; ++l) {
				for (int c = 0; c < COL; ++c) {
					m_matrice[hash({l, c})] = matrice[l][c];
				}
			}
		};

		// Opérateurs
		// - accès élément
		reference operator [] (Point<unsigned,2> const& c) { // (lig, col)
			return m_matrice[hash(c)];
		}

		const_reference operator [] (Point<unsigned,2> const& c) const { // (lig, col)
			return m_matrice[hash(c)];
		}

		// - arithmétique
		Matrice operator - () const {
			Matrice r;

			for (int i = 0; i < size(); ++i) {
				r.m_matrice[i] = -m_matrice[i];
			}

			return r;
		}

		template<size_t L, size_t C>
		Matrice operator + (Matrice<Int,L,C> m) const { m += (*this); return m; }

		template<size_t L, size_t C>
		Matrice operator - (Matrice<Int,L,C> m) const { m -= (*this); return m; }

		Matrice operator / (Int const& lambda) const { Matrice r(*this); r /= lambda; return r; }
		Matrice operator * (Int const& lambda) const { Matrice r(*this); r *= lambda; return r; }
		friend Matrice operator * (Int const& lambda, Matrice m) { m *= lambda; return m; }

		// - assignation
		Matrice& operator += (Matrice const& m) {
			if (nb_lig() != m.nb_lig() || nb_col() != m.nb_col()) throw std::domain_error("Impossible d'ajouter 2 matrices de tailles différentes");

			for (int i = 0; i < size(); ++i) {
				m_matrice[i] += m.m_matrice[i];
			}

			return *this;
		}

		template<size_t L, size_t C>
		Matrice& operator += (Matrice<Int,L,C> const& m) {
			if (nb_lig() != L || nb_col() != C) throw std::domain_error("Impossible d'ajouter 2 matrices de tailles différentes");

			for (int l = 0; l < LIG; ++l) {
				for (int c = 0; c < COL; ++c) {
					m_matrice[hash({l, c})] += m[{l, c}];
				}
			}

			return *this;
		}

		Matrice& operator -= (Matrice const& m) {
			if (nb_lig() != m.nb_lig() || nb_col() != m.nb_col()) throw std::domain_error("Impossible de soustraire 2 matrices de tailles différentes");

			for (int i = 0; i < size(); ++i) {
				m_matrice[i] -= m.m_matrice[i];
			}

			return *this;
		}

		template<size_t L, size_t C>
		Matrice& operator -= (Matrice<Int,L,C> const& m) {
			if (nb_lig() != L || nb_col() != C) throw std::domain_error("Impossible de soustraire 2 matrices de tailles différentes");

			for (int l = 0; l < LIG; ++l) {
				for (int c = 0; c < COL; ++c) {
					m_matrice[hash({l, c})] -= m[{l, c}];
				}
			}

			return *this;
		}

		Matrice& operator *= (Int const& lambda) {
			for (Int& v : *this) {
				v *= lambda;
			}

			return *this;
		}

		Matrice& operator /= (Int const& lambda) {
			for (Int& v : *this) {
				v /= lambda;
			}

			return *this;
		}

		template<size_t L, size_t C>
		Matrice& operator *= (Matrice<Int,L,C> const& m) {
			if (nb_col() != m.nb_lig()) throw std::domain_error("Pour le produit matriciel : C1 = L2");
			std::vector<Int> r(nb_lig() * m.nb_col(), 0);

			for (int l = 0; l < nb_lig(); ++l) {
				for (int c = 0; c < m.nb_col(); ++c) {
					for (int i = 0; i < nb_col(); ++i) {
						r[hash({l, c})] += m_matrice[hash({l, i})] * m[{i, c}];
					}
				}
			}

			m_matrice.swap(r);

			return *this;
		}

		// Méthodes
		Vecteur<unsigned,2> size() const {
			return Vecteur<unsigned,2>({LIG, COL});
		}

		size_type nb_lig() const {
			return LIG;
		}

		size_type nb_col() const {
			return COL;
		}

		void fill(Int const& val) {
			for (int i = 0; i < size(); ++i) m_matrice[i] = val;
		}

		auto colonne(size_type c) {
			return part<column_iterator,const_column_iterator>(column_iterator(begin() + c, COL), LIG);
		}

		auto colonne(size_type c) const {
			return const_part<const_column_iterator>(const_column_iterator(begin() + c, COL), LIG);
		}

		auto colonnes() {
			std::vector<part<column_iterator,const_column_iterator>> colonnes(COL);

			for (int c = 0; c < COL; ++c) {
				colonnes[c] = colonne(c);
			}

			return colonnes;
		}

		auto colonnes() const {
			std::vector<const_part<const_column_iterator>> colonnes(COL);

			for (int c = 0; c < COL; ++c) {
				colonnes[c] = colonne(c);
			}

			return colonnes;
		}

		auto ligne(size_type l) {
			return part<iterator,const_iterator>(begin() + (l * COL), COL);
		}

		auto ligne(size_type l) const {
			return const_part<const_iterator>(begin() + (l * COL), COL);
		}

		auto lignes() {
			std::vector<part<iterator,const_iterator>> lignes(LIG);

			for (int l = 0; l < LIG; ++l) {
				lignes[l] = ligne(l);
			}

			return lignes;
		}

		auto lignes() const {
			std::vector<const_part<const_iterator>> lignes(LIG);

			for (int l = 0; l < LIG; ++l) {
				lignes[l] = ligne(l);
			}

			return lignes;
		}

		// Itérateurs
		iterator begin() { return m_matrice.begin(); }
		iterator end()   { return m_matrice.end(); }

		const_iterator begin() const { return m_matrice.cbegin(); }
		const_iterator end()   const { return m_matrice.cend(); }

	private:
		// Attributs
		const size_type LIG, COL;
		std::hash<Point<unsigned,2>> hash;
		std::vector<Int> m_matrice;
};

} // math

// Opérateurs externes
// produit matriciel
template<class Int, size_t LIG, size_t COLLIG, size_t COL>
typename std::enable_if<LIG != 0 && COLLIG != 0 && COL != 0,math::Matrice<Int,LIG,COL>>::type operator * (math::Matrice<Int,LIG,COLLIG> const& m1, math::Matrice<Int,COLLIG,COL> const& m2) {
	math::Matrice<Int,LIG,COL> r;

	for (unsigned l = 0; l < LIG; ++l) {
		for (unsigned c = 0; c < COL; ++c) {
			r[math::Point<unsigned,2>({l, c})] = 0;

			for (unsigned i = 0; i < COLLIG; ++i) {
				r[math::Point<unsigned,2>({l, c})] += m1[math::Point<unsigned,2>({l, i})] * m2[math::Point<unsigned,2>({i, c})];
			}
		}
	}

	return r;
}

template<class Int, size_t LIG, size_t COL>
typename std::enable_if<LIG != 0 && COL != 0,math::Matrice<Int,0,0>>::type operator * (math::Matrice<Int,LIG,COL> const& m1, math::Matrice<Int,0,0> const& m2) {
	static_assert(LIG > 0, "Doit avoir un nombre non nul de lignes");
	static_assert(COL > 0, "Doit avoir un nombre non nul de colonnes");

	if (COL != m2.nb_lig()) throw std::domain_error("Pour le produit matriciel : C1 = L2");
	math::Matrice<Int,0,0> r(LIG, m2.nb_col());

	for (unsigned l = 0; l < LIG; ++l) {
		for (unsigned c = 0; c < m2.nb_col(); ++c) {
			r[math::Point<unsigned,2>({l, c})] = 0;

			for (unsigned i = 0; i < COL; ++i) {
				r[math::Point<unsigned,2>({l, c})] += m1[math::Point<unsigned,2>({l, i})] * m2[math::Point<unsigned,2>({i, c})];
			}
		}
	}

	return r;
}

template<class Int, size_t LIG, size_t COL>
math::Matrice<Int,0,0> operator * (math::Matrice<Int,0,0> m1, math::Matrice<Int,LIG,COL> const& m2) {
	m1 *= m2;
	return m1;
}
