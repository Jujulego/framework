// Importations
#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>

#include "chars.hpp"

// Namespace
using namespace console;

// Constructeurs
Code::Code(char code[4]) {
	std::move(code, code+4, m_code);
}

// Opérateurs
// - comparaison
bool Code::operator <  (Code const& code) const {
	return m_int < code.m_int;
}

bool Code::operator <= (Code const& code) const {
	return m_int <= code.m_int;
}

bool Code::operator == (Code const& code) const {
	return m_int == code.m_int;
}

bool Code::operator != (Code const& code) const {
	return m_int != code.m_int;
}

bool Code::operator >= (Code const& code) const {
	return m_int >= code.m_int;
}

bool Code::operator >  (Code const& code) const {
	return m_int > code.m_int;
}

// Méthodes
std::string Code::str() const {
	std::string txt;

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	for (char const* c = m_code; c != c + 4; ++c) {
		if (*c == 0) break;

		txt.insert(txt.begin(), *c);
	}
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	for (char c : m_code) {
		if (c != 0) txt += c;
	}
#elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
	for (char const* c = m_code; c != c + 4; c += 2) {
		if (*c == 0 && *(c+1) == 0) break;

		txt.insert(txt.begin(), *(c+1));
		txt.insert(txt.begin(), *c);
	}
#else
# error Ordre de mots binaire non géré
#endif

	return txt;
}

// - accesseurs
std::uint_least32_t& Code::code() {
	return m_int;
}

std::uint_least32_t const& Code::code() const {
	return m_int;
}

// Opérateurs externes
std::ostream& operator << (std::ostream& stream, Code const& code) {
	return stream << code.str();
}

std::ostream& operator << (std::ostream& stream, codestring const& cstr) {
	for (Code c : cstr) {
		stream << c;
	}

	return stream;
}
