#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <time.h> 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	int i, j, p, t, n1, *n, k=0;
	int *a;
	scanf("%d", &t);
	clock_t start = clock();
	n = (int*) malloc (t*sizeof(int));
	for(i=0; i<t; i++)
		scanf("%d", &n[i]);
	for(i=0; i<t; i++)
	{
		if((n[i]/2)%2)
			printf("NO\n");
		else
			{
				a = (int*) malloc (n[i]*sizeof(int));
				printf("YES\n");
				n1 = n[i];
				k = n[i]/2;
				a[0] = 2;
				a[k] = 1;
				for(j=1, p=k+1; ((j<k) && (p<n1)); j++, p++)
				{				
					a[j] = a[j-1] + 2;
					a[p] = a[p-1] + 2;
				}
				a[n1-1] = a[k-1] + (k-1);
				for (j=0; j<n1; j++)
					printf("%d ", a[j]);
				printf("\n");
			}
	}
	printf("Elapsed time: %.5f\n", (double)(clock() - start)/CLOCKS_PER_SEC);
	return 0;
}
