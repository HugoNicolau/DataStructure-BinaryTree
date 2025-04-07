#include <iostream>
#include "ABB.h"
#include "NoABB.h"
#include "NoLSE.h"

using namespace std;

ABB::ABB()
{
	this->raiz = NULL;
}

ABB::~ABB()
{
	delete this->raiz;
}

bool ABB::vazia()
{
	return this->raiz == NULL;
}

void ABB::insere(int valor)
{
	if (this->vazia())
		this->raiz = new NoABB(valor);
	else
		this->raiz->insere(valor);
}

NoABB* ABB::busca(int valor)
{
	if (this->vazia())
		return NULL;
	return this->raiz->busca(valor);
}

void ABB::remove(int valor)
{
	if (!this->vazia())
		this->raiz = this->raiz->remove(this->raiz, valor);
}

void ABB::imprimeEmLargura()
{
	if (!this->vazia())
	{
		NoLSE* lista = new NoLSE(this->raiz);
		for (NoLSE* p = lista; p != NULL; p = p->getProx())
		{
			cout << p->getNo()->getValor() << ", ";
			p->insere(p->getNo()->getEsq());
			p->insere(p->getNo()->getDir());
		}
		delete lista;
	}
	cout << "\b\b  " << endl;
}

void ABB::imprimeOrdemCrescente()
{
	if (!this->vazia())
		this->raiz->imprimeOrdemCrescente();
	cout << "\b\b  " << endl;
}

void ABB::imprimeVisualizacao()
{
	if (!this->vazia())
		this->raiz->imprimeVisualizacao(0);
}

void ABB::destroiArvore()
{
	delete this->raiz;
	this->raiz = NULL;
}

int ABB::soma()
{
    if (this->vazia())
        return 0;
    return this->raiz->soma();
}

float ABB::media()
{
    if (this->vazia())
        return 0.0f;
    
    int totalSoma = this->raiz->soma();
    int totalNos = this->raiz->contaNos();
    
    // Evitar divisão por zero, embora não deva ocorrer se a árvore não estiver vazia
    if (totalNos == 0)
        return 0.0f;
        
    return static_cast<float>(totalSoma) / totalNos;
}

bool ABB::ehCheia()
{
    if (this->vazia())
        return true;  // Uma árvore vazia é considerada cheia por definição
    
    return this->raiz->ehCheia();
}

bool ABB::ehCompleta()
{
    if (this->vazia())
        return true;  // Uma árvore vazia é considerada completa por definição
        
    // Precisamos contar o número total de nós
    int numNos = this->raiz->contaNos();
    
    // Começamos com o índice 0 (raiz) e verificamos se a árvore é completa
    return this->raiz->ehCompleta(0, numNos);
}

void ABB::imprimeIntervalo(int x, int y)
{
    if (this->vazia())
        return;
        
    this->raiz->imprimeIntervalo(x, y);
    cout << endl;
}

bool ABB::estritamenteBinaria()
{
    if (this->vazia())
        return true;  // Uma árvore vazia é considerada estritamente binária por definição
    
    return this->raiz->estritamenteBinaria();
}

int ABB::maioresQue(int valor)
{
    if (this->vazia())
        return 0;
    
    return this->raiz->maioresQue(valor);
}

float ABB::mediaNivel(int nivel)
{
    // Árvore vazia ou nível negativo, retorna 0
    if (this->vazia() || nivel < 0)
        return 0.0f;
    
    // Se for o nível 0 (raiz), retorna o valor da raiz
    if (nivel == 0)
        return static_cast<float>(this->raiz->getValor());
    
    // Variáveis para armazenar a soma e a contagem de nós no nível
    int soma = 0;
    int contadorNos = 0;
    
    // Calcula a soma e conta os nós no nível especificado
    this->raiz->somaENosNoNivel(nivel, 0, soma, contadorNos);
    
    // Se não houver nós no nível especificado, retorna 0
    if (contadorNos == 0)
        return 0.0f;
    
    // Calcula e retorna a média
    return static_cast<float>(soma) / contadorNos;
}

void ABB::alturaNos()
{
    if (this->vazia())
    {
        cout << "Arvore vazia" << endl;
        return;
    }
    
    cout << "Altura dos nos da arvore:" << endl;
    this->raiz->imprimeAlturaNos();
}
