#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static long long comparisons; static int max_depth;
static void swap(int*a,int*b){int t=*a;*a=*b;*b=t;}
static int partition_last(int a[],int lo,int hi){int p=a[hi],i=lo-1;for(int j=lo;j<hi;j++){comparisons++;if(a[j]<=p){i++;swap(&a[i],&a[j]);}}swap(&a[i+1],&a[hi]);return i+1;}
static void quick_bad(int a[],int lo,int hi,int depth){if(depth>max_depth)max_depth=depth;if(lo>=hi)return;int p=partition_last(a,lo,hi);quick_bad(a,lo,p-1,depth+1);quick_bad(a,p+1,hi,depth+1);}
static void merge(int a[],int t[],int l,int m,int r){int i=l,j=m+1,k=l;while(i<=m&&j<=r){comparisons++;if(a[i]<=a[j])t[k++]=a[i++];else t[k++]=a[j++];}while(i<=m)t[k++]=a[i++];while(j<=r)t[k++]=a[j++];for(i=l;i<=r;i++)a[i]=t[i];}
static void merge_sort(int a[],int t[],int l,int r){if(l>=r)return;int m=l+(r-l)/2;merge_sort(a,t,l,m);merge_sort(a,t,m+1,r);merge(a,t,l,m,r);}
int main(void){
    int a[]={7,2,9,4,3,8,5},n=7,pivot=a[n-1],i=-1,swaps=0;
    for(int j=0;j<n-1;j++)if(a[j]<=pivot){i++;int t=a[i];a[i]=a[j];a[j]=t;swaps++;}
    int t=a[i+1];a[i+1]=a[n-1];a[n-1]=t;
    for(int k=0;k<n;k++)printf("%d ",a[k]);printf("| pivot at %d, swaps %d\n",i+1,swaps);
    int x[10000],tmp[10000];for(int k=0;k<10000;k++)x[k]=k;
    comparisons=0;max_depth=0;quick_bad(x,0,9999,1);
    printf("sorted quicksort: comparisons=%lld max_recursion_depth=%d\n",comparisons,max_depth);
    for(int k=0;k<10000;k++)x[k]=9999-k;
    comparisons=0;max_depth=0;quick_bad(x,0,9999,1);
    printf("reverse quicksort: comparisons=%lld max_recursion_depth=%d\n",comparisons,max_depth);
    for(int k=0;k<10000;k++)x[k]=rand();
    comparisons=0;merge_sort(x,tmp,0,9999);
    printf("merge sort random: comparisons=%lld\n",comparisons);
    return 0;
}
