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
const int N = 500;
int nn = 4;
int a;
int score = 0;
int m[10][10], tmp[10][10];
queue<int> q;
struct node{
    int x, y;
}p[100];

void show(){
    for(int i = 0;i < nn;i++){
        for(int j = 0;j < nn;j++){
            if(m[i][j]==0){
                printf("    |");
                continue;
            }
            else
                printf("%d", m[i][j]);
            int num = 0, t = m[i][j];
            while(t!=0){
                t/=10;
                num++;
            }
            num = 4-num;
            for(int i=0;i<num;i++)
                printf(" ");
            printf("|");
        }
        printf("\n--------------------\n");
    }
}

void ask(){
    printf("欢迎来到简单的2048！按F5开始游戏\n");
    int ch = 0;
    while(true){
        int t = _getch();
        if (_kbhit()){//如果有按键按下，则_kbhit()函数返回真
            ch = _getch();//使用_getch()获取按下的键值
        }
        if(ch==63){
            system("cls");
            return;
        }
    }
}

void init(){
    srand((unsigned)time(NULL));
    int t = randomInt(0,15);
    for(int i = 0;i < nn;i++)
        for(int j = 0;j < nn;j++)
            m[i][j] = 0;
    m[t/4][t%4] = 2;
    show();
}

bool mov(){
    for(int i=0;i<nn;i++)
        for(int j=0;j<nn;j++)
            tmp[i][j] = m[i][j];
    int x, y;
    for(int j = 0;j<nn;j++){
        int t = 0;
        for(int i = (a==8||a==4? 0:nn-1);a==8||a==4?i<nn:i>-1;a==8||a==4? i++:i--){
            if(a==2||a==8)
                x = i, y = j;
            else
                x = j, y = i;
            if(m[x][y]==0)
                continue;
            if(m[x][y]!=t){
                if(t!=0)
                    q.push(t);
                t = m[x][y];
                m[x][y] = 0;
            }
            else{
                t = m[x][y]*2;
                score+=t;
                q.push(t);
                t = 0;
                m[x][y] = 0;
            }
        }
        if(t!=0)
            q.push(t);
        int i= (a==8||a==4?0:nn-1);
        while(!q.empty()){
            if(a==2||a==8)
                m[i][y] = q.front();
            else
                m[x][i] = q.front();
            q.pop();
            a==8||a==4?i++:i--;
        }
    }
    int cnt = -1;
    for(int i=0;i<nn;i++)
        for(int j=0;j<nn;j++)
            if(m[i][j]==0)
                p[++cnt].x = i, p[cnt].y = j;
    if(cnt!=-1){
        int pos = randomInt(0, cnt);
        m[p[pos].x][p[pos].y] = 2;
    }
    system("cls");
    show();
    if(cnt==-1){
        printf("你死了！你的最终得分是%d\n", score);
        score = 0;
        system("pause");
        return true;
    }
    printf("你的得分是%d\n", score);
    return false;
}

void play(){
    int ch;
	while(true){
        while(true){
            int t = _getch();
            if (_kbhit()){//如果有按键按下，则_kbhit()函数返回真
                ch = _getch();//使用_getch()获取按下的键值
                break;
            }
        }
        switch(ch){
        case 72:a = 8;break;
        case 80:a = 2;break;
        case 75:a = 4;break;
        case 77:a = 6;break;
        default: break;
        }
        bool f = mov();
        if(f){
            system("cls");
            break;
        }
	}
}

int main(){
    while(true){
        ask();
        init();
        play();
    }
    return 0;
}
