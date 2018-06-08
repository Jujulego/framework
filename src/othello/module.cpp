// Importations
#include <functional>

#include "othellier.hpp"
#include "pion.hpp"

#include "console.hpp"
#include "module.hpp"

// Classe
class Module : public BaseModule {
	private:
		// Attributs
		console::Menu m_menu;

	public:
		// Constructeur
		Module() : m_menu("Othello") {
			// Module !
			m_menu.ajouter("Jouer", std::bind(&Module::jouer, this));
		}

		// Méthodes
		void jouer() {
			// Initialisation
			console::posstream<std::ostream> stream_plateau(&std::cout, 5, 10);
			Othellier othellier;

			// Préparation affichage
			m_menu.aff_entete();
			stream_plateau << console::manip::sauve;

			do {
				// Afficher la carte
				stream_plateau << console::manip::restore;

				for (unsigned l = 0; l < othellier.nbLignes(); ++l) {
					for (int i = 0; i < 2; ++i) {
						for (unsigned c = 0; c < othellier.nbColonnes(); ++c) {
							switch (othellier[l][c].couleur()) {
							case Pion::NOIR:
								stream_plateau << console::style::fnoir;
								break;

							case Pion::BLANC:
								stream_plateau << console::style::fblanc;
								break;

							case Pion::VIDE:
								stream_plateau << console::style::fvert;
								break;
							}

							stream_plateau << "    " << console::style::defaut;
						}

						stream_plateau << std::endl;
					}
				}

			} while (console::getch() != console::ENTREE);

//			std::cout << console::manip::coord(0, 20) << std::endl;
//			std::cout << console::manip::clear;
		}

		// - accesseur
		virtual console::Menu& get_menu() override {
			return m_menu;
		}
};

MODULE_LOADER(Module);
