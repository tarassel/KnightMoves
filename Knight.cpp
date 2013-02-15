/*
// Deep drilling, wrong, should go wide not down
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
	string str(){
 		ostringstream oss;
		oss << "[" << x << ":" << y << "]";
		return oss.str();
	}
};

vector<Pos> moves;
vector<Pos> visitedCells;
unsigned size = 4;

bool IsOnBoard(Pos& pos)
{
	if (pos.x >= 0 && pos.x < size && pos.y >= 0 && pos.y < size)
		return true;
	return false;
}

vector<Pos> FindMoves(Pos& from)
{
	vector<Pos> possibleMoves;

	if (IsOnBoard(*from.move(-1,2)))
		possibleMoves.push_back(from);
	if (IsOnBoard(*from.move(-1,-1)))
		possibleMoves.push_back(from);
	if (IsOnBoard(*from.move(0,-2)))
		possibleMoves.push_back(from);
	if (IsOnBoard(*from.move(1,-1)))
		possibleMoves.push_back(from);
	if (IsOnBoard(*from.move(2,0)))
		possibleMoves.push_back(from);
	if (IsOnBoard(*from.move(1,1)))
		possibleMoves.push_back(from);
	if (IsOnBoard(*from.move(0,2)))
		possibleMoves.push_back(from);
	if (IsOnBoard(*from.move(-1,1)))
		possibleMoves.push_back(from);

	return possibleMoves;
}

struct MovesNode
{
	MovesNode(){}
	MovesNode(Pos p): pos(p){}

	Pos pos;
	vector<MovesNode> moves;
};

void AddLayersUpTo(Pos& from, MovesNode& node, Pos& to)
{
	cout << "Adding layer for " << from.str() << endl;
	node.pos = from;
	vector<Pos> moves = FindMoves(from);
	for (unsigned i=0; i<moves.size() && find(visitedCells.begin(), visitedCells.end(), moves[i]) == visitedCells.end(); i++)
	{
		cout << "> New node " << moves[i].str() << endl;
		MovesNode newNode(moves[i]);
		// Continue only if not found
		if (moves[i] != to)
		{
			visitedCells.push_back(moves[i]);
			AddLayersUpTo(moves[i], newNode, to);
		}
		else
			cout << "FOUND IT!" << endl;
		node.moves.push_back(newNode);
	}
	cout << "Exit from layer" << endl;
}

vector<Pos> GetKnightPath(Pos from, Pos to)
{
	MovesNode root;
	visitedCells.push_back(from);

	AddLayersUpTo(from, root, to);

	return vector<Pos>();
}





int _tmain(int argc, _TCHAR* argv[])
{
	size = 4;
	Pos from(0,0), to(3,3);
	cout << "Start for board " << size << "x" << size << " from " << from.str() << " to " << to.str() << endl;
	GetKnightPath(from, to);

	return 0;
}*/
