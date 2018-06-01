// Importations
#ifdef __gnu_linux__
# include <dlfcn.h>
#else
# include <windows.h>
#endif

#include <map>
#include <string>

#include "module.hpp"
#include "modules.hpp"

// Méthodes
BaseModule* Modules::charger(std::string const& nom) {
	// Check chargé ?
	auto it = m_modules.find(nom);
	if (it != m_modules.end()) {
		return it->second;
	}

	// Chargement du module
#ifdef __gnu_linux__
	void* shared_library = dlopen((nom + ".so").c_str(), RTLD_LAZY);
	BaseModule* (*loader)() = reinterpret_cast<BaseModule* (*)()>(dlsym(shared_library, "loader"));
#else
	HINSTANCE shared_library = LoadLibrary((nom + ".dll").c_str());
	BaseModule* (*loader)() = reinterpret_cast<BaseModule* (*)()>(GetProcAddress(shared_library, "loader"));
#endif

	BaseModule* module = loader();
	m_modules[nom] = module;

	return module;
}
