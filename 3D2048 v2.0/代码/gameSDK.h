#define N 4
class Game {
public:
	int board[N][N][N];//定义棋盘的大小
	int pastBoard[N][N][N];
	bool match[N][N][N];//记录上下左右是否有匹配的
	void setchessboard();// 初始棋盘生成
	void printchessboard();//打印棋盘
    void initial();
    void getmove(char move);
	int askBoard(int i, int j, int k);
	int askMatch(int i, int j, int k);
	void up();
	void down();
	void left();
	void right();
	void front();
	void back();// 上下左右前后六步操作
	void regret();
	int score();//  记录分数
	int ifgameover();// 判断游戏是否结束
	void updateMatch();
};
//Game类，包含二位数组的棋盘、打印棋盘、2048上下左右的操作、计分、以及游戏是否结束的判断
