#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <signal.h>

/*函数声明*/
int show_board(void);
void teset(void);
int move_down(void);
/*宏定义*/
#define X_LENGTH (13)

/*数组*/
char board[] =" ---------------------\n \
|    |    |    |    |\n \
---------------------\n \
|    |    |    |    |\n \
---------------------\n \
|    |    |    |    |\n \
---------------------\n \
|    |    |    |    |\n \
---------------------\n";

const int d_xy[16] = {25,30,35,40, 71,76,81,86, 117,122,127,132, 163,168,173,178};
const int array_rand[5]  = {2,4,4,2,8};/*随机数值*/
int array_core[16] = {0};/*用来保存键盘上的16个数字*/

int move_left(void)
{
    int i=0,j=0,x=0,y=0;
    int temp[4] = {0};

    /*1、合并相邻相同的两个元素*/
    /*2、把0元素移动到最下面*/
    for(y=0;y<=12;y+=4){
        for(x=y,i=0;x<=3+y;i++,x++){
            temp[i] = array_core[x];
        }
        /*上移*/
        for(i=0;i<4;i++){
            for(j=0;j<3;j++){
                if(temp[j] == temp[j+1] && temp[j+1] != 0){
                    temp[j] = 2*temp[j+1];
                    temp[j+1] = 0;
                }
            }
        }
        /*上移*/
        for(i=0;i<4;i++){
            for(j=0;j<3;j++){
                if(temp[j] == 0 && temp[j+1] != 0){
                    temp[j] = temp[j+1];
                    temp[j+1] = 0;
                }
            }
        }
        for(x=y,i=0;x<=3+y;i++,x++){
            array_core[x] = temp[i];
        }
    }

    /*在键盘上显示*/
    for(i=0;i<16;i++)
    {
        place_xy(i,array_core[i]);
    }
    add_random();
    return (0);
}

int move_right(void)
{
    int i=0,j=0,x=0,y=0;
    int temp[4] = {0};

    /*1、合并相邻相同的两个元素*/
    /*2、把0元素移动到最上面*/
    for(y=0;y<=12;y+=4){
        for(x=y,i=0;x<=3+y;i++,x++){
            temp[i] = array_core[x];
        }
        /*合并相邻的两个非0值*/
        for(i=3;i>=0;i--){
            for(j=3;j>0;j--){
                if(temp[j] == temp[j-1] && temp[j-1] != 0){
                    temp[j] = 2*temp[j-1];
                    temp[j-1] = 0;
                }
            }
        }

        /*把0往上移动*/
        for(i=3;i>=0;i--){
            for(j=3;j>0;j--){
                if(temp[j] == 0 && temp[j-1] != 0){
                    temp[j] = temp[j-1];
                    temp[j-1] = 0;
                }
            }
        }
        for(x=y,i=0;x<=3+y;i++,x++){
            array_core[x] = temp[i];
        }
    }

    /*在键盘上显示*/
    for(i=0;i<16;i++)
        place_xy(i,array_core[i]);
    add_random();
    return (0);
}

/*上移动*/
int move_up(void)
{
    int i=0,j=0,x=0,y=0;
    int temp[4] = {0};

    /*1、合并相邻相同的两个元素*/
    /*2、把0元素移动到最下面*/
    for(x=0;x<4;x++){
        for(y=x,i=0;y<=12+x;i++,y+=4){
            temp[i] = array_core[y];
        }
        /*上移*/
        for(i=0;i<4;i++){
            for(j=0;j<3;j++){
                if(temp[j] == temp[j+1] && temp[j+1] != 0){
                    temp[j] = 2*temp[j+1];
                    temp[j+1] = 0;
                }
            }
        }
        /*上移*/
        for(i=0;i<4;i++){
            for(j=0;j<3;j++){
                if(temp[j] == 0 && temp[j+1] != 0){
                    temp[j] = temp[j+1];
                    temp[j+1] = 0;
                }
            }
        }
        for(y=x,i=0;y<=12+x;i++,y+=4){
            array_core[y] = temp[i];
        }
    }

    /*在键盘上显示*/
    for(i=0;i<16;i++)
    {
        place_xy(i,array_core[i]);
    }
    add_random();
    return (0);    
}
/*下移*/
int move_down(void)
{
    int i=0,j=0,x=0,y=0;
    int temp[4] = {0};

    /*1、合并相邻相同的两个元素*/
    /*2、把0元素移动到最上面*/
    for(x=0;x<4;x++){
        for(y=x,i=0;y<=12+x;i++,y+=4){
            temp[i] = array_core[y];
        }
        /*合并相邻的两个非0值*/
        for(i=3;i>=0;i--){
            for(j=3;j>0;j--){
                if(temp[j] == temp[j-1] && temp[j-1] != 0){
                    temp[j] = 2*temp[j-1];
                    temp[j-1] = 0;
                }
            }
        }

        /*把0往上移动*/
        for(i=3;i>=0;i--){
            for(j=3;j>0;j--){
                if(temp[j] == 0 && temp[j-1] != 0){
                    temp[j] = temp[j-1];
                    temp[j-1] = 0;
                }
            }
        }
        for(y=x,i=0;y<=12+x;i++,y+=4){
            array_core[y] = temp[i];
        }
    }

    /*在键盘上显示*/
    for(i=0;i<16;i++)
    {
        place_xy(i,array_core[i]);
    }
    add_random();
    return (0);
}

/*测试函数*/
void teset(void)
{
#if 0
    int i = 0;
    for(i = 0;i<16;i++)
    {
        place_xy(i,i+1);
    }
#else
    /*计算偏移值*/
    int i = 0;
    for(i = 0;i<strlen(board);i++)
    {
        if(board[i] == '\n')
            printf(" %d ",i+3); 
    }   
    printf("\n"); 
#endif
}

int place_xy(int pos,int data)
{
    if(data == 0)
    {
        board[d_xy[pos]] = 0x20; /*十位*/
        board[d_xy[pos] +1 ] = 0x20; /*个位*/
        board[d_xy[pos] +2 ] = 0x20; /*个位*/
        board[d_xy[pos] +3 ] = 0x20; /*个位*/
    }
    else if(data < 10)
    {
        board[d_xy[pos]] = data + 48;/*如果数值是0，就不显示*/
    }
    else if(data < 100)
    {
        board[d_xy[pos]]     = data/10 + 48;   
        board[d_xy[pos] +1]  = data%10 + 48;         
    }
    else if(data < 1000)
    {
        board[d_xy[pos]]     = data/100 + 48;   
        board[d_xy[pos] +1]  = data%100/10 + 48;  
        board[d_xy[pos] +2]  = data%100%10 + 48;  
    }
    else
    {
        board[d_xy[pos]]     = data/1000 + 48;        /*千位*/
        board[d_xy[pos] +1]  = data%1000/100 + 48;    /*百位*/
        board[d_xy[pos] +2 ] = data%1000%100/10 + 48; /*十位*/
        board[d_xy[pos] +3 ] = data%1000%100%10 + 48; /*个位*/
    }
    /*把数字保存到键盘里面去*/
    array_core[pos] = data;
    /*显示键盘*/
    show_board();
    return(0);
}

/*初始化几个数字在键盘上*/
int add_random(void)
{
	static bool initialized = false;
    int pos,data,i;

    /*随机数需要设置种子，用时间来做随机数的种子*/
	if (!initialized) {
		srand(time(NULL));
		initialized = true;
	}

    /*检测如果原来的位置有数据了，就不能在原来的数据上加数据*/
    for(i = 0;i<16;i++)
    {
        pos = rand()%15;
        if(array_core[pos] != 0)
        {
            continue;
        }
        else
        {
            break;
        }
    }
    
    data =  rand()%(4-0+1)+ 0;
    place_xy(pos,array_rand[data]);
    return (0);
}

/*初始化一个键盘*/
int show_board(void)
{
	printf("\033[H\033[J");/*清空屏幕 但是并不是每一个terminal都会生效*/
    printf("%s",board);
    printf("[ ←,↑,→,↓ or q  ]\n");
    return(0);
}

/*设置之后不用按下回车就可以接收到字符*/
void setBufferedInput(bool enable) {
	static bool enabled = true;
	static struct termios old;
	struct termios new;

	if (enable && !enabled) {
		// restore the former settings
		tcsetattr(STDIN_FILENO,TCSANOW,&old);
		// set the new state
		enabled = true;
	} else if (!enable && enabled) {
		// get the terminal settings for standard input
		tcgetattr(STDIN_FILENO,&new);
		// we want to keep the old setting to restore them at the end
		old = new;
		// disable canonical mode (buffered i/o) and local echo
		new.c_lflag &=(~ICANON & ~ECHO);
		// set the new settings immediately
		tcsetattr(STDIN_FILENO,TCSANOW,&new);
		// set the new state
		enabled = false;
	}
}

/*需要检测ctrl+c 按键，要不然输入变成一直输入了不转回来，键盘就输入不了了*/
void signal_callback_handler(int signum) {
	printf("         TERMINATED         \n");
	setBufferedInput(true);
	printf("\033[?25h\033[m");
	exit(signum);
}

int main()
{
    char c;
    bool success;
    memset(array_core,0,sizeof(array_core)/sizeof(array_core[0]));
    /*在键盘上添加三个随机数*/
    add_random();
    add_random();
    add_random();
    /*显示键盘*/
    show_board();
    setBufferedInput(false);
    teset();
    /*注册信号量*/
    signal(SIGINT, signal_callback_handler);
    while(true){
        c=getchar();
        //printf("%d",c);
        #if 1
		if (c == -1){
			puts("\nError! Cannot read keyboard input!");
			break;
		}

		switch(c) {
			case 97:	// 'a' key
			case 104:	// 'h' key
			case 68:	// left arrow
				success = move_left();  break;
			case 100:	// 'd' key
			case 108:	// 'l' key
			case 67:	// right arrow
				success = move_right(); break;
			case 119:	// 'w' key
			case 107:	// 'k' key
			case 65:	// up arrow
				success = move_up();    break;
			case 115:	// 's' key
			case 106:	// 'j' key
			case 66:	// down arrow
                //printf("move_down\n");
				success = move_down();  break;
			default: success = false;
		}
        #endif

        /*判断是否退出*/
        if (c=='q') {
			printf("        退出? (y/n)         \n");
			c=getchar();
			if (c=='y') {
				break;
			}
		}
        usleep(150000);
    }
    setBufferedInput(true);
    //teset();
    return (0);
}
