#include <iostream>
#include <string>
int main () {
	int a = 3;
	int b = 2;

	for(int j = 0; j<5; j++){
		b += a;
		a *= 2;
		for(int i = 0; i<10; i++){
			a += b;

		}
	}
	std::cout << a << "\n";
	std::cout << b << "\n";
	return 0;
}
