#pragma once

// Importations
#include <functional>
#include <string>
#include <tuple>
#include <vector>

namespace console {

// Classe
class Menu {
	private:
		// Attributs
		std::string m_entete;
		std::string m_quitter;
		std::vector<std::tuple<std::string,std::function<void()>>> m_entrees;

	public:
		// Constructeur
		Menu(std::string const& entete);
		Menu(std::string const& entete, std::string const& quitter);

		// Méthodes
		void aff_entete() const;
		void afficher() const;
		void ajouter(std::string const& texte, std::function<void()> const& callback);
};

} // console
