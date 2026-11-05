#include <stdio.h>
#include <stdlib.h>
typedef enum { RED, BLACK } Color;
typedef struct Node {int key;Color color;struct Node *l,*r,*p;} Node;
Node *NIL,*root;
Node *newnode(int k){Node*n=malloc(sizeof *n);n->key=k;n->color=RED;n->l=n->r=n->p=NIL;return n;}
void left_rotate(Node*x){Node*y=x->r;x->r=y->l;if(y->l!=NIL)y->l->p=x;y->p=x->p;if(x->p==NIL)root=y;else if(x==x->p->l)x->p->l=y;else x->p->r=y;y->l=x;x->p=y;}
void right_rotate(Node*y){Node*x=y->l;y->l=x->r;if(x->r!=NIL)x->r->p=y;x->p=y->p;if(y->p==NIL)root=x;else if(y==y->p->r)y->p->r=x;else y->p->l=x;x->r=y;y->p=x;}
void fix_insert(Node*z){while(z->p->color==RED){if(z->p==z->p->p->l){Node*y=z->p->p->r;if(y->color==RED){z->p->color=BLACK;y->color=BLACK;z->p->p->color=RED;z=z->p->p;}else{if(z==z->p->r){z=z->p;left_rotate(z);}z->p->color=BLACK;z->p->p->color=RED;right_rotate(z->p->p);}}else{Node*y=z->p->p->l;if(y->color==RED){z->p->color=BLACK;y->color=BLACK;z->p->p->color=RED;z=z->p->p;}else{if(z==z->p->l){z=z->p;right_rotate(z);}z->p->color=BLACK;z->p->p->color=RED;left_rotate(z->p->p);}}}root->color=BLACK;}
void insert(int k){Node*z=newnode(k),*y=NIL,*x=root;while(x!=NIL){y=x;x=k<x->key?x->l:x->r;}z->p=y;if(y==NIL)root=z;else if(k<y->key)y->l=z;else y->r=z;fix_insert(z);}
void inorder(Node*n){if(n!=NIL){inorder(n->l);printf("%d(%c) ",n->key,n->color==RED?'R':'B');inorder(n->r);}}
int check(Node*n,int *black){if(n==NIL){*black=1;return 1;}if(n->color==RED&&(n->l->color==RED||n->r->color==RED))return 0;int a,b;if(!check(n->l,&a)||!check(n->r,&b)||a!=b)return 0;*black=a+(n->color==BLACK);return 1;}
int main(void){int a[]={10,20,30,15,25,5};NIL=calloc(1,sizeof *NIL);NIL->color=BLACK;NIL->l=NIL->r=NIL;root=NIL;puts("Red-black tree after each insertion (inorder key/color):");for(int i=0;i<6;i++){insert(a[i]);printf("insert %d: ",a[i]);inorder(root);int bh;printf("| properties %s\n",(root->color==BLACK&&check(root,&bh))?"PASS":"FAIL");}puts("Minimum process key: 5");return 0;}
