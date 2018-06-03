// Importations
#include <functional>
#include <iostream>
#include <string>
#include <tuple>

#include "math/coord.hpp"

#include "asciiart.hpp"
#include "chars.hpp"
#include "console.hpp"
#include "manip.hpp"
#include "menu.hpp"
#include "style.hpp"

// Namespaces
using namespace console;

// BaseMenu
// Constructeur
BaseMenu::BaseMenu(std::string const& entete, std::string const& quitter)
	: m_entete(asciiart<8>::conv(entete)), m_quitter(quitter) {}

// Méthodes
void BaseMenu::aff_entete() const {
	asciiart<8>::ostream aas(&std::cout);
	aas << manip::clear << m_entete << std::endl;
}

// Menu
// Constructeur
Menu::Menu(std::string const& entete, std::string const& quitter)
	: BaseMenu(entete, quitter) {}

// Méthodes
void Menu::afficher() {
	// Initialisation
	unsigned item  = 0;
	bool continuer = true;
	CoordManip base(m_entete.screen_size()/2, 10);
	CoordManip fin(  0, 11 + m_entrees.size());

	// Lambda
	const auto aff = [&] (unsigned i) -> void {
		std::string texte;

		if (i == m_entrees.size()) {
			std::cout << style::rouge;
			texte = "Quitter";
		} else {
			texte = std::get<0>(m_entrees[i]);
		}

		if (i == item) std::cout << style::inverse;
		std::cout << base + manip::mouv(-1 -texte.size()/2, i) << " " << texte << " " << style::defaut;
	};

refresh:
	// Entetes
	aff_entete();

	// Entrées
	for (unsigned i = 0; i <= m_entrees.size(); ++i) {
		aff(i);
	}

	// Boucle
	while (continuer) {
		// Entrée !!!
		switch (getch()) {
			case FL_BAS:
				if (item != m_entrees.size()) {
					++item;

					aff(item);
					aff(item-1);
				} else {
					std::cout << manip::buzz;
				}

				break;

			case FL_HAUT:
				if (item != 0) {
					--item;

					aff(item);
					aff(item+1);
				} else {
					std::cout << manip::buzz;
				}

				break;

			case ENTREE:
				if (item == m_entrees.size()) {
					continuer = false;
					break;
				} else {
					std::get<1>(m_entrees[item])();
				}

			case 'r':
			case 'R':
				goto refresh;
		}

		// Position du curseur
		std::cout << fin;
	}
}

void Menu::ajouter(std::string const& texte, std::function<void()> const& callback) {
	m_entrees.push_back(std::make_tuple(texte, callback));
}
