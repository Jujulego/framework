#pragma once

// Importations
#include <string>

// Namespace
namespace console {

/**
 * Caractères utiles :
 * Le nom de certaines constantes indiquent l'orientation du caractère :
 *
 *   H       ex: TAB_DG
 * G   D             ^^
 *   B           Ici DG indique que le caractère va de Droite à Gauche
 */

#ifdef __gnu_linux__ // Pour Linux

// Tableau
static const std::string TAB_HB   = "\xe2\x9";
static const std::string TAB_DG   = "\xe2\x9";
static const std::string TAB_HD   = "\xe2\x9";
static const std::string TAB_DB   = "\xe2\x9";
static const std::string TAB_BG   = "\xe2\x9";
static const std::string TAB_GH   = "\xe2\x9";
static const std::string TAB_HDB  = "\xe2\x9";
static const std::string TAB_DBG  = "\xe2\x9";
static const std::string TAB_BGH  = "\xe2\x9";
static const std::string TAB_GHD  = "\xe2\x9";
static const std::string TAB_HDBG = "\xe2\x9";

// Touches
static const int ENTREE    = '\n';
static const int FL_DROITE = 1792835;
static const int FL_GAUCHE = 1792836;
static const int FL_HAUT   = 1792833;
static const int FL_BAS    = 1792834;

#else // Pour Windows

// Tableau
static const std::string TAB_HB   = "\xb3";
static const std::string TAB_DG   = "\xc4";
static const std::string TAB_HD   = "\xc0";
static const std::string TAB_DB   = "\xda";
static const std::string TAB_BG   = "\xbf";
static const std::string TAB_GH   = "\xd9";
static const std::string TAB_HDB  = "\xc3";
static const std::string TAB_DBG  = "\xc2";
static const std::string TAB_BGH  = "\xb4";
static const std::string TAB_GHD  = "\xc1";
static const std::string TAB_HDBG = "\xc5";

// Touches
static const int ENTREE    = '\r';
static const int FL_DROITE = 57421;
static const int FL_GAUCHE = 57419;
static const int FL_HAUT   = 57416;
static const int FL_BAS    = 57424;

#endif

} // console
