#include <iostream>
#include "NoABB.h"

using namespace std;

NoABB::NoABB(int valor)
{
	this->valor = valor;
	this->esq = NULL;
	this->dir = NULL;
}

NoABB::~NoABB()
{
	delete this->esq;
	delete this->dir;
}

int NoABB::getValor()
{
	return this->valor;
}

NoABB* NoABB::getEsq()
{
	return this->esq;
}

NoABB* NoABB::getDir()
{
	return this->dir;
}

void NoABB::setValor(int valor)
{
	this->valor = valor;
}

void NoABB::setEsq(NoABB* no)
{
	this->esq = no;
}

void NoABB::setDir(NoABB* no)
{
	this->dir = no;
}

void NoABB::insere(int valor)
{
    // Se o valor a ser inserido for menor que o valor do nó atual
    if (valor < this->valor)
    {
        // Se não houver filho à esquerda, cria um novo nó
        if (this->esq == NULL)
            this->esq = new NoABB(valor);
        // Caso contrário, insere recursivamente na subárvore esquerda
        else
            this->esq->insere(valor);
    }
    // Se o valor a ser inserido for maior ou igual ao valor do nó atual
    else
    {
        // Se não houver filho à direita, cria um novo nó
        if (this->dir == NULL)
            this->dir = new NoABB(valor);
        // Caso contrário, insere recursivamente na subárvore direita
        else
            this->dir->insere(valor);
    }
}

NoABB* NoABB::busca(int valor)
{
    // Se encontrou o valor no nó atual, retorna este nó
    if (this->valor == valor)
        return this;
    
    // Se o valor buscado for menor que o valor do nó atual,
    // busca na subárvore esquerda
    if (valor < this->valor && this->esq != NULL)
        return this->esq->busca(valor);
    
    // Se o valor buscado for maior que o valor do nó atual,
    // busca na subárvore direita
    if (valor > this->valor && this->dir != NULL)
        return this->dir->busca(valor);
    
    // Se chegou aqui, o valor não foi encontrado
    return NULL;
}

NoABB* NoABB::remove(NoABB* no, int valor)
{
    // Caso base: árvore vazia ou nó não encontrado
    if (no == NULL)
        return NULL;
    
    // Busca o nó a ser removido
    if (valor < no->valor)
    {
        // O valor está na subárvore esquerda
        no->esq = remove(no->esq, valor);
    }
    else if (valor > no->valor)
    {
        // O valor está na subárvore direita
        no->dir = remove(no->dir, valor);
    }
    else
    {
        // Encontramos o nó a ser removido
        
        // Caso 1: Nó é uma folha (sem filhos)
        if (no->esq == NULL && no->dir == NULL)
        {
            delete no;
            return NULL;
        }
        
        // Caso 2: Nó tem apenas um filho
        else if (no->esq == NULL)
        {
            NoABB* temp = no->dir;
            no->dir = NULL; // Evita que o destrutor delete o filho
            delete no;
            return temp;
        }
        else if (no->dir == NULL)
        {
            NoABB* temp = no->esq;
            no->esq = NULL; // Evita que o destrutor delete o filho
            delete no;
            return temp;
        }
        
        // Caso 3: Nó tem dois filhos
        // Encontra o sucessor (menor valor na subárvore direita)
        NoABB* temp = no->dir;
        while (temp->esq != NULL)
            temp = temp->esq;
        
        // Copia o valor do sucessor para este nó
        no->valor = temp->valor;
        
        // Remove o sucessor
        no->dir = remove(no->dir, temp->valor);
    }
    
    return no;
}

void NoABB::imprimeOrdemCrescente()
{
    // Primeiro visita a subárvore esquerda (todos os valores menores)
    if (this->esq != NULL)
        this->esq->imprimeOrdemCrescente();
    
    // Depois visita o nó atual (imprime seu valor)
    cout << this->valor << " ";
    
    // Por fim, visita a subárvore direita (todos os valores maiores)
    if (this->dir != NULL)
        this->dir->imprimeOrdemCrescente();
}

void NoABB::imprimeVisualizacao(int n)
{
	for (int i = 0; i < n; i++)
		cout << "--";
	cout << "(" << this->valor << ")" << endl;
	if (this->esq != NULL)
		this->esq->imprimeVisualizacao(n + 1);
	if (this->dir != NULL)
		this->dir->imprimeVisualizacao(n + 1);
}

int NoABB::soma()
{
    int resultado = this->valor; // Inicia com o valor do nó atual
    
    // Adiciona os valores da subárvore esquerda
    if (this->esq != NULL)
        resultado += this->esq->soma();
    
    // Adiciona os valores da subárvore direita
    if (this->dir != NULL)
        resultado += this->dir->soma();
    
    return resultado;
}

int NoABB::contaNos()
{
    // Começa com 1 para o nó atual
    int resultado = 1;
    
    // Adiciona contagem da subárvore esquerda
    if (this->esq != NULL)
        resultado += this->esq->contaNos();
    
    // Adiciona contagem da subárvore direita
    if (this->dir != NULL)
        resultado += this->dir->contaNos();
    
    return resultado;
}
