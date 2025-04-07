#ifndef NOABB_H
#define NOABB_H

class NoABB
{
	private:

		int valor;
		NoABB* esq;
		NoABB* dir;

	public:

		// resolver no quadro primeiro
		NoABB(int valor);
		~NoABB();
		int getValor();
		NoABB* getEsq();
		NoABB* getDir();
		void setValor(int valor);
		void setEsq(NoABB* no);
		void setDir(NoABB* no);

		// exercícios
		void insere(int valor);
		NoABB* busca(int valor);
		void imprimeOrdemCrescente();
		void imprimeVisualizacao(int n);
		int soma();
		int contaNos(); // Nova função para contar nós na subárvore
		bool ehCheia();
		bool ehCompleta(int index, int numNos);
		int altura();
		void imprimeIntervalo(int x, int y);
		bool estritamenteBinaria();
		int maioresQue(int valor);
		void somaENosNoNivel(int nivel, int nivelAtual, int& soma, int& contadorNos);

		// resolver no quadro por último
		NoABB* remove(NoABB* no, int valor);
};

#endif
