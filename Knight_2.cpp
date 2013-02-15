// Go wide

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

struct Pos
{
	Pos():x(0),y(0){}
	Pos(int _x, int _y):x(_x),y(_y){}
	int x, y;
	Pos* move(int _x, int _y){x += _x; y += _y; return this;}
	bool operator==(const Pos& rval) const { if (x == rval.x && y == rval.y) return true; return false;}
	bool operator!=(const Pos& rval) const { return !(*this==rval);}
	string str() const {
 		ostringstream oss;
		oss << "[" << x << ":" << y << "]";
		return oss.str();
	}
};

vector<Pos> moves;
vector<Pos> visitedCells;
unsigned size = 4;

bool IsOnBoard(const Pos& pos)
{
	if (pos.x >= 0 && pos.x < size && pos.y >= 0 && pos.y < size)
		return true;
	return false;
}

vector<Pos> FindMoves(const Pos& from)
{
	vector<Pos> possibleMoves;
	Pos fromLoc = from;

	if (IsOnBoard(*fromLoc.move(-1,2)))
		possibleMoves.push_back(fromLoc);
	if (IsOnBoard(*fromLoc.move(-1,-1)))
		possibleMoves.push_back(fromLoc);
	if (IsOnBoard(*fromLoc.move(0,-2)))
		possibleMoves.push_back(fromLoc);
	if (IsOnBoard(*fromLoc.move(1,-1)))
		possibleMoves.push_back(fromLoc);
	if (IsOnBoard(*fromLoc.move(2,0)))
		possibleMoves.push_back(fromLoc);
	if (IsOnBoard(*fromLoc.move(1,1)))
		possibleMoves.push_back(fromLoc);
	if (IsOnBoard(*fromLoc.move(0,2)))
		possibleMoves.push_back(fromLoc);
	if (IsOnBoard(*fromLoc.move(-1,1)))
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
			oss << "[" << node->pos.x << ":" << node->pos.y << "] ";
			node = node->parent;
		} while (node);
		return oss.str();
	}
};

vector<Pos> GetKnightPath(const Pos& from, const Pos& to)
{
	vector<Pos> resPath;
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
			resPath.push_back(resNode->pos);
			resNode = resNode->parent;
		} while (resNode);
	}

	return resPath;
}

int _tmain(int argc, _TCHAR* argv[])
{
	size = 8;
	Pos from(0,0), to(7,7);
	cout << "Start for board " << size << "x" << size << " from " << from.str() << " to " << to.str() << endl;
	vector<Pos> resPath = GetKnightPath(from, to);

	if (resPath.empty())
		cout << "No results found" << endl;
	else
	{
		cout << "Result: ";
		for (vector<Pos>::reverse_iterator pos = resPath.rbegin(); pos != resPath.rend(); ++pos)
			cout << " -> " << pos->str();
		cout << endl;
	}

	return 0;
}
