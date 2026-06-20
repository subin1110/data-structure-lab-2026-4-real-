#pragma once
#include <cstdio>
#include <iostream>

#define MAX_DEGREE 80

class Polynomial {
	int degree;
	float coef[MAX_DEGREE];
public:
	Polynomial() { degree = 0; }
	//다항식의 내용을 입력받는 멤버함수
	void read() {
		printf("Polynomial's Max Degree: ");
		scanf_s("%d", &degree);
		printf("Coefficients of Each Terms(total %d): ", degree + 1);
		for (int i = 0; i <= degree; i++)
			scanf_s("%f", coef + i);
	}
	//다항식의 내용을 화면에 출력하는 함수
	void display(const char* str = "Poly = ") {
		printf("\t%s", str);
		for (int i = 0; i < degree; i++)
			printf("%5.1f x^%d + ", coef[i], degree - i);
		printf("%4.1f\n", coef[degree]);
	}
	//다항식 a와 b를 더하는 함수. a와 b를 더해 자신의 다항식 설정.
	void add(Polynomial a, Polynomial b) {
		if (a.degree > b.degree) {
			*this = a;
			for (int i = 0; i <= b.degree; i++)
				coef[i + (degree - b.degree)] += b.coef[i];
		}
		else {
			*this = b;
			for (int i = 0; i <= a.degree; i++)
				coef[i + (degree - a.degree)] += a.coef[i];
		}
	}
	bool isZero() { return degree == 0; }
	void negate() {
		for (int i = 0; i <= degree; i++) {
			coef[i] = -coef[i];}}
};