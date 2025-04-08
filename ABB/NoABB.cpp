#include <iostream>
#include "NoABB.h"

using namespace std;

NoABB::NoABB(int valor)
{
    this->valor = valor;
    this->esq = NULL;
    this->dir = NULL;
    this->height = 0;
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

int NoABB::getHeight()
{
    return this->height;
}

void NoABB::setHeight(int height)
{
    this->height = height;
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
    // Percorre a subárvore esquerda
    if (this->esq != NULL)
        this->esq->imprimeOrdemCrescente();
    
    // Imprime o valor do nó atual com um espaçador adequado
    cout << this->valor << " ";
    
    // Percorre a subárvore direita
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

bool NoABB::ehCheia()
{
    // Caso 1: Nó folha (sem filhos)
    if (this->esq == NULL && this->dir == NULL)
        return true;
    
    // Caso 2: Nó com dois filhos
    if (this->esq != NULL && this->dir != NULL)
        // Recursivamente verifica se as subárvores também são cheias
        return this->esq->ehCheia() && this->dir->ehCheia();
    
    // Caso 3: Nó com apenas um filho (não é uma árvore cheia)
    return false;
}

int NoABB::altura()
{
    // Altura da subárvore esquerda
    int alturaEsq = 0;
    if (this->esq != NULL)
        alturaEsq = this->esq->altura();
        
    // Altura da subárvore direita
    int alturaDir = 0;
    if (this->dir != NULL)
        alturaDir = this->dir->altura();
        
    // Retorna a maior altura + 1 (para incluir o nó atual)
    return (alturaEsq > alturaDir ? alturaEsq : alturaDir) + 1;
}

bool NoABB::ehCompleta(int index, int numNos)
{
    // Se o índice for maior que o número de nós, não é completa
    if (index >= numNos)
        return false;
        
    // Verifica recursivamente as subárvores
    // O índice do filho esquerdo é 2*i + 1 e do filho direito é 2*i + 2
    bool esqCompleta = true;
    bool dirCompleta = true;
    
    if (this->esq != NULL)
        esqCompleta = this->esq->ehCompleta(2*index + 1, numNos);
        
    if (this->dir != NULL)
        dirCompleta = this->dir->ehCompleta(2*index + 2, numNos);
        
    // Ambas as subárvores devem ser completas
    return esqCompleta && dirCompleta;
}

void NoABB::imprimeIntervalo(int x, int y)
{
    // Usando o princípio de percurso em ordem para visitar os nós em ordem crescente
    
    // 1. Se o valor atual for maior ou igual a x, explore a subárvore esquerda
    // (pois pode conter valores no intervalo)
    if (this->valor >= x && this->esq != NULL)
        this->esq->imprimeIntervalo(x, y);
    
    // 2. Se o valor atual estiver no intervalo [x, y], imprima-o
    if (this->valor >= x && this->valor <= y)
        cout << this->valor << " ";
    
    // 3. Se o valor atual for menor ou igual a y, explore a subárvore direita
    // (pois pode conter valores no intervalo)
    if (this->valor <= y && this->dir != NULL)
        this->dir->imprimeIntervalo(x, y);
}

bool NoABB::estritamenteBinaria()
{
    // Caso 1: Nó folha (sem filhos)
    if (this->esq == NULL && this->dir == NULL)
        return true;
    
    // Caso 2: Nó com dois filhos - verifica recursivamente as subárvores
    if (this->esq != NULL && this->dir != NULL)
        return this->esq->estritamenteBinaria() && this->dir->estritamenteBinaria();
    
    // Caso 3: Nó com apenas um filho - não é estritamente binária
    return false;
}

int NoABB::maioresQue(int valor)
{
    int contador = 0;
    
    // Se o valor atual é menor ou igual ao parâmetro
    if (this->valor <= valor)
    {
        // Só precisamos verificar a subárvore direita, pois toda a subárvore
        // esquerda terá valores menores ou iguais ao nó atual
        if (this->dir != NULL)
            contador += this->dir->maioresQue(valor);
    }
    // Se o valor atual é maior que o parâmetro
    else
    {
        // Contamos o nó atual
        contador = 1;
        
        // Precisamos verificar ambas as subárvores
        if (this->esq != NULL)
            contador += this->esq->maioresQue(valor);
        
        if (this->dir != NULL)
            contador += this->dir->maioresQue(valor);
    }
    
    return contador;
}

void NoABB::somaENosNoNivel(int nivel, int nivelAtual, int& soma, int& contadorNos)
{
    // Se chegamos ao nível desejado
    if (nivelAtual == nivel)
    {
        soma += this->valor;
        contadorNos++;
        return;
    }
    
    // Se ainda não chegamos ao nível desejado, continuamos descendo na árvore
    if (nivelAtual < nivel)
    {
        // Verifica subárvore esquerda
        if (this->esq != NULL)
            this->esq->somaENosNoNivel(nivel, nivelAtual + 1, soma, contadorNos);
        
        // Verifica subárvore direita
        if (this->dir != NULL)
            this->dir->somaENosNoNivel(nivel, nivelAtual + 1, soma, contadorNos);
    }
    
    // Se o nível atual for maior que o desejado, não há mais o que fazer
    // (isso não deve acontecer na chamada recursiva normal)
}

void NoABB::imprimeAlturaNos()
{
    // Calcula a altura do nó atual e salva no campo height
    this->height = this->altura();
    
    // Imprime o valor e a altura do nó atual
    cout << "No " << this->valor << ": altura = " << this->height << endl;
    
    // Percorre a subárvore esquerda
    if (this->esq != NULL)
        this->esq->imprimeAlturaNos();
    
    // Percorre a subárvore direita
    if (this->dir != NULL)
        this->dir->imprimeAlturaNos();
}

bool NoABB::ehPerfeita(int altura, int nivel)
{
    // Caso 1: Nó folha - deve estar no último nível
    if (this->esq == NULL && this->dir == NULL)
        return (nivel == altura);
    
    // Caso 2: Nó com apenas um filho - não é perfeita
    if (this->esq == NULL || this->dir == NULL)
        return false;
    
    // Caso 3: Nó com dois filhos - ambas subárvores devem ser perfeitas
    return this->esq->ehPerfeita(altura, nivel + 1) && 
           this->dir->ehPerfeita(altura, nivel + 1);
}
