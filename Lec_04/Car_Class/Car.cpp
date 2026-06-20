#include "Car.h"

int main() {
	SportsCar a(100, "Porche", 5, 10);
	Car b(200, "Avante", 3);
	a.speedUp();
	a.display();
	a.setTurbo(0);
	a.speedUp();
	a.changeGear();
	a.display();
	return 0;
}