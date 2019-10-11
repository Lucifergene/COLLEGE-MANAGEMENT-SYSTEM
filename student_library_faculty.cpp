#include<bits/stdc++.h>
#include<fstream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<conio.h>
#include<limits.h>
#include "header.h"
#define FLBSTUD "student.txt"
#define FLBGRAD "grade.txt"
using namespace std;
fstream fil;



/*================================================================================*/
/* STUDENT SECTION ------->> AVIK */
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
	CLS();
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
	CLS();
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
	CLS();
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
{		
	CLS();
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
	CLS();
	Student obj;					//Writes to new file except record to be deleted
	int f=0;
	cout<<"\nEnter Roll No. to delete : ";
	int r;
	char ch;
	cin>>r;
	fstream fl(FLBSTUD, ios::in|ios::binary);
	fstream fo("temp.dat", ios::out|ios::binary);
	while(!fl.eof())
	{
		fl.read((char*)&obj, sizeof(obj));
		
		if(fl.eof())
			break;
			
		if (r==obj.retRollNo())
		{
			cout<<"Record with following info will be deleted :\n\n";
			obj.printDetails();
			cout<<"Do you wish to continue ? (Y/N) : ";
			do{
				cin>>ch;
				ch = toupper(ch);
			}while(ch!='N' && ch!='Y');
			
			if(ch=='N')
			{
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
//GRADING SYSTEM ------------->>SHIVAM 

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
//PLACEMENT CELL ------->>DIBYAJYOTI

// Students details class.
class Students
  {
	long roll;
	float cgpa;
	char sname[25];
public:
	void getSData();
	long sroll();
	float scgpa();
	char* ssname();
  };


  void Students::getSData()
    {

    cout<<"Enter the Students name \n";
    cin>>sname;
    cout<<"Enter the Students roll number \n";
    cin>>roll;
    cout<<"Enter the cgpa \n";
    cin>>cgpa;

    }
    long Students ::sroll()
    {
      return roll;
    }

    float Students :: scgpa()
    {
      return cgpa;
    }

    char* Students :: ssname()
    {
      return sname;
    }

  // class company details
class company
   {
	   char name[20];
	   int package;
	   float cgpa;
	public:
	   void getCData();
	   friend class Students;
	   char* cname();
	   int cpackage();
	   float ccgpa();
   };

	void company :: getCData()
	{
		 cout<<"Enter the company name \n";
		 cin>>name;
		 cout<<"Enter the package (in lakhs)\n";
		 cin>>package;
		 cout<<"CGPA required"<<endl;
		 cin>>cgpa;
	}

	char* company ::  cname()
	{
		return name;
	}

	int company:: cpackage()
	{
	  	return package;
	}
    float company::ccgpa()
    {
      	return cgpa;
    }

 // Students qualified for placement
class placement
	{
		char *name;
		char *cname;
		long rollnumber;
	public:
		void putPlacementData(char *Name,char *Cname,long Rollnumber);
		void getData();
	};

	 void placement :: putPlacementData(char *Name,char *Cname,long Rollnumber)
	   {
	       name=Name;
	       cname=Cname;
	       rollnumber=Rollnumber;
	   }

	   void placement :: getData()
	   {
	    cout<<"DETAILS";
	    RULE('-');
	    cout<<"\nName: "<<name<<endl;
	    cout<<"Roll Number: "<<rollnumber<<endl;
	   }

    // Students placed class

    class splaced
    {
      char name[25];
      char cname[20];
      int package;
      long rollnumber;
    public:
        void getpData();
        void putpData();
    };

    void splaced:: getpData()
    {

    }
    void splaced:: putpData()
    {

    }
    
/*================================================================================*/
// LIBRARY MANAGEMENT UNDER UNIVERSITY MANAGEMENT SYSTEM ------------->>Vaibhav

class Library
{
public:
	char book[100], author[100], publication[100], id[20];
	float price;
	int quantity;
	void getData();
	void showData();
	void mainMenu();
	void student();
	void staff();
	int booksCategory(int);
	void modifyBooklist();
	void addBooks();
	void viewBooks(int);
	void removeBook();
	void searchBook(int);
	void issueBook();
	void returnBook();
};

//function to get details of book
void Library::getData()
{
	cin.ignore();
	cout << "\t\t\t\t\t********** ENTER BOOK DETAILS **********";
	cout << "\n\n\n\t\t\tEnter Book's Name: ";
	cin.getline(book, 100);
	cout << "\n\t\t\tEnter Author's Name: ";
	cin.getline(author, 100);
	cout << "\n\t\t\tEnter Publication Name: ";
	cin.getline(publication, 100);
	cout << "\n\t\t\tEnter Book's ID: ";
	cin >> id;
	cout << "\n\t\t\tEnter Book's Price: ";
	cin >> price;
	cout << "\n\t\t\tEnter Book's Quantity: ";
	cin >> quantity;
}

//function to display details of book(s)
void Library::showData()
{
	cout << "\n\t\tName of the book: " << book;
	cout << "\n\n\t\tAuthor's name: " << author;
	cout << "\n\n\t\tPublication's name: " << publication;
	cout << "\n\n\t\tBook's ID: " << id;
	cout << "\n\n\t\tPrice of the book: " << price;
	cout << "\n\n\t\tNumber of books available: " << quantity << endl << endl;
}

//function to display the main menu
void Library::mainMenu()
{
	int choice;
	char ch;

	do {
	fflush(stdin);
	CLS();
	cout << "\t\t\t\t\t********** LIBRARY DETAILS **********\n\n";
	cout << "\t\t\t\t\t>> Choose any option\n\n";
	cout << "\t\t\t\t\t1. Student\n\n" << 
	"\t\t\t\t\t2. Staff\n\n" <<
	 "\t\t\t\t\t0. Back To Main\n\n";
	cout << "\t\t\t\t\tEnter choice: ";
	cin >> choice;
	cout << endl << endl;
	switch (choice)
	{
		case 1:
			student();
			break;
		case 2:
			staff();
			break;
	}	
		fflush(stdin);
	    if(choice)
	        cin>>ch;
	    else
	        load();
	}while(choice!= 0);
}

//function to display options for staff
void Library::staff()
{
	CLS();
	cout << "\t\t\t\t\t********** WELCOME STAFF **********\n\n";
	cout << "\t\t\t\t\t>> Choose any option\n\n";
	cout << "\t\t\t\t\t1. View Category of Books\n\n" << "\t\t\t\t\t2. Search for a Book\n\n" << "\t\t\t\t\t3. Modify Booklist\n\n" << "\t\t\t\t\t4. Go to Main Menu\n\n" << "\t\t\t\t\t5. Exit Application\n\n";
	cout << "\t\t\t\t\tEnter choice: ";
	int choice;
	cin >> choice;
	cout << endl << endl;
	switch (choice)
	{
	case 1:
		viewBooks(2);
		break;
	case 2:
		searchBook(2);
		break;
	case 3:
		modifyBooklist();
		break;
	case 4:
		CLS();
		mainMenu();
		break;
	case 5:
		exit(0);
	default:
		cout << "\t\t\t\t\tInvalid choice.\n\n";
		cout << "\t\t\t\t\tPress any key to be able to enter a valid choice\n\n";
		(void)_getch();
		CLS();
		staff();
	}
}

//function to display options for students
void Library::student()
{
	CLS();
	cout << "\t\t\t\t\t********** WELCOME STUDENT **********\n\n";
	cout << "\t\t\t\t\t>> Choose any option\n\n";
	cout << "\t\t\t\t\t1. View Category of Books\n\n" << "\t\t\t\t\t2. Search for a Book\n\n" << "\t\t\t\t\t3. Go to Main Menu\n\n" << "\t\t\t\t\t4. Exit Application\n\n";
	cout << "\t\t\t\t\tEnter choice: ";
	int choice;
	cin >> choice;
	cout << endl << endl;
	switch (choice)
	{
	case 1:
		viewBooks(1);
		break;
	case 2:
		searchBook(1);
		break;
	case 3:
		CLS();
		mainMenu();
		break;
	case 4:
		exit(0);
	default:
		cout << "\t\t\t\t\tInvalid choice.\n\n";
		cout << "\t\t\t\t\tPress any key to be able to enter a valid choice\n\n";
		(void)_getch();
		CLS();
		student();
	}
}

//function to display a list of category of books available in the library
int Library::booksCategory(int flag)
{
	CLS();
	cout << "\t\t\t\t\t********** CATEGORY OF BOOKS **********\n\n";
	cout << "\t\t\t\t\t>> Select a Category\n\n";
	cout << "\t\t\t\t\t1. School of Computer Engineering\n\n" << "\t\t\t\t\t2. School of Electronics Engineering\n\n" << "\t\t\t\t\t3. School of Electrical Engineering\n\n" << "\t\t\t\t\t4. School of Mechanical Engineering\n\n" << "\t\t\t\t\t5. School of Civil Engineering\n\n" << "\t\t\t\t\t6. First Year\n\n" << "\t\t\t\t\t7. Go Back\n\n" << "\t\t\t\t\t8. Go to Main Menu\n\n";
	cout << "\t\t\t\t\tEnter choice: ";
	int choice;
	cin >> choice;
	cout << endl << endl;
	switch (choice)
	{
	case 1:
		return 1;
		break;
	case 2:
		return 2;
	case 3:
		return 3;
	case 4:
		return 4;
	case 5:
		return 5;
	case 6:
		return 6;
	case 7:
		CLS();
		if (flag == 1)
			student();
		else
			staff();
		break;
	case 8:
		CLS();
		mainMenu();
		break;
	default:
		cout << "\t\t\t\t\tInvalid choice.\n\n";
		cout << "\t\t\t\t\tPress any key to be able to enter a valid choice\n\n";
		(void)_getch();
		CLS();
		booksCategory(flag);
	}
}

//function to modify list of books
void Library::modifyBooklist()
{
	CLS();
	cout << "\t\t\t\t\t********** BOOKLIST MODIFICATION **********\n\n";
	cout << "\t\t\t\t\t>> Choose any option\n\n";
	cout << "\t\t\t\t\t1. Add Books\n\n" << "\t\t\t\t\t2. Remove Books\n\n" << "\t\t\t\t\t3. Issue Book\n\n" << "\t\t\t\t\t4. Return Book\n\n" << "\t\t\t\t\t5. Go Back\n\n";
	cout << "\t\t\t\t\tEnter choice: ";
	int choice;
	cin >> choice;
	cout << endl << endl;
	switch (choice)
	{
	case 1:
		addBooks();
		break;
	case 2:
		removeBook();
		break;
	case 3:
		issueBook();
		break;
	case 4:
		returnBook();
		break;
	case 5:
		CLS();
		staff();
		break;
	default:
		cout << "\t\t\t\t\tInvalid choice.\n\n";
		cout << "\t\t\t\t\tPress any key to be able to enter a valid choice\n\n";
		(void)_getch();
		CLS();
		modifyBooklist();
	}
}

//function to add books
void Library::addBooks()
{
	CLS();
	int aCategory = booksCategory(2);
	CLS();
	getData();
	if (aCategory == 1)
	{
		ofstream fout("csBooks.txt", ios::app);
		fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
		fout.close();
	}
	if (aCategory == 2)
	{
		ofstream fout("eceBooks.txt", ios::app);
		fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
		fout.close();
	}
	if (aCategory == 3)
	{
		ofstream fout("elecBooks.txt", ios::app);
		fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
		fout.close();
	}
	if (aCategory == 4)
	{
		ofstream fout("mechBooks.txt", ios::app);
		fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
		fout.close();
	}
	if (aCategory == 5)
	{
		ofstream fout("civilBooks.txt", ios::app);
		fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
		fout.close();
	}
	if (aCategory == 6)
	{
		ofstream fout("yearOneBooks.txt", ios::app);
		fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
		fout.close();
	}
	cout << "\n\n\t\t\tBook Added Successfully.";
	cout << "\n\n\t\t\tPress any key to continue";
	(void)_getch();
	modifyBooklist();
}

//function to view list of books
void Library::viewBooks(int flag)
{
	int serial_num = 0;
	CLS();
	int vCategory = booksCategory(flag);
	CLS();
	if (vCategory == 1)
	{
		ifstream fin("csBooks.txt", ios::in);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\t\t\t\t\t********** LIST OF BOOKS **********\n\n";
			fin.getline(book, 100);
			fin.getline(author, 100);
			fin.getline(publication, 100);
			fin >> id >> price >> quantity;
			while (1)
			{
				if (book[0] == '\0')
				{
					cout << "\n\n\t\t\t\t\t\tNO BOOK AVAILABLE";
					break;
				}
				serial_num++;
				cout << "\n\t\t\t##### " << serial_num << " #####\n";
				showData();
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
			}
		}
		fin.close();
	}
	if (vCategory == 2)
	{
		ifstream fin("eceBooks.txt", ios::in);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\t\t\t\t\t********** LIST OF BOOKS **********\n\n";
			fin.getline(book, 100);
			fin.getline(author, 100);
			fin.getline(publication, 100);
			fin >> id >> price >> quantity;
			while (1)
			{
				if (book[0] == '\0')
				{
					cout << "\n\n\t\t\t\t\t\tNO BOOK AVAILABLE";
					break;
				}
				serial_num++;
				cout << "\n\t\t\t##### " << serial_num << " #####\n";
				showData();
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
			}
		}
		fin.close();
	}
	if (vCategory == 3)
	{
		ifstream fin("elecBooks.txt", ios::in);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\t\t\t\t\t********** LIST OF BOOKS **********\n\n";
			fin.getline(book, 100);
			fin.getline(author, 100);
			fin.getline(publication, 100);
			fin >> id >> price >> quantity;
			while (1)
			{
				if (book[0] == '\0')
				{
					cout << "\n\n\t\t\t\t\t\tNO BOOK AVAILABLE";
					break;
				}
				serial_num++;
				cout << "\n\t\t\t##### " << serial_num << " #####\n";
				showData();
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
			}
		}
		fin.close();
	}
	if (vCategory == 4)
	{
		ifstream fin("mechBooks.txt", ios::in);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\t\t\t\t\t********** LIST OF BOOKS **********\n\n";
			fin.getline(book, 100);
			fin.getline(author, 100);
			fin.getline(publication, 100);
			fin >> id >> price >> quantity;
			while (1)
			{
				if (book[0] == '\0')
				{
					cout << "\n\n\t\t\t\t\t\tNO BOOK AVAILABLE";
					break;
				}
				serial_num++;
				cout << "\n\t\t\t##### " << serial_num << " #####\n";
				showData();
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
			}
		}
		fin.close();
	}
	if (vCategory == 5)
	{
		ifstream fin("civilBooks.txt", ios::in);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\t\t\t\t\t********** LIST OF BOOKS **********\n\n";
			fin.getline(book, 100);
			fin.getline(author, 100);
			fin.getline(publication, 100);
			fin >> id >> price >> quantity;
			while (1)
			{
				if (book[0] == '\0')
				{
					cout << "\n\n\t\t\t\t\t\tNO BOOK AVAILABLE";
					break;
				}
				serial_num++;
				cout << "\n\t\t\t##### " << serial_num << " #####\n";
				showData();
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
			}
		}
		fin.close();
	}
	if (vCategory == 6)
	{
		ifstream fin("yearOneBooks.txt", ios::in);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\t\t\t\t\t********** LIST OF BOOKS **********\n\n";
			fin.getline(book, 100);
			fin.getline(author, 100);
			fin.getline(publication, 100);
			fin >> id >> price >> quantity;
			while (1)
			{
				if (book[0] == '\0')
				{
					cout << "\n\n\t\t\t\t\t\tNO BOOK AVAILABLE";
					break;
				}
				serial_num++;
				cout << "\n\t\t\t##### " << serial_num << " #####\n";
				showData();
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
			}
		}
		fin.close();
	}
	cout << "\n\n\n\t\tPress any key to continue";
	(void)_getch();
	CLS();
	if (flag == 1)
		student();
	else
		staff();
}

//function to remove books
void Library::removeBook()
{
	CLS();
	int rCategory = booksCategory(2);
	CLS();
	int result = INT_MIN;
	char delBook[100];
	if (rCategory == 1)
	{
		ifstream fin("csBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\n\t\t\tEnter Books's Name: ";
			cin.ignore();
			cin.getline(delBook, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(delBook, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
			}
		}
		fout.close();
		fin.close();
		remove("csBooks.txt");
		result = rename("tempFile.txt", "csBooks.txt");
	}
	if (rCategory == 2)
	{
		ifstream fin("eceBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\n\t\t\tEnter Books's Name: ";
			cin.ignore();
			cin.getline(delBook, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(delBook, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
			}
		}
		fout.close();
		fin.close();
		remove("eceBooks.txt");
		result = rename("tempFile.txt", "eceBooks.txt");
	}
	if (rCategory == 3)
	{
		ifstream fin("elecBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\n\t\t\tEnter Books's Name: ";
			cin.ignore();
			cin.getline(delBook, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(delBook, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
			}
		}
		fout.close();
		fin.close();
		remove("elecBooks.txt");
		result = rename("tempFile.txt", "elecBooks.txt");
	}
	if (rCategory == 4)
	{
		ifstream fin("mechBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\n\t\t\tEnter Books's Name: ";
			cin.ignore();
			cin.getline(delBook, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(delBook, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
			}
		}
		fout.close();
		fin.close();
		remove("mechBooks.txt");
		result = rename("tempFile.txt", "mechBooks.txt");
	}
	if (rCategory == 5)
	{
		ifstream fin("civilBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\n\t\t\tEnter Books's Name: ";
			cin.ignore();
			cin.getline(delBook, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(delBook, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
			}
		}
		fout.close();
		fin.close();
		remove("civilBooks.txt");
		result = rename("tempFile.txt", "civilBooks.txt");
	}
	if (rCategory == 6)
	{
		ifstream fin("yearOneBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\n\t\t\tEnter Books's Name: ";
			cin.ignore();
			cin.getline(delBook, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(delBook, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
			}
		}
		fout.close();
		fin.close();
		remove("yearOneBooks.txt");
		result = rename("tempFile.txt", "yearOneBooks.txt");
	}
	if (result == 0)
		cout << "\n\n\t\t\tBook Deleted Successfully.";
	cout << "\n\n\t\t\tPress any key to continue";
	(void)_getch();
	modifyBooklist();
}

//function to search books
void Library::searchBook(int flag)
{
	CLS();
	int sCategory = booksCategory(2);
	CLS();
	int choice;
	char bookName[100], bookID[20];
	int var = 1;
	cout << "\t\t\t\t\t********** SEARCH BOOK **********\n\n";
	cout << "\t\t\t\t\t>> Choose any option\n\n";
	cout << "\t\t\t\t\t1. Search by name\n\n" << "\t\t\t\t\t2. Search by ID\n\n" << "\t\t\t\t\t3. Go Back\n\n";
	cout << "\t\t\t\t\tEnter choice: ";
	cin >> choice;
	cout << endl << endl;
	switch (choice)
	{
	case 1:
		CLS();
		if (sCategory == 1)
		{
			ifstream fin("csBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's Name: ";
				cin.ignore();
				cin.getline(bookName, 100);
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookName, book) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 2)
		{
			ifstream fin("eceBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's Name: ";
				cin.ignore();
				cin.getline(bookName, 100);
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookName, book) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 3)
		{
			ifstream fin("elecBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's Name: ";
				cin.ignore();
				cin.getline(bookName, 100);
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookName, book) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 4)
		{
			ifstream fin("mechBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's Name: ";
				cin.ignore();
				cin.getline(bookName, 100);
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookName, book) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 5)
		{
			ifstream fin("civilBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's Name: ";
				cin.ignore();
				cin.getline(bookName, 100);
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookName, book) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 6)
		{
			ifstream fin("yearOneBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's Name: ";
				cin.ignore();
				cin.getline(bookName, 100);
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookName, book) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		break;
	case 2:
		CLS();
		if (sCategory == 1)
		{
			ifstream fin("csBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's ID: ";
				cin.ignore();
				cin >> bookID;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookID, id) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 2)
		{
			ifstream fin("eceBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's ID: ";
				cin.ignore();
				cin >> bookID;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookID, id) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 3)
		{
			ifstream fin("elecBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's ID: ";
				cin.ignore();
				cin >> bookID;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookID, id) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 4)
		{
			ifstream fin("mechBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's ID: ";
				cin.ignore();
				cin >> bookID;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookID, id) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 5)
		{
			ifstream fin("civilBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's ID: ";
				cin.ignore();
				cin >> bookID;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookID, id) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 6)
		{
			ifstream fin("yearOneBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's ID: ";
				cin.ignore();
				cin >> bookID;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookID, id) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		break;
	case 3:
		CLS();
		if (flag == 1)
			student();
		else
			staff();
		break;
	default:
		cout << "\n\t\t\t\t\tInvalid choice.\n\n";
		cout << "\n\n\t\t\t\t\tPress any key to be able to enter a valid choice\n\n";
		(void)_getch();
		CLS();
		searchBook(flag);
	}
}

//function to issue books
void Library::issueBook()
{
	CLS();
	int iCategory = booksCategory(2);
	CLS();
	char bookName[100];
	int result = INT_MIN;
	if (iCategory == 1)
	{
		ifstream fin("csBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity - 1;
			}
		}
		fout.close();
		fin.close();
		remove("csBooks.txt");
		result = rename("tempFile.txt", "csbooks.txt");
	}
	if (iCategory == 2)
	{
		ifstream fin("eceBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity - 1;
			}
		}
		fout.close();
		fin.close();
		remove("eceBooks.txt");
		result = rename("tempFile.txt", "ecebooks.txt");
	}
	if (iCategory == 3)
	{
		ifstream fin("elecBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity - 1;
			}
		}
		fout.close();
		fin.close();
		remove("elecBooks.txt");
		result = rename("tempFile.txt", "elecbooks.txt");
	}
	if (iCategory == 4)
	{
		ifstream fin("mechBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity - 1;
			}
		}
		fout.close();
		fin.close();
		remove("mechBooks.txt");
		result = rename("tempFile.txt", "mechbooks.txt");
	}
	if (iCategory == 5)
	{
		ifstream fin("civilBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity - 1;
			}
		}
		fout.close();
		fin.close();
		remove("civilBooks.txt");
		result = rename("tempFile.txt", "civilbooks.txt");
	}
	if (iCategory == 6)
	{
		ifstream fin("yearOneBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity - 1;
			}
		}
		fout.close();
		fin.close();
		remove("yearOneBooks.txt");
		result = rename("tempFile.txt", "yearOnebooks.txt");
	}
	if (result == 0)
		cout << "\n\n\t\t\tBook Issued Successfully.";
	cout << "\n\n\t\t\tPress any key to continue";
	(void)_getch();
	modifyBooklist();
}

//funtion to return book
void Library::returnBook()
{
	CLS();
	int rtCategory = booksCategory(2);
	CLS();
	char bookName[100];
	int result = INT_MIN;
	if (rtCategory == 1)
	{
		ifstream fin("csBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity + 1;
			}
		}
		fout.close();
		fin.close();
		remove("csBooks.txt");
		result = rename("tempFile.txt", "csbooks.txt");
	}
	if (rtCategory == 2)
	{
		ifstream fin("eceBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity + 1;
			}
		}
		fout.close();
		fin.close();
		remove("eceBooks.txt");
		result = rename("tempFile.txt", "ecebooks.txt");
	}
	if (rtCategory == 3)
	{
		ifstream fin("elecBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity + 1;
			}
		}
		fout.close();
		fin.close();
		remove("elecBooks.txt");
		result = rename("tempFile.txt", "elecbooks.txt");
	}
	if (rtCategory == 4)
	{
		ifstream fin("mechBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity + 1;
			}
		}
		fout.close();
		fin.close();
		remove("mechBooks.txt");
		result = rename("tempFile.txt", "mechbooks.txt");
	}
	if (rtCategory == 5)
	{
		ifstream fin("civilBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity + 1;
			}
		}
		fout.close();
		fin.close();
		remove("civilBooks.txt");
		result = rename("tempFile.txt", "civilbooks.txt");
	}
	if (rtCategory == 6)
	{
		ifstream fin("yearOneBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity + 1;
			}
		}
		fout.close();
		fin.close();
		remove("yearOneBooks.txt");
		result = rename("tempFile.txt", "yearOnebooks.txt");
	}
	if (result == 0)
		cout << "\n\n\t\t\tBook Return Success.";
	cout << "\n\n\t\t\tPress any key to continue";
	(void)_getch();
	modifyBooklist();
}    

/*================================================================================*/
//FACULTY MANAGEMENT ----> SWARNAVA   
class teacher
{
    int a;
    int phone;
    string name;
    string section[10];
    string subject;

 public:

    void input()
    {
        cout<<"\n\t\t\t\t\t Enter teacher name:";
        cin.ignore();
        getline(cin,name);
        cout<<"\n\t\t\t\t\tEnter subject : ";
        getline(cin,subject);
        cout<<"\n\t\t\t\t\tenter the phone number: ";
        cin>>phone;
        while(1)
        {
            cout<<"\n\t\t\t\t\tenter the number of section taught ";
            cin>>a;
            if(a<=0)
                cout<<"\n\t\t\t\t\tsections taught cannot be less than or equal to zero\n";
            else
                break;
        }
        cout<<"\n\t\t\t\t\tthe section(s) (press enter after giving each section name):";
        cin.ignore();
        for(int i=0;i<a;i++)
            cin>>section[i];
    }
    void show()
    {
        cout<<"\n\t\t\t\t\tTeacher name: "<<name<<"\n";
        cout<<"\n\t\t\t\t\tEnter subject : "<<subject<<"\n";
        cout<<"\n\t\t\t\t\tenter the phone number: "<<phone<<"\n";
        cout<<"\n\t\t\t\t\tthe sections taught :\n";
        for(int i=0;i<a;i++)
            cout<<"\n\t\t\t\t\t"<<section[i]<<"\n";
    }

    int getph()
    {
        return phone;
    }
    int geta()
    {
        return a;
    }
    string getnm()
    {
        return name;
    }
    string getsub()
    {
        return subject;
    }
    string getsec(int x)
    {
        return section[x];
    }
} t;

void Create();
void Add();
void Display();
void Delete();
void sbn();
void sbs();
void sbsec();



void Create()
{
    system("CLS");
    char ch='y';
    fil.open("teacher.dat",ios::out| ios::binary);
    while(ch=='y' || ch =='Y')
    {
        t.input();
        fil.write((char*)&t, sizeof(t));
        cout<<"\n\t\t\t\t\tWant to Continue (Y/N):";
        cin>>ch;
    }
    fil.close();
}

void Add()              //Function to Add New Record in Data File
{
    system("CLS");
    char ch='y';
    fil.open("teacher.dat",ios::app| ios::binary);
    while(ch=='y' || ch =='Y')
    {
        t.input();
        fil.write((char*)&t, sizeof(t));
        cout<<"\n\t\t\t\t\tWant to Continue (Y/N):";
        cin>>ch;
    }
    fil.close();
}

void Display() //Function to Display All Record from Data File
{
    system("CLS");
    fil.open("teacher.dat",ios::in| ios::binary);
    if(!fil)
    {
        cout<<"\n\t\t\t\t\tFile not created\n";
        exit(0);
    }
    fil.read((char*)&t, sizeof(t));
    if(fil.eof())
    {
        cout<<"\n\t\t\t\t\tNo records present.\n";
        return;
    }
    else
    {
        cout<<"\n\t\t\t\t\t\tShowing Record(s)\n";
        while(!fil.eof())
        {
            t.show();
            fil.read((char*)&t, sizeof(t));
        }
    }
    fil.close();
}
void sbn()//function which searches record using name of faculty
{
    system("CLS");
    fil.open("teacher.dat",ios::in| ios::binary);
    if(!fil)
    {
        cout<<"\n\t\t\t\t\tFile not created\n";
        exit(0);
    }
    fil.read((char*)&t, sizeof(t));
    if(fil.eof())
    {
        cout<<"\n\t\t\t\t\tNo records present.\n";
        return;
    }
    string s;
    cout<<"\n\t\t\t\t\tEnter the name of faculty to be searched : ";
    cin.ignore();
    getline(cin,s);
    while(1)
    {
        if(s==t.getnm())
        {
            cout<<"\n\t\t\t\t\tFaculty found, here are the details :\n";
            t.show();
            return;
        }
        fil.read((char*)&t, sizeof(t));
    }
    cout<<"\n\t\t\t\t\tFaculty does not exist.\n";
}
void sbs()//function which searches record using subject taught by faculty
{
    system("CLS");
    fil.open("teacher.dat",ios::in| ios::binary);
    if(!fil)
    {
        cout<<"\n\t\t\t\t\tFile not created\n";
        exit(0);
    }
    fil.read((char*)&t, sizeof(t));
    if(fil.eof())
    {
        cout<<"\n\t\t\t\t\tNo records present.\n";
        return;
    }
    string s;
    cout<<"\n\t\t\t\t\tEnter the subject to be searched : ";
    cin.ignore();
    getline(cin,s);
    while(1)
    {
        if(s==t.getsub())
        {
            cout<<"\n\t\t\t\t\tFaculty found, here are the details :\n";
            t.show();
            return;
        }
        fil.read((char*)&t, sizeof(t));
    }
    cout<<"\n\t\t\t\t\tFaculty does not exist.\n";
}
void sbsec()//function which searches record using sections taught by faculty
{
    system("CLS");
    fil.open("teacher.dat",ios::in| ios::binary);
    if(!fil)
    {
        cout<<"\n\t\t\t\t\tFile not created\n";
        exit(0);
    }
    fil.read((char*)&t, sizeof(t));
    if(fil.eof())
    {
        cout<<"\n\t\t\t\t\tNo records present.\n";
        return;
    }
    string s;
    cout<<"\n\t\t\t\t\tEnter the section to be searched : ";
    cin.ignore();
    getline(cin,s);
    int i=0;
    while(!fil.eof())
    {
        for(int j=0;j<t.geta();j++)
            if(s==t.getsec(j))
            {
                i++;
                if(i==1)
                    cout<<"\n\t\t\t\t\tFaculty found, here are the details :\n";
                t.show();
                cout<<"\n";
                fil.read((char*)&t, sizeof(t));
                if(!fil.eof())
                    j= -1;
            }
        fil.read((char*)&t, sizeof(t));
    }
    if(i==0)
        cout<<"\n\t\t\t\t\tFaculty does not exist.\n";
}
void Delete() //Function to Delete Particular Record from Data File
{
    system("CLS");
    string srch;
    fstream o;
    o.open("copy.dat",ios::out| ios::binary);
    fil.open("teacher.dat",ios::in| ios::binary);
    if(!fil)
    {
        cout<<"\n\t\t\t\t\tFile not created\n";
        return ;
    }
    cout<<"\n\t\t\t\t\tEnter the name of the teacher whose record is to be deleted :";
    cin.ignore();
    getline(cin,srch);
    fil.read((char*)&t, sizeof(t));
    while(!fil.eof())
    {
        if(srch!=t.getnm())
        {
            o.write((char*)&t, sizeof(t));
            //break;
        }
        fil.read((char*)&t, sizeof(t));
    }
    fil.close();
    o.close();
    remove("teacher.dat");
    rename("copy.dat","teacher.dat");

}

/*================================================================================*/

int main()
{
    int a=1,w;
    ifstream file1;
    ofstream file2;
    Grade g1;
	char ch5;
    char ch;
	char ch1;
	int ch2;
//	load();
	
	do{
		CLS();
		RULE("*");
		cout <<"\t\t\tUNIVERSITY MANAGEMENT SYSTEM";
		RULE("*");
		cout<<"\t1. STUDENT INFORMATION SECTION\n";
		cout<<"\t2. LIBRARY MANAGEMENT SYSTEM\n";
		cout<<"\t3. FACULTY SECTION\n";
		cout<<"\t0. Exit.\n\n";
		cout<<"Enter your choice : ";
		fflush(stdin);
		cin>>ch5;
		if(ch5=='1')
		{
				fflush(stdin);
	//			load();
					do{
						CLS();
						RULE("*");
						cout <<"\t\t\tSTUDENT INFORMATION SECTION";
						RULE("*");
						cout<<"\t1. Admission Details.\n";
						cout<<"\t2. Grading System.\n";
						cout<<"\t3. Placement Cell.\n";
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
							load();
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
					// Dibya's Code for Main Function
						if(ch1=='3')
						{
							fflush(stdin);
							load();
							CLS();
				
							RULE("*");
			                cout <<"\t\t\tSTUDENT INFORMATION SECTION";
			                RULE("*");
			                cout<<"\t\t\t    	PLACEMENT CELL";
			                RULE('-');
				
							int n,m;
							cout<<"Enter the number of Students wants to sit in placement: ";
							cin>>n;
							Students s[n];
							cout<<endl;
							RULE('-');
							cout<<" \n\nEnter the Students details:- ";
							RULE('-');
							for(int i=0;i<n;i++)
							{
								s[i].getSData();
							}
				
							cout<<endl<<endl;
							cout<<"\nEnter the number of Companies: ";
							cin>>m;
							company c[m];
							RULE('-');
							cout<<"\n\nEnter the company details: \n";
							RULE('-');
							for(int i=0;i<m;i++)
							{
								c[i].getCData();
							}
				
							placement p[m];
							int count =0;
							int scount[m];
				
							for (int i = 0; i < m; ++i)
							{
								for(int j=0;j<n;j++)
								{
									if(c[i].ccgpa()>=s[j].scgpa())
									{
										count++;
										p[i].putPlacementData(s[j].ssname(),c[i].cname(),s[j].sroll());
				
									}
								}
								scount[i]=count;
							}
				
				
				//			for(int j=0;j<m;j++)
				//			{
				//				cout<<"COMPANY NAME:  "<<c[j].cname();
				//				for(int i=0;i<scount[j];i++)
				//				{
				//					p[i].getData();
				//				}
				//			}
						}
				    }while(ch1!='0');			
			}
			
			if(ch5=='2')
			{	
				fflush(stdin);
				load();
				CLS();
				Library lib;
				lib.mainMenu();
			}	
			
			if(ch5=='3')
			{	
				int opt;
				fflush(stdin);
				load();
	            do{				
					CLS();
					cout<<"\n\t\t\t\t\t* * * * * * FACULTY SECTION * * * * * *\n"<<endl;
			        cout<<"\n\t\t\t\t\t1. Create Data File"<<endl;
			        cout<<"\n\t\t\t\t\t2. Add New Record in Data File"<<endl;
			        cout<<"\n\t\t\t\t\t3. Display Record From Data File"<<endl;
			        cout<<"\n\t\t\t\t\t4. Delete Particular Record From Data File"<<endl;
			        cout<<"\n\t\t\t\t\t5. Search by name"<<endl;
			        cout<<"\n\t\t\t\t\t6. Search by subject taught"<<endl;
			        cout<<"\n\t\t\t\t\t7. Search by section taught"<<endl;
			        cout<<"\n\t\t\t\t\t8. Exit From the Program"<<endl;
			        cout<<"\n\t\t\t\t\t0. Back To Main Menu"<<endl;
			        cout<<"\n\t\t\t\t\tEnter your choice : ";
			        cin>>opt;
			        switch(opt)
			        {
			            case 1:
			                Create();
			                break;
			            case 2:
			                Add();
			                break;
			            case 3:
			                Display();
			                break;
			            case 4:
			                Delete();
			                break;
			            case 5:
			                sbn();
			                break;
			            case 6:
			                sbs();
			                break;
			            case 7:
			                sbsec();
			                break;
			            case 8:
			            	CLS();
			                exit(0);
			        }
			        fflush(stdin);
		                if(opt)
		                    cin>>ch;
		                else
		                    load();
    			}while(opt!=0);	
			}	
	}while(ch5!='0');
	CLS();
	return 0;
}
