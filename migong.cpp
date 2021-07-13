#include<iostream>
#include<cmath>
#include<cstdio>
#include<queue>
#include<cstring>
#include<random>
#include<ctime>
#define randomInt(a,b) (rand()%(b-a+1)+a)
#include <conio.h>
#include <ctime>
#define inf 0x3f3f3f3f
using namespace std;
const int N = 200;
int a, b, c, d;
int mm = 10, nn = 10;
char m[N][N] = {0};
int val[N][N] = {0};
int lim = 10;
int last_time = 0;
struct node
{
    int x, y, step;
};

int getTime(){
    return clock()/CLOCKS_PER_SEC;
}

bool bfs()
{
    int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    queue<node>q;
    node s;
    s.x = a;
    s.y = b;
    s.step = 0;
    q.push(s);
    int minv = inf;
    while(!q.empty())
    {
        node tmp = q.front();
        q.pop();
        if(m[tmp.x][tmp.y] == '@')
            minv = min(minv, tmp.step);
        for(int i = 0; i < 4; i++)
        {
            int dx = tmp.x + dir[i][0];
            int dy = tmp.y + dir[i][1];
            if(dx >= 0 && dx < mm && dy >=0 && dy < nn && m[dx][dy] != '#' && m[dx][dy] != '*')
            {
                if(val[dx][dy] > tmp.step + 1)
                {
                    node next;
                    next.x = dx;
                    next.y = dy;
                    next.step = tmp.step + 1;
                    val[dx][dy] = next.step;
                    q.push(next);
                }
            }
        }
    }
    if(minv != inf&&minv > 5)
        return true;
    return false;
}
void init(){
    while(true){
        srand((unsigned)time(NULL));
        //uniform_int_distribution<int> u(0,2), x(0, 10);
        //default_random_engine e;
        for(int i = 0;i < mm;i++)
            for(int j = 0;j < nn;j++){
                val[i][j] = inf;
                int t = randomInt(0,3);
                if(t==3)
                    m[i][j] = '#';
                if(t==1||t==0)
                    m[i][j] = '.';
                if(t==2)
                    m[i][j] = '*';
            }
        m[a = randomInt(0,mm-1)][b = randomInt(0,nn-1)] = '&';
        c = randomInt(0,mm-1), d = randomInt(0,nn-1);
        for(;c==a&&d==b;c = randomInt(0,mm-1), d = randomInt(0,nn-1)){}
        m[c][d] = '@';
        if(bfs())
            break;
    }
    printf("欢迎来到简单的迷宫游戏\n");
    for(int i = 0;i < mm;i++){
        for(int j = 0;j < nn;j++)
            printf("%c ", m[i][j]);
        cout<<endl;
    }
    last_time = getTime();
}

bool check(int x, int y){
    int time = getTime();
    if(time-last_time>=lim){
        printf("超时了！你这头笨猪！\n");
        system("pause");
        return true;
    }
    if(a<0||b<0||a>mm-1||b>nn-1||m[a][b]=='*'){
        a = x, b = y;
        return false;
    }
    if(m[a][b]=='#'){
        printf("你死了，你是猪！\n");
        system("pause");
        return true;
    }
    if(m[a][b]=='.'){
        system("cls");
        m[a][b] = '&';
        m[x][y] = '.';
        for(int i = 0;i < mm;i++){
            for(int j = 0;j < nn;j++)
                printf("%c ", m[i][j]);
                cout<<endl;
        }
        return false;
    }
    if(a==c&&b==d){
        printf("你走出了迷宫！你是天才！\n");
        system("pause");
        return true;
    }
    return false;
}

void play(){
    int ch;
	while(true){
        while(getTime() - last_time<lim){
            int t = _getch();
            if (_kbhit()&&getTime() - last_time<lim){//如果有按键按下，则_kbhit()函数返回真
                ch = _getch();//使用_getch()获取按下的键值
                break;
            }
        }
        int now_x = a;
        int now_y = b;
        switch(ch){
        case 72:a-=1;break;
        case 80:a+=1;break;
        case 75:b-=1;break;
        case 77:b+=1;break;
        default: break;
        }
        bool f = check(now_x, now_y);
        if(f){
            last_time = getTime();
            system("cls");
            break;
        }
	}
}
int main(){
    while(true){
        init();
        play();
    }
    return 0;
}
