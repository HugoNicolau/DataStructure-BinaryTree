#include <iostream>
#include "NoAVL.h"

using namespace std;

NoAVL::NoAVL(int valor)
{
	this->valor = valor;
	this->altura = 0;
	this->esq = NULL;
	this->dir = NULL;
}

NoAVL::~NoAVL()
{
	delete this->esq;
	delete this->dir;
}

int NoAVL::getValor()
{
	return this->valor;
}

NoAVL* NoAVL::getEsq()
{
	return this->esq;
}

NoAVL* NoAVL::getDir()
{
	return this->dir;
}

void NoAVL::setValor(int valor)
{
	this->valor = valor;
}

void NoAVL::setEsq(NoAVL* no)
{
	this->esq = no;
}

void NoAVL::setDir(NoAVL* no)
{
	this->dir = no;
}

NoAVL* NoAVL::corrige(NoAVL* no)
{
    // Atualiza a altura do nó atual
    no->atualizaAltura();
    
    // Calcula o fator de balanceamento
    int fb = no->getFB();
    
    // Caso 1: Desbalanceamento à direita
    if (fb > 1)
    {
        // Caso 1.1: Rotação simples à esquerda
        if (no->dir->getFB() >= 0)
            return rotEsq(no);
        
        // Caso 1.2: Rotação dupla (direita-esquerda)
        no->dir = rotDir(no->dir);
        return rotEsq(no);
    }
    
    // Caso 2: Desbalanceamento à esquerda
    if (fb < -1)
    {
        // Caso 2.1: Rotação simples à direita
        if (no->esq->getFB() <= 0)
            return rotDir(no);
        
        // Caso 2.2: Rotação dupla (esquerda-direita)
        no->esq = rotEsq(no->esq);
        return rotDir(no);
    }
    
    // Nó está balanceado
    return no;
}

NoAVL* NoAVL::insere(NoAVL* no, int valor)
{
    // Se o nó é NULL, cria um novo nó
    if (no == NULL)
        return new NoAVL(valor);
    
    // Inserção normal na ABB
    if (valor < no->valor)
        no->esq = insere(no->esq, valor);
    else if (valor > no->valor)
        no->dir = insere(no->dir, valor);
    else
        return no; // Valor já existe, não faz nada
    
    // Corrige o balanceamento após a inserção
    return no->corrige(no);
}

NoAVL* NoAVL::busca(int valor)
{
	// igual à ABB
}

NoAVL* NoAVL::remove(NoAVL* no, int valor)
{
    // Caso base: nó é NULL
    if (no == NULL)
        return NULL;
    
    // Busca o nó a ser removido
    if (valor < no->valor)
        no->esq = remove(no->esq, valor);
    else if (valor > no->valor)
        no->dir = remove(no->dir, valor);
    else
    {
        // Nó encontrado! Vamos removê-lo
        
        // Caso 1: Nó folha ou com apenas um filho
        if (no->esq == NULL)
        {
            NoAVL* temp = no->dir;
            no->dir = NULL; // Evita a remoção recursiva do filho direito no destrutor
            delete no;
            return temp;
        }
        else if (no->dir == NULL)
        {
            NoAVL* temp = no->esq;
            no->esq = NULL; // Evita a remoção recursiva do filho esquerdo no destrutor
            delete no;
            return temp;
        }
        
        // Caso 2: Nó com dois filhos
        // Encontra o sucessor (menor valor na subárvore direita)
        NoAVL* temp = no->dir;
        while (temp->esq != NULL)
            temp = temp->esq;
        
        // Copia o valor do sucessor para este nó
        no->valor = temp->valor;
        
        // Remove o sucessor
        no->dir = remove(no->dir, temp->valor);
    }
    
    // Se a árvore tinha apenas um nó, retorna NULL
    if (no == NULL)
        return NULL;
    
    // Corrige o balanceamento após a remoção
    return no->corrige(no);
}

void NoAVL::imprimeOrdemCrescente()
{
	// igual à ABB
}

void NoAVL::imprimeVisualizacao(int n)
{
	for (int i = 0; i < n; i++)
		cout << "--";
	cout << "(" << this->valor << ")" << endl;
	if (this->esq != NULL)
		this->esq->imprimeVisualizacao(n + 1);
	if (this->dir != NULL)
		this->dir->imprimeVisualizacao(n + 1);
}

void NoAVL::atualizaAltura()
{
    int alturaEsq = (this->esq == NULL) ? -1 : this->esq->altura;
    int alturaDir = (this->dir == NULL) ? -1 : this->dir->altura;
    
    // A altura do nó é o máximo das alturas dos filhos + 1
    this->altura = 1 + ((alturaEsq > alturaDir) ? alturaEsq : alturaDir);
}

int NoAVL::getFB()
{
	return ((this->dir == NULL) ? -1 : this->dir->altura) - ((this->esq == NULL) ? -1 : this->esq->altura);
}

NoAVL* NoAVL::rotEsq(NoAVL* p)
{
    // O filho direito de p se tornará a nova raiz
    NoAVL* q = p->dir;
    
    // O filho esquerdo de q se torna o filho direito de p
    p->dir = q->esq;
    
    // p se torna o filho esquerdo de q
    q->esq = p;
    
    // Atualiza as alturas de p e q
    p->atualizaAltura();
    q->atualizaAltura();
    
    // Retorna a nova raiz (q)
    return q;
}

NoAVL* NoAVL::rotDir(NoAVL* p)
{
    // O filho esquerdo de p se tornará a nova raiz
    NoAVL* q = p->esq;
    
    // O filho direito de q se torna o filho esquerdo de p
    p->esq = q->dir;
    
    // p se torna o filho direito de q
    q->dir = p;
    
    // Atualiza as alturas de p e q
    p->atualizaAltura();
    q->atualizaAltura();
    
    // Retorna a nova raiz (q)
    return q;
}
