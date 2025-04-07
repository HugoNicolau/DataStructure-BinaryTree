#ifndef ABB_H
#define ABB_H

#include "NoABB.h"

class ABB
{
    private:

        NoABB* raiz;

    public:

        ABB();
        ~ABB();
        bool vazia();
        void insere(int valor);
        NoABB* busca(int valor);
        void remove(int valor);
        void imprimeEmLargura();
        void imprimeOrdemCrescente();
        void imprimeVisualizacao();
        void destroiArvore();
        
        // Novas funções
        int soma();                        // Soma todos os valores da árvore
        float media();                     // Calcula a média dos valores da árvore
        bool ehCheia();                    // Verifica se a árvore é cheia
        bool ehCompleta();                 // Verifica se a árvore é completa
        void imprimeIntervalo(int x, int y); // Imprime valores entre x e y
        bool estritamenteBinaria();        // Verifica se todos os nós têm 0 ou 2 filhos
        int maioresQue(int valor);         // Conta nós com valor maior que o parâmetro
        float mediaNivel(int nivel);       // Calcula a média dos valores no nível especificado
        void alturaNos();                  // Imprime a altura de cada nó da árvore
};

#endif
