#pragma once
#include <cstdio>
#include <iostream>
using namespace std;

class Car {
protected:
	int speed;
	char name[40];

public:
	int gear;
	Car(){}
	~Car(){}
	Car(int s, const char* n, int g){
		speed = s;
		gear = g;
		strcpy_s(name, n);
	}
	void changeGear(int g = 4) {
		gear = g;
	}
	void speedUp() {
		speed += 5;
	}
	void display() {
		printf("[%s]: Gear=%d Speed=%dkmph\n", name, gear, speed);
	}
	void whereAmI() { printf("object Address=%x\n", this); }
};

class SportsCar : public Car {
public:
	SportsCar(int s, const char* n, int g, bool b)
		:Car(s, n, g), bTurbo(b) {}
	bool bTurbo;
	void setTurbo(bool bTur) { bTurbo = bTur; }
	void speedUp(){
		if (bTurbo) speed += 20;
		else Car::speedUp();
	}
};