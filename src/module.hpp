#pragma once

// Importations
#include "console/menu.hpp"

// Classe
class BaseModule {
	public:
		// Destructeur
		virtual ~BaseModule() = default;

		// Méthodes
		virtual console::Menu const& get_menu() const = 0;
};

// Macro
#define MODULE_LOADER(cls) extern "C" BaseModule* loader() { return new cls(); }
