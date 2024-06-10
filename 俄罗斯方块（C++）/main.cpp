#include<stdio.h> 
#include <winbgim.h>
#include <conio2.h>
#include <string.h>
#include <time.h>
#define WINDOWS_WIDTH  1024
#define WINDOWS_HEIGHT  800
#define BLOCKSIZE 30
#define NUM_ROW  20
#define NUM_COL 20
#define xSTART 100
#define ySTART 50
#define NUM_PICS 19
#define START_FALL_ROW 0
#define START_FALL_COL (NUM_COL/2-2)
#define BK_COLOR WHITE
#define LINE_COLOR RED 
#define FILL_COLOR BLUE
#define TIPS_COLOR GREEN
#define SCORE_COLOR LIGHTMAGENTA
#define ARROW_LEFT  75
#define ARROW_UP     72
#define ARROW_RIGHT 77
#define ARROW_DOWN  80
#define UK_ESC   27
#define MAX_DELAY (1.5*CLOCKS_PER_SEC)
#define RESTART 114 
unsigned int unMatrixBackGround[NUM_ROW][NUM_COL];
unsigned int unMatrixPictures[NUM_PICS][4][4];
time_t clockStart = 0;
time_t clockCurrent = 0;
unsigned int unTimeDelay = (unsigned int)MAX_DELAY;
unsigned int unMatrixRotation[NUM_PICS] = { 0 };
unsigned int unCurrentPicIndex = 0;
unsigned int unNextPicIndex = 0;
int nCurrentPicRow = 0;
int nCurrentPicCol = 0;
unsigned int unTotalScore = 0;
unsigned int unIsCurrentPlayOver = 0;
void DrawBackGround(int x1, int y1);
void DrawGivenIndexPic(int nRow, int nCol, unsigned int nPicToDraw);
void DrawCurrentPic(int nRow, int nCol, unsigned int maxtrixPic[4][4]);
void EarseGivenIndexPic(int nRow, int nCol, unsigned int nPicToDraw);
void EarseCurrentPic(int nRow, int nCol, unsigned int maxtrixPic[4][4]);
unsigned int CanCurrentIndexPicMoveLeft(int nRow, int nCol, unsigned int unCurPicIndex);
unsigned int CanCurrentPicMoveLeft(int nRow, int nCol, unsigned int curPicMaxtrix[4][4]);
unsigned int CanCurrentIndexPicMoveRight(int nRow, int nCol, unsigned int unCurPicIndex);
unsigned int CanCurrentPicMoveRight(int nRow, int nCol, unsigned int curPicMaxtrix[4][4]);
unsigned int CanCurrentIndexPicMoveDown(int nRow, int nCol, unsigned int unCurPicIndex);
unsigned int CanCurrentPicMoveDown(int nRow, int nCol, unsigned int curPicMaxtrix[4][4]);
unsigned int CanCurrentPicRotate(int nRow, int nCol, unsigned int unCurrentPicIndex);
unsigned int IsCurrentLine_All_1_Line(unsigned int nRow);
unsigned int IsCurrentLine_All_0_Line(unsigned int nRow);
unsigned int Erasse_All_1_Lines(void);
void Start_NewFallPic_After_PreviousCannotMoveDown(void);
void Initialize_AllPictures(void);
unsigned int Random_GenerateNewPicIndex(void);
void Delay_Time(unsigned int unTimeToDelay);
void StartNewPlayGame(void);
unsigned int const Pic_1_matrix[4][4] = {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0}; 
unsigned int const Pic_2_matrix[4][4] = {0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1}; 
unsigned int const Pic_3_matrix[4][4] = {0,0,0,0,0,0,1,0,0,1,1,0,0,0,1,0}; 
unsigned int const Pic_4_matrix[4][4] = {0,0,0,0,0,0,1,0,0,0,1,1,0,0,1,0}; 
unsigned int const Pic_5_matrix[4][4] = {0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0}; 
unsigned int const Pic_6_matrix[4][4] = {0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0}; 
unsigned int const Pic_7_matrix[4][4] = {0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0}; 
unsigned int const Pic_8_matrix[4][4] = {0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0}; 
unsigned int const Pic_9_matrix[4][4] = {0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,0}; 
unsigned int const Pic_10_matrix[4][4] = {0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0};
unsigned int const Pic_11_matrix[4][4] = {0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0}; 
unsigned int const Pic_12_matrix[4][4] = {0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0}; 
unsigned int const Pic_13_matrix[4][4] = {0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0}; 
unsigned int const Pic_14_matrix[4][4] = {0,0,0,0,0,1,1,0,0,0,1,0,0,0,1,0}; 
unsigned int const Pic_15_matrix[4][4] = {0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0}; 
unsigned int const Pic_16_matrix[4][4] = {0,0,0,0,0,0,1,0,0,0,1,0,0,1,1,0}; 
unsigned int const Pic_17_matrix[4][4] = {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0}; 
unsigned int const Pic_18_matrix[4][4] = {0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0}; 
unsigned int const Pic_19_matrix[4][4] = {0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0}; 
int main()
{
	int nRow = 0, nCol = 0;
  	int n = 0, m = 0;
  	char ucKey=0;
  	unsigned int unLinesErased = 0;
    char strScore[10];
  	 
  	srand((unsigned int)time(NULL));
  	Initialize_AllPictures();
  	initwindow(1600, 900);
	  	
	do
	{
		lib:
		StartNewPlayGame();
		fflush(stdin);
		while (ucKey != VK_RETURN) 
		{
		 	ucKey =getch();
		};		 
		setcolor(BK_COLOR);
		outtextxy(xSTART + (NUM_COL + 3)*BLOCKSIZE, ySTART + (NUM_ROW / 2 - 3)*BLOCKSIZE,"               ");

		unIsCurrentPlayOver = 0;

		unCurrentPicIndex = Random_GenerateNewPicIndex();

		unNextPicIndex = Random_GenerateNewPicIndex();

		nCurrentPicRow = START_FALL_ROW;
	    nCurrentPicCol = START_FALL_COL;

	    DrawGivenIndexPic(START_FALL_ROW, NUM_COL + 1, unNextPicIndex);
		DrawGivenIndexPic(nCurrentPicRow, nCurrentPicCol, unCurrentPicIndex);

		while(unIsCurrentPlayOver == 0)
		{
		 	if(kbhit()) 
		 	{
		 		ucKey = getch();
		 		switch(ucKey)
		 		{
		 			
		 		case VK_SPACE:
		 			while (!kbhit());
		 			break;
		 		case ARROW_LEFT: 
				    if(CanCurrentIndexPicMoveLeft(nCurrentPicRow, nCurrentPicCol, unCurrentPicIndex)) 
				    {
				    	EarseGivenIndexPic(nCurrentPicRow,nCurrentPicCol,unCurrentPicIndex);
				    	nCurrentPicCol--;
				    	DrawGivenIndexPic(nCurrentPicRow, nCurrentPicCol, unCurrentPicIndex);
				    	clockStart = clock();
					}
					break;
				case ARROW_RIGHT:
					if(CanCurrentIndexPicMoveRight(nCurrentPicRow, nCurrentPicCol, unCurrentPicIndex))
		 			{
		 				EarseGivenIndexPic(nCurrentPicRow,nCurrentPicCol,unCurrentPicIndex);
				    	nCurrentPicCol++;
				    	DrawGivenIndexPic(nCurrentPicRow, nCurrentPicCol, unCurrentPicIndex);
				    	clockStart = clock();
				    }
				    break;   
		        case ARROW_DOWN:  

				    while(CanCurrentIndexPicMoveDown(nCurrentPicRow, nCurrentPicCol, unCurrentPicIndex)) 
	                {
		 				EarseGivenIndexPic(nCurrentPicRow, nCurrentPicCol, unCurrentPicIndex);
				    	nCurrentPicRow++;
				    	DrawGivenIndexPic(nCurrentPicRow, nCurrentPicCol, unCurrentPicIndex);
				    	Delay_Time(5);
                    }
                    
                    Start_NewFallPic_After_PreviousCannotMoveDown();
                    
                    
                    clockStart = clock();
                    break;
                case ARROW_UP:
                	if (CanCurrentPicRotate(nCurrentPicRow, nCurrentPicCol, unCurrentPicIndex))
                	{
                		EarseGivenIndexPic(nCurrentPicRow, nCurrentPicCol, unCurrentPicIndex);
	                    unCurrentPicIndex = unMatrixRotation[unCurrentPicIndex];
	                    DrawGivenIndexPic(nCurrentPicRow, nCurrentPicCol, unCurrentPicIndex);
	                    clockStart = clock();
					}
					break;
				case VK_ESCAPE:
					unIsCurrentPlayOver = 1;
					break;
				case RESTART:
					goto lib;
					break;
				default:
					break;
			   }
			}
			else
			{
				clockCurrent = clock();
				if(clockCurrent >= clockStart + unTimeDelay)
				{
					if(CanCurrentIndexPicMoveDown(nCurrentPicRow, nCurrentPicCol, unCurrentPicIndex))
					{
						EarseGivenIndexPic(nCurrentPicRow, nCurrentPicCol, unCurrentPicIndex);
	                    nCurrentPicRow++;
	                    DrawGivenIndexPic(nCurrentPicRow, nCurrentPicCol, unCurrentPicIndex);
					}
					else
					{
						
						Start_NewFallPic_After_PreviousCannotMoveDown();
					}
					clockStart = clock();
				}
			}
		}
		
	}while(ucKey!=VK_ESCAPE);
	
	closegraph();
	return 0;
}

void Delay_Time(unsigned int unMilliSecondToDelay)
{
	time_t timeStart = 0, timeCurrent = 0;
	
	timeStart = clock();
	while(1)
	{
		timeCurrent = clock();
		if(timeCurrent > timeStart + unMilliSecondToDelay*CLOCKS_PER_SEC / 1000)
		     return;
	}
} 

void DrawGivenIndexPic(int nRow, int nCol, unsigned int nPicIndexToDraw)
{
	DrawCurrentPic(nRow, nCol, unMatrixPictures[nPicIndexToDraw]);
}

unsigned int Random_GenerateNewPicIndex(void)
{
	return (rand() % NUM_PICS);
} 

void DrawBackGround(int x1, int y1)
{
	int m = 0, n = 0;
	setcolor(LINE_COLOR);
	for (m = 0; m <= NUM_ROW; m++)
	{
		line(x1, y1 + m*BLOCKSIZE, x1 + NUM_COL*BLOCKSIZE, y1 + m*BLOCKSIZE);
	}
	for (n = 0; n <= NUM_COL; n++)
	{
		line(x1 + n*BLOCKSIZE, y1, x1 + n*BLOCKSIZE, y1 + NUM_ROW*BLOCKSIZE);
	}
} 

void DrawCurrentPic(int nRow, int nCol, unsigned int maxtrixPic[4][4])
{
	int m = 0, n = 0;

	for (m = 0; m<4; m++)
	{
		for (n = 0; n<4; n++)
		{
			if (maxtrixPic[m][n] == 1)
			{
				setfillstyle(SOLID_FILL,FILL_COLOR);
				bar(xSTART + (nCol + n)*BLOCKSIZE + 1, ySTART + (nRow + m)*BLOCKSIZE + 1,
					xSTART + (nCol + n + 1)*BLOCKSIZE - 1, ySTART + (nRow + m + 1)*BLOCKSIZE - 1);
			}
		}
	}
}

void EarseGivenIndexPic(int nRow, int nCol, unsigned int nPicToDraw) 
{
	EarseCurrentPic(nRow, nCol, unMatrixPictures[nPicToDraw]);
}

void EarseCurrentPic(int nRow, int nCol, unsigned int maxtrixPic[4][4])
{
	int m = 0, n = 0;
	
	for (m = 0; m<4; m++)
	{
		for (n = 0; n<4; n++)
		{
			if (maxtrixPic[m][n] == 1)
			{
				setfillstyle(SOLID_FILL,BK_COLOR);
				bar(xSTART + (nCol + n)*BLOCKSIZE + 1, ySTART + (nRow + m)*BLOCKSIZE + 1,
					xSTART + (nCol + n + 1)*BLOCKSIZE - 1, ySTART + (nRow + m + 1)*BLOCKSIZE - 1);
			}
		}
	}
}

void StartNewPlayGame(void)
{
	char strScore[10];
	char strTotalOut[128]="成绩: ";
	
	setbkcolor(BK_COLOR);
	cleardevice();
	memset(unMatrixBackGround, 0, sizeof(unMatrixBackGround));
	unIsCurrentPlayOver = 0;
	DrawBackGround(xSTART, ySTART);
	
	settextstyle(0,0,4);
	
	setcolor(SCORE_COLOR);
	outtextxy(xSTART+(NUM_COL+3)*BLOCKSIZE,ySTART+(NUM_ROW/2-5)*BLOCKSIZE,strTotalOut);
	memcpy(strScore, "", sizeof(strScore));
	outtextxy(xSTART + (NUM_COL + 8)*BLOCKSIZE, ySTART + (NUM_ROW / 2 - 5)*BLOCKSIZE, strScore);
	sprintf(strScore, " %-8u", unTotalScore);
	outtextxy(xSTART+(NUM_COL+8)*BLOCKSIZE,ySTART+(NUM_ROW/2-5)*BLOCKSIZE,strScore);
	
	outtextxy(xSTART + (NUM_COL + 3)*BLOCKSIZE, ySTART + (NUM_ROW / 2 - 3)*BLOCKSIZE, "按回车键开始");
	
	setcolor(TIPS_COLOR);
	outtextxy(xSTART+(NUM_COL+2)*BLOCKSIZE,ySTART+(NUM_ROW/2 - 2)*BLOCKSIZE," R:  重开");
	outtextxy(xSTART+(NUM_COL+2)*BLOCKSIZE,ySTART+(NUM_ROW/2)*BLOCKSIZE,"↑:  旋转");
	outtextxy(xSTART+(NUM_COL+2)*BLOCKSIZE,ySTART+(NUM_ROW/2+2)*BLOCKSIZE,"←:  左移");
	outtextxy(xSTART+(NUM_COL+2)*BLOCKSIZE,ySTART+(NUM_ROW/2+4)*BLOCKSIZE,"→:  右移");
	outtextxy(xSTART+(NUM_COL+2)*BLOCKSIZE,ySTART+(NUM_ROW/2+6)*BLOCKSIZE,"↓:  下落");
	outtextxy(xSTART+(NUM_COL+2)*BLOCKSIZE,ySTART+(NUM_ROW/2+8)*BLOCKSIZE,"ESC: 退出");
	outtextxy(xSTART+(NUM_COL+2)*BLOCKSIZE,ySTART+(NUM_ROW/2+10)*BLOCKSIZE,"Enter: 开始");
	outtextxy(xSTART+(NUM_COL+2)*BLOCKSIZE,ySTART+(NUM_ROW/2+12)*BLOCKSIZE,"空格: 暂停");
	
	clockStart = clock();
}

unsigned int CanCurrentIndexPicMoveLeft(int nRow, int nCol, unsigned int unCurPicIndex)
{
	return CanCurrentPicMoveLeft(nRow, nCol, unMatrixPictures[unCurPicIndex]);
}

unsigned int CanCurrentPicMoveLeft(int nRow, int nCol, unsigned int curPicMatrix[4][4])
{
	int m = 0, n = 0;
	unsigned int unCanMoveLeft = 1;
	

	for(m = 0; m<4; m++)
	{

		for(n = 0; n<4; n++)
		{
			if (curPicMatrix[m][n] == 1)
			   break;
		}

		if(n == 4)
		   continue;

		if(nCol + n == 0)
		{
			unCanMoveLeft = 0;
			break;
		}

		if(unMatrixBackGround[nRow + m][nCol + n - 1] == 1)
		{
			unCanMoveLeft = 0;
			break;
		} 
	} 
	return unCanMoveLeft;
}


unsigned int CanCurrentIndexPicMoveRight(int nRow, int nCol, unsigned int unCurPicIndex)
{
	return CanCurrentPicMoveRight(nRow, nCol, unMatrixPictures[unCurPicIndex]);
}  


unsigned int CanCurrentPicMoveRight(int nRow, int nCol, unsigned int curPicMatrix[4][4])
{
	int m = 0, n = 0;
	unsigned int unCanMoveRight = 1;

	for(m = 0; m<4; m++)
	{

		for(n = 3; n >= 0; n--)
		{
			if (curPicMatrix[m][n] == 1)
			   break;
		}

		if(n == -1)
		   continue;

		if(nCol + n == NUM_COL - 1)
		{
			unCanMoveRight = 0;
			break;
		}

		if(unMatrixBackGround[nRow + m][nCol + n + 1] == 1)
		{
			unCanMoveRight = 0;
			break;
		} 
	} 
	return unCanMoveRight;
}


unsigned int CanCurrentIndexPicMoveDown(int nRow, int nCol, unsigned int unCurPicIndex)
{
	return CanCurrentPicMoveDown(nRow, nCol, unMatrixPictures[unCurPicIndex]);
}

unsigned int CanCurrentPicMoveDown(int nRow, int nCol, unsigned int curPicMatrix[4][4])
{
	int m = 0, n = 0;
	unsigned int unCanMoveDown = 1;

	for(n = 0; n<4; n++)
	{

		for(m= 3; m >= 0; m--)
		{
			if (curPicMatrix[m][n] == 1)
			   break;
		}

		if(m == -1)
		   continue;

		if(nRow + m == NUM_ROW - 1)
		{
			unCanMoveDown = 0;
			break;
		}

		if(unMatrixBackGround[nRow + m + 1][nCol + n] == 1)
		{
			unCanMoveDown = 0;
			break;
		} 
	} 
	return unCanMoveDown;
}


unsigned int CanCurrentPicRotate(int nRow, int nCol, unsigned int unCurrentPicIndex)
{
	
	unsigned int unRotatedPicIndex = 0;
	int m = 0, n = 0;
	unsigned int unCurPicCanRotate = 1;
	
	
	unRotatedPicIndex = unMatrixRotation[unCurrentPicIndex];
	
	
	for (m = 0; m < 4; m++)
	{
		for (n = 0; n < 4; n++)
		{
			
			if(unMatrixPictures[unRotatedPicIndex][m][n] == 1)
			{
				
				if ((nRow+m<0)||(nRow+m>NUM_ROW-1)||(nCol+n<0)||(nCol+n>NUM_COL-1))
				{
					unCurPicCanRotate = 0;
					break;
				}
				else if(unMatrixBackGround[nRow+m][nCol+n]==1)
				{
					unCurPicCanRotate = 0;
					break;
				}
				
			}
		}
		if (unCurPicCanRotate == 0)
		    break;
    }
    return unCurPicCanRotate;
}


unsigned int IsCurrentLine_All_1_Line(unsigned int nRow)
{
	unsigned int unIsAll_1_Line = 1;
	int n = 0;
	for (n = 0; n < NUM_COL; n++)
	{
		
		if (unMatrixBackGround[nRow][n] == 0)
		{
			unIsAll_1_Line = 0;
			break;
		}
	}
	return unIsAll_1_Line;
}


unsigned int IsCurrentLine_All_0_Line(unsigned int nRow)
{
	unsigned int unIsAll_0_Line = 1;
	int n = 0;
	for (n = 0; n < NUM_COL; n++)
	{
		
		if(unMatrixBackGround[nRow][n] == 1)
		{
			unIsAll_0_Line = 0;
			break;
		}
	}
	return unIsAll_0_Line;
}

unsigned int Erase_All_1_Lines(void)
{
	unsigned int unLinesErased = 0;

	int nRow = 0;
	int m = 0, n = 0;

	for (nRow = NUM_ROW-1; nRow > 0; nRow--)
	{

		while (IsCurrentLine_All_1_Line(nRow) == 1)
		{

			for (m = nRow - 1; m >= 0; m--)
			{
				for (n = 0; n < NUM_COL; n++)
				{
					if (unMatrixBackGround[m][n] == 0)
					{

						setfillstyle(SOLID_FILL,BK_COLOR);
						bar(xSTART + n*BLOCKSIZE + 1, ySTART + (m+1)*BLOCKSIZE + 1,
								xSTART + (n + 1)*BLOCKSIZE - 1, ySTART + (m + 1+1)*BLOCKSIZE - 1);
					}
					else
					{

						setfillstyle(SOLID_FILL,FILL_COLOR);
						bar(xSTART + n*BLOCKSIZE + 1, ySTART + (m + 1)*BLOCKSIZE + 1,
							xSTART + (n + 1)*BLOCKSIZE - 1, ySTART + (m + 1 + 1)*BLOCKSIZE - 1);
					}
					
					unMatrixBackGround[m + 1][n] = unMatrixBackGround[m][n];
				}

				if (IsCurrentLine_All_0_Line(m) == 1)
					break;
			}
			unLinesErased++;
		}

		if (IsCurrentLine_All_0_Line(nRow) == 1)
			break;
	}
	return  unLinesErased;
}


void Initialize_AllPictures(void)
{
	memset(unMatrixPictures, 0, sizeof(unMatrixPictures));
	
	unMatrixPictures[0][2][1] = unMatrixPictures[0][2][2] = 1;
	unMatrixPictures[0][3][1] = unMatrixPictures[0][3][2] = 1;
	
	
	unMatrixPictures[1][3][0] = unMatrixPictures[1][3][1] = 1;
	unMatrixPictures[1][3][2] = unMatrixPictures[1][3][3] = 1;
	
	
	unMatrixPictures[2][1][2] = unMatrixPictures[2][2][1] = 1;
	unMatrixPictures[2][2][2] = unMatrixPictures[2][3][1] = 1;
	
	
	unMatrixPictures[3][1][1] = unMatrixPictures[3][2][1] = 1;
	unMatrixPictures[3][2][2] = unMatrixPictures[3][3][2] = 1;
	
	
	unMatrixPictures[4][1][2] = unMatrixPictures[4][2][2] = 1;
	unMatrixPictures[4][3][2] = unMatrixPictures[4][3][3] = 1;
	
	
	unMatrixPictures[5][1][3] = unMatrixPictures[5][2][3] = 1;
	unMatrixPictures[5][3][2] = unMatrixPictures[5][3][3] = 1;
	
	
	unMatrixPictures[6][2][2] = unMatrixPictures[6][3][1] = 1;
	unMatrixPictures[6][3][2] = unMatrixPictures[6][3][3] = 1;
	
	
	unMatrixPictures[7][0][3] = unMatrixPictures[7][1][3] = 1;
	unMatrixPictures[7][2][3] = unMatrixPictures[7][3][3] = 1;
	
	
	unMatrixPictures[8][2][0] = unMatrixPictures[8][2][1] = 1;
	unMatrixPictures[8][3][1] = unMatrixPictures[8][3][2] = 1;
	
	
	unMatrixPictures[9][2][2] = unMatrixPictures[9][2][3] = 1;
	unMatrixPictures[9][3][1] = unMatrixPictures[9][3][2] = 1;
	
	
	unMatrixPictures[10][2][3] = unMatrixPictures[10][3][1] = 1;
	unMatrixPictures[10][3][2] = unMatrixPictures[10][3][3] = 1;
	
	
	unMatrixPictures[11][1][2] = unMatrixPictures[11][1][3] = 1;
	unMatrixPictures[11][2][3] = unMatrixPictures[11][3][3] = 1;
	
	
	unMatrixPictures[12][2][1] = unMatrixPictures[12][2][2] = 1;
	unMatrixPictures[12][2][3] = unMatrixPictures[12][3][1] = 1;
	
	
	unMatrixPictures[13][2][1] = unMatrixPictures[13][2][2] = 1;
	unMatrixPictures[13][2][3] = unMatrixPictures[13][3][3] = 1;
	
	
	unMatrixPictures[14][1][2] = unMatrixPictures[14][1][3] = 1;
	unMatrixPictures[14][2][2] = unMatrixPictures[14][3][2] = 1;
	
	
	unMatrixPictures[15][2][1] = unMatrixPictures[15][3][1] = 1;
	unMatrixPictures[15][3][2] = unMatrixPictures[15][3][3] = 1;
	
	
	unMatrixPictures[16][1][2] = unMatrixPictures[16][2][1] = 1;
	unMatrixPictures[16][2][2] = unMatrixPictures[16][3][2] = 1;
	
	
	unMatrixPictures[17][2][1] = unMatrixPictures[17][2][2] = 1;
	unMatrixPictures[17][2][3] = unMatrixPictures[17][3][2] = 1;
	
	
	unMatrixPictures[18][1][2] = unMatrixPictures[18][2][2] = 1;
	unMatrixPictures[18][2][3] = unMatrixPictures[18][3][2] = 1;
	
	
	unMatrixRotation[0] = 0;
	unMatrixRotation[1] = 7;
	unMatrixRotation[2] = 8;
	unMatrixRotation[3] = 9;
	unMatrixRotation[4] = 10;
	unMatrixRotation[5] = 13;
	unMatrixRotation[6] = 16;
	unMatrixRotation[7] = 1;
	unMatrixRotation[8] = 2;
	unMatrixRotation[9] = 3;
	unMatrixRotation[10] = 11;
	unMatrixRotation[11] = 12;
	unMatrixRotation[12] = 4;
	unMatrixRotation[13] = 14;
	unMatrixRotation[14] = 15;
	unMatrixRotation[15] = 5;
	unMatrixRotation[16] = 17;
	unMatrixRotation[17] = 18;
	unMatrixRotation[18] = 6;
}

void Start_NewFallPic_After_PreviousCannotMoveDown(void)
 {
 	int m = 0, n = 0;
 	char strScore[10];
 	unsigned int unLinesErased = 0;
 	

	for(m = 0; m < 4; m++)
	{
	 	for(n = 0; n < 4; n++)
	 	{
	 		if(unMatrixPictures[unCurrentPicIndex][m][n] == 1)
	 		   unMatrixBackGround[nCurrentPicRow + m][nCurrentPicCol + n] = 1;
		}
    }     

    unLinesErased = Erase_All_1_Lines();
	unTotalScore = unTotalScore + 200 * unLinesErased;

	unTimeDelay = (unsigned int )MAX_DELAY-(unTotalScore/3000) * (CLOCKS_PER_SEC/10);

	setcolor(SCORE_COLOR);
	memcpy(strScore,"         ",sizeof(strScore));
	outtextxy(xSTART + (NUM_COL + 8)*BLOCKSIZE, ySTART + (NUM_ROW / 2 - 5)*BLOCKSIZE, strScore);
	sprintf(strScore, " %-8u ", unTotalScore);
	outtextxy(xSTART + (NUM_COL + 8)*BLOCKSIZE, ySTART + (NUM_ROW / 2 - 5)*BLOCKSIZE, strScore);

	EarseGivenIndexPic(START_FALL_ROW, NUM_COL + 1, unNextPicIndex);

	unCurrentPicIndex = unNextPicIndex;

	unNextPicIndex = Random_GenerateNewPicIndex();
	DrawGivenIndexPic(START_FALL_ROW, NUM_COL + 1, unNextPicIndex);

	nCurrentPicRow = START_FALL_ROW;
	nCurrentPicCol = START_FALL_COL;
		 

	if(CanCurrentIndexPicMoveDown(nCurrentPicRow, nCurrentPicCol, unCurrentPicIndex))
	   DrawGivenIndexPic(nCurrentPicRow, nCurrentPicCol, unCurrentPicIndex);
	else
		unIsCurrentPlayOver = 1;
  }


