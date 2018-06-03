// Importations
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>

#include "console/menu.hpp"
#include "terrain.hpp"

#include "module.hpp"

#include "math/coord.hpp"

#include "console/chars.hpp"
#include "console/console.hpp"
#include "console/manip.hpp"
#include "console/posstream.hpp"

// Namespaces
using namespace std::placeholders;

// Classe
class Module : public BaseModule {
	private:
		console::Menu m_menu;

	public:
		// Constructeur
		Module() : m_menu("Demineur") {
			// Module !
			m_menu.ajouter("Jouer (10x10)", std::bind(&Module::jouer<10,10,10>, this));
			m_menu.ajouter("Jouer (10x30)", std::bind(&Module::jouer<10,30,33>, this));
		}

		// Méthodes
		template<size_t LIG, size_t COL, unsigned MINES>
		void jouer() {
			// Initialisation
			bool continuer = true;
			Terrain<LIG,COL> terrain(MINES);
			math::Point<unsigned,2> perso({LIG/2, COL/2});
			console::posstream<std::ostream> stream_terrain(&std::cout, 5, 8);

			static const std::map<int,math::Vecteur<int,2>> DIRS = {
				{console::FL_HAUT,   math::Vecteur<int,2>({-1, 0})},
				{console::FL_BAS,    math::Vecteur<int,2>({ 1, 0})},
				{console::FL_GAUCHE, math::Vecteur<int,2>({0, -1})},
				{console::FL_DROITE, math::Vecteur<int,2>({0,  1})},
			};

			// Affichage
			m_menu.aff_entete();
			stream_terrain << console::manip::sauve;

			while (continuer) {
				stream_terrain << console::manip::restore;
				terrain.afficher(stream_terrain, perso);

				int c = console::getch();

				switch (c) {
					case console::FL_HAUT:
					case console::FL_BAS:
					case console::FL_GAUCHE:
					case console::FL_DROITE: {
						math::Vecteur<int,2> dir = DIRS.at(c);

						if (terrain.RECTANGLE.contient(perso + dir)) {
							perso += dir;
						}

						break;
					}

					case console::ENTREE:
						terrain.toucher(perso);
						break;

					case 'q':
					case 'Q':
						continuer = false;
						break;
				}
			}
		}

		// - accesseur
		virtual console::Menu& get_menu() override {
			return m_menu;
		}
};

MODULE_LOADER(Module);
