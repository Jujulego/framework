#pragma once

// Dépendances
#include <mutex>

#include "math/forme.hpp"

// Classe
namespace console {

// Prototypes
void gotoLigCol(int lig, int col);
void clear();
int kbhit();
int getch(bool bloc = true);

math::Rectangle<size_t> taille_terminal();

std::unique_lock<std::mutex> lock();

} // console
