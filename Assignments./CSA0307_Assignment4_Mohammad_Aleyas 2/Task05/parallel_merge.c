#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
static void merge(int*a,int*t,int l,int m,int r){int i=l,j=m+1,k=l;while(i<=m&&j<=r)t[k++]=a[i]<=a[j]?a[i++]:a[j++];while(i<=m)t[k++]=a[i++];while(j<=r)t[k++]=a[j++];for(i=l;i<=r;i++)a[i]=t[i];}
static void sort_task(int*a,int*t,int l,int r,int depth){if(l>=r)return;int m=l+(r-l)/2;if(depth>0){
#pragma omp task shared(a,t) firstprivate(l,m,depth)
sort_task(a,t,l,m,depth-1);
#pragma omp task shared(a,t) firstprivate(m,r,depth)
sort_task(a,t,m+1,r,depth-1);
#pragma omp taskwait
}else{sort_task(a,t,l,m,0);sort_task(a,t,m+1,r,0);}merge(a,t,l,m,r);}
int main(int argc,char**argv){int n=argc>1?atoi(argv[1]):10000000,threads=argc>2?atoi(argv[2]):4;int*a=malloc((size_t)n*sizeof(int)),*t=malloc((size_t)n*sizeof(int));if(!a||!t)return 2;srand(7);for(int i=0;i<n;i++)a[i]=rand();omp_set_num_threads(threads);double st=omp_get_wtime();
#pragma omp parallel
{
#pragma omp single
sort_task(a,t,0,n-1,4);
}
double sec=omp_get_wtime()-st;int ok=1;for(int i=1;i<n;i++)if(a[i-1]>a[i])ok=0;printf("n=%d threads=%d seconds=%.6f sorted=%s\n",n,threads,sec,ok?"yes":"no");free(a);free(t);return !ok;}
