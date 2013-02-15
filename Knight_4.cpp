// Find all pathes

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <utility>

using namespace std;

typedef pair<int, int> Pos;
#define X(p) p.first
#define Y(p) p.second
Pos& move(Pos& p, int x, int y){X(p) += x; Y(p) += y; return p;}
string strpos(const Pos& p) {
  	ostringstream oss;
 	oss << "[" << X(p) << ":" << Y(p) << "]";
 	return oss.str();
}

vector<Pos> moves;
vector<Pos> visitedCells;
unsigned size = 4;

bool IsOnBoard(const Pos& pos)
{
	if (X(pos) >= 0 && X(pos) < size && Y(pos) >= 0 && Y(pos) < size)
		return true;
	return false;
}

vector<Pos> FindMoves(const Pos& from)
{
	vector<Pos> possibleMoves;
	Pos fromLoc = from;

	if (IsOnBoard(move(fromLoc,-1,2)))
		possibleMoves.push_back(fromLoc);
	if (IsOnBoard(move(fromLoc,-1,-1)))
		possibleMoves.push_back(fromLoc);
	if (IsOnBoard(move(fromLoc,0,-2)))
		possibleMoves.push_back(fromLoc);
	if (IsOnBoard(move(fromLoc,1,-1)))
		possibleMoves.push_back(fromLoc);
	if (IsOnBoard(move(fromLoc,2,0)))
		possibleMoves.push_back(fromLoc);
	if (IsOnBoard(move(fromLoc,1,1)))
		possibleMoves.push_back(fromLoc);
	if (IsOnBoard(move(fromLoc,0,2)))
		possibleMoves.push_back(fromLoc);
	if (IsOnBoard(move(fromLoc,-1,1)))
		possibleMoves.push_back(fromLoc);

	return possibleMoves;
}

struct MovesNode
{
	MovesNode():parent(0){}
	MovesNode(Pos p, MovesNode* par): pos(p), parent(par){}

	MovesNode* parent;
	Pos pos;
	vector<MovesNode> moves;
	string strPath() const {
		ostringstream oss;
		const MovesNode* node = this;
		do 
		{
			oss << "[" << X(node->pos) << ":" << Y(node->pos) << "] ";
			node = node->parent;
		} while (node);
		return oss.str();
	}
};

vector<vector<Pos>> GetKnightPath(const Pos& from, const Pos& to)
{
	vector<vector<Pos>> resPathes;
	vector<MovesNode*> resNodes;
	MovesNode root;
	root.pos = from;
	visitedCells.push_back(from);

	vector<MovesNode*> currLevel, nextLevel;
	currLevel.push_back(&root);

	cout << "Exploring root layer" << endl;

	while(!currLevel.empty())
	{
		MovesNode* node = currLevel.back();
		currLevel.pop_back();

		if (node->pos == to)
		{
			cout << "FOUND IT!!!" << endl;
			resNodes.push_back(node);
		}
		else
		{
			vector<Pos> moves = FindMoves(node->pos);
			for (unsigned i=0; i<moves.size(); i++)
			{
				if (find(visitedCells.begin(), visitedCells.end(), moves[i]) != visitedCells.end())
					continue;
				cout << "> New node: ";
				node->moves.push_back(MovesNode(moves[i], node));
				cout << node->moves.back().strPath() << endl;
				// Allow other to find "to"
				if (moves[i] != to)
					visitedCells.push_back(moves[i]);
			}
			// Copy subnodes to next level
			for (vector<MovesNode>::iterator pos = node->moves.begin(); pos != node->moves.end(); ++pos)
				nextLevel.insert(nextLevel.end(), &(*pos));
		}

		if (currLevel.empty())
		{
			cout << "Exit from layer" << endl;

			if (resNodes.empty())
			{
				currLevel = nextLevel;
				nextLevel.clear();
				cout << "Exploring next layer" << endl;
			}
		}
	}
	cout << "Search complete" << endl;

	// Expand result node to path
	if (!resNodes.empty())
	{
		MovesNode* resNode = resNodes.back();
		resNodes.pop_back();

		do 
		{
			resPath.push_back(resNode->pos); // fix
			resNode = resNode->parent;
		} while (resNode);
	}

	return resPathes;
}

int _tmain(int argc, _TCHAR* argv[])
{
	size = 8;
	Pos from(0,0), to(7,7);
	cout << "Start for board " << size << "x" << size << " from " << strpos(from) << " to " << strpos(to) << endl;
	vector<vector<Pos>> resPathes = GetKnightPath(from, to);

	if (resPath.empty())
		cout << "No results found" << endl;
	else
	{
		cout << "Result: ";
		for (vector<Pos>::reverse_iterator pos = resPath.rbegin(); pos != resPath.rend(); ++pos) // fix
			cout << " -> " << strpos(*pos);
		cout << endl;
	}

	return 0;
}

