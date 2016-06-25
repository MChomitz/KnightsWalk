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



/*
	The Node class. This is a simple class that holds only a single datum.
	This class will be the foundation for a vertice class that will be defined later.
*/

template<class T>
class Node
{
public:
	Node(T datum);

	T getDatum();
	void setDatum(const T& datum);

	virtual int getValue() const = 0;
	virtual valueUp() const = 0;
	virtual valueDown() const = 0;
private:
	T m_Datum;
};

template<class T>
Node<T>::Node(T datum) :
	m_Datum(datum)
{}

template<class T>
T getDatum()
{
	return m_Datum;
}

template<class T>
void Node<T>::setDatum(const T& datum)
{
	m_Datum = datum;
}

template<class T>
int getValue()
{
	return 0;
}




/*
	The Path class. This object will link two nodes together.
	Through inheiritance, the nodes stored in the path will know how many paths they are connected to.
	These form the links in a graph.
*/

template<class T>
class Path
{
public:
	Path(const Node<T>& origin, const Node<T>& end);	//ctor
	~Path();											//dtor
	Path(const Path& c);								//copy ctor
	Path(Path&& m);										//move ctor
	Path& operator=(const Path& c);						//copy ass op
	Path& operator=(Path&& m);							//move ass op

	bool checkActive();
	void calculateValue();
	void toggle();
	void valueUp();
	void valueDown();
private:
	int m_Value;
	bool m_Active;
	std::vector<Node*> m_LinkedNodes;
};

template<class T>
Path<T>::Path(const Node<T>& origin, const Node<T>& end) :	//ctor
	m_Active(true),
	m_Value(0)
{
	m_LinkedNodes.resize(2);
	Node<T>* newOrigin = new Node<T>(origin);
	m_LinkedNodes[0](newOrigin);
	Node<T>* newEnd = new Node<T>(end);
	m_LinkedNodes[1](newEnd);
}

template<class T>
Path<T>::~Path()											//dtor
{
	delete m_LinkedNodes[0];
	delete m_LinkedNodes[1];
}

template<class T>
Path<T>::Path(const Path& c) :								//copy ctor
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
Path<T>::Path(Path&& m) :									//move ctor
	m_Value(m.m_Value),
	m_Active(m.m_active),
	m_LinkedNodes(m.m_LinkedNodes)
{
	m.m_Value = 0;
	m.m_Active = false;
	m.m_LinkedNodes[0] = nullptr;
	m.m_LinkedNodes[1] = nullptr;
}

template<class T>
Path<T>& Path<T>::operator=(const Path& c)					//copy ass op
{
	Path temp(c);
	this* = std::move(temp);
	return this*;
}

template<class T>
Path<T>& Path<T>::operator=(Path&& m)						//move ass op
{
	if (this != &m)
	{
		delete m_LinkedNodes[0];
		delete m_LinkedNodes[1];
		m_LinkedNodes[0] = m.m_LinkedNodes[0];
		m_LinkedNodes[1] = m.m_LinkedNodes[1];
		m.m_LinkedNodes[0] = nullptr;
		m.m_LinkedNodes[1] = nullptr;
		m_Value = m.m_Value;
		m_Active = m.m_Active;
	}
	return this*
}

template<class T>
bool Path<T>::checkActive()
{
	return m_Active;
}

template<class T>
void Path<T>::calculateValue()
{
	int originValue = m_LinkedNodes[0].getValue();
	int endValue = m_LinkedNodes[1].getValue();
	if ((originValue <= 2) || (endValue <= 2))
	{
		m_Value = 0;
	}
	else
	{
		m_Value = originValue + endValue;
	}
}

template<class T>
void Path<T>::toggle()
{
	if (m_Active)
	{
		m_Active = false;
		m_LinkedNodes[0].valueDown();
		m_LinkedNodes[1].valueDown();
	}
	else
	{
		m_Active = true;
		m_LinkedNodes[0].valueUp();
		m_LinkedNodes[1].valueUp();
	}
}

template<class T>
void Path<T>::valueUp()
{
	m_Value++;
}

template<class T>
void Path<T>::valueDown()
{
	m_Value--;
}



/*
The Vertice class. This objects inheirits from Node and can thus be linked using Path.
A vertice is more useful than a node because it knows what paths are connected to it.
*/

template<class T>
class Vertice : public Node
{
public:
	Vertice(T datum);						//ctor
	~Vertice();								//dtor
	Vertice(const Vertice& c);				//copy ctor
	Vertice(Vertice&& m);					//move ctor
	Vertice& operator=(const Vertice& c);	//copy ass op
	Vertice& operator=(Vertice&& m);		//move ass op

	void calculateValue();

	int getValue();
	void valueUp();
	void valueDown();
private:
	std::vector<Path*> m_Paths;
	int m_Value;
};

template<class T>
Vertice<T>::Vertice(T datum) :							//ctor
	Node(datum),
	m_Value(0)
{}

template<class T>
Vertice<T>::~Vertice()									//dtor
{
	for (i = 0; i < m_Value; i++)
	{
		delete m_Paths[i];
	}
}

template<class T>
Vertice<T>::Vertice(const Vertice& c) :					//copy ctor
	Node(c),
	m_Value(c.m_Value),
	m_Paths(c.m_Paths.size())
{
	for (std::size_t i = 0; i < c.m_Paths.size(); i++)
	{
		m_Paths[i] = new Path(*c.m_Paths[i]);
	}
}

template<class T>
Vertice<T>::Vertice(Vertice&& m) :						//move ctor
	Node(m),
	m_Value(m.m_Value),
	m_Paths(m.m_Paths)
{
	for (std::size_t i = 0; i < m.m_Paths.size(); i++)
	{
		m.m_Paths[i] = nullptr;
	}
}

template<class T>
Vertice<T>& Vertice<T>::operator=(const Vertice& c)		//copy ass op
{
	Vertice temp(c);
	this* = std::move(temp);
	return this*;
}

template<class T>
Vertice<T>& Vertice<T>::operator=(Vertice&& m)			//move ass op
{
	if (this != &m)
	{
		Node(m)
		for (int i = 0; i < m_Paths.size(); i++)
		{
			delete m_Paths[i];
		}
		m_Paths.resize(m.m_Paths.size());
		for (int i = 0; j i < m_Paths.size(); i++)
		{
			m_Paths[i] = m.m_Paths[i];
			m.m_Paths[i] = nullptr;
		}
		m_Value = m.m_Value;
	}
}

template<class T>
void Vertice<T>::calculateValue()
{
	m_Value = 0;
	for (int i = 0; i < m_Paths.size(); i++)
	{
		m_Value += m_Paths[i].checkActive();
	}
}

template<class T>
int Vertice<T>::getValue()
{
	return m_Value;
}

template<class T>
void Vertice<T>::valueDown()
{
	m_Value--;
	for (int i = 0; i < m_Paths.size(); i++)
	{
		m_Paths[i].valueDown();
	}
}

template<class T>
void Vertice<T>::valueUp()
{
	m_Value++;
	for (int i = 0; i < m_Paths.size(); i++)
	{
		m_Paths[i].valueUp();
	}
}

#endif // !TREE_H