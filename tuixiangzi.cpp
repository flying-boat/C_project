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
int p_x, p_y;//这里一定注意，二维矩阵的输出顺序是y轴先输出
int n_box = 3;
int mm = 10, nn = 10;
char m[N][N] = {0};
int lim = 50;
int last_time = 0;
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
struct node
{
    int x, y;
}ter[10], box[10];

int getTime(){
    return clock()/CLOCKS_PER_SEC;
}

void out(){
    for(int i = 0;i < mm;i++){
        for(int j = 0;j < nn;j++)
            printf("%c ", m[i][j]);
            cout<<endl;
    }
}

void box_ter(int n, node tmp[10]){
    for(int i=0;i<n_box;i++){
    bool flag = false;
    for(tmp[i].y = randomInt(0,mm-1), tmp[i].x = randomInt(0,nn-1);true;
        tmp[i].y = randomInt(0,mm-1), tmp[i].x = randomInt(0,nn-1)){
            bool f = false;
            if(n==3){
                for(int k = 0;k<n_box;k++){
                    if(tmp[i].y==box[k].y&&tmp[i].x==box[k].x){
                        if(m[tmp[i].y][tmp[i].x] != '$'){
                            m[tmp[i].y][tmp[i].x] = '$';
                            flag = true;
                        }
                        else
                            f = true;
                            break;
                    }
                }
            }
            else{
                if(tmp[i].y==0||tmp[i].y==mm-1||tmp[i].x==0||tmp[i].x==nn-1)
                    f = true;
            }
            if(flag) break;
            if(f) continue;
            if(tmp[i].y==p_y&&tmp[i].x==p_x)
                continue;
            for(int k = i-1;k>-1;k--){
                if(tmp[i].y==tmp[k].y&&tmp[i].x==tmp[k].x){
                    f = true;
                    break;
                }
            }
            if(f)
                continue;
            int cnt = 0;
            for(int j = 0; j < 4; j++)
            {
                int dx = tmp[i].x + dir[j][0];
                int dy = tmp[i].y + dir[j][1];
                if(dx < 0 || dx >= nn || dy < 0 || dy >= mm || m[dy][dx] == '*')
                    cnt++;
            }
            if(cnt>n)
                continue;
            else
                break;
        }
        if(!flag)
            m[tmp[i].y][tmp[i].x] = (n==1?'#':'@');
    }
}

void init(){
    srand((unsigned)time(NULL));
    for(int i = 0;i < mm;i++)
        for(int j = 0;j < nn;j++){
            int t = randomInt(0,3);
            if(t==0)
                m[i][j] = '*';
            if(t!=0)
                m[i][j] = '.';
        }
    for(int ty = randomInt(0,mm-1), tx = randomInt(0,nn-1);true;
    ty = randomInt(0,mm-1), tx = randomInt(0,nn-1)){
        int cnt = 0;
        for(int j = 0; j < 4; j++)
        {
            int dx = tx + dir[j][0];
            int dy = ty + dir[j][1];
            if(dx < 0 || dx >= nn || dy < 0 || dy >= mm || m[dy][dx] == '*')
                cnt++;
        }
        if(cnt>3)
            continue;
        else{
            m[p_y = ty][p_x = tx] = '&';
            break;
        }
    }
    box_ter(1, box);
    box_ter(3, ter);
    printf("欢迎来到简单的推箱子游戏\n");
    for(int i = 0;i < mm;i++){
        for(int j = 0;j < nn;j++)
            printf("%c ", m[i][j]);
        cout<<endl;
    }
    last_time = getTime();
}

bool check(int x, int y, int m_x, int m_y){
    int time = getTime();
    if(time-last_time>=lim){
        printf("超时了！你这头笨猪！\n");
        system("pause");
        return true;
    }
    int y_nex = p_y+m_y, x_nex = p_x+m_x;
    if(m[p_y][p_x]=='#'||m[p_y][p_x]=='$'){
        if(m[y_nex][x_nex]=='*'||m[y_nex][x_nex]=='#'||m[y_nex][x_nex]=='$'||y_nex<0||x_nex<0||y_nex>mm-1||x_nex>nn-1){
            p_y = y, p_x = x;
            return false;
        }
        else{
            system("cls");
            m[y_nex][x_nex] = m[y_nex][x_nex]=='.'?'#':'$';
            m[p_y][p_x] = m[p_y][p_x]=='#'?'&':'!';
            m[y][x] = m[y][x]=='&'?'.':'@';
            out();
            bool f = false;
            for(int i=0;i<mm;i++){
                for(int j=0;j<nn;j++){
                    if(m[i][j]=='#'){
                        f = true;
                        break;
                    }
                }
                if(f)
                    break;
            }
            if(f)   return false;
            else{
                printf("你成功了！你是天才！");
                system("pause");
                return true;
            }
        }
    }
    if(p_y<0||p_x<0||p_y>mm-1||p_x>nn-1||m[p_y][p_x]=='*'){
        p_y = y, p_x = x;
        return false;
    }
    if(m[p_y][p_x]=='.'){
        system("cls");
        m[p_y][p_x] = '&';
        m[y][x] = m[y][x]=='&'?'.':'@';
        out();
        return false;
    }
    if(m[p_y][p_x] = '@'){
        system("cls");
        m[p_y][p_x] = '!';
        m[y][x] = m[y][x]=='&'?'.':'@';
        out();
        return false;
    }
    return false;
}

void play(){
    int ch;
	while(true){
        while(getTime() - last_time<lim){
            int t = _getch();
            if (_kbhit()&&getTime() - last_time<lim){
                ch = _getch();
                break;
            }
        }
        bool f = false;
        int now_x = p_x;
        int now_y = p_y;
        int now_m_x, now_m_y;
        switch(ch){
        case 72:p_y-=1, now_m_x = 0, now_m_y = -1;break;
        case 80:p_y+=1, now_m_x = 0, now_m_y = 1;break;
        case 75:p_x-=1, now_m_x = -1, now_m_y = 0;break;
        case 77:p_x+=1, now_m_x = 1, now_m_y = 0; break;
        case 63:f = true;break;
        default: break;
        }
        if(f){
            printf("你选择了自杀！你是一头大笨猪！\n");
            system("pause");
            last_time = getTime();
            system("cls");
            break;
        }
        f = check(now_x, now_y, now_m_x, now_m_y);
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
