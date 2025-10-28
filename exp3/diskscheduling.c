#include <stdio.h>
#include <stdlib.h>
#define max_size 200

//sort for both cscan and scan
void sort(int req[], int n)
{
    for(int i=0; i <n-1; i++ )
    {
        for(int j=0; j<n-i-1;j++)
        {
            if(req[j]>req[j+1])
            {
                int temp=req[j];
                req[j]=req[j+1];
                req[j+1]=temp;
            }
        }
    }
}

int  fcfs(int req[], int n , int ini)
{
    int total_seek_time =0;
    int curr=ini;
    printf("fcfs");
    printf(" head movements: %d -> ", ini);
    for(int i=0; i<n; i++)
    {
        total_seek_time+= abs(req[i]-curr);
        printf("%d ->", req[i]);
        curr= req[i];
    }
    int avg_seek_time = total_seek_time/n;
    return avg_seek_time;

}

int scan(int req[], int n, int ini, int dir)
{
    int total_seek_time=0, curr=ini;
    sort(req, n);

    printf("scan\n");
    printf(" head movements: %d -> ", ini);
    if(dir==1)//upwards
    {
        for(int i=0; i<n; i++)
        {
            if(req[i]>=ini)
            {
                total_seek_time+=abs(req[i]-curr);
                printf("%d -> ", req[i]);
                curr=req[i];
            }
        }

        total_seek_time+=abs(max_size -1-curr);
        curr=max_size -1;
        printf("%d ->", curr);

        for(int i=n-1; i>=0; i--)
        {
            if(req[i]<ini)
            {
                total_seek_time+=abs(req[i]-curr);
                printf("%d ->", req[i]);
                curr=req[i];
            }
        }
    }

    else//downwards
    {
        for(int i=n-1; i>=0; i--)
        {
            if(req[i]<=ini)
            {
                total_seek_time+=abs(req[i]-curr);
                printf("%d ->", req[i]);
                curr=req[i];
            }
        }

        total_seek_time+=abs(curr-0);
        curr=0;

        for(int i=0; i<n; i++)
        {
            if(req[i]>ini)
            {
                total_seek_time+=abs(req[i]-curr);
                printf("%d ->", req[i]);
                curr=req[i];
            }
        }
    }

    return total_seek_time/n;
}

int cscan(int req[], int n, int ini, int dir)
{
    int total_seek_time=0, curr=ini;
    sort(req,n);
    printf("cscan\n");
    printf(" head movements: %d -> ", ini);    

    if(dir==1)
    {
        for(int i=0; i<n; i++)
        {
            if(req[i]>=ini)
            {
                total_seek_time+=abs(req[i]-curr);
                printf("%d ->", req[i]);
                curr=req[i];
            }
        }

        total_seek_time+=abs(max_size -1-curr);//goes to the end 
        total_seek_time+=abs(max_size-1);//jumps to beginning
        curr=0;

        for(int i=0; i<n; i++)
        {
            if(req[i]<ini)
            {
                total_seek_time+=abs(req[i]-curr);
                printf("%d ->", req[i]);
                curr=req[i];
            }
        }
    }

    else
    {
        for(int i=n-1; i>=0; i--)
        {
            if(req[i]<=ini)
            {
                total_seek_time+=abs(req[i]-curr);
                printf("%d ->", req[i]);
                curr=req[i];
            }
        }
        total_seek_time+=abs(curr-0);
        total_seek_time+=abs(max_size-1);
        curr=max_size-1;
        for(int i=n-1; i>=0; i--)
        {
            if(req[i]>ini)
            {
                total_seek_time+=abs(req[i]-curr);
                printf("%d ->", req[i]);
                curr=req[i];
            }
        } 
    }

    return total_seek_time/n;
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

printf("enter the initial position: ");
scanf("%d", &ini);


int avg=fcfs(req, n, ini);
printf("avg fcfs seek time: %d\n", avg);

int dir; 
printf("\nenter direction (1 for upwards, 0 for downwards): ");
scanf("%d", &dir);
int avg_scan=scan(req, n, ini, dir);
printf("\navg scan seek time: %d", avg_scan);

int avg_cscan=cscan(req, n, ini, dir);
printf("\navg cscan seek time: %d", avg_cscan);


return 0;
}