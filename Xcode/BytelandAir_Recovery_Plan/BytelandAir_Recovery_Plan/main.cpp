//
//  main.cpp
//  BytelandAir_Recovery_Plan
//
//
/* The BytelandAir company is recovering after the pandemic crisis.
 
 There are n airports in the Byteland labelled 1 to n, and BytelandAir plans m bidirectional
 airlines where each line connects two airports. The only thing remaining is to decide which pairs
 of airports should be connected. One important requirement is that it should be possible to get
 from any airport to any other by one or several airlines. In addition to this, director had the
 brilliant idea that the airlines should be labelled by the sum of their endpoints. This means that
 all of these sums must be different.

 More formally, you are given two integers n and m. Construct a graph with m edges and n vertices
 labelled 1 to n, such that:

 1. The graph is connected.

 2. All m sums of edge endpoints are distinct. */
//
//  Created by Кирилл Глебов on 20.09.2021.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    int m, n, k = 0;
    
    scanf("%d%d", &n, &m);
    if((n > (m + 1)) || (m > ((n - 1) + (n - 2))))
    {
        printf("-1");
        return 0;
    }
    else
    {
            for(int i = 2; i <= n; i++)
            {
                printf("1 %d\n", i);
                k++;
                if(k == m)
                    return 0;
            }
            for(int i = 2; i < n; i++)
            {
                printf("%d %d\n", i, n);
                k++;
                if(k == m)
                    return 0;
            }
    }
    return 0;
}
