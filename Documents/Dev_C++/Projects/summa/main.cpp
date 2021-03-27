#include <iostream>
#include <stdio.h>
#include <malloc.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int i, j, p, a, t, *n, *k, ch=2, nch=1;
	scanf("%d", &t);
	n = (int*) malloc (t*sizeof(int));
	k = (int*) malloc (t*sizeof(int));
	for(i=0; i<t; i++)
		scanf("%d%d", &n[i], &k[i]);
	printf("\n");
	for(i=0; i<t; i++)
	{
		if(n[i] < k[i])
		{
			printf("NO\n");
			continue;
		}
		if(n[i] == k[i])
		{
			printf("YES\n");
			for(j=0; j<t; j++)
				printf("%d ", nch);
			printf("\n");
			continue;
		}
		p = n[i]/k[i];
//		((p%2) == ((n[i] - p*(k[i]-1))%2) ? : p+=1;
		if ((p%2) == ((n[i] - p*(k[i]-1))%2));
		else 
			p+=1;
		a=n[i] - p*(k[i]-1);
		if((a > 0) && ((p%2) == ((n[i] - p*(k[i]-1))%2)))
		{
			printf("YES\n");
			for (j=0;j<k[i]-1;j++)
				printf("%d ", p);
			printf("%d\n", a);
		}
		else printf("NO\n");
	}
	return 0;
}

