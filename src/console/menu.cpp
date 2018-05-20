// Importations
#include <functional>
#include <iostream>
#include <string>
#include <tuple>

#include "math/coord.hpp"

#include "chars.hpp"
#include "console.hpp"
#include "manip.hpp"
#include "menu.hpp"
#include "style.hpp"

// Namespaces
using namespace console;

// Constructeur
Menu::Menu(std::string const& entete) : Menu(entete, "Quitter") {}
Menu::Menu(std::string const& entete, std::string const& quitter)
	: m_entete(entete), m_quitter(quitter) {}

// Méthodes statiques
void Menu::aff_entete() const {
	std::cout << manip::clear;
	std::cout << "         _____" << std::endl;
	std::cout << "        / ___ \\                     __" << std::endl;
	std::cout << "       / /  / / ___    ________    /_/ ____    ___    __  __  ____" << std::endl;
	std::cout << "      / /  / / / _ \\  / __  __ \\  __  / __ \\  / _ \\  / / / / / __ \\" << std::endl;
	std::cout << "     / /__/ / /  __/ / / / / / / / / / / / / /  __/ / /_/ / / / /_/" << std::endl;
	std::cout << "    /______/  \\___/ /_/ /_/ /_/ /_/ /_/ /_/  \\___/ /_____/ /_/" << std::endl;
	std::cout << std::endl;
}

// Méthodes
void Menu::afficher() const {
	// Initialisation
	unsigned item  = 0;
	bool continuer = true;
	CoordManip base(38, 8);
	CoordManip fin(  0, 9 + m_entrees.size());

	// Lambda
	static const auto aff = [&] (unsigned i) -> void {
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
				}

				break;

			case FL_HAUT:
				if (item != 0) {
					--item;

					aff(item);
					aff(item+1);
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
