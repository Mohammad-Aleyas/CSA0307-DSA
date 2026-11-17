#include <stdio.h>
#define MAX 32
typedef struct { int severity; int patient; unsigned long arrival; } Case;
Case heap[MAX]; int size=0; unsigned long sequence=0;
static int higher(Case a,Case b){return a.severity>b.severity || (a.severity==b.severity && a.arrival<b.arrival);}
static void swap(Case*a,Case*b){Case t=*a;*a=*b;*b=t;}
void push(int severity,int patient){
    if(size==MAX)return;
    heap[size]=(Case){severity,patient,sequence++}; int i=size++;
    while(i>0){int p=(i-1)/2;if(!higher(heap[i],heap[p]))break;swap(&heap[i],&heap[p]);i=p;}
}
Case pop(void){
    Case top=heap[0];heap[0]=heap[--size];int i=0;
    for(;;){int l=2*i+1,r=l+1,b=i;if(l<size&&higher(heap[l],heap[b]))b=l;if(r<size&&higher(heap[r],heap[b]))b=r;if(b==i)break;swap(&heap[i],&heap[b]);i=b;}
    return top;
}
int main(void){int sev[]={3,9,5,7,1,8};for(int p=0;p<6;p++)push(sev[p],101+p);while(size){Case c=pop();printf("P%d(%d) ",c.patient,c.severity);}puts("");return 0;}
