#pragma once

// Importations
#include <map>
#include <string>

#include "module.hpp"

// Classe
class Modules {
	private:
		// Attributs
		std::map<std::string,BaseModule*> m_modules;

	public:
		// Méthodes
		BaseModule* charger(std::string const& nom);
};
