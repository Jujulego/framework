// Importations
#include <string>

#include "asciiart.hpp"

// Namespaces
using namespace console;

// Fonctions
asciiart<8>::char_t asciiart<8>::conv(char c) {
	auto it = TABLE.find(c);

	if (it != TABLE.end()) {
		return it->second;
	}

	return espace;
}

asciiart<8>::string asciiart<8>::conv(std::string const& str) {
	string aastr;

	for (char c : str) {
		aastr += conv(c);
	}

	return aastr;
}

// Charactères
// - minuscules
const asciiart<8>::char_t asciiart<8>::a = asciiart<8>::char_t('a', true, {"     ", "     ", "___  ", "___ \\", "/ _  /", " \\___/", "      ", "      "});
const asciiart<8>::char_t asciiart<8>::b = asciiart<8>::char_t('b', true, {"__     ", "/ /    ", "/ /_   ", "/ __ \\ ", "/ /_/ /", " \\____/", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::c = asciiart<8>::char_t('c', {"     ", "     ", "_____ ", "/ ___/", "/ /__ ", " \\___/", "      ", "      "});
const asciiart<8>::char_t asciiart<8>::d = asciiart<8>::char_t('d', {"    __ ", "    / /", "____/ /", "/ __  /", "/ /_/ /", " \\____/", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::e = asciiart<8>::char_t('e', true, {"      ", "      ", "___   ", "/ _ \\ ", "/  __/", " \\___/", "      ", "      "});
const asciiart<8>::char_t asciiart<8>::f = asciiart<8>::char_t('f', {"  _____ ", "  / ___/", "__/ /_  ", "/_  __/ ", "  / /   ", "  /_/   ", "        ", "        "});
const asciiart<8>::char_t asciiart<8>::g = asciiart<8>::char_t('g', true, {"       ", "       ", "____   ", "/ __ \\ ", "/ /_/ /", " \\__  /", "  __/ /", "  /___/"});
const asciiart<8>::char_t asciiart<8>::h = asciiart<8>::char_t('h', true, {"__    ", "/ /   ", "/ /_  ", "/ __ \\", "/ / / /", "/_/ /_/", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::i = asciiart<8>::char_t('i', {"   ", "__ ", "/_/", "__ ", "/ /", "/_/", "   ", "   "});
const asciiart<8>::char_t asciiart<8>::j = asciiart<8>::char_t('j', -2, {"     ", "  __ ", "  /_/", "  __ ", "  / /", "  / /", "__/ /", "/___/"});
const asciiart<8>::char_t asciiart<8>::k = asciiart<8>::char_t('k', {"__      ", "/ /     ", "/ /___  ", "/   __/ ", "/ /\\ \\  ", "/_/  \\_\\", "        ", "        "});
const asciiart<8>::char_t asciiart<8>::l = asciiart<8>::char_t('l', {"__ ", "/ /", "/ /", "/ /", "/ /", "/_/", "   ", "   "});
const asciiart<8>::char_t asciiart<8>::m = asciiart<8>::char_t('m', true, {"           ", "           ", "________   ", "/ __  __ \\ ", "/ / / / / /", "/_/ /_/ /_/", "           ", "           "});
const asciiart<8>::char_t asciiart<8>::n = asciiart<8>::char_t('n', true, {"       ", "       ", "____   ", "/ __ \\ ", "/ / / /", "/_/ /_/", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::o = asciiart<8>::char_t('o', true, {"       ", "       ", "____   ", "/ __ \\ ", "/ /_/ /", " \\____/", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::p = asciiart<8>::char_t('p', true, {"       ", "       ", "____   ", "/ __ \\ ", "/ /_/ /", "/ ____/", "/ /    ", "/_/    "});
const asciiart<8>::char_t asciiart<8>::q = asciiart<8>::char_t('q', true, {"       ", "       ", "____   ", "/ __ \\ ", "/ /_/ /", " \\__  /", "    / /", "    /_/"});
const asciiart<8>::char_t asciiart<8>::r = asciiart<8>::char_t('r', true, {"       ", "       ", "____   ", "/ __ \\ ", "/ / /_/", "/_/    ", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::s = asciiart<8>::char_t('s', true, {"       ", "       ", "____   ", "/ ___\\ ", "/___  /", " \\____/", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::t = asciiart<8>::char_t('t', -2, {"  __   ", "__/ /_ ", "/_  __/", "  / /  ", "  / /  ", "  /_/  ", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::u = asciiart<8>::char_t('u', {"       ", "       ", "__  __ ", "/ / / /", "/ /_/ /", " \\____/", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::v = asciiart<8>::char_t('v', -2, {"         ", "         ", "__    __ ", " \\ \\  / /", "   \\ \\/ /", "     \\__/", "         ", "         "});
const asciiart<8>::char_t asciiart<8>::w = asciiart<8>::char_t('w', -2, {"             ", "             ", "__        __ ", " \\ \\  __  / /", "   \\ \\/  \\/ /", "     \\__/\\__/", "             ", "             "});
const asciiart<8>::char_t asciiart<8>::x = asciiart<8>::char_t('x', {"        ", "        ", "__  __  ", " \\ \\/ / ", "  /   / ", "  /_/\\_\\", "        ", "        "});
const asciiart<8>::char_t asciiart<8>::y = asciiart<8>::char_t('y', {"       ", "       ", "__  __ ", " \\ \\/ /", "   \\  /", "    / /", "    /_/", "       "});
const asciiart<8>::char_t asciiart<8>::z = asciiart<8>::char_t('z', {"       ", "       ", "______ ", "/___  /", "/  ___/", "/_____/", "       ", "       "});

// - majuscules
const asciiart<8>::char_t asciiart<8>::A = asciiart<8>::char_t('A', {"____   ", "/ __ \\ ", "/ /_/ /", "/ __  /", "/ / / /", "/_/ /_/", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::B = asciiart<8>::char_t('B', {"___     ", "/ _ \\   ", "/ // /  ", "/ ___ \\ ", "/ /__/ /", "/______/", "        ", "        "});
const asciiart<8>::char_t asciiart<8>::C = asciiart<8>::char_t('C', {"_____  ", "/ ___/ ", "/ /    ", "/ /    ", "/ /___ ", " \\____/", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::D = asciiart<8>::char_t('D', {"_____   ", "/ ___ \\ ", "/ /  / /", "/ /  / /", "/ /__/ /", "/______/","        ", "        "});
const asciiart<8>::char_t asciiart<8>::E = asciiart<8>::char_t('E', {"_____ ", "/ ___/", "/ /_  ", "/ __/ ", "/ /__ ", "/____/", "      ", "      "});
const asciiart<8>::char_t asciiart<8>::F = asciiart<8>::char_t('F', {"_____ ", "/ ___/", "/ /_  ", "/ __/ ", "/ /   ", "/_/   ", "      ", "      "});
const asciiart<8>::char_t asciiart<8>::G = asciiart<8>::char_t('G', {"______   ", "/ ____/  ", "/ / __   ", "/ / /_ \\ ", "/ /___/ /", " \\______/", "         ", "         "});
const asciiart<8>::char_t asciiart<8>::H = asciiart<8>::char_t('H', {"__   __ ", "/ /  / /", "/ /__/ /", "/ ___  /", "/ /  / /", "/_/  /_/", "        ", "        "});
const asciiart<8>::char_t asciiart<8>::I = asciiart<8>::char_t('I', {"______ ", "/_  __/", "  / /  ", "  / /  ", "__/ /_ ", "/_____/", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::J = asciiart<8>::char_t('J', {" _______ ", " /__  __/", "    / /  ", "__  / /  ", "/ /_/ /  ", " \\____/  ", "         ", "         "});
const asciiart<8>::char_t asciiart<8>::K = asciiart<8>::char_t('K', {"__      ", "/ / ___ ", "/ /_/ _/", "/   __/ ", "/ /\\ \\  ", "/_/  \\_\\", "        ", "        "});
const asciiart<8>::char_t asciiart<8>::L = asciiart<8>::char_t('L', {"__     ", "/ /    ", "/ /    ", "/ /    ", "/ /___ ", "/_____/", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::M = asciiart<8>::char_t('M', {"__     ____", "/  \\  _/   /", "/ /\\ \\/ _/ /", "/ /  \\__// /", "/ /      / /", "/_/      /_/", "            ", "            "});
const asciiart<8>::char_t asciiart<8>::N = asciiart<8>::char_t('N', {"__      __ ", "/  \\    / /", "/ /\\ \\  / /", "/ /  \\ \\/ /", "/ /    \\  /", "/_/     /_/", "           ", "           "});
const asciiart<8>::char_t asciiart<8>::O = asciiart<8>::char_t('O', {"_____     ", "/ ___ \\   ", "/ /   \\ \\ ", "/ /    / /", " \\ \\___/ /", "   \\_____/", "          ", "          "});
const asciiart<8>::char_t asciiart<8>::P = asciiart<8>::char_t('P', {"____   ", "/ __ \\ ", "/ /_/ /", "/ ____/", "/ /    ", "/_/    ", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::Q = asciiart<8>::char_t('Q', {"______    ", "/ ____ \\  ", "/ /   / / ", "/ / __/ / ", "/ /__\\ \\/ ", " \\_____\\_\\", "          ", "          "});
const asciiart<8>::char_t asciiart<8>::R = asciiart<8>::char_t('R', {"___     ", "/ _ \\   ", "/ // /  ", "/ ___ \\ ", "/ /  / /", "/_/  /_/", "        ", "        "});
const asciiart<8>::char_t asciiart<8>::S = asciiart<8>::char_t('S', {"______   ", "/ ____/  ", " \\ \\     ", "   \\ \\   ", " ____\\ \\ ", " /______/", "         ", "         "});
const asciiart<8>::char_t asciiart<8>::T = asciiart<8>::char_t('T', {"________ ", "/__  ___/", "   / /   ", "   / /   ", "   / /   ", "   /_/   ", "         ", "         "});
const asciiart<8>::char_t asciiart<8>::U = asciiart<8>::char_t('U', {"__   __ ", "/ /  / /", "/ /  / /", "/ /  / /", "/ /__/ /", " \\_____/", "        ", "        "});
const asciiart<8>::char_t asciiart<8>::V = asciiart<8>::char_t('V', {"__        __ ", " \\ \\      / /", "   \\ \\    / /", "     \\ \\  / /", "       \\ \\/ /", "         \\__/", "             ", "             "});
const asciiart<8>::char_t asciiart<8>::W = asciiart<8>::char_t('W', {"__              __ ", " \\ \\            / /", "   \\ \\    __    / /", "     \\ \\  /  \\  / /", "       \\ \\/ /\\ \\/ /", "         \\__/  \\__/", "                   ", "                   "});
const asciiart<8>::char_t asciiart<8>::X = asciiart<8>::char_t('X', {"__    __    ", " \\ \\  / /   ", "   \\ \\/ /   ", "    /   /   ", "    / /\\ \\  ", "    /_/  \\_\\", "            ", "            "});
const asciiart<8>::char_t asciiart<8>::Y = asciiart<8>::char_t('Y', {"__    __ ", " \\ \\  / /", "   \\ \\/ /", "     \\  /", "      / /", "      /_/", "         ", "         "});
const asciiart<8>::char_t asciiart<8>::Z = asciiart<8>::char_t('Z', {"______   ", "/___  /  ", "    / /  ", "   / /   ", "  / /___ ", "  /_____/", "         ", "         "});

// - spéciaux
const asciiart<8>::char_t asciiart<8>::eof    = asciiart<8>::char_t();
const asciiart<8>::char_t asciiart<8>::espace = asciiart<8>::char_t(' ', {"     ", "     ", "     ", "     ", "     ", "     ", "     ", "     "});

// Table
const std::map<char,asciiart<8>::char_t> asciiart<8>::TABLE = {
	{'a', asciiart<8>::a},
	{'b', asciiart<8>::b},
	{'c', asciiart<8>::c},
	{'d', asciiart<8>::d},
	{'e', asciiart<8>::e},
	{'f', asciiart<8>::f},
	{'g', asciiart<8>::g},
	{'h', asciiart<8>::h},
	{'i', asciiart<8>::i},
	{'j', asciiart<8>::j},
	{'k', asciiart<8>::k},
	{'l', asciiart<8>::l},
	{'m', asciiart<8>::m},
	{'n', asciiart<8>::n},
	{'o', asciiart<8>::o},
	{'p', asciiart<8>::p},
	{'q', asciiart<8>::q},
	{'r', asciiart<8>::r},
	{'s', asciiart<8>::s},
	{'t', asciiart<8>::t},
	{'u', asciiart<8>::u},
	{'v', asciiart<8>::v},
	{'w', asciiart<8>::w},
	{'x', asciiart<8>::x},
	{'y', asciiart<8>::y},
	{'z', asciiart<8>::z},

	{'A', asciiart<8>::A},
	{'B', asciiart<8>::B},
	{'C', asciiart<8>::C},
	{'D', asciiart<8>::D},
	{'E', asciiart<8>::E},
	{'F', asciiart<8>::F},
	{'G', asciiart<8>::G},
	{'H', asciiart<8>::H},
	{'I', asciiart<8>::I},
	{'J', asciiart<8>::J},
	{'K', asciiart<8>::K},
	{'L', asciiart<8>::L},
	{'M', asciiart<8>::M},
	{'N', asciiart<8>::N},
	{'O', asciiart<8>::O},
	{'P', asciiart<8>::P},
	{'Q', asciiart<8>::Q},
	{'R', asciiart<8>::R},
	{'S', asciiart<8>::S},
	{'T', asciiart<8>::T},
	{'U', asciiart<8>::U},
	{'V', asciiart<8>::V},
	{'W', asciiart<8>::W},
	{'X', asciiart<8>::X},
	{'Y', asciiart<8>::Y},
	{'Z', asciiart<8>::Z},

	{'\0', asciiart<8>::eof},
	{' ',  asciiart<8>::espace}
};
