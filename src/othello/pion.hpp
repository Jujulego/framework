#pragma once

// Classe
class Pion {
	public:
		// Enumérations
		enum Couleur { VIDE, BLANC, NOIR };

		// Constructeur
		Pion(Couleur couleur = VIDE);

		// Méthodes
		void changer();
		bool vide() const;
		bool ami(Pion const& pion) const;
		bool ennemi(Pion const& pion) const;

		// - accesseurs
		Couleur& couleur();
		Couleur const& couleur() const;

	private:
		// Attributs
		Couleur m_couleur = VIDE;
};
