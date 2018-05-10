#pragma once

// Importations
#include <iterator>

#include "coord.hpp"

// Namespace
namespace math {

// Template
template<class Int, size_t DEG>
class Range {
	public:
		// Alias
		using value_type      = Point<DEG,Int>;
		using const_reference = Point<DEG,Int> const&;
		using const_pointer   = Point<DEG,Int> const*;

		// Classes
		class const_iterator {
			public:
				// Alias
				using value_type        = Range::value_type;
				using const_reference   = Range::const_reference;
				using const_pointer     = Range::const_pointer;
				using iterator_category = std::bidirectional_iterator_tag;

				// Constructeur
				const_iterator() = default;
				const_iterator(Point<DEG,Int> const& point, Range const& r) : m_point(point), m_range(r) {}

				// Opérateurs
				// - déférenciation
				const_reference operator *  () const { return m_point;  }
				const_pointer   operator -> () const { return &m_point; }

				// - comparaison
				bool operator == (const_iterator const& it) const {
					return m_point == it.m_point;
				}

				bool operator != (const_iterator const& it) const {
					return m_point != it.m_point;
				}

				// - incrémentation & décrémentation
				const_iterator& operator ++ () {
					for (size_t d = DEG-1; d >= 0; --d) {
						++(m_point[d]);

						if (m_point[d] >= m_range.m_fin[d]) {
							if (d > 0) m_point[d] = m_range.m_debut[d];
						} else {
							break;
						}
					}

					return *this;
				}

				const_iterator& operator -- () {
					for (size_t d = DEG-1; d >= 0; --d) {
						--(m_point[d]);

						if (m_point[d] < m_range.m_debut[d]) {
							m_point[d] = m_range.m_fin[d]-1;
						} else {
							break;
						}
					}

					return *this;
				}

				const_iterator operator ++ (int) {
					const_iterator tmp(*this);
					++(*this);
					return tmp;
				}

				const_iterator operator -- (int) {
					const_iterator tmp(*this);
					--(*this);
					return tmp;
				}

			private:
				// Attributs
				Point<DEG,Int> m_point;
				Range m_range;
		};

		// Constructeur
		Range(Point<DEG,Int> const& debut, Point<DEG,Int> const& fin) : m_debut(debut), m_fin(fin) {};

		// Itérateurs
		const_iterator begin() const { return const_iterator(m_debut, *this); }
		const_iterator end()   const {
			Point<DEG,Int> fin;

			for (size_t d = 1; d < DEG; ++d) fin[d] = m_debut[d];
			fin[0] = m_fin[0];

			return const_iterator(fin, *this);
		}

	private:
		// Attributs
		Point<DEG,Int> m_debut;
		Point<DEG,Int> m_fin;
};

template<class Int, size_t DEG>
Range<Int,DEG> range(Point<DEG,Int> const& debut, Point<DEG,Int> const& fin) {
	return Range<Int,DEG>(debut, fin);
}

template<class Int, size_t DEG>
Range<Int,DEG> range(Point<DEG,Int> const& debut, Vecteur<DEG,Int> const& t) {
	return Range<Int,DEG>(debut, debut + t);
}

template<class Int, size_t DEG>
Range<Int,DEG> range(Vecteur<DEG,Int> const& t) {
	Point<DEG,Int> debut;
	for (size_t d = 0; d < DEG; ++d) debut[d] = 0;

	return range(debut, t);
}

} // math
