#include <iostream>
#include <stdio.h>
#include <math.h>
#include <malloc.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	int i, *n, *k, t;
	scanf("%d", &t);
	n = (int*) malloc (t*sizeof(int));
	k = (int*) malloc (t*sizeof(int));
	for(i=0; i<t; i++)
		scanf("%d%d", &n[i], &k[i]);
	for(i=0; i<t; i++)
	{
		if (n[i] < k[i])
			printf("\n %d", k[i]-n[i]);
		else if ((k[i]+n[i])%2 == 0)
			printf("\n 0");
			else printf("\n 1");
		
			
	}
	return 0;
}
