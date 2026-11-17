#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_ORDERS 100005
#define TABLE 262147
typedef struct {long id;int restaurant,amount;long promised,created;int cancelled,active;} Order;
typedef struct {long id;int index;int used;} Slot;
static Order orders[MAX_ORDERS];static Slot map[TABLE];static int heap[MAX_ORDERS],hn=0,on=0;
static unsigned hash_id(long x){unsigned long z=(unsigned long)x;z^=z>>33;z*=0xff51afd7ed558ccdULL;z^=z>>33;z*=0xc4ceb9fe1a85ec53ULL;z^=z>>33;return (unsigned)(z%TABLE);}
static int find_slot(long id){unsigned p=hash_id(id);while(map[p].used&&map[p].id!=id)p=(p+1)%TABLE;return (int)p;}
static int higher(int x,int y){Order*a=&orders[x],*b=&orders[y];long da=a->created-a->promised,db=b->created-b->promised;if(da!=db)return da>db;return a->created<b->created;}
static void hs(int a,int b){int t=heap[a];heap[a]=heap[b];heap[b]=t;}
static void up(int i){while(i){int p=(i-1)/2;if(!higher(heap[i],heap[p]))break;hs(i,p);i=p;}}
static void down(int i){for(;;){int b=i,l=2*i+1,r=l+1;if(l<hn&&higher(heap[l],heap[b]))b=l;if(r<hn&&higher(heap[r],heap[b]))b=r;if(b==i)break;hs(i,b);i=b;}}
static void place(long id,int rest,int amount,long promised,long created){if(on>=MAX_ORDERS-1)return;int k=on++;orders[k]=(Order){id,rest,amount,promised,created,0,1};int p=find_slot(id);map[p]=(Slot){id,k,1};heap[hn]=k;up(hn++);}
static int lookup(long id){int p=find_slot(id);return map[p].used?map[p].index:-1;}
static int assign_next(void){while(hn){int k=heap[0];heap[0]=heap[--hn];if(hn)down(0);if(orders[k].active&&!orders[k].cancelled)return k;}return -1;}
static int cancel_order(long id){int k=lookup(id);if(k<0||!orders[k].active)return 0;orders[k].cancelled=1;orders[k].active=0;return 1;}
static int cmp_order(const void*x,const void*y){const Order*a=x,*b=y;if(a->restaurant!=b->restaurant)return a->restaurant-b->restaurant;if(a->amount!=b->amount)return a->amount-b->amount;return a->created<b->created?-1:a->created>b->created;}
int main(int argc,char**argv){int n=argc>1?atoi(argv[1]):50000;if(n>100000)n=100000;clock_t st=clock();for(int i=0;i<n;i++)place(1000000L+i,i%100,100+(i*37)%900,1000+(i%50),900+(i%100));double insert=(double)(clock()-st)/CLOCKS_PER_SEC;
st=clock();long hits=0;for(int i=0;i<n;i++)if(lookup(1000000L+i)>=0)hits++;double search=(double)(clock()-st)/CLOCKS_PER_SEC;
st=clock();for(int i=0;i<n/10;i++)cancel_order(1000000L+i*3);double cancel=(double)(clock()-st)/CLOCKS_PER_SEC;
st=clock();int assigned=0;for(int i=0;i<n/10;i++)if(assign_next()>=0)assigned++;double dispatch=(double)(clock()-st)/CLOCKS_PER_SEC;
st=clock();qsort(orders,n,sizeof(Order),cmp_order);double report=(double)(clock()-st)/CLOCKS_PER_SEC;
printf("orders=%d insert_s=%.6f lookup_%ld_s=%.6f cancel_%d_s=%.6f assign_%d_s=%.6f report_sort_s=%.6f\n",n,hits,search,n/10,cancel,assigned,dispatch,report);return 0;}
