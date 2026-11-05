#include <stdio.h>
#include <stdlib.h>
typedef struct Node{int key;struct Node*l,*r;}Node;
Node*right(Node*y){Node*x=y->l;y->l=x->r;x->r=y;return x;}Node*left(Node*x){Node*y=x->r;x->r=y->l;y->l=x;return y;}
Node*splay(Node*r,int k){if(!r||r->key==k)return r;if(k<r->key){if(!r->l)return r;if(k<r->l->key){r->l->l=splay(r->l->l,k);r=right(r);}else if(k>r->l->key){r->l->r=splay(r->l->r,k);if(r->l->r)r->l=left(r->l);}return r->l?right(r):r;}else{if(!r->r)return r;if(k>r->r->key){r->r->r=splay(r->r->r,k);r=left(r);}else if(k<r->r->key){r->r->l=splay(r->r->l,k);if(r->r->l)r->r=right(r->r);}return r->r?left(r):r;}}
Node*insert(Node*r,int k){if(!r){Node*n=calloc(1,sizeof *n);n->key=k;return n;}r=splay(r,k);if(r->key==k)return r;Node*n=calloc(1,sizeof *n);n->key=k;if(k<r->key){n->r=r;n->l=r->l;r->l=NULL;}else{n->l=r;n->r=r->r;r->r=NULL;}return n;}
void pre(Node*r){if(r){printf("%d ",r->key);pre(r->l);pre(r->r);}}void freeall(Node*r){if(r){freeall(r->l);freeall(r->r);free(r);}}
int main(void){int a[]={1,2,3,4,5,6,7,8,9};Node*r=NULL;for(int i=0;i<9;i++)r=insert(r,a[i]);printf("Initial preorder: ");pre(r);puts("");int access[]={3,9,3,9,3,9};for(int i=0;i<6;i++){r=splay(r,access[i]);printf("access %d -> root %d, preorder: ",access[i],r->key);pre(r);puts("");}freeall(r);return 0;}
