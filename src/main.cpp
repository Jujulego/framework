// Importations
#include <iomanip>
#include <iostream>

#include "console/manip.hpp"

// Main
int main() {
	std::cout << manip::clear << std::endl;
	std::cout << "         ____                              __ " << std::endl;
	std::cout << "        / __ \\                 __       __/ /_" << std::endl;
	std::cout << "       / /_/ / ____    ___    /_/ ___  /_  __/" << std::endl;
	std::cout << "      / ____/ / __ \\  / _ \\  __  / _ \\  / /   " << std::endl;
	std::cout << "     / /     / / /_/ / // / / / /  __/ / /    " << std::endl;
	std::cout << "    /_/     /_/      \\___/ / /  \\___/ /_/     " << std::endl;
	std::cout << "                        __/ /                 " << std::endl;
	std::cout << "                       /___/                  " << std::endl;

	std::cout << manip::coord(20, 10) << "Millieu";
	std::cout << -6 * manip::dx + manip::dy << "Super";
	std::cout << std::endl;

	return 0;
}
