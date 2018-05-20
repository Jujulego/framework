// Importations
#include <ostream>
#include <string>

#include "math/coord.hpp"
#include "manip.hpp"

#ifndef __gnu_linux__
# include <windows.h>
#endif

// Namespaces
using namespace console;

// Opérateur externe
std::ostream& operator << (std::ostream& stream, BaseManip const& manip) {
	return manip.appliquer(stream);
}

// ------------- ClearManip ------------
// Méthodes
std::ostream& ClearManip::appliquer(std::ostream& stream) const {
#ifdef __gnu_linux__
	return stream << "\x1b[2J";
#else
	system("cls");
	return stream;
#endif
}

// ------------- CoordManip ------------
// Constructeur
CoordManip::CoordManip(math::Point<unsigned,2> const& pt) : m_point(pt) {}
CoordManip::CoordManip(unsigned x, unsigned y)              : m_point({x, y}) {}

// Opérateurs
CoordManip  CoordManip::operator +  ()                         const { return CoordManip(+m_point); }
CoordManip  CoordManip::operator -  ()                         const { return CoordManip(-m_point); }
CoordManip  CoordManip::operator +  (math::Vecteur<int,2> const& v) const { return CoordManip(m_point + v); }
CoordManip  CoordManip::operator -  (math::Vecteur<int,2> const& v) const { return CoordManip(m_point - v); }
CoordManip& CoordManip::operator += (math::Vecteur<int,2> const& v)       { m_point += v; return *this; }
CoordManip& CoordManip::operator -= (math::Vecteur<int,2> const& v)       { m_point -= v; return *this; }
CoordManip  CoordManip::operator +  (MouvManip const& mm) const { return CoordManip(m_point + mm.vecteur()); }
CoordManip  CoordManip::operator -  (MouvManip const& mm) const { return CoordManip(m_point - mm.vecteur()); }
CoordManip& CoordManip::operator += (MouvManip const& mm)       { m_point += mm.vecteur(); return *this; }
CoordManip& CoordManip::operator -= (MouvManip const& mm)       { m_point -= mm.vecteur(); return *this; }

// Méthodes
std::ostream& CoordManip::appliquer(std::ostream& stream) const {
#ifdef __gnu_linux__
	return stream << "\x1b[" << y()+1 << ";" << x()+1 << "H";
#else
	COORD coord;
    coord.X = x();
    coord.Y = y();

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return stream;
#endif
}

math::Point<unsigned,2>& CoordManip::point() {
	return m_point;
}

math::Point<unsigned,2> const& CoordManip::point() const {
	return m_point;
}

unsigned& CoordManip::x() {
	return m_point[0];
}

unsigned const& CoordManip::x() const {
	return m_point[0];
}

unsigned& CoordManip::y() {
	return m_point[1];
}

unsigned const& CoordManip::y() const {
	return m_point[1];
}

// ------------- MouvManip -------------
// Constructeur
MouvManip::MouvManip(math::Vecteur<int,2> const& v) : m_vecteur(v) {}
MouvManip::MouvManip(int dx, int dy) : m_vecteur({dx, dy}) {}

// Opérateurs
MouvManip  MouvManip::operator +  () const { return MouvManip(+m_vecteur); }
MouvManip  MouvManip::operator -  () const { return MouvManip(-m_vecteur); }

MouvManip  MouvManip::operator +  (math::Vecteur<int,2> const& v) const { return MouvManip(m_vecteur + v); }
MouvManip  MouvManip::operator -  (math::Vecteur<int,2> const& v) const { return MouvManip(m_vecteur + v); }
MouvManip& MouvManip::operator += (math::Vecteur<int,2> const& v)       { m_vecteur += v; return *this; }
MouvManip& MouvManip::operator -= (math::Vecteur<int,2> const& v)       { m_vecteur += v; return *this; }

MouvManip  MouvManip::operator +  (MouvManip const& mm) const { return MouvManip(m_vecteur + mm.m_vecteur); }
MouvManip  MouvManip::operator -  (MouvManip const& mm) const { return MouvManip(m_vecteur + mm.m_vecteur); }
MouvManip& MouvManip::operator += (MouvManip const& mm)       { m_vecteur += mm.m_vecteur; return *this; }
MouvManip& MouvManip::operator -= (MouvManip const& mm)       { m_vecteur += mm.m_vecteur; return *this; }

MouvManip  MouvManip::operator *  (int k) const { return MouvManip(m_vecteur * k); }
MouvManip  MouvManip::operator /  (int k) const { return MouvManip(m_vecteur / k); }
MouvManip& MouvManip::operator *= (int k)       { m_vecteur *= k; return *this; }
MouvManip& MouvManip::operator /= (int k)       { m_vecteur /= k; return *this; }

// Méthodes
std::ostream& MouvManip::appliquer(std::ostream& stream) const {
#ifdef __gnu_linux__
	// Verticalement
	if (dy() < 0) stream << "\x1b[" << (-dy()) << "A";
	if (dy() > 0) stream << "\x1b[" <<   dy()  << "B";

	if (dx() < 0) stream << "\x1b[" << (-dx()) << "D";
	if (dx() > 0) stream << "\x1b[" <<   dx()  << "C";
#else
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(h, &csbi);

	COORD coord = csbi.dwCursorPosition;
    coord.X += dx();
    coord.Y += dy();

	SetConsoleCursorPosition(h, coord);
#endif
	return stream;
}

math::Vecteur<int,2>& MouvManip::vecteur() {
	return m_vecteur;
}

math::Vecteur<int,2> const& MouvManip::vecteur() const {
	return m_vecteur;
}

int& MouvManip::dx() {
	return m_vecteur[0];
}

int const& MouvManip::dx() const {
	return m_vecteur[0];
}

int& MouvManip::dy() {
	return m_vecteur[1];
}

int const& MouvManip::dy() const {
	return m_vecteur[1];
}

// Opérateurs externes
MouvManip operator * (int const& k, MouvManip const& mm) { return mm * k; }

// ----------- EffLigneManip -----------
// Méthodes
std::ostream& EffLigneManip::appliquer(std::ostream& stream) const {
#ifdef __gnu_linux__
	return stream << "\x1b[2K";
#else
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(h, &csbi);

	COORD coord = csbi.dwCursorPosition;
    coord.X = 0;

	SetConsoleCursorPosition(h, coord);

	for (int i = 0; i < csbi.srWindow.Right; ++i)
		stream << ' ';

	SetConsoleCursorPosition(h, csbi.dwCursorPosition);
	return stream;
#endif
}

#ifndef __gnu_linux__
static COORD curseur_coord;
#endif

// ------------ SauveManip -------------
// Méthodes
std::ostream& SauveManip::appliquer(std::ostream& stream) const {
#ifdef __gnu_linux__
	return stream << "\x1b[s";
#else
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	curseur_coord = csbi.dwCursorPosition;

	return stream;
#endif
}

// ----------- RestoreManip ------------
// Méthodes
std::ostream& RestoreManip::appliquer(std::ostream& stream) const {
#ifdef __gnu_linux__
	return stream << "\x1b[u";
#else
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), curseur_coord);

	return stream;
#endif
}

// ------------- BuzzManip -------------
// Méthodes
std::ostream& BuzzManip::appliquer(std::ostream& stream) const {
#ifdef __gnu_linux__
	return stream << "\a";
#else
    Beep(150, 300);
	return stream;
#endif
}
