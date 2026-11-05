#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXW 1000
#define LEN 64
typedef struct Trie{struct Trie*c[26];int end;}Trie;Trie*newnode(void){return calloc(1,sizeof(Trie));}
void add(Trie*t,const char*w){for(;*w;w++){int i=*w-'a';if(i<0||i>25)continue;if(!t->c[i])t->c[i]=newnode();t=t->c[i];}t->end=1;}
int exact(Trie*t,const char*w){for(;*w;w++){int i=*w-'a';if(i<0||i>25||!t->c[i])return 0;t=t->c[i];}return t->end;}
void collect(Trie*t,char*b,int d,char out[][LEN],int*count){if(t->end&&*count<MAXW){b[d]=0;strcpy(out[(*count)++],b);}for(int i=0;i<26;i++)if(t->c[i]){b[d]='a'+i;collect(t->c[i],b,d+1,out,count);}}
int cmp(const void*a,const void*b){return strcmp((const char*)a,(const char*)b);}
void freeall(Trie*t){if(t){for(int i=0;i<26;i++)freeall(t->c[i]);free(t);}}
int main(void){const char*words[]={"apple","apply","apt","banana","band","bandit","cat","cater","dog","dove"};int n=10;Trie*t=newnode();for(int i=0;i<n;i++)add(t,words[i]);printf("exact 'band': %s\n",exact(t,"band")?"found":"missing");printf("exact 'bad': %s\n",exact(t,"bad")?"found":"missing");char (*all)[LEN]=calloc(MAXW,LEN);char buf[LEN];int count=0;collect(t,buf,0,all,&count);qsort(all,count,LEN,cmp);printf("alphabetical range [banana..cat]: ");for(int i=0;i<count;i++)if(strcmp(all[i],"banana")>=0&&strcmp(all[i],"cat")<=0)printf("%s ",all[i]);puts("");printf("autocomplete 'ba': ");for(int i=0;i<count;i++)if(strncmp(all[i],"ba",2)==0)printf("%s ",all[i]);puts("");printf("verified dictionary words=%d\n",count);free(all);freeall(t);return 0;}
