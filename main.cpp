#include "Prog4.h"
#include <iostream>

using namespace std;
using namespace prog4;

int main() 
{
	Tabl tab = Tabl();
	Excurtion Item = Excurtion("Moscow Tour", 1, 2, 3, 4, 3);
	tab.add_elem(12, &Item);
	tab.add_elem(1, &Item);
	Excurtion Item1 = Excurtion("Moscow Tour 2", 2, 2, 3, 4, 2);
	tab.add_elem(101, &Item1);
	tab.show_tabl();

	int rc;
	while (static_cast<void>(display_menu()), get_command(rc)) {
		calc(rc, tab);
		cout << endl;
	}

	cout << "ERROR: NO ERRORS!\n     Bye!" << endl;

	return 0;
}