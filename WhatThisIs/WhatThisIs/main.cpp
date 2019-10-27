#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

const char PianoKeys[] = { 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',  0x27};

int main() {
	unsigned char KeyPress = ' '; 
	int mod = 1;
	cout << "Jakieœ tam pianino :O" << endl;
	while (KeyPress != 0x1b) {
		KeyPress = _getch();
		for (int i = 0; i < (sizeof(PianoKeys) / sizeof(*PianoKeys)); i++) {
			if (PianoKeys[i] == toupper(KeyPress)) Beep(100 * i * mod + 1, 100);
		}
		if ((KeyPress == '-' || KeyPress == '_') && mod > 1) {
			mod--;
			cout << "Mod decreased to " << mod << '!' << endl;;
		}
		else if ((KeyPress == '+' || KeyPress == '=') && mod < 10) {
			mod++;
			cout << "Mod increased to " << mod << '!' << endl;;
		}
	}
	return 0;
}