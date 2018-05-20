// Importations
#include <dlfcn.h>

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
	void* shared_library = dlopen(nom.c_str(), RTLD_LAZY);
	BaseModule* (*loader)() = reinterpret_cast<BaseModule* (*)()>(dlsym(shared_library, "loader"));

	BaseModule* module = loader();
	m_modules[nom] = module;

	return module;
}
