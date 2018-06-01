#pragma once

// Importations
#include <array>
#include <chrono>
#include <functional>
#include <ostream>
#include <random>

#include "math.hpp"
#include "meta/algo.hpp"

#include "console/chars.hpp"
#include "console/style.hpp"

// Classe
template<size_t LIG, size_t COL>
class Terrain {
	private:
		// Attributs
		unsigned m_nbMines = 0;
		math::Matrice<int,LIG,COL> m_mines;
		math::Matrice<int,LIG,COL> m_marques;

	public:
		// Constantes
		static const std::array<math::Vecteur<int,2>,8> DIRECTIONS;
		static const math::Rectangle<unsigned> RECTANGLE;

		// Constructeur
		Terrain(unsigned nbMines) {
			// Initialisation générateur aléatoire
			std::hash<math::Point<unsigned,2>> hash(meta::max<size_t,LIG,COL>::value);
			auto generateur = std::bind(std::uniform_int_distribution<int>(0, LIG*COL-1), std::mt19937(std::chrono::system_clock::now().time_since_epoch().count()));

			// Positionnement des mines
			while (m_nbMines < nbMines) {
				math::Point<unsigned,2> pt = unhash(hash, generateur());

				if (RECTANGLE.contient(pt) && m_mines[pt] >= 0) {
					// Pose de la mine
					m_mines[pt] = -1;
					++m_nbMines;

					// Indices
					for (auto v : DIRECTIONS) {
						auto npt = pt + v;

						if (RECTANGLE.contient(npt) && m_mines[npt] != -1) ++m_mines[npt];
					}
				}
			}
		}

		// Méthodes
		template<class Stream>
		void afficher(Stream& stream, math::Point<unsigned,2> const& curseur, bool indices = true) {
			// Ligne supérieure
			stream << console::TAB_DB << console::TAB_DG;
			for (unsigned c = 0; c < COL; ++c)
				stream << console::TAB_DG << console::TAB_DG;

			stream << console::TAB_DG << console::TAB_BG << std::endl;

			// Constenu
			for (unsigned l = 0; l < LIG; ++l) {
				stream << console::TAB_HB << " ";

				for (unsigned c = 0; c < COL; ++c) {
					math::Point<unsigned,2> pt({l, c});

					int val = m_mines[pt];
					int marque = m_marques[pt];

					// Affichage de la case
					if (marque) {
						if (pt == curseur) {
							stream << console::style::inverse << console::style::fbleu;
						}

						if (val == -1) {
							stream << console::style::rouge << "x";
						} else if (indices && val > 0) {
							if (val < 3)      stream << console::style::vert;
							else if (val < 6) stream << console::style::jaune;
							else              stream << console::style::violet;

							stream << val;
						} else {
							stream << " ";
						}
					} else {
						if (pt == curseur) {
							stream << console::style::bleu;
						}

						stream << console::style::inverse << " ";
					}

					stream << " " << console::style::defaut;
				}

				stream << " " << console::TAB_HB << std::endl;
			}

			// Ligne inférieure
			stream << console::TAB_HD << console::TAB_DG;
			for (unsigned c = 0; c < COL; ++c)
				stream << console::TAB_DG << console::TAB_DG;

			stream << console::TAB_DG << console::TAB_HG << std::endl;
		}

		bool toucher(math::Point<unsigned,2> const& pt) {
			m_marques[pt] = 1;

			if (m_mines[pt] == 0) {
				for (auto dir : DIRECTIONS) {
					auto npt = pt + dir;

					if (RECTANGLE.contient(npt) && m_marques[npt] == 0) {
						toucher(npt);
					}
				}
			}

			return m_mines[pt] == -1;
		}
};

// Constantes
template<size_t LIG, size_t COL>
const std::array<math::Vecteur<int,2>,8> Terrain<LIG,COL>::DIRECTIONS = {
	math::Vecteur<int,2>({ 1,  0}), // Droite
	math::Vecteur<int,2>({ 1,  1}),
	math::Vecteur<int,2>({ 0,  1}), // Bas
	math::Vecteur<int,2>({-1,  1}),
	math::Vecteur<int,2>({-1,  0}), // Gauche
	math::Vecteur<int,2>({-1, -1}),
	math::Vecteur<int,2>({ 0, -1}), // Haut
	math::Vecteur<int,2>({ 1, -1})
};

template<size_t LIG, size_t COL>
const math::Rectangle<unsigned> Terrain<LIG,COL>::RECTANGLE = math::Rectangle<unsigned>(LIG, COL);
