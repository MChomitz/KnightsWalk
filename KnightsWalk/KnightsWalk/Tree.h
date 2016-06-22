/*

	Tree.h
	MChomitz - June 19, 2016

	This defines a set of template classes that work together to create a "tree."
	The Node class will be the basis for the Vertice class.
	The Path class acts as links between vertices.
	The Vertice class will inherit from the Node class, and contain an array of Paths.

	class Node
		public:
		 stuff
		private:
		 other stuff

	class Path
		public:
		 stuff
		private:
		 other stuff

	class Vertice : Node
		public:
		 stuff
		private
		 other stuff

	Becuase these are template classes, the function definitions are also in the header file.

*/

#ifndef TREE_H

#define TREE_H

#include <vector>

template<class T>
class Node
{
public:
	Node(T data);
private:
	T m_Data;
};

template<class T>
Node<T>::Node(T data) :
	m_Data(data)
{}

template<class T>
class Path
{
public:
	Path(const Node<T>& origin, const Node<T>& end);
	~Path();
	Path(const Path& c);
private:
	int m_Value;
	bool m_Active;
	std::vector<Node*> m_LinkedNodes;
};

template<class T>
Path<T>::Path(const Node<T>& origin, const Node<T>& end)
{
	m_LinkedNodes.resize(2);
	Node<T>* newOrigin = new Node<T>(origin);
	m_LinkedNodes[0](newOrigin);
	Node<T>* newEnd = new Node<T>(end);
	m_LinkedNodes[1](newEnd);
}

template<class T>
Path<T>::~Path()
{
	delete m_LinkedNodes[0];
	delete m_LinkedNodes[1];
}

template<class T>
Path<T>::Path(const Path& c) :
	m_Value(c.m_Value),
	m_Active(c.m_Active)
{

	m_LinkedNodes.resize(2);
	Node<T>* origin = new Node<T>(*c.m_Value[0]);
	m_LinkedNodes[0](origin);
	Node<T>* end = new Node<T>(*c.m_Active[1]);
	m_LinkedNodes[1](end);
}

template<class T>
class Vertice : public Node
{
public:
	Vertice(T data);
	~Vertice();
	Vertice(const Vertice& c);
private:
	std::vector<Path*> m_Paths;
	int m_Value;
};

template<class T>
Vertice<T>::Vertice(T data)
{
	Node(data);
}

template<class T>
Vertice<T>::~Vertice()
{}

template<class T>
Vertice<T>::Vertice(const Vertice& c) :
	Node(c),
	m_Value(c.m_Value),
	m_Paths(c.m_Paths.size())
{
	for (std::size_t i = 0; i < c.m_Paths.size(); i++)
	{
		m_Paths[i] = new Path(*c.m_Paths[i]);
	}
}

#endif // !TREE_H
