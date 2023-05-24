
//1:12:33

//输入5行5列迷宫路径  
//0表示能走，1表示不能走
/*
0 0 0 1 1
1 0 0 0 1
1 1 0 1 1
1 1 0 0 1
1 1 1 0 0
*/



#include <stack>
#include <iostream>
using namespace std;
//定义迷宫每一个节点的四个方向
const int RIGHT = 0;
const int DOWN = 1;
const int LEFT = 2;
const int UP = 3;

//迷宫每一个节点方向的数量
const int WAY_NUM = 4;

//定义节点行走状态
const int YES = 4;
const int NO = 5;

//迷宫
class Maze
{
private:
	//定义迷宫节点路径信息
	struct Node
	{
		int _x;
		int _y;
		int _val;  //节点的值
		int _state[WAY_NUM];   //记录节点四个方向的状态
	};

	Node** _pMaze;   //动态生成迷宫路径
	int _row;
	int _col;
	stack<Node> _stack;

public:
	Maze(int row, int col):_row(row),_col(col)
	{
		//动态开辟二维数组，表示迷宫的路径
		_pMaze = new Node * [_row];   
		for (int i = 0; i < _row; ++i)
		{
			_pMaze[i] = new Node[_col];
		}
	}

	//初始化迷宫路径的节点信息
	void initNode(int x, int y, int val)
	{
		_pMaze[x][y]._x = x;
		_pMaze[x][y]._y = y;
		_pMaze[x][y]._val = val;
		//节点四个方向默认的初始化为不能走
		for (int i = 0;i < WAY_NUM; ++i)
		{
			_pMaze[x][y]._state[i] = NO;
		}
	}

	//初始化迷宫节点四个方向的行走状态信息
	void setNodeState()
	{
		for (int i = 0; i < _row; ++i)
		{
			for (int j = 0; j < _col; ++j)
			{
				if (_pMaze[i][j]._val == 1)  //当前节点值为1表示当前节点不可通行，不用调整该节点的行走状态信息
				{
					continue;
				}

				if (j < _col - 1 && _pMaze[i][j + 1]._val == 0) //当前节点的右方向是0
				{
					_pMaze[i][j]._state[RIGHT] = YES;
				}

				if (i < _row - 1 && _pMaze[i + 1][j]._val == 0)  //当前节点的下方是0
				{
					_pMaze[i][j]._state[DOWN] = YES;
				}

				if (j > 0 && _pMaze[i][j - 1]._val == 0)  //当前节点的左方向是0
				{
					_pMaze[i][j]._state[LEFT] = YES;
				}

				if (i > 0 && _pMaze[i - 1][j]._val == 0)  //当前节点的上方是0
				{
					_pMaze[i][j]._state[UP] = YES;
				}
			}
		}
	}

	//从左上角开始深度搜索迷宫路径
	void searchMazePath()
	{
		if (_pMaze[0][0]._val == 1)
			return;
		_stack.push(_pMaze[0][0]);

		while (!_stack.empty())
		{
			Node top = _stack.top();
			int x = top._x;
			int y = top._y;

			//已经找到右下角出口的迷宫路径
			if (x == _row - 1 && y == _col - 1)
				return;

			//往右方向寻找
			if (_pMaze[x][y]._state[RIGHT] == YES)
			{
				_pMaze[x][y]._state[RIGHT] = NO;
				_pMaze[x][y + 1]._state[LEFT] = NO;
				_stack.push(_pMaze[x][y + 1]);
				continue;
			}

			//往下方向寻找
			if (_pMaze[x][y]._state[DOWN] == YES)
			{
				_pMaze[x][y]._state[DOWN] = NO;
				_pMaze[x + 1][y]._state[UP] = NO;
				_stack.push(_pMaze[x + 1][y]);
				continue;
			}

			//往左方向寻找
			if (_pMaze[x][y]._state[LEFT] == YES)
			{
				_pMaze[x][y]._state[LEFT] = NO;
				_pMaze[x][y - 1]._state[RIGHT] = NO;
				_stack.push(_pMaze[x][y - 1]);
				continue;
			}

			//往上方向寻找
			if (_pMaze[x][y]._state[UP] == YES)
			{
				_pMaze[x][y]._state[UP] = NO;
				_pMaze[x - 1][y]._state[DOWN] = NO;
				_stack.push(_pMaze[x - 1][y]);
				continue;
			}

			_stack.pop();  //上下左右都不能走  走过后会拆桥，所有会造成上下左右都没有路的情况
		}
	}

	//打印迷宫路径
	void showMazePath()
	{
		if (_stack.empty())
			cout << "不存在一条迷宫路径" << endl;
		else
		{
			cout << endl;
			while (!_stack.empty())
			{
				Node top = _stack.top();
				_pMaze[top._x][top._y]._val = '*';
				_stack.pop();
			}
			for (int i = 0; i < _row; ++i)
			{
				for (int j = 0; j < _col; ++j)
				{
					if(_pMaze[i][j]._val == '*')
					{
						cout << "* ";
					}
					else
					{
						cout << _pMaze[i][j]._val << " ";
					}
				}
				cout << endl;
			}
			cout << endl;
		}
	}
};


#if 0
int main()
{
	cout << "输入迷宫的行列数（如：10 10):";
	int row, col, data;
	cin >> row >> col;

	Maze maze(row, col);   //创建迷宫对象

	cout << "输入迷宫具体的路径信息（0表示可以走，1表示不能走）：" << endl;

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			cin >> data;
			//初始化迷宫节点的基本信息
			maze.initNode(i, j, data);
		}
	}

	//设置所有节点四个方向的状态
	maze.setNodeState();

	//开始从左上角搜索迷宫路径
	maze.searchMazePath();

	//打印迷宫路径搜索的结果
	maze.showMazePath();

	return 0;
}

#endif