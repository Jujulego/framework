#pragma once

// Importations
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "math/forme.hpp"

#include "asciiart.hpp"
#include "chars.hpp"
#include "console.hpp"
#include "manip.hpp"
#include "style.hpp"

namespace console {

// Classe de base
class BaseMenu {
	protected:
		// Attributs
		asciiart<8>::string m_entete;
		std::string m_quitter;

	public:
		// Constructeur
		BaseMenu(std::string const& entete, std::string const& quitter = "Quitter");

		// Destructeur
		virtual ~BaseMenu() = default;

		// Méthodes
		void aff_entete() const;
		virtual void afficher() = 0;
};

// Menu à callbacks
class Menu : public BaseMenu {
	private:
		// Attributs
		std::vector<std::tuple<std::string,std::function<void()>>> m_entrees;

	public:
		// Constructeur
		Menu(std::string const& entete, std::string const& quitter = "Quitter");

		// Méthodes
		virtual void afficher() override;
		void ajouter(std::string const& texte, std::function<void()> const& callback);
};

// Menu à choix
template<class VAL>
class MenuChoix : public BaseMenu {
	private:
		// Attributs
		size_t m_largmax;
		unsigned m_choix;
		std::vector<std::tuple<std::string,VAL>> m_propositions;

	public:
		// Constructeur
		MenuChoix(std::string const& entete, std::string const& quitter = "Quitter")
			: BaseMenu(entete, quitter), m_largmax(std::max(quitter.size(), 7ul)) {}

		// Méthodes
		virtual void afficher() override {
			// Initialisation
			bool continuer = true;
			unsigned page = 0;
			math::Point<unsigned,2> pos;

		refresh:
			// Préparation pagination
			math::Rectangle<size_t> terminal(m_entete.screen_size(), taille_terminal().ty());
			math::Rectangle<size_t> espace(
				math::Point<size_t,2>({5, 10}),
				terminal.vecteur() - math::Vecteur<size_t,2>({10, 15})
			);

			size_t nbcol  = espace.tx() / (m_largmax + 2);
			size_t nbitem = std::min(nbcol * espace.ty(), m_propositions.size());
			size_t nblig  = nbitem / nbcol;
			size_t nbderlig = nbitem - nblig * nbcol;
			size_t nbpage = (m_propositions.size() / nbitem) + 1;
			page = 0;

			std::cout << terminal.ty() << std::endl;
			std::cout << m_propositions.size() << " " << nbitem << " " << nbpage << " " << nblig << std::endl;

			CoordManip base(5 + (espace.tx() - nbcol * (m_largmax + 2)) / 2, 10);
			CoordManip fin (0, nblig + 13);

			const auto aff = [&] (unsigned c, unsigned l) -> void {
				std::cout << base + manip::mouv(c * (m_largmax + 2), l);
				std::string texte;

				if (pos[0] == c && pos[1] == l) {
					std::cout << style::inverse;
				}

				if (l > nblig) {
					std::cout << (c * espace.tx() / 4) * manip::dx;

					switch (c) {
					case 0:
						if (page == 0) return;
						std::cout << -3 * manip::dx;
						texte = "<< Prev";
						break;

					case 1:
						texte = m_quitter;
						std::cout << -(m_quitter.size() / 2) * manip::dx << style::rouge;
						break;

					case 2:
						if (page == nbpage-1) return;
						std::cout << -4 * manip::dx;
						texte = "Suiv >>";
						break;
					}
				} else {
					texte = std::get<0>(m_propositions[c + l * nbcol]);
				}

				std::cout << " " << texte << " " << style::defaut;
			};

			// Entete
			aff_entete();

			// Entrées
			for (unsigned l = 0; l < nblig; ++l) {
				for (unsigned c = 0; c < nbcol; ++c) {
					aff(c, l);
				}
			}

			for (unsigned c = 0; c < nbderlig; ++c) {
				aff(c, nblig);
			}

			for (unsigned c = 0; c < 3; ++c) {
				aff(c, nblig + (nbderlig == 0 ? 1 : 2));
			}

			while (continuer) {
				std::cout << fin;

				// Entrée !!!
				switch (getch()) {
					case FL_BAS:
						if (pos[1] < (nbderlig == 0 ? nblig-1 : nblig)) {
							auto opos = pos;
							pos += math::Vecteur<int,2>({0, 1});

							if (pos[1] == nblig && pos[0] >= nbderlig) {
								pos[0] = nbderlig-1;
							}

							aff(pos[0], pos[1]);
							aff(opos[0], opos[1]);
						} else {
							std::cout << manip::buzz;
						}

						break;

					case FL_HAUT:
						if (pos[1] > 0) {
							auto opos = pos;
							pos += math::Vecteur<int,2>({0, -1});

							aff(pos[0], pos[1]);
							aff(opos[0], opos[1]);
						} else {
							std::cout << manip::buzz;
						}

						break;

					case FL_DROITE:
						if (pos[0] < (pos[1] == nblig ? nbderlig : nbcol) -1) {
							auto opos = pos;
							pos += math::Vecteur<int,2>({1, 0});

							aff(pos[0], pos[1]);
							aff(opos[0], opos[1]);
						} else {
							std::cout << manip::buzz;
						}

						break;

					case FL_GAUCHE:
						if (pos[0] > 0) {
							auto opos = pos;
							pos += math::Vecteur<int,2>({-1, 0});

							aff(pos[0], pos[1]);
							aff(opos[0], opos[1]);
						} else {
							std::cout << manip::buzz;
						}

						break;

					case 'r':
					case 'R':
						goto refresh;
				}
			}
		}

		void ajouter(std::string const& texte, VAL const& valeur) {
			// Ajout
			m_propositions.push_back(std::make_tuple(texte, valeur));

			// Mise à jour du maximum
			if (texte.size() >= m_largmax) {
				m_largmax = texte.size();
			}
		}

		void modifier(std::string const& texte, VAL const& nv) {
			// Changement
			for (std::tuple<std::string,VAL>& p : m_propositions) {
				if (std::get<0>(p) == texte) {
					std::get<1>(p) = nv;
				}
			}
		}

		VAL enlever(std::string const& texte) {
			// Suppression
			auto it = m_propositions.find(texte);
			if (it == m_propositions.end()) {
				return;
			}

			VAL ov = it->second;
			m_propositions.erase(it);

			if (texte.size() == m_largmax) {
				m_largmax = std::max(m_quitter.size(), 7ul);

				for (std::tuple<std::string,VAL> p : m_propositions) {
					if (std::get<0>(p).size() > m_largmax) {
						m_largmax = std::get<0>(p).size();
					}
				}
			}

			return ov;
		}

		VAL recup_choix() const {
			return std::get<1>(m_propositions[m_choix]);
		}
};

} // console
