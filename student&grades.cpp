#include<bits/stdc++.h>	
#include "header.h"
#define FLBSTUD "student.txt"	
#define FLBGRAD "grade.txt"	
using namespace std;



class Student 
{						
	int title;  //Master  = 1, Mr = 2, Miss = 3
	char studentName[30];
	int rollNo;
	char fatherName[30];
	char motherName[30];
	char address[80];
	char bloodGroup[4];
	public:
		
	void getDetails();	
	
	char * strTitle(int x)  	//Converting Title from Integer to readable text
	{			
		static char title[8] = " ";
		if(x==1)
			strcpy(title,"Master");
		else if(x==2)
			strcpy(title,"Mr");
		else
			strcpy(title,"Miss");
		return title;
	}		
	
	void printDetails()
	{		
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
	char * retString(char x)
	{		//Return all strings avaialable from the Student Class
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
};

void Student::getDetails()
{			
	system("CLS");
	cout<<"Enter Title \n(Master = 1, Mr = 2, Miss = 3)  : ";
	do{
		title = scan();
	}while(title!=1 && title!=2 && title!=3);
	
	cout<<"Enter Student Name        : ";
	do{
		gets(studentName);
	}while(strlen(studentName)==0);
	cout<<"Enter Roll No.            : ";
	do{
		rollNo=scan();
	}while(rollNo<1);
	cout<<"Enter Father Name         : ";
	do{
		gets(fatherName);
	}while(strlen(fatherName)==0);
	cout<<"Enter Mother Name         : ";
	do{
		gets(motherName);
	}while(strlen(motherName)==0);
	cout<<"Enter Address             : ";
	do{
		gets(address);
	}while(strlen(address)==0);
	
	cout<<"Enter Blood Group [eg. B+]: ";
	do{
		gets(bloodGroup);			
	}while(strlen(bloodGroup)==0);
}

void insertStudent()			//Insert Student Record in File
{			
	system("CLS");
	Student obj,obj2;
	char ch;
	int v=0;
	cout<<"Enter Details for new Student :\n";
	obj.getDetails();
	fstream fl1(FLBSTUD, ios::in|ios::binary);
	ofstream fl2;
	if(!fl1)			//If file does not exist, create new file
	{					
		fl2.open(FLBSTUD,ios::out|ios::binary);
		fl2.write((char*)&obj, sizeof(obj));
		fl2.close();
		cout<<"Record successfully inserted !\n";
		return;
	}
	while(!fl1.eof())
	{
		fl1.read((char*)&obj2,sizeof(obj));
		if(fl1.eof())
		{
			break;
		}
		if(obj.retRollNo()==obj2.retRollNo())		//If record with same Roll No. exists, then abort insertion
		{		
			cout<<"Record with same Roll No. with following details already exists : \n";
			obj2.printDetails();
			cout<<"Insertion Aborted !\n";
			return;
		}
		else if(strcmpi(obj.retStudentName(),obj2.retStudentName())==0)
		{
			if (!v)							//Warns user that Record with same name exists
				cout<<"Warning : Record with same name exists with follwing details : \n";
			obj2.printDetails();
			cout<<'\n';
			v=1;
		}
	}
	if(v)
	{
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



int dispStudentRecord()		//Display all Student Records
{		
	system("CLS");
	Student obj;
	int v=0;
	fstream fl(FLBSTUD, ios::in|ios::binary);
	if(!fl)
	{					//If file does not exist
		cout<<"Empty Records !\n";
		return 0;
	}
	while(!fl.eof())
	{
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



int searchByRollNo(int i)
{			//Search Record by Roll No., 1 for Class, 2 for Student
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
	while(!fl.eof())
	{
		fl.read((char*)&obj,sizeof(obj));
		if(fl.eof())
		{
			break;
		}
		if(r==obj.retRollNo())
		{
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



void delStudentRecord()
{			
	system("CLS");
	Student obj;					//Writes to new file except record to be deleted
	int f=0;
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


/*================================================================================*/

class Grade
{
    private:
        char  name[30];
        int   rollNo;
        int   total;
        float perc;
    public:    	
    	int retRollNo()
		{ return rollNo; }
		void retGrade(float marks)
		{
			if(marks<50)
		    {
		        printf("Grade F");
		    }
		    else if(marks>=50 && marks<60)
		    {
		        printf("Grade D");
		    }
		    else if(marks>=60 && marks<70)
		    {
		        printf("Grade C");
		    }
		    else if(marks>=70 && marks<80)
		    {
		        printf("Grade B");
		    }
		    else if(marks>=80 && marks<90)
		    {
		        printf("Grade A");
		    }
		    else
		    {
		        printf("Grade A+");
		    }
		}
        void getDetails(void);
        void putDetails(void);
};

void Grade::getDetails(void)
{
	cout << "Enter Roll No. :";
    cin >> rollNo;
    cout << "Enter Full Name: " ;
    cin >> name;    
    cout << "Enter Total Marks (500) : ";
    cin >> total;
    perc=(float)total/500*100;
}

void Grade::putDetails(void)
{
    cout<<"Student Name     : "<<name<<endl;
	cout<<"Roll No.         : "<<rollNo<<endl;
	cout<<"Total		 : "<<total<<endl;
	cout<<"Percentage	 : "<<perc<<endl;
	retGrade(perc);
}

void insertGrade()			//Insert Grade  in File
{			
	system("CLS");
	Grade obj,obj2;
	char ch;
	int v=0;
	obj.getDetails();
	fstream gl1(FLBGRAD, ios::in|ios::binary);
	ofstream gl2;
	if(!gl1)			
	{					
		gl2.open(FLBGRAD,ios::out|ios::binary);
		gl2.write((char*)&obj, sizeof(obj));
		gl2.close();
		cout<<"Grade successfully inserted !\n";
		return;
	}

	gl2.open(FLBGRAD,ios::out|ios::app|ios::binary);
	gl2.seekp(0,ios::end);
	gl2.write((char*)&obj, sizeof(obj));
	gl2.close();
	cout<<"Grade Inserted successfully !\n";
}



int dispGrade()		//Display all Student Records
{		
	system("CLS");
	Grade obj;
	int v=0;
	fstream fl(FLBGRAD, ios::in|ios::binary);
	if(!fl)
	{					//If file does not exist
		cout<<"Empty Records !\n";
		return 0;
	}
	while(!fl.eof())
	{
		fl.read((char*)&obj, sizeof(obj));
		if(fl.eof())
			break;
		v=1;
		obj.putDetails();
		RULE('-');
	}
	fl.close();
	if(!v)
		cout<<"Empty Records !\n";
	return v;
}

int searchGradeByRollNo(int i)
{			
	system("CLS");
	int r;
	int found=0;
	Grade obj;
	cout<<"Enter Roll No. to search for : ";
	cin>>r;
	fstream fl(FLBGRAD,ios::in|ios::binary);
	if(!fl){					//No file exists
		cout<<"No Records Found !\n";
		return 0;
	}
	while(!fl.eof())
	{
		fl.read((char*)&obj,sizeof(obj));
		if(fl.eof())
		{
			break;
		}
		if(r==obj.retRollNo())
		{
			if(!found)
				cout<<"\nSearch Results : \n\n";
				
			obj.putDetails();
			RULE('-');
			found = 1;
		}
	}
	if(!found)
		cout<<"No Records Found !\n";
	fl.close();
	return found;
}

/*================================================================================*/

int main()
{
    int a=1,w;
    ifstream file1;
    ofstream file2;
    Grade g1;
        
    char ch;
	char ch1;
	int ch2;
//	load();
	do{
		CLS();
		RULE("*");
		cout <<"\t\t\tSTUDENT INFORMATION SECTION";
		RULE("*");
		cout<<"\t1. Admission Details.\n";
		cout<<"\t2. Grading System.\n";
		cout<<"\t0. Exit.\n\n";
		cout<<"Enter your choice : ";
		fflush(stdin);
		cin>>ch1;
		if(ch1=='1')
		{
			fflush(stdin);
//			load();
            do
			{
                CLS();
                RULE("*");
                cout <<"\t\t\tSTUDENT INFORMATION SECTION";
                RULE("*");
                cout<<"\t\t\t     ADMISSION DETAILS";
                RULE('-');

                cout<<"\t1.  Register Student\n";
                cout<<"\t2.  Display all Records.\n";
                cout<<"\t3.  Search for a Record\n";                                      
                cout<<"\t4.  Delete a Record.\n";
                cout<<"\t0.  Exit.\n";
                cout<<"\nEnter your choice : ";
						
                cin>>ch2;
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
//			load();
            do
			{
                CLS();
                RULE("*");
                cout <<"\t\t\tSTUDENT INFORMATION SECTION";
                RULE("*");
                cout<<"\t\t\t    	GRADING SYSTEM";
                RULE('-');

                cout<<"\t1.  Upload Grades\n";
	            cout<<"\t2.  View All Grades\n";
	            cout<<"\t3.  Search Grades By Roll Number\n";
	            cout<<"\t0.  Exit.\n";
                cout<<"\nEnter your choice : ";
						
                cin>>w;
                switch(w)
                {
                    case 1:
                        insertGrade();
                        break;
                    case 2:
                        dispGrade();
                        break;
                    case 3:
                        searchGradeByRollNo(2);
                        break;                    
                }                    
	                fflush(stdin);
	                if(w)
	                    cin>>ch;
	                else
	                    load();
           	}while(w!=0);			     
		}

    }while(ch1!='0');
	CLS();
	return 0;
}
