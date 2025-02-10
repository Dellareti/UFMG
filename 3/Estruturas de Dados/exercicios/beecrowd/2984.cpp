#include<bits/stdc++.h>
#define MAX 100

using namespace std;

typedef struct pilhas {
    char elementos[MAX];
    int topo;
} Pilhas;

Pilhas *create() {
    Pilhas *p = (Pilhas *) malloc(sizeof(Pilhas));
    p->topo = -1;
    for (int i = 0; i < MAX; i++) {
        p->elementos[i] = 0;
    }
    return p;
}

int isFull(Pilhas *p) {
    return p->topo == MAX - 1;
}

char pop(Pilhas *p) {
    char c = p->elementos[p->topo];
    p->topo--;
    return c;
}

int push(Pilhas *p, char c) {
    if (isFull(p)) {
        return 0;
    }
    p->topo++;
    p->elementos[p->topo] = c;
    return 1;
}
stack<char> pilha;
int empty(Pilhas *p) {
    return p->topo == -1;
}

int size(Pilhas *p) {
    return p->topo + 1;
}

int main(){

    string vetor;
    cin>>vetor;

    for(int i=0; i<vetor.size(); i++){
        if(vetor[i]=='('){
            pilha.push(vetor[i]);
        }
        else{
            if(!pilha.empty()){
                pilha.pop();
            }
        }
    }

    if(pilha.size()!=0)
        cout<<"Ainda temos "<<pilha.size()<<" assunto(s) pendente(s)!"<<endl;
    else
        cout<<"Partiu RU!"<<endl;

    return 0;
}
