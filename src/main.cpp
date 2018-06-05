
// Importations
#include <functional>
#include <iostream>
#include <string>

#include "console.hpp"
#include "modules.hpp"

// Fonctions
void charger_module(Modules& modules, std::string const& nom) {
	std::cout << std::endl;

	BaseModule* module = modules.charger(nom);
	module->get_menu().afficher();
}

// Lister les modules
void menu_modules(Modules& modules) {
	// Initialisation menu
}

// Main
int main() {
/*	Modules modules;

	console::Menu menu("Framework");
	menu.ajouter("Démineur", std::bind(&charger_module, modules, "demineur"));
	menu.afficher();*/

	console::MenuChoix<int> menu("Framework");
	for (int i = 0; i < 100; ++i) {
		menu.ajouter("n°" + std::to_string(i), i);
	}
	menu.afficher();

	if (menu.choix_valide()) {
		std::cout << menu.recup_choix() << std::endl;
	} else {
		std::cout << ":(" << std::endl;
	}

	return 0;
}
