#include <stdio.h>
#include <stdlib.h>
#define T 2
#define MAX_KEYS (2*T-1)
#define MAX_CHILD (2*T)
typedef struct BNode { int n, leaf, key[MAX_KEYS]; struct BNode *c[MAX_CHILD]; } BNode;
BNode *make_node(int leaf){BNode*x=calloc(1,sizeof *x);x->leaf=leaf;return x;}
void traverse(BNode*x){if(!x)return;int i;for(i=0;i<x->n;i++){if(!x->leaf)traverse(x->c[i]);printf("%d ",x->key[i]);}if(!x->leaf)traverse(x->c[i]);}
int search(BNode*x,int k,int *reads){*reads=0;while(x){(*reads)++;int i=0;while(i<x->n&&k>x->key[i])i++;if(i<x->n&&k==x->key[i])return 1;if(x->leaf)return 0;x=x->c[i];}return 0;}
void split(BNode*p,int i){BNode*y=p->c[i],*z=make_node(y->leaf);z->n=T-1;for(int j=0;j<T-1;j++)z->key[j]=y->key[j+T];if(!y->leaf)for(int j=0;j<T;j++)z->c[j]=y->c[j+T];y->n=T-1;for(int j=p->n;j>=i+1;j--)p->c[j+1]=p->c[j];p->c[i+1]=z;for(int j=p->n-1;j>=i;j--)p->key[j+1]=p->key[j];p->key[i]=y->key[T-1];p->n++;}
void nonfull(BNode*x,int k){int i=x->n-1;if(x->leaf){while(i>=0&&k<x->key[i]){x->key[i+1]=x->key[i];i--;}x->key[i+1]=k;x->n++;}else{while(i>=0&&k<x->key[i])i--;i++;if(x->c[i]->n==MAX_KEYS){split(x,i);if(k>x->key[i])i++;}nonfull(x->c[i],k);}}
void insert(BNode **root,int k){BNode*r=*root;if(!r){*root=make_node(1);(*root)->key[0]=k;(*root)->n=1;return;}if(r->n==MAX_KEYS){BNode*s=make_node(0);s->c[0]=r;split(s,0);int i=k>s->key[0];nonfull(s->c[i],k);*root=s;}else nonfull(r,k);}
void print_level(BNode*r){BNode*q[256];int f=0,b=0;if(!r)return;q[b++]=r;while(f<b){BNode*x=q[f++];printf("[");for(int i=0;i<x->n;i++)printf("%s%d",i?" ":"",x->key[i]);printf("] ");if(!x->leaf)for(int i=0;i<=x->n;i++)q[b++]=x->c[i];}puts("");}
void free_tree(BNode*x){if(x){if(!x->leaf)for(int i=0;i<=x->n;i++)free_tree(x->c[i]);free(x);}}
int main(void){int a[]={10,20,5,6,12,30,7,17};BNode*r=NULL;puts("B-tree (minimum degree 2), after each insertion:");for(int i=0;i<8;i++){insert(&r,a[i]);printf("insert %d: ",a[i]);print_level(r);}printf("sorted traversal: ");traverse(r);puts("");int reads=0;int ok=search(r,6,&reads);printf("search 6: %s, node reads=%d\n",ok?"found":"missing",reads);ok=search(r,99,&reads);printf("search 99: %s, node reads=%d\n",ok?"found":"missing",reads);free_tree(r);return 0;}
