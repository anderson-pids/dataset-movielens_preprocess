#include "graph.h"

Graph::~Graph()
{
	for (G::iterator it = mGraph->begin(); it!=mGraph->end(); ++it)
	{
		delete(it->second);
	}

	delete(mGraph);
}

Graph* Graph::Clone()
{
	Graph *copia = new Graph();
	double value;
	Vertex *v;
	for(int i = 0; i < mGraph->size(); ++i)
	{		
		copia->AddVertex(i, mGraph->at(i)->GetId());
		v = mGraph->at(i);

		for(Edge::iterator it = v->begin(); it != v->end(); ++it)
		{
			value = mGraph->at(i)->at(it->first);
			copia->AddEdge(i,it->first, value);
		}
	}

	return copia;
}

void Graph::Show()
{
	Vertex* v;

	for (G::iterator it = mGraph->begin(); it!=mGraph->end(); ++it)
	{
		v = it->second;
		cout << it->first << " (" << v->GetId() << ") =>" << endl;    		
		v->Show();		
	}
}

int Vertex::Size()
{
	return mE->size();
}

string Vertex::GetId()
{
	return mId;
}

void Vertex::SetId(string id)
{
	mId = id;
}

void Vertex::Show()
{
	for (Edge::iterator it_v = mE->begin(); it_v!= mE->end(); ++it_v)
	{
		cout << "\t\t[" << it_v->first << "][" << it_v->second << "]" << endl;
	}
}


bool Graph::HasVertex(int v)
{
	G::iterator it = mGraph->find(v);

	if(it != mGraph->end())
		return true;
	return false;
}

void Graph::AddVertex(int v, string id)
{
	Vertex *vertex = new Vertex();
	vertex->SetId(id);
	mGraph->insert(make_pair(v,vertex));
}

void Graph::AddEdge(int a, int b, double value)
{
	Vertex *v = mGraph->at(a);		
	v->AddEdge(b, value);
}

void Vertex::AddEdge(int vertex, double value)
{
	mE->insert(make_pair(vertex,value));	
}

int Graph::Size()
{
	return mGraph->size();
}

void Graph::SetEdge(int v1, int v2, double value)
{
	mGraph->at(v1)->at(v2,value);
}

void Vertex::at(int vertex, double value)
{
	mE->at(vertex) = value;
}

double Vertex::at(int vertex)
{
	Edge::iterator found = mE->find(vertex);
	if(found != mE->end())
		return mE->at(vertex);
	return 0;
}

Edge::iterator Vertex::find(int e)
{
	return mE->find(e);
}

Edge::iterator Vertex::begin()
{
	return mE->begin();
}

Edge::iterator Vertex::end()
{
	return mE->end();
}

Vertex* Graph::at(int v)
{
	return mGraph->at(v);
}

G::iterator Graph::begin()
{
	return mGraph->begin();
}

G::iterator Graph::end()
{
	return mGraph->end();
}

double Graph::GetEdge(int v1, int v2)
{
	return mGraph->at(v1)->at(v2);
}

void Graph::Clear(double vDefault)
{
	Vertex* vertex;

	for (G::iterator it = mGraph->begin(); it!=mGraph->end(); ++it)
	{
		vertex = it->second;

		for (Edge::iterator itEdge = vertex->begin(); itEdge != vertex->end(); ++itEdge)
		{
			itEdge->second = vDefault;
		}
	}
}

void Graph::PrintPair(string outputName)
{
	fstream fs(outputName, ios::out);
	Vertex* v;

	for (G::iterator it = mGraph->begin(); it!=mGraph->end(); ++it)
	{
		v = it->second;
		fs << it->first << " " << v->GetId() << endl;    		

		Edge::iterator it_v = v->begin();
		fs << it_v->first << " " << it_v->second;
		++it_v;
		for (; it_v!= v->end(); ++it_v)
		{
			fs << " " << it_v->first << " " << it_v->second;
		}

		fs << endl;
	}
}

void Graph::PrintList(string outputName, int start_pos)
{
	fstream fs(outputName, ios::out);
	Vertex *arestas;

	for (G::iterator it = mGraph->begin(); it!=mGraph->end(); ++it)
	{
		arestas = it->second;

		for (Edge::iterator it_aresta = arestas->begin(); it_aresta!=arestas->end(); ++it_aresta)
		{
			fs << it->first + start_pos << "  ";
			fs << it_aresta->first + start_pos << "  " << it_aresta->second << endl;
		}
	}

	fs.close();
}