#pragma once

// Importations
#include <algorithm>
#include <array>
#include <cstdint>
#include <ostream>
#include <string>

// Namespace
namespace console {

class Code {
	private:
		// Attributs
		union {
			char m_code[4];
			std::uint_least32_t m_int;
		};

	public:
		// Constructeurs
		constexpr Code() : m_int(0) {};
		constexpr Code(std::uint_least32_t code) : m_int(code) {};
		Code(char code[4]);

		// Opérateurs
		// - comparaison
		bool operator <  (Code const& code) const;
		bool operator <= (Code const& code) const;
		bool operator == (Code const& code) const;
		bool operator != (Code const& code) const;
		bool operator >= (Code const& code) const;
		bool operator >  (Code const& code) const;

		// Méthodes
		std::string str() const;

		// - accesseurs
		std::uint_least32_t& code();
		std::uint_least32_t const& code() const;
};

} // console

// Opérateurs externes
std::ostream& operator << (std::ostream& stream, console::Code const& code);

// Litteral
constexpr console::Code operator "" _code(unsigned long long code) {
	return console::Code(code);
}

// std !
namespace std {

template<>
struct char_traits<console::Code> : public char_traits<char> {
	// Alias
	using char_type = console::Code;
	using int_type  = uint_least32_t;

	// Comparaison
	static bool eq(console::Code const& c1, console::Code const& c2) {
		return c1 == c2;
	}

	static bool lt(console::Code const& c1, console::Code const& c2) {
		return c1 < c2;
	}

	static int compare(console::Code const* p, console::Code const* q, size_t n) {
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
	static size_t length(console::Code const* code) {
		size_t i = 0;

		while (code[i] != console::Code()) ++i;

		return i;
	}

	// Assignation
	static void assign(console::Code& r, console::Code const& c) {
		r = c;
	}

	static console::Code* assign(console::Code* p, size_t n, console::Code const& c) {
		std::fill_n(p, n, c);
		return p;
	}

	// Recherche
	static console::Code const* find(console::Code const* p, size_t n, console::Code const& c) {
		while (--n) {
			if (eq(*p, c))
				return p;

			++p;
		}

		return 0;
	}

	// Copie
	static console::Code* move(console::Code* dest, console::Code const* src, size_t n) {
		for (size_t i = 0; i < n; ++i) {
			dest[i] = std::move(src[i]);
		}

		return dest;
	}

	static console::Code* copy(console::Code* dest, console::Code const* src, size_t n) {
		for (size_t i = 0; i < n; ++i) {
			dest[i] = src[i];
		}

		return dest;
	}

	// EOF
	static constexpr uint_least32_t eof() {
		return 0;
	}

	static constexpr uint_least32_t not_eof(uint_least32_t c) {
		return c != eof() ? c : 1;
	}

	// Convertions
	static console::Code to_char_type(uint_least32_t c) {
		return console::Code(c);
	}

	static uint_least32_t to_int_type(console::Code const& c) {
		return c.code();
	}
};

}

namespace console {

// codestring
using codestring = std::basic_string<Code>;

}

// Opérateurs externes
std::ostream& operator << (std::ostream& stream, console::codestring const& cstr);

namespace console {

/**
 * Caractères utiles :
 * Le nom de certaines constantes indiquent l'orientation du caractère :
 *
 *   H       ex: TAB_DG
 * G   D             ^^
 *   B           Ici DG indique que le caractère va de Droite à Gauche
 */

#ifdef __gnu_linux__ // Pour Linux

// Tableau
static const Code TAB_HB   = 0xe29482_code;
static const Code TAB_DG   = 0xe29480_code;
static const Code TAB_HD   = 0xe295b0_code;
static const Code TAB_DB   = 0xe295ad_code;
static const Code TAB_BG   = 0xe295ae_code;
static const Code TAB_HG   = 0xe295af_code;
static const Code TAB_HDB  = 0xe2949c_code;
static const Code TAB_DBG  = 0xe294ac_code;
static const Code TAB_HBG  = 0xe294a4_code;
static const Code TAB_HGD  = 0xe294b4_code;
static const Code TAB_HDBG = 0xe294bc_code;

// Touches
static const int ENTREE    = '\n';
static const int FL_DROITE = 0x1b5b43;
static const int FL_GAUCHE = 0x1b5b44;
static const int FL_HAUT   = 0x1b5b41;
static const int FL_BAS    = 0x1b5b42;

#else // Pour Windows

// Tableau
static const Code TAB_HB   = 0xb3_code;
static const Code TAB_DG   = 0xc4_code;
static const Code TAB_HD   = 0xc0_code;
static const Code TAB_DB   = 0xda_code;
static const Code TAB_BG   = 0xbf_code;
static const Code TAB_HG   = 0xd9_code;
static const Code TAB_HDB  = 0xc3_code;
static const Code TAB_DBG  = 0xc2_code;
static const Code TAB_HBG  = 0xb4_code;
static const Code TAB_HGD  = 0xc1_code;
static const Code TAB_HDBG = 0xc5_code;

// Touches
static const int ENTREE    = '\r';
static const int FL_DROITE = 0xe04d;
static const int FL_GAUCHE = 0xe04b;
static const int FL_HAUT   = 0xe048;
static const int FL_BAS    = 0xe050;

#endif

} // console
