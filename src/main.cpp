// Importations
#include <functional>
#include <iostream>

#include "console.hpp"
#include "modules.hpp"

#include "meta.hpp"

// Tests
using liste = meta::vpush_front<meta::vliste<size_t,1,2,3>,4>::type;
static_assert(meta::taille<liste>::value == 4, "Booum !");

template<class V>
struct identite {
	// Alias
	using type = V;
};

static_assert(meta::for_each<liste,identite,meta::add_>::type::value == 10, "Cool !");

// Fonctions
void charger_demineur(Modules& modules) {
	std::cout << std::endl;

	BaseModule* module = modules.charger("demineur");
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
