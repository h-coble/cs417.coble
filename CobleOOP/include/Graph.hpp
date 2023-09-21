#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <functional>

template <class N>
class Graph
{
public:
	Graph() {};
	Graph(std::vector<N> nodes, std::vector<std::pair<N, N>> edges) {};
	virtual ~Graph() {};

	virtual void deleteNode(N node)=0;
	virtual void addNode(N x) = 0;
	virtual void addEdge(N x, N y) = 0;
	virtual void deleteEdge(N x, N y) = 0;
};

template <class N>
class AdjListGraph : public Graph<N>
{
private:
	using Edges = std::list<std::pair<int, int>>;
	std::vector<N> nodeVector;						//A vector of node values - objects
	std::vector<Edges> edgesVector;					//A vector of entries to show nodes adjacent; Nodes in pair are represented by their corresponding index in the nodeVector <source, dest>
public:
	//========| CONSTRUCTOR/DESTRUCTOR |========================

	//Default
	AdjListGraph() : Graph<N>() {};

	//Copy
	AdjListGraph(const AdjListGraph& other) : Graph<N>()
	{
		nodeVector = other.nodeVector;
		edgesVector = other.edgesVector;
	}

	//Assignment Operator
	AdjListGraph& operator= (const AdjListGraph& source)
	{
		AdjListGraph<N> tempGraph = source;
		this->nodeVector = source.nodeVector;
		this->edgesVector = source.edgesVector;
		return tempGraph;
	}

	//Specified Constructor
	AdjListGraph(std::vector<N> newNodes, std::vector<std::pair<N, N>> newEdges) : Graph<N>(newNodes, newEdges) { }

	//Destructor
	~AdjListGraph() {}
	//===========================================================

	//============| METHODS |================
	
	virtual void addNode(N node)
	{
		//Prevent duplicates
		for (int i = 0; i < nodeVector.size(); i++)
		{
			if (nodeVector[i] == node)
			{
				return;
			}
		}
		nodeVector.push_back(node);
		Edges temp;
		edgesVector.push_back(temp);
	}
	virtual void  addEdge(N source, N dest)
	{
		int x_index = -1;
		int y_index = -1;
		for (int i = 0; i < nodeVector.size(); i++)
		{
			//Find node in nodeVector and record their index 
			if (nodeVector[i] == source)
			{
				x_index = i;
			}
			if (nodeVector[i] == dest)
			{
				y_index = i;
			}
		}
		if (x_index < 0)
		{
			std::cout << "Source node not found\n";
			return;
		}
		if (y_index < 0)
		{
			addNode(dest);
			y_index = nodeVector.size() - 1;
		}
		std::pair<int, int> newPair;
		newPair.first = x_index;
		newPair.second = y_index;
		edgesVector[x_index].push_back(newPair);
	}
	virtual void deleteEdge(N source, N dest)
	{
		int x_index = -1;	//source index
		int y_index = -1;	//dest index
		bool found = true;
		for (int i = 0; i < nodeVector.size(); i++)
		{
			//Find node in nodeVector and record the index 
			if (nodeVector[i] == source)
			{
				x_index = i;
			}
			if (nodeVector[i] == dest)
			{
				y_index = i;
			}
		}
		if (x_index < 0)
		{
			std::cout << "Source node not found\n";
			found = false;
		}
		if (y_index < 0)
		{
			std::cout << "Destination node not foudn\n;";
			found = false;
		}
		if (!found)
		{
			std::cout << "No such node and edge exist.\n";
			return;
		}
		else
		{
			std::pair<int, int> edgeRemoval;
			edgeRemoval.first = x_index;
			edgeRemoval.second = y_index;
			edgesVector[x_index].remove(edgeRemoval);
		}
	}
	virtual void deleteNode(N node)
	{
		int x_index = -1;
		for (int i = 0; i < nodeVector.size(); i++)
		{
			//Find node in nodeVector and record the index 
			if (nodeVector[i] == node)
			{
				x_index = i;
			}
		}
		if (x_index < 0)
		{
			std::cout << "Node node not found\n";
		}
		else
		{
			for (int first = 0; first < nodeVector.size(); first++)
			{
				if (first == x_index)
					edgesVector[first].clear();
				else
				{
					//Remove all edges from ____ (first) to node at x_index
					deleteEdge(nodeVector[first], nodeVector[x_index]);
				}
			}

			for (int i = x_index; i < edgesVector.size(); i++)
			{
				edgesVector[i].clear();

				int iPlusOne = i + 1;
				if (iPlusOne >= edgesVector.size())		//If next subscript is out of range
					continue;
				for (auto edge : edgesVector[iPlusOne])
				{
					if (!edgesVector[iPlusOne].empty())
					{
						edge.first -= 1;
						if (edge.second > x_index)	//If destination will be moved left
							edge.second -= 1;		//Adjust pair accordingly (shift left by one as well)
						edgesVector[i].push_back(edge);
					}
				}
				nodeVector[i] = nodeVector[iPlusOne];
			}
			//Once nodes are shifted/overwritten, pop the back, which is now a duplicate
			edgesVector.pop_back();
			nodeVector.pop_back();
		}
	}

	
};
