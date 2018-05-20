#pragma once

// Importations
#include <algorithm>
#include <array>
#include <map>
#include <ostream>
#include <string>
#include <type_traits>
#include <vector>

#include "manip.hpp"
#include "posstream.hpp"

// Namespace
namespace console {

// Classes
namespace base {

// char
template<size_t LIG>
class asciiart_char {
	private:
		// Attributs
		char m_char = '\0';

		int m_decalx = 0;
		std::array<std::string,LIG> m_asciiart;

	public:
		// Constructeur
		asciiart_char() {
			m_asciiart.fill("");
		}

		asciiart_char(char c, std::array<std::string,LIG> const& asciiart) : asciiart_char(c, 0, asciiart) {
		}

		asciiart_char(char c, int decalx, std::array<std::string,LIG> const& asciiart) : m_char(c), m_decalx(decalx), m_asciiart(asciiart) {
		}

		// Opérateurs
		// - comparaison
		bool operator < (asciiart_char<LIG> const& aac) const {
			return m_char < aac.m_char;
		}

		bool operator <= (asciiart_char<LIG> const& aac) const {
			return m_char <= aac.m_char;
		}

		bool operator == (asciiart_char<LIG> const& aac) const {
			return m_char == aac.m_char;
		}

		bool operator != (asciiart_char<LIG> const& aac) const {
			return m_char != aac.m_char;
		}

		bool operator >= (asciiart_char<LIG> const& aac) const {
			return m_char >= aac.m_char;
		}

		bool operator > (asciiart_char<LIG> const& aac) const {
			return m_char > aac.m_char;
		}

		// Méthodes
		size_t screen_size() const {
			return m_asciiart[0].size();
		}

		// - accesseurs
		char to_char() const {
			return m_char;
		}

		int decalx() const {
			return m_decalx;
		}

		std::array<std::string,LIG> const& asciiart() const {
			return m_asciiart;
		}
};

// String
template<size_t LIG, class Traits, class Alloc>
class asciiart_string {
	public:
		// Alias
		using traits_type     = Traits;
		using allocator_type  = typename std::vector<asciiart_char<LIG>,Alloc>::allocator_type;
		using value_type      = typename std::vector<asciiart_char<LIG>,Alloc>::value_type;
		using reference       = typename std::vector<asciiart_char<LIG>,Alloc>::reference;
		using const_reference = typename std::vector<asciiart_char<LIG>,Alloc>::const_reference;
		using pointer         = typename std::vector<asciiart_char<LIG>,Alloc>::pointer;
		using const_pointer   = typename std::vector<asciiart_char<LIG>,Alloc>::const_pointer;
		using iterator        = typename std::vector<asciiart_char<LIG>,Alloc>::iterator;
		using const_iterator  = typename std::vector<asciiart_char<LIG>,Alloc>::const_iterator;
		using reverse_iterator = typename std::vector<asciiart_char<LIG>,Alloc>::reverse_iterator;
		using const_reverse_iterator = typename std::vector<asciiart_char<LIG>,Alloc>::const_reverse_iterator;
		using difference_type = typename std::vector<asciiart_char<LIG>,Alloc>::difference_type;
		using size_type       = typename std::vector<asciiart_char<LIG>,Alloc>::size_type;

		// Constructeur
		// - par défaut
		asciiart_string() = default;
		explicit asciiart_string(allocator_type const& alloc) : m_chaine(alloc) {}

		// - copie
		asciiart_string(asciiart_string const& str) = default;
		asciiart_string(asciiart_string const& str, allocator_type const& alloc) : m_chaine(str.m_chaine, alloc) {};

		// - move
		asciiart_string(asciiart_string&& str) noexcept = default;
		asciiart_string(asciiart_string&& str, allocator_type const& alloc) : m_chaine(std::forward<std::vector<asciiart_char<LIG>>>(str.m_chaine), alloc) {};

		// - substring
		asciiart_string(asciiart_string const& str, size_type pos, size_type len = asciiart_string::npos, allocator_type const& alloc = allocator_type())
			: m_chaine(str.m_chaine.begin() + pos, (len == asciiart_string::npos) || (pos + len > str.m_chaine.size()) ? str.m_chaine.end() : str.m_chaine.begin() + pos + end, alloc) {}

		// - from c-string
		asciiart_string(asciiart_char<LIG> const* s, allocator_type const& alloc = allocator_type())
			: m_chaine(alloc) {

			// Copie !
			while (*s != asciiart_char<LIG>()) {
				m_chaine.push_back(*s);
				++s;
			}
		}

		// - from buffer
		asciiart_string(asciiart_char<LIG> const* s, size_t n, allocator_type const& alloc = allocator_type())
			: m_chaine(alloc) {

			// Copie !
			m_chaine.reserve(n);
			for (size_t i = 0; i < n; ++i) {
				m_chaine.push_back(s[i]);
			}
		}

		// - fill
		asciiart_string(size_t n, asciiart_char<LIG> const& c, allocator_type const& alloc = allocator_type())
			: m_chaine(n, c, alloc) {}

		// - range
		template<class InputIterator>
		asciiart_string(InputIterator first, InputIterator last, allocator_type const& alloc = allocator_type())
			: m_chaine(first, last, alloc) {
		}

		// - initializer list
		asciiart_string(std::initializer_list<asciiart_char<LIG>> il, allocator_type const& alloc = allocator_type())
			: m_chaine(il, alloc) {
		}

		// Opérateurs
		// - assignation
		asciiart_string& operator = (asciiart_string const& str) = default;
		asciiart_string& operator = (asciiart_string&& str) noexcept = default;

		asciiart_string& operator = (asciiart_char<LIG> const* s) {
			// Copie !
			while (*s != asciiart_char<LIG>()) {
				m_chaine.push_back(*s);
				++s;
			}

			return *this;
		}

		asciiart_string& operator = (std::initializer_list<asciiart_char<LIG>> il) {
			m_chaine = il;

			return *this;
		}

		asciiart_string& operator += (asciiart_string const& str) {
			m_chaine.insert(m_chaine.end(), str.m_chaine.begin(), str.m_chaine.end());

			return *this;
		}

		asciiart_string& operator += (asciiart_char<LIG> const* s) {
			// Copie !
			while (*s != asciiart_char<LIG>()) {
				m_chaine.push_back(*s);
				++s;
			}

			return *this;
		}

		asciiart_string& operator += (asciiart_char<LIG> const& c) {
			m_chaine.push_back(c);

			return *this;
		}

		asciiart_string& operator += (std::initializer_list<asciiart_char<LIG>> il) {
			m_chaine.insert(m_chaine.end, il);

			return *this;
		}

		// - acces
		reference operator [] (size_type pos) {
			return m_chaine[pos];
		}

		const_reference operator [] (size_type pos) const {
			return m_chaine[pos];
		}

		// - arithmétique
		friend asciiart_string operator + (asciiart_string const& lhs, asciiart_string const& rhs) {
			asciiart_string res = lhs;
			res += rhs;

			return res;
		}

		friend asciiart_string operator + (asciiart_string&& lhs, asciiart_string&& rhs) {
			asciiart_string res = lhs;
			res += rhs;

			return res;
		}

		friend asciiart_string operator + (asciiart_string&& lhs, asciiart_string const& rhs) {
			asciiart_string res = lhs;
			res += rhs;

			return res;
		}

		friend asciiart_string operator + (asciiart_string const& lhs, asciiart_string&& rhs) {
			asciiart_string res = lhs;
			res += rhs;

			return res;
		}

		friend asciiart_string operator + (asciiart_string const& lhs, asciiart_char<LIG> const* rhs) {
			asciiart_string res = lhs;
			res += rhs;

			return res;
		}

		friend asciiart_string operator + (asciiart_string&& lhs, asciiart_char<LIG> const* rhs) {
			asciiart_string res = lhs;
			res += rhs;

			return res;
		}

		friend asciiart_string operator + (asciiart_char<LIG> const* lhs, asciiart_string const& rhs) {
			asciiart_string res = lhs;
			res += rhs;

			return res;
		}

		friend asciiart_string operator + (asciiart_char<LIG> const* lhs, asciiart_string&& rhs) {
			asciiart_string res = lhs;
			res += rhs;

			return res;
		}

		friend asciiart_string operator + (asciiart_string const& lhs, asciiart_char<LIG> const& rhs) {
			asciiart_string res = lhs;
			res += rhs;

			return res;
		}

		friend asciiart_string operator + (asciiart_string&& lhs, asciiart_char<LIG> const& rhs) {
			asciiart_string res = lhs;
			res += rhs;

			return res;
		}

		friend asciiart_string operator + (asciiart_char<LIG> const& lhs, asciiart_string const& rhs) {
			asciiart_string res = lhs;
			res += rhs;

			return res;
		}

		friend asciiart_string operator + (asciiart_char<LIG> const& lhs, asciiart_string&& rhs) {
			asciiart_string res = lhs;
			res += rhs;

			return res;
		}

		// Méthodes
		size_t screen_size() const {
			size_t t = 0;

			for (size_t i = 0; i < m_chaine.size(); ++i) {
				t += m_chaine[i].screen_size()+1;

				if (i != 0) t += m_chaine[i].decalx();
			}

			return t;
		}

		// - taille / capacité
		size_type size() const noexcept {
			return m_chaine.size();
		}

		size_type length() const noexcept {
			return m_chaine.size();
		}

		size_type capacity() const noexcept {
			return m_chaine.capacity();
		}

		size_type max_size() const {
			return m_chaine.max_size();
		}

		void resize(size_type n) {
			m_chaine.resize(n);
		}

		void resize(size_type n, asciiart_char<LIG> const& c) {
			m_chaine.resize(n, c);
		}

		void reserve(size_type n = 0) {
			m_chaine.reserve(n);
		}

		void clear() noexcept {
			m_chaine.clear();
		}

		void empty() const noexcept {
			m_chaine.empty();
		}

		void shrink_to_fit() {
			m_chaine.shrink_to_fit();
		}

		// - accès
		asciiart_char<LIG>& at(size_type pos) {
			return m_chaine.at(pos);
		}

		asciiart_char<LIG> const& at(size_type pos) const {
			return m_chaine.at(pos);
		}

		asciiart_char<LIG>& front() {
			return m_chaine.front();
		}

		asciiart_char<LIG> const& front() const {
			return m_chaine.front();
		}

		asciiart_char<LIG>& back() {
			return m_chaine.back();
		}

		asciiart_char<LIG> const& back() const {
			return m_chaine.back();
		}

		asciiart_char<LIG>* data() noexcept {
			return m_chaine.data();
		}

		asciiart_char<LIG> const* data() const noexcept {
			return m_chaine.data();
		}

		// - modifiantes
		asciiart_string& assign(asciiart_string const& str) {
			m_chaine = str.m_chaine;
			return *this;
		}

		asciiart_string& assign(asciiart_string&& str) noexcept {
			m_chaine = std::forward<std::vector<asciiart_char<LIG>>>(str.m_chaine);
			return *this;
		}

		asciiart_string& assign(asciiart_string const& str, size_type subpos, size_type sublen = std::string::npos) {
			auto deb = str.m_chaine.begin() + subpos;
			auto fin = sublen == std::string::npos ||subpos + sublen >= str.size() ? str.m_chaine.end() : deb + sublen;

			m_chaine.assign(deb, fin);

			return *this;
		}

		asciiart_string& assign(asciiart_char<LIG> const* s) {
			m_chaine.clear();

			// Copie !
			while (*s != asciiart_char<LIG>()) {
				m_chaine.push_back(*s);
				++s;
			}

			return *this;
		}

		asciiart_string& assign(asciiart_char<LIG> const* s, size_type n) {
			m_chaine.clear();
			m_chaine.reserve(n);

			// Copie !
			for (int i = 0; i < n; ++i) {
				m_chaine.push_back(s[i]);
			}

			return *this;
		}

		asciiart_string& assign(size_type n, asciiart_char<LIG> const& c) {
			m_chaine.assign(n, c);
			return *this;
		}

		template<class InputIterator>
		asciiart_string& assign(InputIterator first, InputIterator last) {
			m_chaine.assign(first, last);
			return *this;
		}

		asciiart_string& assign(std::initializer_list<asciiart_char<LIG>> il) {
			m_chaine.assign(il);
			return *this;
		}

		asciiart_string& append(asciiart_string const& str) {
			m_chaine.insert(m_chaine.cend(), str.m_chaine.begin(), str.m_chaine.end());
			return *this;
		}

		asciiart_string& append(asciiart_string const& str, size_type subpos, size_type sublen = std::string::npos) {
			auto deb = str.m_chaine.begin() + subpos;
			auto fin = sublen == std::string::npos ||subpos + sublen >= str.size() ? str.m_chaine.end() : deb + sublen;

			m_chaine.insert(m_chaine.cend(), deb, fin);

			return *this;
		}

		asciiart_string& append(asciiart_char<LIG> const* s) {
			// Copie !
			while (*s != asciiart_char<LIG>()) {
				m_chaine.push_back(*s);
				++s;
			}

			return *this;
		}

		asciiart_string& append(asciiart_char<LIG> const* s, size_type n) {
			m_chaine.reserve(m_chaine.capacity + n);
			m_chaine.insert(m_chaine.cend(), s, s+n);

			return *this;
		}

		asciiart_string& append(size_type n, asciiart_char<LIG> const& c) {
			m_chaine.insert(m_chaine.cend(), n, c);
			return *this;
		}

		template<class InputIterator>
		asciiart_string& append(InputIterator first, InputIterator last) {
			m_chaine.insert(m_chaine.cend(), first, last);
			return *this;
		}

		asciiart_string& append(std::initializer_list<asciiart_char<LIG>> il) {
			m_chaine.insert(m_chaine.cend(), il);
			return *this;
		}

		void push_back(asciiart_char<LIG> const& c) {
			m_chaine.push_back(c);
		}

		void push_back(asciiart_char<LIG>&& c) {
			m_chaine.push_back(std::forward<asciiart_char<LIG>>(c));
		}

		asciiart_string& insert(size_type pos, asciiart_string const& str) {
			m_chaine.insert(m_chaine.cbegin() + pos, str.m_chaine.begin(), str.m_chaine.end());
			return *this;
		}

		asciiart_string& insert(size_type pos, asciiart_string const& str, size_type subpos, size_type sublen = std::string::npos) {
			auto deb = str.m_chaine.begin() + subpos;
			auto fin = sublen == std::string::npos ||subpos + sublen >= str.size() ? str.m_chaine.end() : deb + sublen;

			m_chaine.insert(m_chaine.cbegin() + pos, deb, fin);

			return *this;
		}

		asciiart_string& insert(size_type pos, asciiart_char<LIG> const* s) {
			// Copie !
			auto it = m_chaine.cbegin() + pos;

			while (*s != asciiart_char<LIG>()) {
				m_chaine.insert(it, *s);
				++s; ++it;
			}

			return *this;
		}

		asciiart_string& insert(size_type pos, asciiart_char<LIG> const* s, size_type n) {
			m_chaine.reserve(m_chaine.capacity + n);
			m_chaine.insert(m_chaine.cbegin() + pos, s, s+n);

			return *this;
		}

		asciiart_string& insert(size_type pos, size_type n, asciiart_char<LIG> const& c) {
			m_chaine.insert(m_chaine.cbegin() + pos, n, c);
			return *this;
		}

		iterator insert(const_iterator it, size_type n, asciiart_char<LIG> const& c) {
			return m_chaine.insert(it, n, c);
		}

		iterator insert(const_iterator it, asciiart_char<LIG> const& c) {
			return m_chaine.insert(it, c);
		}

		template<class InputIterator>
		iterator insert(const_iterator it, InputIterator first, InputIterator last) {
			return m_chaine.insert(it, first, last);
		}

		asciiart_string& insert(const_iterator it, std::initializer_list<asciiart_char<LIG>> il) {
			m_chaine.insert(it, il);
			return *this;
		}

		asciiart_string& erase(size_type pos = 0, size_type len = std::string::npos) {
			auto deb = m_chaine.cbegin() + pos;
			auto fin = len == std::string::npos || pos + len >= m_chaine.size() ? m_chaine.cend() : deb + len;

			m_chaine.erase(deb, fin);

			return *this;
		}

		iterator erase(const_iterator p) {
			return m_chaine.erase(p);
		}

		iterator erase(const_iterator first, const_iterator last) {
			return m_chaine.erase(first, last);
		}

		asciiart_string& replace(size_type pos, size_type len, asciiart_string const& str) {
			m_chaine.erase(pos, len);
			m_chaine.insert(pos, str);

			return *this;
		}

		asciiart_string& replace(const_iterator it1, const_iterator it2, asciiart_string const& str) {
			m_chaine.erase(it1, it2);
			m_chaine.insert(it1, str);

			return *this;
		}

		asciiart_string& replace(size_type pos, size_type len, asciiart_string const& str, size_type subpos, size_type sublen = std::string::npos) {
			m_chaine.erase(pos, len);
			m_chaine.insert(pos, str, subpos, sublen);

			return *this;
		}

		asciiart_string& replace(size_type pos, size_type len, asciiart_char<LIG> const* str) {
			m_chaine.erase(pos, len);
			m_chaine.insert(pos, str);

			return *this;
		}

		asciiart_string& replace(const_iterator it1, const_iterator it2, asciiart_char<LIG> const* str) {
			m_chaine.erase(it1, it2);
			m_chaine.insert(it1, str);

			return *this;
		}

		asciiart_string& replace(size_type pos, size_type len, asciiart_char<LIG> const* str, size_type n) {
			m_chaine.erase(pos, len);
			m_chaine.insert(pos, str, n);

			return *this;
		}

		asciiart_string& replace(const_iterator it1, const_iterator it2, asciiart_char<LIG> const* str, size_type n) {
			m_chaine.erase(it1, it2);
			m_chaine.insert(it1, str, n);

			return *this;
		}

		asciiart_string& replace(size_type pos, size_type len, size_type n, asciiart_char<LIG> const& c) {
			m_chaine.erase(pos, len);
			m_chaine.insert(pos, n, c);

			return *this;
		}

		asciiart_string& replace(const_iterator it1, const_iterator it2, size_type n, asciiart_char<LIG> const& c) {
			m_chaine.erase(it1, it2);
			m_chaine.insert(it1, n, c);

			return *this;
		}

		template<class InputIterator>
		asciiart_string& replace(const_iterator it1, const_iterator it2, InputIterator first, InputIterator last) {
			m_chaine.erase(it1, it2);
			m_chaine.insert(it1, first, last);

			return *this;
		}

		asciiart_string& replace(const_iterator it1, const_iterator it2, std::initializer_list<asciiart_char<LIG>> il) {
			m_chaine.erase(it1, it2);
			m_chaine.insert(it1, il);

			return *this;
		}

		void swap(asciiart_string& str) {
			m_chaine.swap(str.m_chaine);
		}

		void pop_back() {
			m_chaine.pop_back();
		}

		// - autres
		allocator_type get_allocator() const noexcept {
			return m_chaine.get_allocator();
		}

		asciiart_string substring(size_type pos = 0, size_type len = std::string::npos) const {
			return asciiart_string(*this, pos, len, get_allocator());
		}

		// - convertion
		std::string to_string() const {
			std::string str;

			for (asciiart_char<LIG> c : m_chaine) {
				str += c.to_char();
			}

			return str;
		}

		// - itérators
		iterator begin() noexcept { return m_chaine.begin(); }
		iterator end()   noexcept { return m_chaine.end(); }

		const_iterator begin() const noexcept { return m_chaine.begin(); }
		const_iterator end()   const noexcept { return m_chaine.end(); }

		const_iterator cbegin() const noexcept { return m_chaine.cbegin(); }
		const_iterator cend()   const noexcept { return m_chaine.cend(); }

		reverse_iterator rbegin() noexcept { return m_chaine.rbegin(); }
		reverse_iterator rend()   noexcept { return m_chaine.rend(); }

		const_reverse_iterator rbegin() const noexcept { return m_chaine.rbegin(); }
		const_reverse_iterator rend()   const noexcept { return m_chaine.rend(); }

		const_reverse_iterator crbegin() const noexcept { return m_chaine.crbegin(); }
		const_reverse_iterator crend()   const noexcept { return m_chaine.crend(); }

	private:
		// Attributs
		std::vector<asciiart_char<LIG>,Alloc> m_chaine;
};

// Stream
template<size_t LIG, class Stream>
class asciiart_stream {
	private:
		// Attribut
		Stream* m_flux;

	public:
		// Constructeur
		asciiart_stream(Stream* flux) : m_flux(flux) {}

		// Opérateurs
		asciiart_stream& operator << (asciiart_char<LIG> const& c) {
			*m_flux << manip::mouv(c.decalx(), 0);
			*m_flux << manip::sauve;

			for (unsigned i = 0; i < LIG; ++i) {
				std::string str = c.asciiart()[i];
				*m_flux << manip::mouv(LIG - i, i+1);

				for (char c : str) {
					if (c == ' ') {
						*m_flux << manip::mouv(1, 0);
					} else {
						*m_flux << c;
					}
				}

				*m_flux << manip::restore;

				if (i == LIG-1) {
					*m_flux << manip::mouv(1 + str.size(), 0);
				}
			}

			return *this;
		}

		template<class Traits, class Alloc>
		asciiart_stream& operator << (asciiart_string<LIG,Traits,Alloc> const& str) {
			for (asciiart_char<LIG> const& c : str) {
				(*this) << c;
			}

			return *this;
		}

		asciiart_stream& operator << (Stream& (*manip)(Stream&)) {
			if (manip == (Stream& (*)(Stream&)) std::endl) {
				*m_flux << std::endl << manip::mouv(0, LIG);
			}

			return *this;
		}

		asciiart_stream& operator << (EffLigneManip const& eff) {
			*m_flux << manip::sauve;

			for (unsigned i = 0; i < LIG; ++i) {
				*m_flux << eff << std::endl;
			}

			*m_flux << manip::restore;
			return *this;
		}

		asciiart_stream& operator << (CoordManip const& cm) {
			*m_flux << manip::coord(cm.x(), LIG*cm.y());
			return *this;
		}

		asciiart_stream& operator << (MouvManip const& mm) {
			*m_flux << manip::mouv(mm.dx(), LIG*mm.dy());
			return *this;
		}

		template<class MANIP>
		typename std::enable_if<std::is_base_of<BaseManip,MANIP>::value,asciiart_stream&>::type operator << (MANIP const& m) {
			*m_flux << m;
			return *this;
		}

		// Méthodes
		void flush() {
			m_flux->flush();
		}
};

template<size_t LIG, class Stream>
class asciiart_stream<LIG,posstream<Stream>> {
	private:
		// Attribut
		posstream<Stream> m_flux;

	public:
		// Constructeur
		asciiart_stream(Stream* flux, math::Point<unsigned,2> const& pt) : m_flux(flux, pt) {}
		asciiart_stream(Stream* flux, unsigned x, unsigned y) : m_flux(flux, x, y) {}

		// Opérateurs
		asciiart_stream& operator << (asciiart_char<LIG> const& c) {
			m_flux << manip::mouv(c.decalx(), 0);
			m_flux << manip::sauve;

			for (unsigned i = 0; i < LIG; ++i) {
				std::string str = c.asciiart()[i];
				m_flux << manip::mouv(LIG - i, i+1);

				for (char c : str) {
					if (c == ' ') {
						m_flux << manip::mouv(1, 0);
					} else {
						m_flux << c;
					}
				}

				m_flux << manip::restore;

				if (i == LIG-1) {
					m_flux << manip::mouv(1 + str.size(), 0);
				}
			}

			return *this;
		}

		template<class Traits, class Alloc>
		asciiart_stream& operator << (asciiart_string<LIG,Traits,Alloc> const& str) {
			for (asciiart_char<LIG> const& c : str) {
				(*this) << c;
			}

			return *this;
		}

		asciiart_stream& operator << (Stream& (*manip)(Stream&)) {
			if (manip == (Stream& (*)(Stream&)) std::endl) {
				m_flux << std::endl << manip::mouv(0, LIG);
			}

			return *this;
		}

		asciiart_stream& operator << (EffLigneManip const& eff) {
			m_flux << manip::sauve;

			for (unsigned i = 0; i < LIG; ++i) {
				m_flux << eff << std::endl;
			}

			m_flux << manip::restore;
			return *this;
		}

		asciiart_stream& operator << (CoordManip const& cm) {
			m_flux << manip::coord(cm.x(), LIG*cm.y());
			return *this;
		}

		asciiart_stream& operator << (MouvManip const& mm) {
			m_flux << manip::mouv(mm.dx(), LIG*mm.dy());
			return *this;
		}

		template<class MANIP>
		typename std::enable_if<std::is_base_of<BaseManip,MANIP>::value,asciiart_stream&>::type operator << (MANIP const& m) {
			m_flux << m;
			return *this;
		}

		// Méthodes
		CoordManip& coord() {
			return m_flux.coord();
		}

		void flush() {
			m_flux.flush();
		}

		void style(Style const& style) {
			m_flux.style(style);
		}
};

} // base

// Charactères
template<size_t LIG>
struct asciiart {
	// Alias
	using char_t = base::asciiart_char<LIG>;

	template<class Traits = std::char_traits<char_t>, class Alloc = std::allocator<char_t>>
	using basic_string = base::asciiart_string<LIG,Traits,Alloc>;
	using string = basic_string<>;

	template<class Stream>
	using stream = base::asciiart_stream<LIG,Stream>;
	using ostream = base::asciiart_stream<LIG,std::ostream>;

	template<class Stream>
	using posstream = base::asciiart_stream<LIG,posstream<Stream>>;

	// Caractères spéciaux
	static const char_t eof;
};

template<size_t LIG>
const typename asciiart<LIG>::char_t asciiart<LIG>::eof = asciiart<LIG>::char_t();

template<>
struct asciiart<8> {
	// Alias
	using char_t = base::asciiart_char<8>;

	template<class Traits = std::char_traits<char_t>, class Alloc = std::allocator<char_t>>
	using basic_string = base::asciiart_string<8,Traits,Alloc>;
	using string = basic_string<>;

	template<class Stream>
	using stream = base::asciiart_stream<8,Stream>;
	using ostream = base::asciiart_stream<8,std::ostream>;

	template<class Stream>
	using posstream = base::asciiart_stream<8,posstream<Stream>>;

	// Fonctions
	static char_t conv(char c); // renvoie espace si inconnu
	static string conv(std::string const& str);

	// Table
	static const std::map<char,char_t> TABLE;

	// Minuscules
	static const char_t a;
	static const char_t b;
	static const char_t c;
	static const char_t d;
	static const char_t e;
	static const char_t f;
	static const char_t g;
	static const char_t h;
	static const char_t i;
	static const char_t j;
	static const char_t k;
	static const char_t l;
	static const char_t m;
	static const char_t n;
	static const char_t o;
	static const char_t p;
	static const char_t q;
	static const char_t r;
	static const char_t s;
	static const char_t t;
	static const char_t u;
	static const char_t v;
	static const char_t w;
	static const char_t x;
	static const char_t y;
	static const char_t z;

	// Majuscules
	static const char_t A;
	static const char_t B;
	static const char_t C;
	static const char_t D;
	static const char_t E;
	static const char_t F;
	static const char_t G;
	static const char_t H;
	static const char_t I;
	static const char_t J;
	static const char_t K;
	static const char_t L;
	static const char_t M;
	static const char_t N;
	static const char_t O;
	static const char_t P;
	static const char_t Q;
	static const char_t R;
	static const char_t S;
	static const char_t T;
	static const char_t U;
	static const char_t V;
	static const char_t W;
	static const char_t X;
	static const char_t Y;
	static const char_t Z;

	// Caractères spéciaux
	static const char_t eof;
	static const char_t espace;
};

} // console

namespace std {

// char_traits
template<size_t LIG>
struct char_traits<typename console::base::asciiart_char<LIG>> : public char_traits<char> {
	// Alias
	using char_type = console::base::asciiart_char<LIG>;

	// Comparaison
	static bool eq(console::base::asciiart_char<LIG> const& c1, console::base::asciiart_char<LIG> const& c2) {
		return c1 == c2;
	}

	static bool lt(console::base::asciiart_char<LIG> const& c1, console::base::asciiart_char<LIG> const& c2) {
		return c1 < c2;
	}

	static int compare(console::base::asciiart_char<LIG> const* p, console::base::asciiart_char<LIG> const* q, size_t n) {
		while (n--) {
			if (!eq(*p, *q))
				return lt(*p, *q) ? -1 : 1;

			++p;
			++q;
		}

		return 0;
	}

	static constexpr bool eq_int_type(uint_least32_t x, uint_least32_t y) {
		return x == y;
	}

	// Longueur
	static size_t length(console::base::asciiart_char<LIG> const* c) {
		size_t i = 0;

		while (c[i] != console::base::asciiart_char<LIG>()) ++i;

		return i;
	}

	// Assignation
	static void assign(console::base::asciiart_char<LIG>& r, console::base::asciiart_char<LIG> const& c) {
		r = c;
	}

	static console::base::asciiart_char<LIG>* assign(console::base::asciiart_char<LIG>* p, size_t n, console::base::asciiart_char<LIG> const& c) {
		std::fill_n(p, n, c);
		return p;
	}

	// Recherche
	static console::base::asciiart_char<LIG> const* find(console::base::asciiart_char<LIG> const* p, size_t n, console::base::asciiart_char<LIG> const& c) {
		while (--n) {
			if (eq(*p, c))
				return p;

			++p;
		}

		return 0;
	}

	// Copie
	static console::base::asciiart_char<LIG>* move(console::base::asciiart_char<LIG>* dest, console::base::asciiart_char<LIG> const* src, size_t n) {
		for (size_t i = 0; i < n; ++i) {
			dest[i] = std::move(src[i]);
		}

		return dest;
	}

	static console::base::asciiart_char<LIG>* copy(console::base::asciiart_char<LIG>* dest, console::base::asciiart_char<LIG> const* src, size_t n) {
		for (size_t i = 0; i < n; ++i) {
			dest[i] = src[i];
		}

		return dest;
	}

	// EOF
	static constexpr int_type eof() {
		return 0;
	}

	static constexpr int_type not_eof(int_type c) {
		return c != eof() ? c : 1;
	}

	// Convertions
	static console::base::asciiart_char<LIG> to_char_type(int_type i) {
		if (i == eof()) {
			return console::asciiart<LIG>::eof();
		}

		return console::asciiart<LIG>::conv(
			char_traits<char>::to_char_type(i)
		);
	}

	static int_type to_int_type(console::base::asciiart_char<LIG> const& c) {
		return char_traits<char>::to_int_type(c.to_char());
	}
};

} // std

// Opérateurs externes
template<size_t LIG>
std::ostream& operator << (std::ostream& stream, console::base::asciiart_char<LIG> const& c) {
	return stream << c.to_char();
}

template<size_t LIG, class Traits, class Alloc>
std::ostream& operator << (std::ostream& stream, console::base::asciiart_string<LIG,Traits,Alloc> const& str) {
	return stream << str.to_string();
}
