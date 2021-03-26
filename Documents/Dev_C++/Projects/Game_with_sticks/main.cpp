#include <iostream>
#include <stdio.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	unsigned int k, n, m;
	scanf("%d%d", &n, &m);
	(n<m) ? (k=n%2) : (k=m%2);
	if (k)
		printf("Akshat");
	else
		printf("Malvika");
	return 0;
}
