#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <string.h>
#include <conio.h>
#include "gameSDK.h"
#define N 4
#define aim 2048
using namespace std;
 
void Game::setchessboard() {               // 初始棋盘生成
	srand((unsigned)time(NULL));
	int x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;;
	int num1, num2, num3, num4;
	num1 = rand() % 100;
	num2 = rand() % 100;
	num3 = rand() % 100;
	num4 = rand() % 100;//num1、num2生成随机数对100取余，大于20时生成2，小于20时生成4
	x1 = rand() % N;
	y1 = rand() % N;
	z1 = rand() % N;//x1,y1控制随机生成数的位置，生成随机数对4取余，能得到0、1、2、3正好对应4*4的数组的下标
	if (num1 > 20) {
		board[x1][y1][z1] = 2;
	}
	else {
		board[x1][y1][z1] = 4;
	}
	do {
		x2 = rand() % N;
		y2 = rand() % N;
		z2 = rand() % N;
	} while (x1 == x2 && y1 == y2 && z1 == z2);//保证两个生成随机的2或者4位置的不重复性
	if (num2 > 20) {
		board[x2][y2][z2] = 2;
	}
	else {
		board[x2][y2][z2] = 4;
	}

	do {
		x3 = rand() % N;
		y3 = rand() % N;
		z3 = rand() % N;
	} while ((x1 == x3 && y1 == y3 && z1 == z3)||(x3 == x2 && y3 == y2 && z3 == z2));//保证两个生成随机的2或者4位置的不重复性
	if (num3 > 20) {
		board[x3][y3][z3] = 2;
	}
	else {
		board[x3][y3][z3] = 4;
	}

	do {
		x4 = rand() % N;
		y4 = rand() % N;
		z4 = rand() % N;
	} while ((x1 == x4 && y1 == y4 && z1 == z4)||(x4 == x2 && y4 == y2 && z4 == z2)||(x4 == x3 && y4 == y3 && z4 == z3));//保证两个生成随机的2或者4位置的不重复性
	if (num4 > 20) {
		board[x4][y4][z4] = 2;
	}
	else {
		board[x4][y4][z4] = 4;
	}
}
 
void Game::printchessboard() {   // 棋盘的打印实现
	cout << "------------------------" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << "|" <<setw(4) << board[i][j][0] << "|";
		}
		cout << endl;
		cout << "------------------------" << endl;
	}
	cout << endl;
	cout << "------------------------" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << "|" <<setw(4) << board[i][j][1] << "|";
		}
		cout << endl;
		cout << "------------------------" << endl;
	}
	cout << endl;
	cout << "------------------------" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << "|" <<setw(4) << board[i][j][2] << "|";
		}
		cout << endl;
		cout << "------------------------" << endl;
	}
	cout << endl;
	cout << "------------------------" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << "|" <<setw(4) << board[i][j][3] << "|";
		}
		cout << endl;
		cout << "------------------------" << endl;
	}

}

void Game::up() {//向上合并，第一行不用向上合并。后一行向前一行来看判断操作。
	//cout << "up" << endl;

	int h = 0;//定义h判断是否要在为0的位置上生成新的2或4
	for (int a = 1; a < N; a++) {
		for (int b = 0; b < N; b++) {
			for(int c = 0; c < N; c++){
				if (board[a][b][c] != 0 && board[a - 1][b][c] == 0) {//出现了0，需要生成2或4，h赋值为1
					h = 1;
					break;
				}
				if (board[a - 1][b][c] == board[a][b][c] && board[a - 1][b][c] != 0) {//有数可以合并，合并后会出现0，需要生成2或4，h赋值为1
					h = 1;
					break;
				}
			}
		}
	}
	for(int d = 0; d < N; d++){
		for (int c = 0; c < N - 1; c++) {//第一行到最后一行的前一行需要操作
			for (int a = c + 1; a > 0; a--) {//从下一行向上一行扫描
				for (int b = 0; b < N; b++) {
					if (board[a - 1][b][d] == 0) {//上一行的数要是为0，就进行交换
						board[a - 1][b][d] = board[a][b][d];
						board[a][b][d] = 0;// 从上往下进行交换
					}
				}
			}
		}
		for (int a = 1; a < N; a++) {
			for (int b = 0; b < N; b++) {
				board[a - 1][b][d] == board[a][b][d] ? board[a - 1][b][d] *= 2, board[a][b][d] = 0 : board[a][b][d] = board[a][b][d]; //上下两个数是否相等，相等就上面的值*2，下面值变成0（等价于向上合并）,不相等就不进行操作
			}
		}
		for (int c = 0; c < N - 1; c++) {//第一行到最后一行的前一行需要操作
			for (int a = c + 1; a > 0; a--) {//从下一行向上一行扫描
				for (int b = 0; b < N; b++) {
					if (board[a - 1][b][d] == 0) {//上一行的数要是为0，就进行交换
						board[a - 1][b][d] = board[a][b][d];
						board[a][b][d] = 0;// 从上往下进行交换
					}
				}
			}
		}//合并操作后再进行一次上移操作，让值都跑到上面去，既进行向上合并操作
	}
	if (h) {
		srand((unsigned)time(NULL));
		int x1, y1, z1, x2, y2, z2;
		do {
			x1 = rand() % N;
			y1 = rand() % N;
			z1 = rand() % N;
		} while (board[x1][y1][z1] != 0);//在为0的位置才能生成新的2或者4
		int num1 = rand() % 100;//与初始化棋盘一样，用来控制在0上生成的数是2还是4
		if (num1 > 20) {
			board[x1][y1][z1] = 2;
			h = 0;
		}
		else {
			board[x1][y1][z1] = 4;
			h = 0;
		}

		do {
			x2 = rand() % N;
			y2 = rand() % N;
			z2 = rand() % N;
		} while (board[x2][y2][z2] != 0 || (x1 == x2 && y1 == y2 && z1 == z2));//在为0的位置才能生成新的2或者4
		int num2 = rand() % 100;//与初始化棋盘一样，用来控制在0上生成的数是2还是4
		if (num2 > 20) {
			board[x2][y2][z2] = 2;
			h = 0;
		}
		else {
			board[x2][y2][z2] = 4;
			h = 0;
		}
	}
}
 
void Game::down() { // 向下合并，最后一行不需要向下进行合并。前一行向后一行判断操作。
	//cout << "down" << endl;
	int h = 0;//定义h判断是否要在为0的位置上生成新的2或4
		for (int a = N - 2; a >= 0; a--) {
			for (int b = 0; b < N; b++) {
				for(int c = 0; c < N; c++){
					if (board[a][b][c] != 0 && board[a + 1][b][c] == 0) {//出现了0，需要生成2或4，h赋值为1
						h = 1;
						break;
					}
					if (board[a + 1][b][c] == board[a][b][c] && board[a + 1][b][c] != 0) {//有数可以合并，合并后会出现0，需要生成2或4，h赋值为1
						h = 1;
						break;
					}
				}
			}
		}
		for(int d = 0; d < N; d++){
			for (int c = N - 1; c > 0; c--) {//最后一行的前一行到第一行需要操作
				for (int a = c - 1; a < N - 1; a++) {//从上一行向下一行扫描
					for (int b = 0; b < N; b++) {
						if (board[a + 1][b][d] == 0) {//下一行的数要是0，就进行交换
							board[a + 1][b][d] = board[a][b][d];
							board[a][b][d] = 0;
						}
					}
				}
			}
			for (int a = N - 2; a >= 0; a--) {
				for (int b = 0; b < N; b++) {
					board[a + 1][b][d] == board[a][b][d] ? board[a + 1][b][d] *= 2, board[a][b][d] = 0 : board[a][b][d] = board[a][b][d];//上下两个数是否相等，相等就下面的值*2，上面值变成0（等价于向下合并）,不相等就不进行操作
				}
			}
			for (int c = N - 1; c > 0; c--) {//最后一行的前一行到第一行需要操作
				for (int a = c - 1; a < N - 1; a++) {//从上一行向下一行扫描
					for (int b = 0; b < N; b++) {
						if (board[a + 1][b][d] == 0) {//下一行的数要是0，就进行交换
							board[a + 1][b][d] = board[a][b][d];
							board[a][b][d] = 0;
						}
					}
				}
			}//合并操作后再进行一次下移操作，让值都跑到下面去，既进行向下合并操作
		}
		if (h) {
		srand((unsigned)time(NULL));
		int x1, y1, z1, x2, y2, z2;
		do {
			x1 = rand() % N;
			y1 = rand() % N;
			z1 = rand() % N;
		} while (board[x1][y1][z1] != 0);//在为0的位置才能生成新的2或者4
		int num1 = rand() % 100;//与初始化棋盘一样，用来控制在0上生成的数是2还是4
		if (num1 > 20) {
			board[x1][y1][z1] = 2;
			h = 0;
		}
		else {
			board[x1][y1][z1] = 4;
			h = 0;
		}

		do {
			x2 = rand() % N;
			y2 = rand() % N;
			z2 = rand() % N;
		} while (board[x2][y2][z2] != 0 || (x1 == x2 && y1 == y2 && z1 == z2));//在为0的位置才能生成新的2或者4
		int num2 = rand() % 100;//与初始化棋盘一样，用来控制在0上生成的数是2还是4
		if (num2 > 20) {
			board[x2][y2][z2] = 2;
			h = 0;
		}
		else {
			board[x2][y2][z2] = 4;
			h = 0;
		}
	}
}
 
void Game::left() { // 向左合并，第一列不用合并。右一列向左一列判断操作
	//cout << "left" << endl;
	int h = 0;//定义h判断是否要在为0的位置上生成新的2或4
	for (int b = 1; b < N; b++) {
		for (int a = 0; a < N; a++) {
			for(int c = 0; c < N; c++){
				if (board[a][b][c] != 0 && board[a][b - 1][c] == 0) {//出现了0，需要生成2或4，h赋值为1
					h = 1;
					break;
				}
				if (board[a][b - 1][c] == board[a][b][c] && board[a][b][c] != 0) {//有数可以合并，合并后会出现0，需要生成2或4，h赋值为1
					h = 1;
					break;
				}
			}
		}
	}
	for(int d = 0; d < N; d++){
		for (int c = 0; c < N - 1; c++) {//左第一列到右最后一列的前一列需要操作
			for (int b = c + 1; b > 0; b--) {//从右一列向左一列扫描
				for (int a = 0; a < N; a++) {
					if (board[a][b - 1][d] == 0) {//左边的数为0，就进行交换
						board[a][b - 1][d] = board[a][b][d];
						board[a][b][d] = 0;
					}
				}
			}
		}
		for (int b = 1; b < N; b++) {
			for (int a = 0; a < N; a++) {
				board[a][b - 1][d] == board[a][b][d] ? board[a][b - 1][d] *= 2, board[a][b][d] = 0 : board[a][b - 1][d] = board[a][b - 1][d];//左右两个数是否相等，相等就左边的值*2，右边值变成0（等价于向左合并）,不相等就不进行操作
			}
		}
		for (int c = 0; c < N - 1; c++) {//左第一列到右最后一列的前一列需要操作
			for (int b = c + 1; b > 0; b--) {//从右一列向左一列扫描
				for (int a = 0; a < N; a++) {
					if (board[a][b - 1][d] == 0) {//左边的数为0，就进行交换
						board[a][b - 1][d] = board[a][b][d];
						board[a][b][d] = 0;
					}
				}
			}
		}//合并操作后再进行一次左移操作，让值都跑到左边去，既进行向左合并操作
	}
	if (h) {
		srand((unsigned)time(NULL));
		int x1, y1, z1, x2, y2, z2;
		do {
			x1 = rand() % N;
			y1 = rand() % N;
			z1 = rand() % N;
		} while (board[x1][y1][z1] != 0);//在为0的位置才能生成新的2或者4
		int num1 = rand() % 100;//与初始化棋盘一样，用来控制在0上生成的数是2还是4
		if (num1 > 20) {
			board[x1][y1][z1] = 2;
			h = 0;
		}
		else {
			board[x1][y1][z1] = 4;
			h = 0;
		}

		do {
			x2 = rand() % N;
			y2 = rand() % N;
			z2 = rand() % N;
		} while (board[x2][y2][z2] != 0 || (x1 == x2 && y1 == y2 && z1 == z2));//在为0的位置才能生成新的2或者4
		int num2 = rand() % 100;//与初始化棋盘一样，用来控制在0上生成的数是2还是4
		if (num2 > 20) {
			board[x2][y2][z2] = 2;
			h = 0;
		}
		else {
			board[x2][y2][z2] = 4;
			h = 0;
		}
	}
}
 
void Game::right() { // 向右合并，最后一列不用合并。左一列向右一列判断操作
	//cout << "right" << endl;
	int h = 0;//定义h判断是否要在为0的位置上生成新的2或4
	for (int b = N - 2; b >= 0; b--) {
		for (int a = 0; a < N; a++) {
			for(int c = 0; c < N; c++){
				if (board[a][b][c] != 0 && board[a][b + 1][c] == 0) {//出现了0，需要生成2或4，h赋值为1
					h = 1;
					break;
				}
				if (board[a][b + 1][c] == board[a][b][c] && board[a][b][c] != 0) {//有数可以合并，合并后会出现0，需要生成2或4，h赋值为1
					h = 1;
					break;
				}
			}
		}
	}
	for(int d = 0; d < N; d++){
		for (int c = N - 1; c > 0; c--) {//左边第二列到最后一列需要操作
			for (int b = c - 1; b < N - 1; b++) {//从左一列向右一列扫描
				for (int a = 0; a < N; a++) {
					if (board[a][b + 1][d] == 0) {//右边的数为0，就进行交换
						board[a][b + 1][d] = board[a][b][d];
						board[a][b][d] = 0;
					}
				}
			}
		}
		for (int b = N - 2; b >= 0; b--) {
			for (int a = 0; a < N; a++) {
				board[a][b + 1][d] == board[a][b][d] ? board[a][b + 1][d] *= 2, board[a][b][d] = 0 : board[a][b][d] = board[a][b][d];//左右两个数是否相等，相等就右边的值*2，左边值变成0（等价于向左合并）,不相等就不进行操作
			}
		}
		for (int c = N - 1; c > 0; c--) {//左边第二列到最后一列需要操作
			for (int b = c - 1; b < N - 1; b++) {//从左一列向右一列扫描
				for (int a = 0; a < N; a++) {
					if (board[a][b + 1][d] == 0) {//右边的数为0，就进行交换
						board[a][b + 1][d] = board[a][b][d];
						board[a][b][d] = 0;
					}
				}
			}
		}//合并操作后再进行一次右移操作，让值都跑到右边去，既进行向右合并操作
	}
	if (h) {
		srand((unsigned)time(NULL));
		int x1, y1, z1, x2, y2, z2;
		do {
			x1 = rand() % N;
			y1 = rand() % N;
			z1 = rand() % N;
		} while (board[x1][y1][z1] != 0);//在为0的位置才能生成新的2或者4
		int num1 = rand() % 100;//与初始化棋盘一样，用来控制在0上生成的数是2还是4
		if (num1 > 20) {
			board[x1][y1][z1] = 2;
			h = 0;
		}
		else {
			board[x1][y1][z1] = 4;
			h = 0;
		}

		do {
			x2 = rand() % N;
			y2 = rand() % N;
			z2 = rand() % N;
		} while (board[x2][y2][z2] != 0 || (x1 == x2 && y1 == y2 && z1 == z2));//在为0的位置才能生成新的2或者4
		int num2 = rand() % 100;//与初始化棋盘一样，用来控制在0上生成的数是2还是4
		if (num2 > 20) {
			board[x2][y2][z2] = 2;
			h = 0;
		}
		else {
			board[x2][y2][z2] = 4;
			h = 0;
		}
	}
}

void Game::front(){
	// 向前合并，最后一列不用合并。左一列向右一列判断操作
	int h = 0;//定义h判断是否要在为0的位置上生成新的2或4
	for (int c = N - 2; c >= 0; c--) {
		for (int a = 0; a < N; a++) {
			for(int b = 0; b < N; b++){
				if (board[a][b][c] != 0 && board[a][b][c + 1] == 0) {//出现了0，需要生成2或4，h赋值为1
					h = 1;
					break;
				}
				if (board[a][b][c + 1] == board[a][b][c] && board[a][b][c] != 0) {//有数可以合并，合并后会出现0，需要生成2或4，h赋值为1
					h = 1;
					break;
				}
			}
		}
	}
	for(int b = 0; b < N; b++){
		for (int c = N - 1; c > 0; c--) {//后边第二列到最后一列需要操作
			for (int d = c - 1; d < N - 1; d++) {//从后一列向前一列扫描
				for (int a = 0; a < N; a++) {
					if (board[a][b][d + 1] == 0) {//前边的数为0，就进行交换
						board[a][b][d + 1] = board[a][b][d];
						board[a][b][d] = 0;
					}
				}
			}
		}
		for (int d = N - 2; d >= 0; d--) {
			for (int a = 0; a < N; a++) {
				board[a][b][d + 1] == board[a][b][d] ? board[a][b][d + 1] *= 2, board[a][b][d] = 0 : board[a][b][d] = board[a][b][d];//左右两个数是否相等，相等就右边的值*2，左边值变成0（等价于向左合并）,不相等就不进行操作
			}
		}
		for (int c = N - 1; c > 0; c--) {//后边第二列到最后一列需要操作
			for (int d = c - 1; d < N - 1; d++) {//从后一列向右一列扫描
				for (int a = 0; a < N; a++) {
					if (board[a][b][d + 1] == 0) {//前边的数为0，就进行交换
						board[a][b][d + 1] = board[a][b][d];
						board[a][b][d] = 0;
					}
				}
			}
		}//合并操作后再进行一次前移操作，让值都跑到前边去，既进行向前合并操作
	}
	if (h) {
		srand((unsigned)time(NULL));
		int x1, y1, z1, x2, y2, z2;
		do {
			x1 = rand() % N;
			y1 = rand() % N;
			z1 = rand() % N;
		} while (board[x1][y1][z1] != 0);//在为0的位置才能生成新的2或者4
		int num1 = rand() % 100;//与初始化棋盘一样，用来控制在0上生成的数是2还是4
		if (num1 > 20) {
			board[x1][y1][z1] = 2;
			h = 0;
		}
		else {
			board[x1][y1][z1] = 4;
			h = 0;
		}

		do {
			x2 = rand() % N;
			y2 = rand() % N;
			z2 = rand() % N;
		} while (board[x2][y2][z2] != 0 || (x1 == x2 && y1 == y2 && z1 == z2));//在为0的位置才能生成新的2或者4
		int num2 = rand() % 100;//与初始化棋盘一样，用来控制在0上生成的数是2还是4
		if (num2 > 20) {
			board[x2][y2][z2] = 2;
			h = 0;
		}
		else {
			board[x2][y2][z2] = 4;
			h = 0;
		}
	}
}

void Game::back() { 
	// 向左合并，第一列不用合并。右一列向左一列判断操作
	//cout << "left" << endl;
	int h = 0;//定义h判断是否要在为0的位置上生成新的2或4
	for (int c = 1; c < N; c++) {
		for (int a = 0; a < N; a++) {
			for(int b = 0; b < N; b++){
				if (board[a][b][c] != 0 && board[a][b][c - 1] == 0) {//出现了0，需要生成2或4，h赋值为1
					h = 1;
					break;
				}
				if (board[a][b][c - 1] == board[a][b][c] && board[a][b][c] != 0) {//有数可以合并，合并后会出现0，需要生成2或4，h赋值为1
					h = 1;
					break;
				}
			}
		}
	}
	for(int b = 0; b < N; b++){
		for (int c = 0; c < N - 1; c++) {//后第一列到前最后一列的前一列需要操作
			for (int d = c + 1; d > 0; d--) {//从前一列向后一列扫描
				for (int a = 0; a < N; a++) {
					if (board[a][b][d - 1] == 0) {//后边的数为0，就进行交换
						board[a][b][d - 1] = board[a][b][d];
						board[a][b][d] = 0;
					}
				}
			}
		}
		for (int d = 1; d < N; d++) {
			for (int a = 0; a < N; a++) {
				board[a][b][d - 1] == board[a][b][d] ? board[a][b][d - 1] *= 2, board[a][b][d] = 0 : board[a][b][d - 1] = board[a][b][d - 1];//前后两个数是否相等，相等就后边的值*2，前边值变成0（等价于向左合并）,不相等就不进行操作
			}
		}
		for (int c = 0; c < N - 1; c++) {//后第一列到前最后一列的前一列需要操作
			for (int d = c + 1; d > 0; d--) {//从前一列向后一列扫描
				for (int a = 0; a < N; a++) {
					if (board[a][b][d - 1] == 0) {//后边的数为0，就进行交换
						board[a][b][d - 1] = board[a][b][d];
						board[a][b][d] = 0;
					}
				}
			}
		}//合并操作后再进行一次后移操作，让值都跑到后边去，既进行向后合并操作
	}
	if (h) {
		srand((unsigned)time(NULL));
		int x1, y1, z1, x2, y2, z2;
		do {
			x1 = rand() % N;
			y1 = rand() % N;
			z1 = rand() % N;
		} while (board[x1][y1][z1] != 0);//在为0的位置才能生成新的2或者4
		int num1 = rand() % 100;//与初始化棋盘一样，用来控制在0上生成的数是2还是4
		if (num1 > 20) {
			board[x1][y1][z1] = 2;
			h = 0;
		}
		else {
			board[x1][y1][z1] = 4;
			h = 0;
		}

		do {
			x2 = rand() % N;
			y2 = rand() % N;
			z2 = rand() % N;
		} while (board[x2][y2][z2] != 0 || (x1 == x2 && y1 == y2 && z1 == z2));//在为0的位置才能生成新的2或者4
		int num2 = rand() % 100;//与初始化棋盘一样，用来控制在0上生成的数是2还是4
		if (num2 > 20) {
			board[x2][y2][z2] = 2;
			h = 0;
		}
		else {
			board[x2][y2][z2] = 4;
			h = 0;
		}
	}
}
 
int Game::score() {//计分函数，返回值为二维数值每一个数的和
	int c = 0;
	for (int a = 0; a < N; a++) {
		for (int b = 0; b < N; b++) {
			for(int d = 0; d < N; d++)
				c += board[a][b][d];
		}
	}
	return c;
}
 
int Game::ifgameover() {//判断游戏是否结束
	int c = 0;//先默认输了
	for (int a = 0; a < N; a++) {
		if (c == 1) break;//c为1，已经判断赢了，跳出
		for (int b = 0; b < N; b++) {
			if (c == 1) break;
			for (int d = 0; d < N; d++) {
			if (board[a][b][d] == aim) {//二维数组中有数字为2048，赢了，c值赋为1
				c = 1;
				break;
			}
			}
		}
	}
	for (int a = 0; a < N; a++) {//检查左右是否有可以合并的
		for(int d = 0; d < N; d++){
			if (c == 1) break;//c为1，已经判断赢了，跳出
			if (c != 1) {
				for (int b = 0; b < N - 1; b++) {
					if (board[a][b][d] == 0 || board[a][b][d] == board[a][b + 1][d]) {
						c = 2;  //左右还有可以合并的，c值赋为2
						break;
					}
				}
			}
		}
	}
	for (int b = 0; b < N; b++) {//检查上下是否有可以合并的
		for(int d = 0; d < N; d++){
			if (c == 1) break;//c为1，已经判断赢了，跳出
			if (c != 1) {
				for (int a = 0; a < N - 1; a++) {
					if (board[a][b][d] == 0 || board[a][b][d] == board[a + 1][b][d]) {
						c = 2;//上下还有可以合并的，c值为2
						break;
					}
				}
			}
		}
	}
	for (int b = 0; b < N; b++) {//检查前后是否有可以合并的
		for(int a = 0; a < N; a++){
			if (c == 1) break;//c为1，已经判断赢了，跳出
			if (c != 1) {
				for (int d = 0; d < N - 1; d++) {
					if (board[a][b][d] == 0 || board[a][b][d] == board[a][b][d + 1]) {
						c = 2;//前后还有可以合并的，c值为2
						break;
					}
				}
			}
		}
	}
	return c;//返回c的值，c为0就输了，用计分函数算分，c为2还能继续游戏，c为1就赢了
}

void Game::updateMatch() {//更新匹配信息
	memset(match,0,sizeof(match));
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++){
			for(int k = 0; k < N; k++){
				if (board[i][j][k] == 0) continue;
				for(int ii = i + 1; ii < N; ii++){
					if (board[ii][j][k] == board[i][j][k]) match[i][j][k] = 1;
					else if(board[ii][j][k] == 0)	continue;
					else break;
				}
				for(int ii = i - 1; ii >= 0; ii--){
					if (board[ii][j][k] == board[i][j][k]) match[i][j][k] = 1;
					else if(board[ii][j][k] == 0)	continue;
					else break;
				}
				for(int jj = j + 1; jj < N; jj++){
					if (board[i][jj][k] == board[i][j][k]) match[i][j][k] = 1;
					else if(board[i][jj][k] == 0)	continue;
					else break;
				}
				for(int jj = j - 1; jj >= 0; jj--){
					if (board[i][jj][k] == board[i][j][k]) match[i][j][k] = 1;
					else if(board[i][jj][k] == 0)	continue;
					else break;
				}
				for(int kk = k + 1; kk < N; kk++){
					if (board[i][j][kk] == board[i][j][k]) match[i][j][k] = 1;
					else if(board[i][j][kk] == 0)	continue;
					else break;
				}
				for(int kk = k - 1; kk >= 0; kk--){
					if (board[i][j][kk] == board[i][j][k]) match[i][j][k] = 1;
					else if(board[i][j][kk] == 0)	continue;
					else break;
				}
			}
		}
}

void Game::initial() {//初始化和归零
	//cout << "initial" << endl;
	memset(board,0,sizeof(board));
	memset(pastBoard,0,sizeof(pastBoard));
	memset(match,0,sizeof(match));
    this->setchessboard();
	memcpy(pastBoard,board,sizeof(board));
}

void Game::getmove(char move) {//用于控制输入
	if (this->ifgameover() != 2) return;
	memcpy(pastBoard,board,sizeof(board));
    if (move == 'w') this->up();
    if (move == 's') this->down();
    if (move == 'a') this->left();
    if (move == 'd') this->right();
	if (move == 'q') this->front();
	if (move == 'e') this->back();
	this->updateMatch();
    //this->printchessboard();
}

void Game::regret(){
	memcpy(board,pastBoard,sizeof(board));
}

int Game::askBoard(int i, int j, int k) {//用于查询棋盘
	return board[i][j][k];
}

int Game::askMatch(int i, int j, int k) {
	return match[i][j][k];
}
