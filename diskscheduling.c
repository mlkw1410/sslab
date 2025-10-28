#include <stdio.h>
#include <stdlib.h>

int  fcfs(int req[], int n , int ini)
{
    int total_seek_time =0;
    int curr=ini;
    for(int i=0; i<n; i++)
    {
        total_seek_time+= abs(req[i]-curr);
        printf("%d ->", req[i]);
        curr= req[i];
    }
    int avg_seek_time = total_seek_time/n;
    return avg_seek_time;

}


int main()
{
int n, ini;

printf("enter no.of requests: ");
scanf("%d", &n);

int req[n];

printf("enter requests: ");
for(int i =0; i<n; i++)
{
    scanf("%d",&req[i]);
}

printf("enter the initial position");
scanf("%d", &ini);

printf("head movements: %d -> ", ini);

int avg=fcfs(req, n, ini);
printf("avg seek time: %d", avg);
return 0;
}