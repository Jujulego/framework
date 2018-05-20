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

//	std::cout << str << std::endl;
	for (char c : str) {
		aastr += conv(c);
//		std::cout << c << " " << aastr.size() << std::endl;
	}

	return aastr;
}

// Charactères
// - minuscules
const asciiart<8>::char_t asciiart<8>::a = asciiart<8>::char_t('a', {"     ", "     ", "___  ", "___ \\", "/ _  /", " \\___/", "      ", "      "});
const asciiart<8>::char_t asciiart<8>::b = asciiart<8>::char_t('b', {"__     ", "/ /    ", "/ /_   ", "/ __ \\ ", "/ /_/ /", " \\____/", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::c = asciiart<8>::char_t('c', {"     ", "     ", "_____ ", "/ ___/", "/ /__ ", " \\___/", "      ", "      "});
const asciiart<8>::char_t asciiart<8>::d = asciiart<8>::char_t('d', {"    __ ", "    / /", "____/ /", "/ __  /", "/ /_/ /", " \\____/", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::e = asciiart<8>::char_t('e', {"      ", "      ", "___   ", "/ _ \\ ", "/  __/", " \\___/", "      ", "      "});
const asciiart<8>::char_t asciiart<8>::f = asciiart<8>::char_t('f', {"  _____ ", "  / ___/", "__/ /_  ", "/_  __/ ", "  / /   ", "  /_/   ", "        ", "        "});
const asciiart<8>::char_t asciiart<8>::g = asciiart<8>::char_t('g', {"       ", "       ", "____   ", "/ __ \\ ", "/ /_/ /", " \\__  /", "  __/ /", "  /___/"});
const asciiart<8>::char_t asciiart<8>::h = asciiart<8>::char_t('h', {"__    ", "/ /   ", "/ /_  ", "/ __ \\", "/ / / /", "/_/ /_/", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::i = asciiart<8>::char_t('i', {"   ", "__ ", "/_/", "__ ", "/ /", "/_/", "   ", "   "});
const asciiart<8>::char_t asciiart<8>::j = asciiart<8>::char_t('j', -2, {"     ", "  __ ", "  /_/", "  __ ", "  / /", "  / /", "__/ /", "/___/"});
const asciiart<8>::char_t asciiart<8>::k = asciiart<8>::char_t('k', { "__      ", "/ /     ", "/ /___  ", "/   __/ ", "/ /\\ \\  ", "/_/  \\_\\", "        ", "        "});
const asciiart<8>::char_t asciiart<8>::l = asciiart<8>::char_t('l', {"__ ", "/ /", "/ /", "/ /", "/ /", "/_/", "   ", "   "});
const asciiart<8>::char_t asciiart<8>::m = asciiart<8>::char_t('m', {"           ", "           ", "________   ", "/ __  __ \\ ", "/ / / / / /", "/_/ /_/ /_/", "           ", "           "});
const asciiart<8>::char_t asciiart<8>::n = asciiart<8>::char_t('n', {"       ", "       ", "____   ", "/ __ \\ ", "/ / / /", "/_/ /_/", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::o = asciiart<8>::char_t('o', {"       ", "       ", "____   ", "/ __ \\ ", "/ /_/ /", " \\____/", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::p = asciiart<8>::char_t('p', {"       ", "       ", "____   ", "/ __ \\ ", "/ /_/ /", "/ ____/", "/ /    ", "/_/    "});
const asciiart<8>::char_t asciiart<8>::q = asciiart<8>::char_t('q', {"       ", "       ", "____   ", "/ __ \\ ", "/ /_/ /", " \\__  /", "    / /", "    /_/"});
const asciiart<8>::char_t asciiart<8>::r = asciiart<8>::char_t('r', {"       ", "       ", "____   ", "/ __ \\ ", "/ / /_/", "/_/    ", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::s = asciiart<8>::char_t('s', {"       ", "       ", "____   ", "/ ___\\ ", "/___  /", " \\____/", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::t = asciiart<8>::char_t('t', -2, {"  __   ", "__/ /_ ", "/_  __/", "  / /  ", "  / /  ", "  /_/  ", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::u = asciiart<8>::char_t('u', {"       ", "       ", "__  __ ", "/ / / /", "/ /_/ /", " \\____/", "       ", "       "});
const asciiart<8>::char_t asciiart<8>::v = asciiart<8>::char_t('v', -2, {"         ", "         ", "__    __ ", " \\ \\  / /", "   \\ \\/ /", "     \\__/", "         ", "         "});
const asciiart<8>::char_t asciiart<8>::w = asciiart<8>::char_t('w', -2, {"             ", "             ", "__        __ ", " \\ \\  __  / /", "   \\ \\/  \\/ /", "     \\__/\\__/", "             ", "             "});
const asciiart<8>::char_t asciiart<8>::x = asciiart<8>::char_t('x', {"        ", "        ", "__  __  ", " \\ \\/ / ", "  /   / ", "  /_/\\_\\", "        ", "        "});
const asciiart<8>::char_t asciiart<8>::y = asciiart<8>::char_t('y', {"       ", "       ", "__  __ ", " \\ \\/ /", "   \\  /", "    / /", "    /_/", "       "});
const asciiart<8>::char_t asciiart<8>::z = asciiart<8>::char_t('z', {"       ", "       ", "______ ", "/___  /", "/  ___/", "/_____/", "       ", "       "});

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

	{'\0', asciiart<8>::eof},
	{' ',  asciiart<8>::espace}
};
