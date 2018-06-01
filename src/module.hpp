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
#ifdef __gnu_linux__
# define MODULE_LOADER(cls) extern "C" BaseModule* loader() { return new cls(); }
#else
#include <windows.h>
# define MODULE_LOADER(cls) extern "C" BaseModule* __declspec(dllexport) __stdcall loader() { return new cls(); }
#endif
