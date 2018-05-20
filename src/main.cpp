// Importations
#include <iomanip>
#include <iostream>

#include "console.hpp"

// Main
int main() {
	console::asciiart<8>::posstream<std::ostream> aasout(&std::cout, 0, 0);

	std::cout << console::manip::clear << console::manip::mouv(0, 10);
	std::cout << "Cool !" << std::endl;

	aasout << console::style::bleu << console::style::gras << console::asciiart<8>::conv("framework") << console::style::defaut;// << std::endl;
	aasout << std::endl;

	return 0;
}
