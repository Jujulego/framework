// Importations
#include <functional>
#include <iostream>

#include "console.hpp"
#include "modules.hpp"

// Fonctions
void charger_demineur(Modules& modules) {
	std::cout << std::endl;

	BaseModule* module = modules.charger("lib/libdemineur.so");
	module->get_menu().afficher();
}

// Main
int main() {
	Modules modules;

	console::Menu menu("Framework");
	menu.ajouter("Démineur", std::bind(&charger_demineur, modules));
	menu.afficher();

	return 0;
}
