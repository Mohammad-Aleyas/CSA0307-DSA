#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef void (*sort_fn)(int*,int);
static long long cmp;
void insertion(int*a,int n){for(int i=1;i<n;i++){int x=a[i],j=i-1;while(j>=0){cmp++;if(a[j]<=x)break;a[j+1]=a[j];j--;}a[j+1]=x;}}
void selection(int*a,int n){for(int i=0;i<n-1;i++){int m=i;for(int j=i+1;j<n;j++){cmp++;if(a[j]<a[m])m=j;}int t=a[i];a[i]=a[m];a[m]=t;}}
void bubble(int*a,int n){for(int i=0;i<n-1;i++){int changed=0;for(int j=0;j<n-i-1;j++){cmp++;if(a[j]>a[j+1]){int t=a[j];a[j]=a[j+1];a[j+1]=t;changed=1;}}if(!changed)break;}}
static void ms(int*a,int*t,int l,int r){if(l>=r)return;int m=l+(r-l)/2;ms(a,t,l,m);ms(a,t,m+1,r);int i=l,j=m+1,k=l;while(i<=m&&j<=r){cmp++;t[k++]=a[i]<=a[j]?a[i++]:a[j++];}while(i<=m)t[k++]=a[i++];while(j<=r)t[k++]=a[j++];for(i=l;i<=r;i++)a[i]=t[i];}
void merge_sort(int*a,int n){int*t=malloc((size_t)n*sizeof(int));if(!t)exit(2);ms(a,t,0,n-1);free(t);}
static void qs(int*a,int l,int r){while(l<r){int p=a[l+(r-l)/2],i=l,j=r;while(i<=j){while(a[i]<p){cmp++;i++;}cmp++;while(a[j]>p){cmp++;j--;}cmp++;if(i<=j){int t=a[i];a[i]=a[j];a[j]=t;i++;j--;}}if(j-l<i-r){if(l<j)qs(a,l,j);l=i;}else{if(i<r)qs(a,i,r);r=j;}}}
void quick_sort(int*a,int n){qs(a,0,n-1);}
void sift(int*a,int n,int i){for(;;){int b=i,l=2*i+1,r=l+1;if(l<n){cmp++;if(a[l]>a[b])b=l;}if(r<n){cmp++;if(a[r]>a[b])b=r;}if(b==i)return;int t=a[i];a[i]=a[b];a[b]=t;i=b;}}
void heap_sort(int*a,int n){for(int i=n/2-1;i>=0;i--)sift(a,n,i);for(int e=n-1;e>0;e--){int t=a[0];a[0]=a[e];a[e]=t;sift(a,e,0);}}
int main(int argc,char**argv){int n=argc>1?atoi(argv[1]):100000;char*kind=argc>2?argv[2]:"random";if(n<1)return 1;int*a=malloc((size_t)n*sizeof(int));if(!a)return 2;srand(42);for(int i=0;i<n;i++)a[i]=!strcmp(kind,"sorted")?i:!strcmp(kind,"reverse")?n-i:rand();sort_fn f[]={bubble,insertion,selection,merge_sort,quick_sort,heap_sort};const char*names[]={"bubble","insertion","selection","merge","quick","heap"};for(int s=0;s<6;s++){for(int i=0;i<n;i++)a[i]=!strcmp(kind,"sorted")?i:!strcmp(kind,"reverse")?n-i:rand();cmp=0;clock_t st=clock();f[s](a,n);double sec=(double)(clock()-st)/CLOCKS_PER_SEC;printf("%s,n=%d,input=%s,seconds=%.6f,comparisons=%lld\n",names[s],n,kind,sec,cmp);}free(a);return 0;}
