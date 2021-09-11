//=====================================================================================================
// Name         :   game.cpp
// Author       :   Hassan Mustafa
// Modified By  :   Muhammad Talha Zeb Khan
// Roll No      :   19I-0641
// Section      :   A
// Version      :   Beta
// Copyright    :   (c) Reserved
// Description  :   Basic 2D game of Dodge 'Em...
//=====================================================================================================

#ifndef DODGE_CPP_
#define DODGE_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<fstream> //----Read / Write Data
#include<cmath>	//---- for basic math functions such as cos, sin, sqrt

using namespace std;

//=====================================================================================================
//---------------------------------------ALL FUNCTIONS USED--------------------------------------------
//=====================================================================================================

void SetCanvasSize(int width, int height);
void Arena();
void car_hor(float x,float y,float width,float height, float radius,float* color);
void gift_display();
void main_menu();
void help();
void pause_menu();
void win();
void lost();
void move_player();
void move_opponent();
void game_sense(int level);
void collision();
int level_speed();
int player_fast_speed();
void score_display();
void lives_display();
void level_display();
void reset();
void level_reset();
void update_level_score();
void highscores();	
void startAnimation();
void pauseAnimation();
int write_data(int final_score);
string read_data();
void updateFrame();

//=====================================================================================================
//-----------------------------------ALL GLOBAL INITIALIZATIONS----------------------------------------
//=====================================================================================================

int animating = 0; //For Start and Pause of Animation

//path tracks ( start , middle , extreme) 
int layer_1_x[3]={55,417,780};
int layer_1_y[3]={55,367,680};
int layer_2_x[3]={145,417,690};
int layer_2_y[3]={145,367,590};
int layer_3_x[3]={235,417,600};
int layer_3_y[3]={235,367,500};
int layer_4_x[3]={325,417,510};
int layer_4_y[3]={325,367,410};

	 // left ,right,  up,  down
bool dir[4]={  0 ,  0  ,  0  ,  0  };	

int current_layer=1;		//Player current layer
int m=0; int n=0; int n2=0;	//for suitable multiplier
int opponent_layer=1;		//Opponent current layer
int opponent2_layer=1;		//Opponent 2 current layer
int menu=1;

//---------------------------------------DISPLAY SWITCHES----------------------------------------------

bool en_menu=1;
bool en_help=0;
bool en_pause=0;
bool switch_menu=0;
bool en_start_key=1;
bool en_score=0;

//--------------------------------------GIFT / FOOD DATA--------------------------------------------

// Food / Gift Blocks
int food_x=45;
int food_y=670;
int food_width=25;
int food_height=10;
float food_center_x;
float food_center_y;
float *scolor = colors[BROWN];
bool blocks[8][8]={			//--->1 for display food and vice versa
		   {1,1,1,1,1,1,1,1},
		   {1,1,1,1,1,1,1,1},
		   {1,1,1,1,1,1,1,1},
		   {1,1,1,1,1,1,1,1},
		   {1,1,1,1,1,1,1,1},
		   {1,1,1,1,1,1,1,1},
		   {1,1,1,1,1,1,1,1},
		   {1,1,1,1,1,1,1,1}
		  };
		  

//---------------------------------------CAR PROPERTIES-------------------------------------------------

//Player properties
	float x1 = 460; 
	float h1 = 35; 
	float width1 = 10; 
	float height1 = 8;
	float* color1 = colors[YELLOW]; 
	float radius1 = 7.0;
	float car_center_x;
	float car_center_y;

//Opponent properties
	float x2 = 340; 	
	float h2 = 35; 
	float width2 = 10; 
	float height2 = 8;
	float* color2 = colors[BLUE_VIOLET]; 
	float radius2 = 7.0;
	float opp_center_x;
	float opp_center_y;
	
//Opponent 2 properties
	float x3 = 35; 	
	float h3 = 660; 				
	float width3 = 10; 
	float height3 = 8;
	float* color3 = colors[BLUE_VIOLET]; 
	float radius3 = 7.0;
	float opp2_center_x;
	float opp2_center_y;
	
//---------------------------------------SCORES / LIVES / SPEED--------------------------------------------

int score=0;
int final_score=0;
int lives=3;
float speed_player=5;
float speed_opponent=2.5;
float speed_opponent2=1;
int level=1;
bool spacebar=0; //For Doubling Speed

//---------------------------------------------WINDOW SIZE-------------------------------------------------

void SetCanvasSize(int width, int height)
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

//=========================================================================================================
//---------------------------------------ARENA  DRAWING----------------------------------------------------
//=========================================================================================================

void Arena()
{
	int sx;
	int sy;
	int swidth;
	int sheight;
	
	sx = 0;
	sy = 10;
	swidth = 370; // half width
	sheight = 10;
	
	for(int i=0;i<=3;i++,sx+=90,sy+=90,swidth-=90)
		DrawRectangle(sx, sy, swidth, sheight, scolor); // bottom left
		
	sx = 480;
	sy = 10;
	swidth = 360;
	
	for(int i=0;i<=3;i++,sy+=90,swidth-=90)
		DrawRectangle( sx, sy , swidth, sheight, scolor); // bottom right
		
	sx = 0;
	sy = 720;
	swidth = 370;
	
	for(int i=0;i<=3;i++,sx+=90,sy-=90,swidth-=90)
		DrawRectangle(sx , sy, swidth, sheight, scolor); // top left
		
	sx = 480;
	sy = 720;
	swidth = 360;//err
	
	for(int i=0;i<=3;i++,sy-=90,swidth-=90)
		DrawRectangle( sx, sy, swidth, sheight, scolor); // top right
		
	
	sx = 0;
	sy = 10;
	swidth = 20;
	sheight = 300;
	
	for(int i=0;i<=3;i++,sx+=90,sy+=90,sheight-=90)
		DrawRectangle(sx , sy , swidth , sheight , scolor);// left down
		
	sx = 820;
	sy = 10;
	swidth = 20;
	sheight = 300;
	
	for(int i=0;i<=3;i++,sx-=90,sy+=90,sheight-=90)
		DrawRectangle( sx, sy , swidth , sheight, scolor);// right down
		
	sx = 0;
	sy = 430;
	swidth = 20;
	sheight=300;
	
	for(int i=0;i<=3;i++,sx+=90,sheight-=90)
		DrawRectangle( sx, sy , swidth, sheight, scolor);// left up
		
	sx = 820;
	sy = 430;
	swidth = 20;
	sheight=300;
	
	for(int i=0;i<=3;i++,sx-=90,sheight-=90)
		DrawRectangle( sx, sy , swidth, sheight, scolor);// right up
		
	DrawRectangle( 370 , 350 , 110 , 20 , scolor);
	DrawRectangle( 370 , 365 , 110 , 20 , scolor);	
}

//=====================================================================================================
//--------------------------------------- CAR  DRAWING-------------------------------------------------
//=====================================================================================================

//Horizental car drawing function
void car_hor(float x,float y,float width,float height, float radius,float* color)
{
	DrawRoundRect(x,y,width,height,color,radius); // bottom left tyre
	DrawRoundRect(x+width*3,y,width,height,color,radius); // bottom right tyre
	DrawRoundRect(x+width*3,y+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(x,y+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(x, y+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(x+width, y+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(x+width*3, y+height*2, width, height, color, radius/2); // body right rect
}

//=====================================================================================================
//-----------------------------GIFT / FOOD DISPLAY AND DISAPPERANCE------------------------------------
//=====================================================================================================

void gift_display()
{
	car_center_x=(2*(x1+width1)+(2*width1))/2;	//--PLAYER CAR
	car_center_y=(2*(h1+height1)+(3*height1))/2;	//------------CENTER
	
	opp_center_x=(2*(x2+width2)+(2*width2))/2;	//--OPPONENT CAR
	opp_center_y=(2*(h2+height2)+(3*height2))/2;	//--------------CENTER
	
	opp2_center_x=(2*(x3+width3)+(2*width3))/2;	//--OPPONENT 2 CAR
	opp2_center_y=(2*(h3+height3)+(3*height3))/2;	//--------------CENTER
	
	for(int i=0;i<8;i++)
	{	
		
		for(int j=0;j<8;j++)
		{
			//Food Center == Rectangle Center
			food_center_x=(2*food_x+food_width)/2; 
			food_center_y=(2*food_y+food_height)/2;
			
			if(abs(car_center_x-food_center_x)<30&&abs(car_center_y-food_center_y)<30) //--Car and Gift Range
			{
				blocks[i][j]=0; //---Array set to FALSE so no Gift/Food Display
			}
			if(blocks[i][j]) //---If TRUE , will display Gift
				DrawRectangle(food_x , food_y , food_width , food_height , scolor);
			if(j==3)
				food_x+=190; //---For Larger Gift Distance ahead of 3rd Gift on X-Axis
			else
				food_x+=90;  //---Regular Gift Distance on X-Axis
		}
		food_x=45;
		if(i==3)
			food_y-=130; //---For Larger Gift Distance ahead of 3rd Gift on Y-Axis
		else
			food_y-=80; //---Regular Gift Distance on Y-Axis
	}
	food_x=45;	//------POSITIONS RESETED SO THAT IT FORMS
	food_y=670;	//------AT SAME DISTANCES WHEN REDISPLAYED
	
}

//=====================================================================================================
//---------------------------------------MAIN MENU DRAWING---------------------------------------------
//=====================================================================================================

void main_menu()
{
	
	DrawSquare( 0 , 0 ,840,colors[BLACK]);
	DrawString( 350, 700, "D  O  D  G  E   '  E  M", colors[RED]); 
	DrawString( 370, 600, "MAIN MENU", colors[RED]);
	DrawString( 355, 580, "------------", colors[RED]);
	if(menu==1)
		DrawRectangle(350 , 543 , 150 , 30 , colors[CYAN]);
	DrawString( 330, 550, "1. Start a new game", colors[RED]);
	if(menu==2)
		DrawRectangle(350 , 495 , 150 , 30 , colors[CYAN]);
	DrawString( 330, 500, "2. See high-scores", colors[RED]);
	if(menu==3)
		DrawRectangle(350 , 443 , 45 , 30 , colors[CYAN]);
	DrawString( 330, 450, "3. Help", colors[RED]);
	if(menu==4)
		DrawRectangle(350 , 395 , 35 , 30 , colors[CYAN]);
	DrawString( 330, 400, "4. Exit", colors[RED]);
}

//=====================================================================================================
//----------------------------------------HELP DRAWING-------------------------------------------------
//=====================================================================================================

void help()
{
	DrawSquare( 0 , 0 ,840,colors[BLACK]);
	DrawString( 20, 600, "INSTRUCTIONS :", colors[GOLD]);
	DrawString( 20, 580, "--------------", colors[GOLD]);
	DrawString( 20, 550, "1. Press A to start and P pause game.", colors[RED]);
	DrawString( 20, 520, "2. Move Player to next layer by pressing Up / Down / Left / Right keys", colors[RED]);
	DrawString( 20, 490, "3. Press SPACEBAR to boost.", colors[RED]);
	DrawString( 20, 460, "4. There are 4 levels and 3 lives", colors[RED]);
	DrawString( 20, 430, "5. Each level increases difficulty accordingly:", colors[RED]);
	DrawString( 50, 400, "Level 1 : Enemy is in Slow mode ,can only follow you by moving Up and Down only in layers.", colors[RED]);
	DrawString( 50, 370, "Level 2 : Enemy is Active Mode ,can take any turns.", colors[RED]);
	DrawString( 50, 340, "Level 3 : Enemy is in Active mode and its speed is also doubled.", colors[RED]);
	DrawString( 50, 310, "Level 4 : 2 Enemies in Active mode starts chasing.", colors[RED]);
	DrawString( 20, 280, "6. Have Fun :)", colors[RED]);
	DrawString( 300, 150, "PRESS ESCAPE TO EXIT", colors[GREEN]);	
	
}

//=====================================================================================================
//-------------------------------------PAUSE MENU DRAWING----------------------------------------------
//=====================================================================================================


void pause_menu()
{
	DrawSquare( 230 , 250 ,430,colors[BLACK]); 
	DrawString( 370, 600, "GAME PAUSED", colors[RED]);
	if(menu==1)
		DrawRectangle(350 , 543 , 150 , 30 , colors[CYAN]);
	DrawString( 330, 550, "1. Start a new game", colors[RED]);
	if(menu==2)
		DrawRectangle(350 , 495 , 150 , 30 , colors[CYAN]);
	DrawString( 330, 500, "2. See high-scores", colors[RED]);
	if(menu==3)
		DrawRectangle(350 , 443 , 45 , 30 , colors[CYAN]);
	DrawString( 330, 450, "3. Help", colors[RED]);
	if(menu==4)
		DrawRectangle(350 , 395 , 35 , 30 , colors[CYAN]);
	DrawString( 330, 400, "4. Exit", colors[RED]);	
	if(menu==5)
		DrawRectangle(350 , 343 , 100 , 30 , colors[CYAN]);
	DrawString( 330, 350, "5. Continue", colors[RED]);
	
		
	DrawRectangle(230 , 250 , 430 , 20 , colors[RED]);
	DrawRectangle(230 , 250 , 20 , 430 , colors[RED]);
	DrawRectangle(230 , 660 , 430 , 20 , colors[RED]);
	DrawRectangle(640 , 250 , 20 , 430 , colors[RED]);

}

//=====================================================================================================
//-------------------------------------HIGHSCORE DRAWING-----------------------------------------------
//=====================================================================================================

void highscores()
{
	DrawSquare( 0 , 0 ,840,colors[BLACK]);
	DrawString( 20, 600, "HIGHSCORES :", colors[GOLD]);
	DrawString( 20, 580, "--------------", colors[GOLD]);
	
	DrawString( 300, 150, "PRESS ESCAPE TO EXIT", colors[GREEN]);	
}

//=====================================================================================================
//-------------------------------------WIN / LOSE DRAWING----------------------------------------------
//=====================================================================================================

void win()
{	
	DrawString( 390, 630, "YOU WON", colors[GREEN]);
}

void lost()
{
	DrawString( 390, 700, "YOU LOST", colors[GREEN]);
}

//=====================================================================================================
//----------------------------------------------MOVEMENTS----------------------------------------------
//=====================================================================================================

//=====================================================================================================
//----------------------------------------PLAYER MOVEMENTS---------------------------------------------
//=====================================================================================================

void move_player()
{
//-----------------------------PLAYER CAR TRACK / LAYER DETECTION--------------------------------------
		
	if((car_center_x==layer_1_x[0])||(car_center_y==layer_1_y[0])||(car_center_x==layer_1_x[2])||(car_center_y==layer_1_y[2]))
		current_layer=1;
	else if((car_center_x==layer_2_x[0])||(car_center_y==layer_2_y[0])||(car_center_x==layer_2_x[2])||(car_center_y==layer_2_y[2]))
		current_layer=2;
	else if((car_center_x==layer_3_x[0])||(car_center_y==layer_3_y[0])||(car_center_x==layer_3_x[2])||(car_center_y==layer_3_y[2]))
		current_layer=3;
	else if((car_center_x==layer_4_x[0])||(car_center_y==layer_4_y[0])||(car_center_x==layer_4_x[2])||(car_center_y==layer_4_y[2]))
		current_layer=4;
	//cout<<"Player Layer : "<<current_layer<<endl;
			
	m=current_layer;
	m>1?m-=1:m=0;	//--->Used for Factor Multiplication used in determining Track Accordingly

//--------------------------MOVEMENT ACCORDING TO BOUNDRY DETECTION-------------------------------------

//-----------------------------SPACEBAR INCLUDED FOR DOUBLE SPEED---------------------------------------
	
	if(car_center_y==(layer_1_y[0]+(m*90))&&car_center_x<(layer_1_x[2]-(m*90)))
		x1+=speed_player+ player_fast_speed();//-->If spacebar TRUE i.e 1, SPEED FACTOR DOUBLED
	else if(car_center_x==(layer_1_x[2]-(m*90))&&car_center_y<(layer_1_y[2]-(m*90)))
		h1+=speed_player+player_fast_speed();
	else if(car_center_y==(layer_1_y[2]-(m*90))&&car_center_x>(layer_1_x[0]+(m*90)))
		x1-=speed_player+player_fast_speed();
	else if(car_center_x==(layer_1_x[0]+(m*90))&&car_center_y>(layer_1_y[0]+(m*90)))
		h1-=speed_player+player_fast_speed();		
	
	
	int inner_layer=4;
	int a;
	for(int i=0;i<4;i++)
	{
		if(dir[i])
			a=i+1;	//-->Used to translate button detection to Direction detection and act accordingly
	}
	switch(a)
	{
		case 1: //--->If in RIGHT VERTICAL PATH
			if((abs(car_center_y-layer_1_y[1])<50)&&current_layer<inner_layer&&car_center_x>layer_1_x[1])
			{
				current_layer++;
				x1-=90;	//Can only move left
			}
			else if((abs(car_center_y-layer_1_y[1])<50)&&current_layer<=inner_layer&&car_center_x<layer_1_x[1])
			{
				if(current_layer!=1)	//If not in 1st Layer can Move LEFT or RIGHT
				{	
					current_layer--;
					x1-=90;
				}
				else
				{
					x1+=(layer_1_x[2]-layer_1_x[0]);
				}
			}
			dir[0]=0; //-->Resets Left Direction(button) After one time pressed
			break;
		case 2:	//--->If in LEFT VERTICAL PATH
			if((abs(car_center_y-layer_1_y[1])<50)&&current_layer<inner_layer&&car_center_x<layer_1_x[1])
			{
				current_layer++;
				x1+=90; //Can only move right
			}
			else if((abs(car_center_y-layer_1_y[1])<50)&&current_layer<=inner_layer&&car_center_x>layer_1_x[1])
			{
				if(current_layer!=1)	//If not in 1st Layer can Move LEFT or RIGHT
				{	
					current_layer--;
					x1+=90;
				}
				else
				{
					x1-=(layer_1_x[2]-layer_1_x[0]);
				}
			}
			dir[1]=0; //-->Resets Right Direction(button) After one time pressed
			break;
		case 3:	//--->If in BOTTOM HORIZENTAL PATH
			if((abs(car_center_x-layer_1_x[1])<50)&&current_layer<inner_layer&&car_center_y<layer_1_y[1])
			{
				current_layer++;
				h1+=90;	//Can only move up
			}
			else if((abs(car_center_x-layer_1_x[1])<50)&&current_layer<=inner_layer&&car_center_y>layer_1_y[1])
			{
				if(current_layer!=1)	//If not in 1st Layer can Move UP or DOWN
				{	
					current_layer--;
					h1+=90;
				}
				else
				{
					h1-=(layer_1_y[2]-layer_1_y[0]);
				}
			}
			dir[2]=0; //-->Resets Up Direction(button) After one time pressed
			break;
		case 4:	//--->If in TOP HORIZENTAL PATH
			if((abs(car_center_x-layer_1_x[1])<50)&&current_layer<inner_layer&&car_center_y>layer_1_y[1])
			{
				current_layer++;
				h1-=90;	//Can only move down
			}
			else if((abs(car_center_x-layer_1_x[1])<50)&&current_layer<=inner_layer&&car_center_y<layer_1_y[1])
			{
				if(current_layer!=1)	//If not in 1st Layer can Move UP or DOWN
				{	
					current_layer--;
					h1-=90;
				}
				else
				{
					h1+=(layer_1_y[2]-layer_1_y[0]);
				}
			}
			dir[3]=0; //-->Resets Down Direction(button) After one time pressed
			break;
	}
	a=0;	//-->Set All directions to ZERO for correct answer after Redisplay.
}

//=====================================================================================================
//--------------------------------------OPPONENT-1 MOVEMENTS-------------------------------------------
//=====================================================================================================

void move_opponent()
{

//-----------------------------OPPONENT-1 CAR TRACK / LAYER DETECTION--------------------------------------

	if((opp_center_x==layer_1_x[0])||(opp_center_y==layer_1_y[0])||(opp_center_x==layer_1_x[2])||(opp_center_y==layer_1_y[2]))
		opponent_layer=1;
	else if((opp_center_x==layer_2_x[0])||(opp_center_y==layer_2_y[0])||(opp_center_x==layer_2_x[2])||(opp_center_y==layer_2_y[2]))
		opponent_layer=2;
	else if((opp_center_x==layer_3_x[0])||(opp_center_y==layer_3_y[0])||(opp_center_x==layer_3_x[2])||(opp_center_y==layer_3_y[2]))
		opponent_layer=3;
	else if((opp_center_x==layer_4_x[0])||(opp_center_y==layer_4_y[0])||(opp_center_x==layer_4_x[2])||(opp_center_y==layer_4_y[2]))
		opponent_layer=4;
		
	n=opponent_layer;
	n>1?n-=1:n=0;	//--->Used for Factor Multiplication used in determining Track Accordingly

//--------------------------MOVEMENT ACCORDING TO BOUNDRY DETECTION-------------------------------------
	
	if(opp_center_y==(layer_1_y[0]+(n*90))&&opp_center_x>(layer_1_x[0]+(n*90)))
		x2-=speed_opponent;//*level_speed();
	else if(opp_center_x==(layer_1_x[0]+(n*90))&&opp_center_y<(layer_1_y[2]-(n*90)))
		h2+=speed_opponent;//*level_speed();
	else if(opp_center_y==(layer_1_y[2]-(n*90))&&opp_center_x<(layer_1_x[2]-(n*90)))
		x2+=speed_opponent;//level_speed();
	else if(opp_center_x==(layer_1_x[2]-(n*90))&&opp_center_y>(layer_1_y[0]+(n*90)))
		h2-=speed_opponent;//level_speed();	
/*		
//=====================================================================================================
//--------------------------------------OPPONENT-2 MOVEMENTS-------------------------------------------
//=====================================================================================================
		
	if(level==4)
	{

//-----------------------------OPPONENT-2 CAR TRACK / LAYER DETECTION------------------------------------

	if((opp2_center_x==layer_1_x[0])||(opp2_center_y==layer_1_y[0])||(opp2_center_x==layer_1_x[2])||(opp2_center_y==layer_1_y[2]))
		opponent2_layer=1;
	else if((opp2_center_x==layer_2_x[0])||(opp2_center_y==layer_2_y[0])||(opp2_center_x==layer_2_x[2])||(opp2_center_y==layer_2_y[2]))
		opponent2_layer=2;
	else if((opp2_center_x==layer_3_x[0])||(opp2_center_y==layer_3_y[0])||(opp2_center_x==layer_3_x[2])||(opp2_center_y==layer_3_y[2]))
		opponent2_layer=3;
	else if((opp2_center_x==layer_4_x[0])||(opp2_center_y==layer_4_y[0])||(opp2_center_x==layer_4_x[2])||(opp2_center_y==layer_4_y[2]))
		opponent2_layer=4;
		
	//cout<<"Opponent Layer : "<<opponent_layer<<endl;
		
	n2=opponent2_layer;
	n2>1?n2-=1:n2=0;	//--->Used for Factor Multiplication used in determining Track Accordingly

//--------------------------MOVEMENT ACCORDING TO BOUNDRY DETECTION---------------------------------------
	
	if(opp2_center_y==(layer_1_y[0]+(n2*90))&&opp2_center_x>(layer_1_x[0]+(n2*90)))
		x3-=speed_opponent2+level_speed();
	else if(opp2_center_x==(layer_1_x[0]+(n2*90))&&opp2_center_y<(layer_1_y[2]-(n2*90)))
		h3+=speed_opponent2+level_speed();
	else if(opp2_center_y==(layer_1_y[2]-(n2*90))&&opp2_center_x<(layer_1_x[2]-(n2*90)))
		x3+=speed_opponent2+level_speed();
	else if(opp2_center_x==(layer_1_x[2]-(n2*90))&&opp2_center_y>(layer_1_y[0]+(n2*90)))
		h3-=speed_opponent2+level_speed();	
	}*/	
	
	
}


//=====================================================================================================
//-------------------------------------------AI / GAME SENSE-------------------------------------------
//=====================================================================================================

//=====================================================================================================
//-------------------------------------OPPONENT-1 GAME SENSE-------------------------------------------
//=====================================================================================================

//Game Sense(Opponent Catching to Player)
void game_sense(int level)
{
	int diff1=abs(opponent_layer-current_layer); //--Finds Difference between Opponent and Player Layer
	if((diff1>=1))	//--If Difference means opponent has to move to another level.
	{
		if(abs(opp_center_y-layer_1_y[1])<20)//--If Y-Axis Match of Opponent Car Center and Track Center -->Horizental Track
		{
			if(opponent_layer<current_layer)	//--Layer Difference
			{
				if(opp_center_x>layer_1_x[1])	//Opponent----------------------------------------
					x2-=90;			//----------Car-----------------------------------
				else				//-------------Movement---------------------------
					x2+=90;			//-----------------------To-----------------------
			}					//--------------------------Other-----------------
			else					//--------------------------------Track-----------
			 {					//--------------------------------------Accordingly
				if(opp_center_x>layer_1_x[1])	
					x2+=90;			
				else				
					x2-=90;			
			 }
		}					//Unfornately level not detecting
		if(((abs(opp_center_x-layer_1_x[1]))<20)&&(level>1))//--If X-Axis Match of Opponent Car Center and Track Center-->Vertical Track
		{
			if(opponent_layer<current_layer)	//--Layer Difference
			{
				if(opp_center_y>layer_1_y[1])
					h2-=90;
				else
					h2+=90;
			}
			else//(opponent_layer>current_layer)
			{
				if(opp_center_y<layer_1_y[1])
					h2-=90;
				else
					h2+=90;
			}
		}
		
	}
/*	
//=====================================================================================================
//-------------------------------------OPPONENT-2 GAME SENSE-------------------------------------------
//=====================================================================================================
	
	if(level==4)
	{
	int diff2=abs(opponent2_layer-current_layer); //--Finds Difference between Opponent and Player Layer
	//cout<<"difference"<<diff<<endl;
	if((diff2>=1))	//--If Difference means opponent has to move to another level.
	{
		if(abs(opp2_center_y-layer_1_y[1])<20)//--If Y-Axis Match of Opponent Car Center and Track Center -->Horizental Track
		{
			if(opponent2_layer<current_layer)	//--Layer Difference
			{
				if(opp2_center_x>layer_1_x[1])	//Opponent----------------------------------------
					x3-=90;			//----------Car-----------------------------------
				else				//-------------Movement---------------------------
					x3+=90;			//-----------------------To-----------------------
			}					//--------------------------Other-----------------
			else					//--------------------------------Track-----------
			 {					//--------------------------------------Accordingly
				if(opp2_center_x>layer_1_x[1])	
					x3+=90;			
				else				
					x3-=90;			
			 }
		}
		else if(abs(opp2_center_x-layer_1_x[1])<20)//--If X-Axis Match of Opponent Car Center and Track Center-->Vertical Track
									//and level detection
		{
			
			if(opponent2_layer<current_layer)	//--Layer Difference
			{
				if(opp2_center_y>layer_1_y[1])
					h3-=90;
				else
					h3+=90;
			}
			else//(opponent_layer>current_layer)
			{
				if(opp2_center_y<layer_1_y[1])
					h3-=90;
				else
					h3+=90;
			}
		}
		
	}
	
	}*/
	
}


//=====================================================================================================
//-------------------------------------COLLISION DETECTION---------------------------------------------
//=====================================================================================================

void collision()
{
	int diff_x=abs(opp_center_x-car_center_x);	//Player and Opponent Cars
	int diff_y=abs(opp_center_y-car_center_y);	//X & Y Axis Difference
	
	if(diff_x<30&&diff_y<30)	//If Less then Certain Range --> Boom :>
	{
		 x1 = 460; 		//Back
		 h1 = 35; 		//    To
					//      Initial 
		 x2 = 340; 		//             State
		 h2 = 35;		
					
		 for(int i=0;i<8;i++)	
		 	for(int j=0;j<8;j++)
		 		blocks[i][j]=1;	//Gift Also reset
		  		  
		lives--;
		
		if(lives==0)
		{	
			write_data(final_score);
			reset();
			lost();
			pauseAnimation();
			en_start_key=1;
			en_pause=1;
			
		}
	}
	
}

//=====================================================================================================
//-----------------------------------------SPEED VARIATION---------------------------------------------
//=====================================================================================================

//OPPONENT SPEED
int level_speed()
{
	if(level>2)
		return 2;
	else
		return 1;

}

//PLAYER SPEED
int player_fast_speed()
{
	return (speed_player*spacebar);
}

//=====================================================================================================
//-----------------------------------------SCORE COUNTER-----------------------------------------------
//=====================================================================================================

int score_counter()
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(blocks[i][j]==0) //---Score +1 for each Food/Gift taken
			{
				score++;
				
			}		
		}
	}
	final_score=((level-1)*64)+score;
	return final_score;
}

//=====================================================================================================
//-----------------------------------------SCORE DISPLAY-----------------------------------------------
//=====================================================================================================

void score_display()
{
	DrawString( 620, 750, "SCORE : ", colors[GREEN]);
	DrawString( 700, 750, Num2Str(final_score), colors[YELLOW]);
	score=0;		
}

//=====================================================================================================
//-----------------------------------------LIVES DISPLAY-----------------------------------------------
//=====================================================================================================


void lives_display()
{
	DrawString( 30, 750, "LIVES : ", colors[GREEN]);
	DrawString( 100, 750, Num2Str(lives) , colors[YELLOW]);
}		

//=====================================================================================================
//-----------------------------------------LEVEL DISPLAY-----------------------------------------------
//=====================================================================================================

void level_display()
{	
	DrawString( 30, 780, "LEVEL : ", colors[GREEN]);
	DrawString( 100, 780, Num2Str(level) , colors[YELLOW]);
}		

//=====================================================================================================
//--------------------------------SCORE / LIVES / LEVEL RESET------------------------------------------
//=====================================================================================================


//--------------------------------NEXT LEVEL POSITIONS UPDATE---------------------------------------------

void level_reset()
{
	x1 = 460; 		//Back
	h1 = 35; 		//    To
				//      Initial 
	x2 = 340; 		//             State
	h2 = 35;
	
	if(level==4)
	{
		x3 = 35; 	
		h3 = 660;
	} 		
					
	for(int i=0;i<8;i++)	
		for(int j=0;j<8;j++)
			blocks[i][j]=1;
	
	
	pauseAnimation();
		
}

//----------------------------------------ALL RESET-------------------------------------------------

void reset()
{
	x1 = 460; 		//Back
	h1 = 35; 		//    To
				//      Initial 
	x2 = 340; 		//             State
	h2 = 35;		
					
	for(int i=0;i<8;i++)	
		for(int j=0;j<8;j++)
			blocks[i][j]=1;

	score=0;
	lives=3;
	level=1;
}

//----------------------------------NEXT LEVEL SCORE UPDATE---------------------------------------------

void update_level_score()
{
	if(final_score==64)
	{
		level=2;
		level_reset();
		en_start_key=1;
	}
	if(final_score==128)
	{
		level=3;
		level_reset();
		en_start_key=1;
	}
	if(final_score==192)
	{
		level=4;
		level_reset();
		en_start_key=1;
	}
	if(final_score==256)
	{
		reset();
		en_start_key=1;
		en_pause=1;
		win();
		pauseAnimation();
	}
}


//=====================================================================================================
//--------------------------------READ / WRITE HIGHSCORE FILE------------------------------------------
//=====================================================================================================

//--------------------------------------WRITE HIGHSCORE FILE-------------------------------------------

int write_data(int final_score)
{
	
	int high_scores[5]; //scores array
	int temp = 0;
	
	for(int i=0;i<5;i++)
	{
		if(final_score>high_scores[i])
			high_scores[i]=final_score;
	
	}
	for (int i = 0; i < 4; ++i)   //  'for' loop is used for sorting the numbers in descending order
	{
	        for (int j = i + 1; j < 5; ++j)
	        {
	            if (high_scores[i] < high_scores[j])
	            {
	                temp = high_scores[i];
	                high_scores[i] = high_scores[j];
	                high_scores[j] = temp;
	            }
	        }
	}
	
	//writing to a file
	ofstream fout;
	fout.open ("highscores.txt"); //this function takes the name of the file that you are writing to
	
	for (int i = 0; i < 5; i++){
		fout << high_scores[i] << endl;
	}
		
	fout.close();
	return 1;
}

//--------------------------------------READ HIGHSCORE FILE---------------------------------------------

string read_data()
{
	string score;
	ifstream fin ("highscores.txt"); //name of the file it is supposed to read
	if (fin.is_open())
	{
		int i=550;
		int j=1;
		highscores();
		while ( getline (fin, score) ) //this loop will run depending on the number of lines in the file
		{
		  DrawString( 10, i, Num2Str(j), colors[GOLD]);
		  DrawString( 35, i, "-", colors[RED]);
		  DrawString( 60, i, score, colors[RED]);//stoi() to convert string into Integer
		  i-=30;
		  j++;
		}
		
		fin.close();
	}
	else 
		cout << "Unable to open file";
	return score;
}

//=====================================================================================================
//-------------------------------------ANIMATING FUNCTIONS---------------------------------------------
//=====================================================================================================

//Function Animating Movements
void updateFrame()
{
	//This is called before each frame of the Animation.
	
	move_player();		//Player Movement
	
	move_opponent();	//Opponent Movement
	
	game_sense(1);		//Opponent Game Sense (AI :>)
	
	collision();		//Collision Detection 
		
	score_counter();	//Score Display
	
	if(score==64)
	update_level_score();	//Update Score
	
		
} 

//=====================================================================================================
//-------------------------------------MAIN CANVAS DRAWING---------------------------------------------
//=====================================================================================================

void GameDisplay()
{
	//             RED    GREEN    BLUE     ALPHA
	glClearColor(   0  ,   0   ,   0.0    ,   0    ); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	 if(en_menu==0)
	{
		Arena();
		gift_display();
		car_hor(x1,h1,width1,height1,radius1,color1);//PLAYER
		car_hor(x2,h2,width2,height2,radius2,color2);//OPPONENT-1
		if(level==4)
			car_hor(x3,h3,width3,height3,radius3,color3);//OPPONENT-2
		score_display();
		lives_display();
		level_display();
		
		//INSTRUCTIONS-->Button Press
		if(en_start_key==1)
			DrawString( 200, 750, "PRESS A TO START GAME", colors[GOLD]);
	}
	
//------------------------------------MIAN MENU SWITCHES-----------------------------------------------

	else if(en_menu==1)
		main_menu();
		
	if(en_help==1)
		help();
	
	if(en_pause==1)
		pause_menu();	
		
	if(en_score==1)
		read_data();
		

	//------------------------------Grid Functionality
	/*for(int x=0;x<=840;x+=20)
	{
		DrawLine(x, 0, x, 700, 1, 0);
	}
	for(int y=0;y<=700;y+=20)
	{
		DrawLine(0, y, 840, y, 1, 0);
	}*/

	glutSwapBuffers(); // do not modify this line.. or draw anything below this line
}

//=====================================================================================================
//-------------------------------------START / PAUSE / FPS---------------------------------------------
//=====================================================================================================

//----------------------------------------FPS CONTROL--------------------------------------------------

void timerFunction(int timerID)
{
	if (animating)
	{
        	updateFrame();
        	glutTimerFunc(1, timerFunction, 0);
        	glutPostRedisplay();
	}
}

//--------------------------------START / RESTART ANIMATION---------------------------------------------

void startAnimation()
{
	if (!animating)
	{
		animating = 1;
		glutTimerFunc(1, timerFunction, 0);
	}
}

//-------------------------------------PAUSE ANIMATION--------------------------------------------------

void pauseAnimation()
{
	animating = 0;
}

//=====================================================================================================
//------------------------------------------KEY BINDINGS-----------------------------------------------
//=====================================================================================================
 
void NonPrintableKeys(int key, int x, int y)
{	
	if (key == GLUT_KEY_LEFT) //--> LEFT ARROW KEY	
	{
		if(animating)
			dir[0]=1;
						
		
	}
	else if (key == GLUT_KEY_RIGHT) //--> RIGHT ARROW KEY
	{
		
		if(animating)		
			dir[1]=1;
		
	} 
	else if (key == GLUT_KEY_UP) //--> UP ARROW KEY	
	{
		
		if(animating)
			dir[2]=1;
		if(en_menu||en_pause)
			if(menu>1)
				--menu;
		
	}
	else if (key == GLUT_KEY_DOWN) //--> DOWN ARROW KEY
	{
	
		if(animating)	
			dir[3]=1;
		if(en_menu)
			if(menu<4)
				++menu;
		if(en_pause)
			if(menu<5)
				++menu;
		
	}

	glutPostRedisplay(); //--REDARW
	score_counter(); //--KEEP SCORE CONSTANT IN MENU

}

void PrintableKeys(unsigned char key, int x, int y)
{
	if (key == 27)		/* Escape key ASCII*/
	{
		if(switch_menu==0&&en_help)
		{
			en_help=0;
			en_menu=1;
		}
		if(switch_menu==1&&en_help)
		{
			en_help=0;
			en_pause=1;
		}
		if(switch_menu==0&&en_score)
		{
			en_score=0;
			en_menu=1;
		}
		if(switch_menu==1&&en_score)
		{
			en_score=0;
			en_pause=1;
		}				
	}

	if (key == 'p' || key == 'P')
	{
		if ( animating )
		{	
			pauseAnimation(); //--->Pauses Animation
			en_pause=1;
		}
	}
	if (key == ' ')	//SPACE BAR KEY
	{
	//-------------------EXCLUSIVE OR-----------------	
	/*The result is 1 if either one of the two bits is 1,
	  but not in the case that both are. There for,
	  if neither or both of them are equal to 1 the result is 0.*/
		spacebar^=1;
		
	}
	if(key == 13) // 'Enter' ASCII Key
	{
		if((en_menu||en_pause)&&menu==1)	//Various switches used accordingly
		{					//for correct functionality of 'Enter' KEY.
			if(switch_menu==0)		
			{	
				en_menu=0;
				switch_menu=1;
				
			}
			if(switch_menu==1)
			{
				en_pause=0;
				reset();
				en_start_key=1;
			}
		}
		
		if((en_menu||en_pause)&&menu==2)
		{	
			if(switch_menu==0)
			{
				en_score=1;
				en_menu=0;
			}
			if(switch_menu==1)
			{
				en_score=1;
				en_pause=0;
			}
			
						
		}
			
		if((en_menu||en_pause)&&menu==3)
		{	
			if(switch_menu==0)
			{
				en_help=1;
				en_menu=0;
			}
			if(switch_menu==1)
			{
				en_help=1;
				en_pause=0;
			}
			
						
		}
		if((en_menu||en_pause)&&menu==4)
			exit(1);
			
		if(menu==5)
		{
			en_pause=0;
			startAnimation();
		}
		
					
	}
	if(key == 'a'|| key=='A')	//Initial car start button
		{
			en_start_key=0;
			startAnimation();
		}
	glutPostRedisplay();
	score_counter();	//Score redisplayed so that score remains constant for user in background
	
}


//=====================================================================================================
//------------------------------------------MAIN FUNCTION----------------------------------------------
//=====================================================================================================
 
int main(int argc, char*argv[])
{
	
	int width = 840, height = 840; //WINDOW SIZE
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Dodge em"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
