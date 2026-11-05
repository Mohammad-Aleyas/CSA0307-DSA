#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Trie{struct Trie*c[26];int pass,end;}Trie;Trie*node(void){return calloc(1,sizeof(Trie));}
void insert(Trie*t,const char*w){for(;*w;w++){int i=*w-'a';if(i<0||i>=26)continue;if(!t->c[i])t->c[i]=node();t=t->c[i];t->pass++;}t->end=1;}
Trie*walk(Trie*t,const char*s){for(;*s;s++){int i=*s-'a';if(i<0||i>=26||!t->c[i])return NULL;t=t->c[i];}return t;}
int search(Trie*t,const char*w){Trie*n=walk(t,w);return n&&n->end;}int count(Trie*t,const char*p){Trie*n=walk(t,p);return n?n->pass:0;}
void list(Trie*t,char*b,int d){if(t->end){b[d]=0;printf("%s ",b);}for(int i=0;i<26;i++)if(t->c[i]){b[d]='a'+i;list(t->c[i],b,d+1);}}
int erase(Trie*t,const char*w){Trie*n=walk(t,w);if(!n||!n->end)return 0;n->end=0;for(const char*p=w;*p;p++){int i=*p-'a';t->c[i]->pass--;t=t->c[i];}return 1;}
void destroy(Trie*t){if(t){for(int i=0;i<26;i++)destroy(t->c[i]);free(t);}}
int main(void){const char*a[]={"anand","anitha","anu","arun","bala","anusuya"};Trie*r=node();for(int i=0;i<6;i++)insert(r,a[i]);const char*p[]={"a","an","anu","b","z"};for(int i=0;i<5;i++)printf("%s:%d ",p[i],count(r,p[i]));puts("");char b[128];printf("autocomplete 'an': ");Trie*n=walk(r,"an");strcpy(b,"an");if(n)list(n,b,2);puts("");printf("search anu: %s\n",search(r,"anu")?"found":"missing");int removed=erase(r,"anu");printf("delete anu: %s; prefix anu count=%d\n",removed?"success":"not found",count(r,"anu"));destroy(r);return 0;}
