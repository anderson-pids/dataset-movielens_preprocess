#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>

using namespace std;

typedef map<int,double> Edge;

class Vertex
{
public:
	Vertex() { mE = new map<int,double>(); }
	~Vertex() { delete mE; }

	void AddEdge(int vertex, double value);
	string GetId();
	void SetId(string id);
	void Show();
	void at(int vertex, double value);
	double at(int vertex);
	int Size();
	Edge::iterator begin();
	Edge::iterator end();
	Edge::iterator find(int e);

private:
	string mId;	
	Edge* mE;
};

typedef map<int, Vertex*> G;

class Graph
{

public:

	Graph() { mGraph = new map<int, Vertex* >(); }
	~Graph();
	
	//copia o grafo atual
	Graph* Clone();
	//imprime todos os vertices e arestas do grafo
	void Show();
	// //Adiciona Vertice
	void AddVertex(int v, string id = "");
	// //Adiciona aresta
	void AddEdge(int a, int b, double peso=1);
	//retorna o numero de vertices
	int Size();
	//altera aresta de um vertice para outro vertice
	void SetEdge(int v1, int v2, double value);
	//retorna a aresta entre um vertice v1 e vertice v2
	double GetEdge(int v1, int v2);
	//Altera todas arestas com um valor padrao
	void Clear(double vDefault = 0);
	// Verifica se tem o vertice v no grafo
	bool HasVertex(int v);

	// strategy to access operator [][]
	// class Proxy
	// {
	// 	Graph& _h;
	// 	int _i;
	// public:
	// 	Proxy(Graph& h, int i): _h(h), _i(i) {}
	// 	double& operator[](int j) { 
	// 		return _h.mGraph->at(_i)->at(j);
	// 	}
	// };
	// Proxy operator[](int i) { return Proxy(*this, i); }

	G::iterator begin();
	G::iterator end();
	Vertex* at(int v);
	void PrintPair(string outputName);
	void PrintList(string outputName, int start_pos = 0);

private:
	G *mGraph;
};

#endif