
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
	console::MenuChoix<std::string> menu("Framework");
	menu.ajouter("Démineur", "demineur");
	menu.ajouter("Othello", "othello");
	menu.afficher();

	if (menu.choix_valide()) {
		charger_module(modules, menu.recup_choix());
	}
}

// Main
int main() {
	Modules modules;

	console::Menu menu("Framework");
	menu.ajouter("Charger module", std::bind(&menu_modules, modules));
	menu.afficher();

	return 0;
}
