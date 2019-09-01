/*

THIS IS THE STUDENT SECTION. 

FILES : STUDENT.TXT --> STUDENT DETAILS
		ATTENDANCE1.TXT  --> ATTENDANCE DETAILS


*/

#include<bits/stdc++.h>						//Includes all Standard C++ Headers
#define strcasecmp _stricmp
#ifdef unix									//If Compilation Environment is UNIX
#include <math.h>
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <stdlib.h>
#include <unistd.h>							//For usleep() function
#define delay(x) usleep(x*1000)				//For Windows delay function
#define CLS() cout<<"\033[2J\033[1;1H"		//ANSI Escape sequence for clearing screen
int login();
void gotoxy(int x,int y){					//gotoxy function for UNIX
 	printf("%c[%d;%df",0x1B,y,x);			//ANSI Escape Seqeuence  for gotoxy
 }
#endif
#ifndef unix								//If Compilation Environment is not UNIX
#define CLS() system("cls")					//Windows clearscreen function
#include<windows.h>
void gotoxy(int x,int y){					//gotoxy for Windows - it isn't my code
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

#endif
#define FLBSTUD "student.txt"				//Macros for storing filenames for ease
#define FLBCLAS "class.txt"					//The files are binary files
#define RULE(x) cout<<'\n'; for(int _=0;_<80;_++) cout<<x; cout<<'\n' //Outputs Horizontal Consisting of 'x's
#define CL(cl,x) cl==0?1:cl==x				//Macro for disabling search through class
using namespace std;

int strcmpi(const char * s1, const char* s2){			//String compare without case
	return strcasecmp(s1,s2);
}
bool strcmpis(pair <string, int> s1, pair <string,int> s2){ //Compare function for sort()
	return (strcasecmp(s1.first.c_str(),s2.first.c_str()))<0;
}

void load(){								//Loader function [c-p cp]
	CLS();
	cout<<"\n\n\n\n\t\t\t\t  Loading\n\n";
	for (int i=0;i<80;i++){
		cout<<"!";
		gotoxy(i,3);						//Top Loading line
		cout<<"!";
		cout.flush();						//Flush output buffer for delay()
		gotoxy(i+1,7);						//Bottom Loading line
		delay((rand()%80) + 20);
	}
	cout.flush();
	delay(200);
}
int scan(){							//Scan function for input of only non-negative integers
	string ch;						//Taking inital input through string
	int i,v;
	do{
		v=1;
		cin>>ch;
		for(i=0;i<ch.size();i++){	//Checking each character is digit
			if(!isdigit(ch[i])){
				v=0;
				break;
			}
		}
	}while(!v);
	return atoi(ch.c_str());		//Coverting string back to integer
}
char bGs[8][4] = {"A+","B+", "AB+", "O+", "A-", "B-", "AB-", "O-"}; //Allowed Blood Groups
int fee[12] = {						//Fee for each standard
1000,
1000,
1000,
1000,
1000,
1000,
1000,
1000,
1000,
1000,
1000,
1000
};
char * strTitle(int x){				//Coverting Title from Integer to readable text
	static char title[8] = " ";
	if(x==1)
		strcpy(title,"Master");
	else if(x==2)
		strcpy(title,"Mr");
	else
		strcpy(title,"Miss");
	return title;
}


using namespace std;
class Admission
{
public:
};


class Student {						//Student class for storing Records in the student file
	int title;  //Master  = 1, Mr = 2, Miss = 3
	char studentName[30];
	int rollNo;
	char fatherName[30];
	char motherName[30];
	char address[80];
	char bloodGroup[4];
	public:
	void getDetails(void);			//Get Student Details from user
	void printDetails(void){		//Printing the details of Student
		cout<<"Student Name  : "<<strTitle(title)<<' '<<studentName<<endl;
		cout<<"Roll No.      : "<<rollNo<<endl;
		cout<<"Father's Name : "<<fatherName<<endl;
		cout<<"Mother's Name : "<<motherName<<endl;
		cout<<"Address       : "<<address<<endl;
		cout<<"Blood Group   : "<<bloodGroup<<endl;
	}
	int retRollNo(){				//Return Roll No
		return rollNo;
	}
	char * retString(char x){		//Return all strings avaialable from the Student Class
		if(x=='T')
			return strTitle(title);
		if(x=='N')
			return studentName;
		if(x=='F')
			return fatherName;
		if(x=='M')
			return motherName;
		if(x=='A')
			return address;
		if(x=='B')
			return bloodGroup;
	}
	char * retStudentName(){		//Returns Student Name
		return retString('N');
	}
	void modDetail(char ch);		//Modify Details for Student
};

void Student::getDetails(){			//Get Student Details from user
system("CLS");
	cout<<"Enter Title \n(Master = 1, Mr = 2, Miss = 3)  : ";
	do{
		title = scan();
	}while(title!=1 && title!=2 && title!=3);
	cout<<"Enter Student Name    : ";
	do{
		gets(studentName);
	}while(strlen(studentName)==0);
	cout<<"Enter Roll No.        : ";
	do{
		rollNo=scan();
	}while(rollNo<1);
	cout<<"Enter Father Name     : ";
	do{
		gets(fatherName);
	}while(strlen(fatherName)==0);
	cout<<"Enter Mother Name     : ";
	do{
		gets(motherName);
	}while(strlen(motherName)==0);
	cout<<"Enter Address         : ";
	do{
		gets(address);
	}while(strlen(address)==0);
	cout<<"Enter Blood Group     : ";
	int v = 0,i;
	do{
		gets(bloodGroup);
		for (i=0;i<strlen(bloodGroup);i++) bloodGroup[i] = toupper(bloodGroup[i]);
		for(i=0;i<8;i++)
			if(!strcmp(bloodGroup,bGs[i])){
				v=1;
				break;
			}
	}while(!v);
}

void insertStudent(){			//Insert Student Record in File
system("CLS");
	Student obj,obj2;
	char ch;
	int v=0;
	cout<<"Enter Details for new Student :\n";
	obj.getDetails();
	fstream fl1(FLBSTUD, ios::in|ios::binary);
	ofstream fl2;
	if(!fl1){					//If file does not exist, create new file
		fl2.open(FLBSTUD,ios::out|ios::binary);
		fl2.write((char*)&obj, sizeof(obj));
		fl2.close();
		cout<<"Record successfully inserted !\n";
		return;
	}
	while(!fl1.eof()){
		fl1.read((char*)&obj2,sizeof(obj));
		if(fl1.eof()){
			break;
		}
		if(obj.retRollNo()==obj2.retRollNo()){		//If record with same Roll No. exists, then abort insertion
			cout<<"Record with same Roll No. with following details already exists : \n";
			obj2.printDetails();
			cout<<"Insertion Aborted !\n";
			return;
		}
		else if(strcmpi(obj.retStudentName(),obj2.retStudentName())==0){
			if (!v)							//Warns user that Record with same name exists
				cout<<"Warning : Record with same name exists with follwing details : \n";
			obj2.printDetails();
			cout<<'\n';
			v=1;
		}
	}
	if(v){
		cout<<"Do you still wish to insert record (Y/N) ? ";
		do{									//Asks for user confirmation after warning
			cin>>ch;
			ch = toupper(ch);
		}while(ch!= 'Y' && ch!='N');
		if(ch=='N'){
			cout<<"Insertion Aborted !\n";
			return;
		}
	}
	fl2.open(FLBSTUD,ios::out|ios::app|ios::binary);
	fl2.seekp(0,ios::end);
	fl2.write((char*)&obj, sizeof(obj));
	fl2.close();
	cout<<"Record Inserted successfully !\n";
}



int dispStudentRecord(){		//Display all Student Records
system("CLS");
	Student obj;
	int v=0;
	fstream fl(FLBSTUD, ios::in|ios::binary);
	if(!fl){					//If file does not exist
		cout<<"Empty Records !\n";
		return 0;
	}
	while(!fl.eof()){
		fl.read((char*)&obj, sizeof(obj));
		if(fl.eof())
			break;
		v=1;
		obj.printDetails();
		RULE('-');
	}
	fl.close();
	if(!v)
		cout<<"Empty Records !\n";
	return v;
}

int searchStudentID(const string str = "search"){	//Search Student by Attributes
system("CLS");
	fstream fl(FLBSTUD,ios::in|ios::ate|ios::binary);
	if((!fl)||fl.tellg()==0){						//If file is empty or zero size
		cout<<" No Records Found !\n";
		return 0;
	} 
	fl.close();
	fl.open(FLBSTUD,ios::in|ios::binary);
	char ch;
	char query[30];
	Student obj;
	int found = 0;
	cout<<"Enter Attribute to "<<str<<" :\n";
	cout<<"  (T)itle.\n";
	cout<<"  (N)ame of Student.\n";
	cout<<"  (F)ather's Name.\n";
	cout<<"  (M)other's Name.\n";
	cout<<"  (A)ddress.\n";
	cout<<"  (B)lood Group.\n";
	cout<<"Enter your choice : ";
	do{
		cin>>ch;
		ch = toupper(ch);
	}while(ch!='T' && ch!='N' && ch!='F' && ch!='M' && ch!='A' && ch!='B');
	cout<<"\nEnter Query : ";
	do{
		gets(query);
	}while(strlen(query)==0);
	while(!fl.eof()){
		fl.read((char*)&obj,sizeof(obj));
		if(fl.eof()){
			break;
		}
		if((strcmpi(query,obj.retString(ch))==0)){
			if(!found)
				cout<<"\nSearch Results : \n\n";
			obj.printDetails();
			RULE('-');
			found = 1;
		}
	}
	if(!found)
		cout<<"No Records Found !\n";
	fl.close();
	return found;
}

int searchByRollNo(int i){			//Search Record by Roll No., 1 for Class, 2 for Student
system("CLS");
	int r;
	int found=0;
	Student obj;
	cout<<"Enter Roll No. to search for : ";
	cin>>r;
	fstream fl(FLBSTUD,ios::in|ios::binary);
	if(!fl){					//No file exists
		cout<<"No Records Found !\n";
		return 0;
	}
	while(!fl.eof()){
		fl.read((char*)&obj,sizeof(obj));
		if(fl.eof()){
			break;
		}
		if(r==obj.retRollNo()){
			if(!found)
				cout<<"\nSearch Results : \n\n";
			obj.printDetails();
			RULE('-');
			found = 1;
		}
	}
	if(!found)
		cout<<"No Records Found !\n";
	fl.close();
	return found;
}

void sortByStudents(char ch){			//Sort Records
	vector <pair<string,int> > lst;		//Make vector of pairs of string to sort by and Roll No.
	int i;		
	Student obj;
	int v=0;
	char c;
	fstream fl(FLBSTUD, ios::in|ios::binary);
	system("CLS");
	cout<<"Enter criteria to sort :\n";
	cout<<"  (N)ame of Student.\n";
	cout<<"  (T)itle.\n";
	cout<<"Enter your choice : \n";		
	do{
		cin>>c;
		c=toupper(c);
	}while(c!='N' && c!='T');
	if(!fl){
		cout<<"Empty Records !\n";
		return;
	}
	while(!fl.eof()){
		fl.read((char*)&obj, sizeof(obj));
		if(fl.eof())
			break;
		v=1;
		lst.push_back(make_pair(obj.retString(c),obj.retRollNo()));	//Push each pair in the vector
	}
	fl.close();
	if(v==0){
		cout<<"Empty Records !\n";
		return;
	}
	sort(lst.begin(),lst.end(),strcmpis);	//Sort using <algorithm> sort and Custom Comparison 
	fstream tmp("temp.txt",ios::out|ios::binary);
	fl.open(FLBSTUD,ios::in|ios::binary);
	fl.seekg(0,ios::beg);
	for(i=0;i<lst.size();i++){
		fl.close();
		fl.open(FLBSTUD,ios::in|ios::binary);
		while(!fl.eof()){
			fl.read((char*)&obj, sizeof(obj));
			if(fl.eof())
				break;
			if(obj.retRollNo()==lst[i].second){		//Check each Roll No. from each pair and write record to new file
				tmp.write((char*)&obj,sizeof(obj));
			}
		}
	}
	fl.close();
	tmp.close();
	remove(FLBSTUD);
	rename("temp.txt",FLBSTUD);
	cout<<"\nThe Records have been successfully sorted !\n\n";
	dispStudentRecord();
}


void delStudentRecord(){			//Delete Student Records
system("CLS");
	Student obj;					//Writes to new file except record to be deleted
	int f=0;
	if(!searchStudentID("delete using"))
		return;
	cout<<"\nEnter Roll No. to delete : ";
	int r;
	char ch;
	cin>>r;
	fstream fl(FLBSTUD, ios::in|ios::binary);
	fstream fo("temp.dat", ios::out|ios::binary);
	while(!fl.eof()){
		fl.read((char*)&obj, sizeof(obj));
		if(fl.eof())
			break;
		if (r==obj.retRollNo()){
			cout<<"Record with following info will be deleted :\n\n";
			obj.printDetails();
			cout<<"Do you wish to continue ? (Y/N) : ";
			do{
				cin>>ch;
				ch = toupper(ch);
			}while(ch!='N' && ch!='Y');
			if(ch=='N'){
				cout<<"Deletion Aborted !\n";
				
				fl.close();
				fo.close();
				remove("temp.dat");
				return;
			}
			f=1;
			continue;
		}
		fo.write((char*)&obj,sizeof(obj));
	}
	fl.close();
	fo.close();
	remove(FLBSTUD);
	rename("temp.dat",FLBSTUD);
	if(f)
		cout<<"Record Successfully Deleted !\n";
	else
		cout<<"No Such Record Exists !\n";
}


//ATTENDANCE SECTION

class attend
{
        float p=0,t=0,w;
        public:
                int enter();
                void calculate();
};
int attend::enter()//update the attendance
{
        int date,month,year;
        int i=1,n,k,a,c;
        int z[20];
        
        while(i)
        {
        	cout<<"->Enter DATE <space> MONTH <space> YEAR: "<<endl;
        	cin>>date>>month>>year;
        	cout<<endl;
                if(month== 1||month==3||month==5||month==7||month==8||month==10||month==12)
                {
                		if(date>31||date==0)
                		{
							c=0;
						}
						else
						{
							 c=1;
						}
                }
                if(month== 4||month==6||month==9||month==11)
                {
                	if(date>30 ||date==0)
                	{
                		 c=0;
                	}
                	else
                	{
                		 c=1;
                	}
                }
                if(month==2)
                {
                	if(date>29||date==0)
                	{
                		 c=0;
                	}
                	else
                	{
                		 c=1;
                	}
                }
                if(month>12)
                {
                	c=0;
                }
                if(month==0||year==0)
				{
					c=0;
				}
                switch(c)//gives if the given date is correct or not and update
                {
                	case 0:cout<<"Please enter::VALID DATE::"<<endl<<endl;
                			break;
               		 case 1:
               			 cout<<">>ENTER NUMBER OF PERIODS IN THE DAY...(max periods=7): ";
                		cin>>n;
                		cout<<endl;
                		for(k=1;k<n+1;k++)
                		{
                    	    cout<<"->ENTER '1' IF PRESENT ELSE '0' TO UPDATE THE STATUS OF PERIOD "<<k<<" :";
                    	    cin>>a;
                    	    if(a==1)
                    	    {
                    	            p++;
                        	        t++;
                        	        z[k]=1;
                        	        RULE("*");
                						cout<<endl<<endl;
                            	    cout<<"                         :::UPDATED AS PRESENT:::"<<endl<<endl;
                            	    RULE("*");
                						cout<<endl<<endl;
                        	}
                			else
                        	{
                        	        t++;
                        	        z[k]=0;
                        	         RULE("*");
                						cout<<endl<<endl;
                        	        cout<<"                          :::UPDATED AS ABSENT:::"<<endl<<endl;
                        	         RULE("*");
                						cout<<endl<<endl;
                        	}
                		}
                		cout<<endl;
                		cout<<"                    ::::::ATTENDANCE OF THE DAY IS UPDATED AS:::::"<<endl;
                		for(k=1;k<n+1;k++)
                		{
                			cout<<"__________";
                		}
                		cout<<endl<<endl;
                		cout<<"DD/MM/YY    ";
                		for(k=1;k<n+1;k++)
                		{
                		cout<<"p"<<k<<"    ";
                		}
                		cout<<endl<<endl;
                		cout<<date<<"/"<<month<<"/"<<year<<"   ";
                		for(k=1;k<n+1;k++)
                		{
                			if(z[k]==1)
                			{
                				cout<<"P"<<"     ";
                			}
                			else
                			{
                				cout<<"A"<<"     ";
                			}
                		}
                		cout<<endl<<endl;
                		for(k=1;k<n+1;k++)
                		{
                			cout<<"__________";
                		}
                		cout<<endl;
                		cout<<endl;
                		break;
						default://To exit
				exit(0);
            	}
                cout<<">>ENTER 1 TO TO UPDATE ANOTHER DAY ELSE 0  :";
                cin>>i;
                cout<<endl;
        }

}
void attend::calculate()//calculate the percentage
{
         int x,r;
         float s;
        x=(t*75)/100;
        s=(p*100)/t;
        if(s<75&&s>65)
        {
        		RULE("_");
        		cout<<endl;
                cout<<"                           YOUR ATTENDANCE IS LOW : "<<s<<"  %  "<<endl;
                r=x-p;
                cout<<endl;
                RULE("*");
                cout<<"                        you must have attended "<<r<<" classes                "<<endl;
                RULE("_");
                cout<<endl;
        }
         if(s<65)
        {
                int y;
                y=(t*65)/100;
                int  k=y-p;
                RULE("_");
                cout<<endl;
                cout<<"                     YOUR ATTENDANCE IS : "<<s<<" % "<<endl;
                RULE("*");
                cout<<endl;
                cout<<"                   you must have attended "<<k<<" classes                      "<<endl;
                RULE("_");
                cout<<endl;
        }
        if(s>75)
        {
        		RULE("_");
                cout<<endl;
                cout<<"                      YOUR ATTENDANCE IS :"<<s<<" % "<<endl;
                RULE("_");
                cout<<endl;
        }
}


int main()
{
	attend o1,o2,o3;
    int a=1,w;
    ifstream file1;
    ofstream file2;
        
    char ch;
	char ch1;
	int ch2;
	load();
	do{
		CLS();
		RULE("*");
		cout <<"\t\t\tSTUDENT INFORMATION SECTION";
		RULE("*");
		cout<<"\t1. Admission Details.\n";
		cout<<"\t2. Attendance System.\n";
		cout<<"\t0. Exit.\n\n";
		cout<<"Enter your choice : ";
		fflush(stdin);
		cin>>ch1;
		if(ch1=='1'){
			fflush(stdin);

			load();

            do{
                    CLS();
                    RULE("*");
                    cout <<"\t\t\tSTUDENT INFORMATION SECTION";
                    RULE("*");
                    cout<<"\t\t\t     ADMISSION DETAILS";
                    RULE('-');

                    cout<<"\t1.  Register Student\n";
                    cout<<"\t2.  Display all Records.\n";
                    cout<<"\t3.  Search for a Record using Roll No.\n";                    
                    cout<<"\t4.  Sort all Records.\n";                   
                    cout<<"\t5.  Delete a Record.\n";
                    cout<<"\t0.  Exit.\n";
                    cout<<"\nEnter your choice : ";

                    ch2 = scan();
                        switch(ch2)
                        {
                            case 1:
                                insertStudent();
                                break;
                            case 2:
                                dispStudentRecord();
                                break;
                            case 3:
                                searchByRollNo(2);
                                break;
                            
                            case 4:
                                sortByStudents('S');
                                break;
                            
                            case 5:
                                delStudentRecord();
                                break;
                        }
                        fflush(stdin);
                        if(ch2)
                            cin>>ch;
                        else
                            load();
                    }while(ch2!=0);
            }
            
    if(ch1=='2')
	{
		fflush(stdin);
		load();	
		CLS();		
        cout<<endl;
        
        RULE("*");
                    cout <<"\t\t\tSTUDENT INFORMATION SECTION";
                    RULE("*");
                    cout<<"\t\t\tATTENDANCE MAINTAINANCE SYSTEM";
                    RULE('-');
        
        cout<<endl;
        while(a)
        {
        	RULE("*");
        	cout<<"\t1.  View Your Attendance\n";
            cout<<"\t2.  Update Your Attendance\n";
        	RULE("*");
        	cin>>w;
        switch(w)//perform options
        {
        	case 1:
        		file1.open("attendance.txt");
        		file1.read((char *)& o1, sizeof(o1));
        		o1.calculate();
        		file1.close();
        		break;
        	case 2:
				file1.open("attendance.txt");
				file1.read((char *)& o2, sizeof(o2));
				file1.close();
				o2.enter();
				file2.open("attendance.txt");
				file2.write((char *)& o2, sizeof(o2));
				file2.close();
				break;
        }
	        cout<<">>ENTER 1 TO CONTINUE ELSE 0"<<endl;
	        cin>>a;
    	}
	}

    }while(ch1!='0');


	CLS();
	return 0;

}
