
//======================================//
#ifdef unix									//If Compilation Environment is UNIX
#include <math.h>
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <stdlib.h>
#include <unistd.h>							//For usleep() function
#define delay(x) usleep(x*1000)				//For Windows delay function
#define CLS() cout<<"\033[2J\033[1;1H"		//ANSI Escape sequence for clearing screen
#define RULE(x) cout<<'\n'; for(int i=0;i<80;i++) cout<<x; cout<<'\n'
using namespace std;
int login();
void gotoxy(int x,int y)					//gotoxy function for UNIX
{					
 	printf("%c[%d;%df",0x1B,y,x);			//ANSI Escape Seqeuence  for gotoxy
}
 
void load()
{							
	CLS();
	std::cout<<"\n\n\n\n\t\t\t\t  Loading\n\n";
	for (int i=0;i<80;i++){
		std::cout<<"!";
		gotoxy(i,3);						//Top Loading line
		std::cout<<"!";
		std::cout.flush();						//Flush output buffer for delay()
		gotoxy(i+1,7);						//Bottom Loading line
		delay(10);
	}
	std::cout.flush();
}

int scan()
{							//Scan function for input of only non-negative integers
	string ch;						//Taking inital input through string
	int i,v;
	do
	{
		v=1;
		cin>>ch;
		for(i=0;i<ch.size();i++)
		{
			if(!isdigit(ch[i])){
				v=0;
				break;
			}
		}
	}while(!v);
	return atoi(ch.c_str());		//Coverting string back to integer
}

#endif
//======================================//
#ifndef unix								//If Compilation Environment is not UNIX
#define CLS() system("cls")					//Windows clearscreen function
#define RULE(x) cout<<'\n'; for(int _=0;_<80;_++) cout<<x; cout<<'\n'
#include<windows.h>
using namespace std;
void gotoxy(int x,int y)
{					//gotoxy for Windows - it isn't my code
	y--;
	static HANDLE h=NULL;
	if(!h){
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	COORD c = {x,y};
	SetConsoleCursorPosition(h,c);
}
void delay(unsigned int secs){				//Defining delay function for Windows
	clock_t goal = secs +  clock();			//Using clock to set time to delay till
	while(goal>clock());					//Waiting till that time
}

void load()
{								//Loader function [c-p cp]
	CLS();
	std::cout<<"\n\n\n\n\t\t\t\t  Loading\n\n";
	for (int i=0;i<80;i++){
		std::cout<<"!";
		gotoxy(i,3);						//Top Loading line
		std::cout<<"!";
		std::cout.flush();						//Flush output buffer for delay()
		gotoxy(i+1,7);						//Bottom Loading line
		delay(10);
	}
	std::cout.flush();
}

int scan()
{							//Scan function for input of only non-negative integers
	string ch;						//Taking inital input through string
	int i,v;
	do
	{
		v=1;
		cin>>ch;
		for(i=0;i<ch.size();i++)
		{
			if(!isdigit(ch[i])){
				v=0;
				break;
			}
		}
	}while(!v);
	return atoi(ch.c_str());		//Coverting string back to integer
}
#endif
//======================================//
