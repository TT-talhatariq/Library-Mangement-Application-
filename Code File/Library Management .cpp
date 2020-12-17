#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>													//Libraries for different Particulars Tasks
#include<conio.h>
#include<cstring>
#include<Windows.h>
using namespace std;

#define Arrow() ("--->")			   //Defined a Pre_Processor for Mostly Usage in this Project for Formatting Output
#define Tab()("\t\t\t\t\t\t\t")		  //Used For Formatting

void main_text();					//main Header of Library
void input_test(int &input);	   //it test if string input instead of int then it clear cin error state & prevent programe from crashing
void books_section(int &a);		  //It asks for Book's Section choice		
HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);	//Used for Better Font
void fontsize(int a, int b);


/* Date Section which will be used in further classes via Aggregation*/
class Date {
private:
	int day, month, year;
public:
	Date(); 							 //default Constructor that assign all values to 0 
	Date(int, int, int);                //Constructor with Parameters
	Date(const Date& copy);			   //Copy_Constrcutor
	void get_date();				  //Funtion for Getting all Data			
	int put_day();			         //Accessor for Accessing private member day 
	int put_month();			    //Accessor for Accessing Private member month
	int put_year();				   //Accessor for Accessing Private member year
	void set_day(int a);		  //Mutator for setting Day of Date
	void set_month(int b);		 //Mutator for setting Month of Date
	void set_year(int c);		//Mutator for setting Year of Date
};

//Date Constructor for intitilize to defualt 
Date::Date() {
	day = 0;
	month = 0;
	year = 0;
}
//Constructor for User's Values
Date::Date(int a, int b, int c) {
	day = a;
	month = b;
	year = c;
}
Date::Date(const Date& copy) {
	day = copy.day;
	month = copy.month;														 //Copy Constructor
	year = copy.year;
}																			
void Date::get_date() {
	while (1) {
		cout << endl << Tab() << "Enter Day: ";
		cin >> day;
		input_test(day);
		if (day > 31 || day < 1) {
			cout << Tab() << "Day is wrong. It should be between 1 to 31. Try again please\n";
			continue;
		}
		else break;
	}
	while (1) {
		cout << Tab() << "Enter Month: ";
		cin >> month;
		input_test(month);
		if (month > 12 || month < 1) {
			cout << Tab() << "Month is wrong. It should be between 1 to 12. Try again please\n";
			continue;
		}
		else break;
	}
	cout << Tab() << "Enter Year: ";
	cin >> year;
	input_test(year);
}
int Date::put_day() {
	return day;
}
int Date::put_month() {
	return month;
}
int Date::put_year() {
	return year;
}
void Date::set_day(int a) {
	day = a;
}
void Date::set_month(int b) {
	month = b;
}
void Date::set_year(int c) {
	year = c;
}


/*Class Admin Which have several authorities, have private & protected members & many Method for several Tasks.

It will be used as Base class for Inheritance of Class Student.

An Admin has Following Authotities:
	1)Addition, Updation or Deletion of a Book record in Library Stock
	2)Have Acces to all record of Student, Addition, Removal of a Student
	3)Issued, Deposit & Fine Record authorities  
*/

class Admin {
private:									 //Private members for Admin Authorities
	int isbn, quantity;						//Books Quantity and ISBN Number
	string book_name, author;			   //Book Name and Author
	string name;
protected:								  //Protected members of Students for availibility 									
	string student_name, roll_no;	   	 //Student Roll_no & Student Name 
	int validity;                       //Student's Card Validity 
	Date today_date;				   // Date Class via Aggregation

public:
	string put_name();									    //Accessor for Private Member Book_Name 								    
	string put_roll_no();							       //Accessor for Private Member of Roll_No
	void add_book(string txt);                            //Adding New books to Library Stock
	void delte_book(string txt);					     //Deleting an exisiting book from Library Stock
	void check_book(string txt);					    //Searching a Particular Book by ISBN or Book Name
	void all_books(string txt);					       //Checking All books of a Particular Section
	void update_book(string txt);					  //For updating a Particular record of Book
	void issue_book(string txt);					 //Issuing a Book to a Student
	void deposit_book(string txt);			 	    //Disposting a Book from a Member
	void add_member(string txt);			       //Adding a Member to the Domain of Libaray
	void remove_member(string txt);			      //Removing a Libaray Member from Domain after ending Validity
	void fine_record(string txt);				 //Fine Related Queries	
	void check_issued_books_record(string txt); //Checking of Record of Issued Books
	void check_all_members(string txt);		   //Checking all Members of Library
	void check_fine_record(string txt);		  //Checking of Fine Record
};


/*
Class Student which is Derived class & Inherited from Admin class which is Base Class

A Student have Authorities to followoing Task:
	1)Login & Changing His Password
	2)Checking that which Books Are Enrolled to His/Her
	3)Checking all Books or Searching a Particular Book in Library Record
*/
class Student : public Admin {
private:
	string password;									//Private Member Password of a Student
public:
	bool login_user(string txt);					  //Login a Particular User
	void check_enroll_books(string txt);			 //Check Which Books Are Enrolled to You Previously
	void change_password(string txt);				//Changing Previous Old Password
};

//Admin Class Accessor for Student_Name 
string Admin::put_name() {
	return student_name;
}

//Admin Class Accessor for Roll_No
string Admin::put_roll_no() {
	return roll_no;
}

//Addition of a New Member in Library
void Admin::add_member(string txt) {
	//Opening of File in Backend for Adding a Member
	ofstream file;
	file.open(txt.c_str(), ios::app);
	ofstream file2;
	file2.open("Student_Password.txt", ios::app);

	//Asking for Record of Student	
	cout << Tab() << "Enter Roll_No of Student: ";
	cin >> roll_no;
	cin.ignore();
	cout << endl << Tab() << "Enter Name Of Student: ";
	getline(cin, student_name);
	cout << endl << Tab() << "Enter it's issued Card Validity: ";
	cin >> validity;
	input_test(validity);
	file << endl << roll_no << "   " << student_name << endl << validity;		//Adding to File
	file.close();
	file2 << endl << "1234" << endl;
	file2 << roll_no << "  " << student_name;
	cout << endl << endl << Tab() << "Default Password: 1234" << endl;
	file2.close();
}

//Removal of a Member from Library record
void Admin::remove_member(string txt) {
	ifstream file1;
	ofstream file2;
	file1.open(txt.c_str());					//Opening of two Files for deleting & Updating Particular Record
	file2.open("temp.txt");
	//Asking for Student Roll_No for Removal of him/her from Library
	string temp_roll;
	cout << "\n\n\n\nEnter Roll_No of Member for Removing him/her(Note: First Letter should be Capital):  ";
	cin >> temp_roll;

	while (!file1.eof()) {
		file1 >> roll_no;
		getline(file1, student_name);
		file1 >> validity;
		int x = roll_no.compare(temp_roll);
		if (x != 0) {
			file2 << endl << roll_no << " " << student_name << endl << validity;
		}
	}
	file1.close();
	file2.close();

	//Removing Previous Record & Rename file with same name as previous files has with deletion record of Member
	remove(txt.c_str());
	rename("temp.txt", txt.c_str());
}

//Checking all Members of Libaray
void Admin::check_all_members(string txt) {
	ifstream file;
	file.open(txt.c_str());

	cout << endl << "\t\t" << setw(24) <<left << "Roll_Number" << setw(25) <<left << "Student Name" << "Validity" << endl << endl << endl;
	
	while (!file.eof()) {
		file >> roll_no;
		file >> ws;
		getline(file, student_name);
		file >> validity;
		cout << "\t\t" << left << setw(24) << roll_no << left << setw(26) << student_name << left << setw(5) << validity << endl <<  endl;
	}
	file.close();
}

//Checking All Books record
void Admin :: all_books(string txt) {
	ifstream file;
	file.open(txt.c_str());				//Opening a Section of Library

	if (file.is_open()) {
		cout << endl <<  endl  << endl << "      " << setw(15) << left << "ISBN" << setw(35) << left << "Title" << setw(30) << left << "Author Name" << "Available Quanitity" << endl << endl << endl;
		while (!file.eof()) {

			file >> isbn;
			getline(file, book_name);
			getline(file, author);
			file >> quantity;
			cout << "      " << left << setw(10) << isbn << left << setw(40) << book_name << left << setw(35) << author << right << quantity << endl << endl;
		}
	}
	else {
		cout << "Sorry! This Section is not Exist in our Domain.\n Sorry for Inconvinence\n";
	}
}

//Searching aP Paricular Book
void Admin :: check_book(string txt) {
	int ab, option, pos;			  //Extra Variable for usage in Funtion(Local Variables)
	bool error = false;
	string name;

	ifstream file;                  //Opening file in reading mode
	file.open(txt.c_str());
	main_text();
	cout << endl << endl << endl;
	cout << "\t\t\t\t\tSlecet your Option for Searching a Book: \n\n\n";
	cout <<  Tab() << "1" << Arrow() << "By ISBN Number\n\n";
	cout << Tab() << "2" << Arrow() << "By Book Name\n\n";							//Asking for Options from Users that how can he/she want to search
	cout << Tab() << "3" << Arrow() << "By Both of them\n\n";
	cout << endl << endl << Tab() << "Enter Your Option: ";
	while (1) {
		cin >> option;
		input_test(option);
		if (option < 1 || option > 3) {
			cout <<  endl << Tab() << "Invalid Input. Please try Again: ";				//Testor for Valid Input from User
			continue;
		}
		else break;
	}
	system("CLS");
	main_text();
	//Action Based on User Input
	switch (option){
	case 1:											//User want to search by ISBN so asking this to him/her
		cout << endl << endl << endl << endl <<Tab() << "Enter ISBN Number: ";
		cin >> ab;
		input_test(ab);
		break;
	case 2:										//User want to search by Book Name so asking this to him/her
		cout << "\n\n\n\n\n" << "\tEnter Only The Fisrt Word of Book Name";
		cout << "(Note: First Letter should be Capital): ";
		cin >> name;
		break;
	case 3:										//User want to search by ISBN & Books Name both, so asking this to him/her
		cout << endl << endl  << endl << endl << Tab() << "Enter ISBN Number: ";
		cin >> ab;
		input_test(option);
		cout  << "\n\n" << "\tEnter Only The Fisrt Word of Book Name";
		cout << "(Note: First Letter should be Capital) ";
		cin >> name;
		break;
	}
	system("CLS");
	main_text();
	//Searching Book From Record
	if (option == 1) {
		while (!file.eof()) {
			file >> isbn;
			if (isbn == ab) {
				getline(file, book_name);
				getline(file, author);
				file >> quantity;
				cout <<  "\n\n\n\n\n" <<  Tab() << "ISBN: " << isbn << endl << endl << Tab() << "Book Name: " << book_name << endl << endl << Tab() << "Author Name: " << author << endl  << endl << Tab() << "Available Quantity: " << quantity << endl << endl;
				error = true;
				break;
			}
			else {
				file.ignore(100, '\n');
				file.ignore(100, '\n');
				file.ignore(100, '\n');
				continue;
			}
		}
	}
	if (option == 2 || option == 3) {

		while (!file.eof())
		{
			
			file >> isbn;
			pos = file.tellg();
			file >> book_name;
			int x = book_name.compare(name);
			file.seekg(pos, ios::beg);
			getline(file, book_name);
			getline(file, author);
			file >> quantity;
			if (option == 3) {
				if (isbn == ab) {
					cout << "\n\n\t\tMatching Results are by ISBN: \n";
					cout << "\n\n\n\n\n" << Tab() << "ISBN: " << isbn << endl << endl << Tab() << "Book Name: " << book_name << endl << endl << Tab() << "Author Name: " << author << endl << endl << Tab() << "Available Quantity: " << quantity << endl << endl;
					error = true;
					break;
				}
				if (x == 0) {
					cout << "\n\n\t\t\tMatching Results are by Book_name: \n";
					cout <<  "\n\n\n\n\n" << Tab() << "ISBN: " << isbn << endl << endl << Tab() << "Book Name: " << book_name << endl << endl << Tab() << "Author Name: " << author << endl << endl << Tab() << "Available Quantity: " << quantity << endl << endl;
					error = true;
				}

			}
			if (option == 2) {

				if (x == 0) {
					cout <<  "\n\n\n\n\n" << Tab() << "ISBN: " << isbn << endl << endl << Tab() << "Book Name: " << book_name << endl << endl << Tab() << "Author Name: " << author << endl << endl << Tab() << "Available Quantity: " << quantity << endl << endl;
					error = true;
					break;
				}
			}

		}
	}

	//Testor while Book is found or not
	if (!error) {
		cout << "\n\n\n\n\n\n" << "\t\t\t\tSorry! This book is not exist in our Library\n";
	}
}

//Adding a Book to a Special Section
void Admin :: add_book(string txt) {
	ofstream file1;
	file1.open(txt.c_str(), ios::app);
	system("CLS");
	main_text();
	//Asking Admin for Book's Details
	cout << endl << endl << Tab() << "Enter ISBN Number: ";
	cin >> isbn;
	input_test(isbn);
	cout << endl << Tab() << "Enter Qunatity of New Book: ";
	cin >> quantity;
	input_test(quantity);
	cin.ignore();
	cout << endl << Tab() << "Enter Name of Book (Note: Write all first Letter in Capital) ";
	getline(cin, book_name);
	cout << "\n\n\n\t\t\t\tEnter the Name of the Author of this Book (Note: Write all first letter in Capital) ";
	getline(cin, author);

	//Adding this Book to Library Stock
	file1  << endl << isbn << " " << book_name << endl;
	file1 << author << endl;
	file1 << quantity;
	file1.close();
}

//Delete a Book from Library Stock
void Admin :: delte_book(string txt) {
	int option, temporary_isbn;
	ifstream file1;
	file1.open(txt.c_str());
	ofstream file2;
	file2.open("temp_file.txt");
	system("CLS");
	//Asking Admin he/she want to delete by which method
	cout << endl << endl << Tab() << "Want to Delete Book by Which Method ?\n\n\n";
	cout << Tab() << "1)" << Arrow() << " By Inputting ISBN Number\n\n";
	cout << Tab() << "2)" << Arrow() << " By  Checking Record One by One & Deleting Book of Your own Choice\n\n";
	cout << Tab() << "Enter Your Option Please: ";
	cin >> option;
	input_test(option);		//Checking wheter int or not

		while (option > 2 || option < 1) {				//Testor for Valid Input
			cout << endl << Tab() << "Error :: Invalid Input";
			cout << endl << Tab() << "  Enter again please: ";
			cin >> option;
			input_test(option);
		}
		system("CLS");
		main_text();
		if (option == 1) {
			cout << endl << Tab() << "Enter ISBN of Book: ";
			cin >> temporary_isbn;
			input_test(temporary_isbn);
			while (!file1.eof()) {
				file1 >> isbn;
				getline(file1, book_name);
				getline(file1, author);
				file1 >> quantity;
				if (isbn != temporary_isbn) {
					file2 << isbn << " " << book_name << endl << author << endl << quantity << endl;
				}
				else {
					cout << setw(50) << "Deleted Data\n\n";
					cout << Tab() << "ISBN: " << isbn << endl << endl;
					cout << Tab() << "Name : " << book_name << endl << endl;
					cout << Tab() << "Author Name: " << author << endl << endl;
					cout << Tab() << "Available Quantity: " << quantity << endl << endl;
				}
			}
	}
		if (option == 2) {
			system("CLS");
			main_text();
			all_books(txt);
			cout << "\t\t\tNow! Enter ISBN Number of Book Whome you want to remove: ";
			cin >> temporary_isbn;
			input_test(temporary_isbn);
			while (!file1.eof()) {
				file1 >> isbn;
				getline(file1, book_name);
				getline(file1, author);
				file1 >> quantity;
				if (isbn != temporary_isbn) {
					file2 << isbn << " " << book_name << endl << author << endl << quantity << endl;
				}
			}
		}
		file1.close();
		file2.close();
		
		//After Deletion
		const char* permanent_file = txt.c_str();
		remove(permanent_file);
	rename("temp_file.txt", permanent_file);
}

//Update Record of a Particular Book like quantity or ISBN Number
void Admin :: update_book(string txt) {
	ifstream file1;
	file1.open(txt.c_str());
	ofstream file2;
	file2.open("temp_file.txt");
	int option, update_option, temp_isbn;
	
	//Asking User for his/her choice
	main_text();
	cout << endl << endl;
	cout << Tab() << "Want to update by Which Method?\n\n";
	cout <<"\t\t\t\t1)" << Arrow() << " Do You Know ISBN of Book Whose Record you want to update?(If yes press 1) \n";
	cout << endl  << "\t\t\t\t2) " << Arrow() << " Want to Check all Books in Stock? \n";
	cout << endl << "\t\t\t\t3) " << Arrow() << " Want to First Search a Book Record than Update? \n";
	cin >> option;
	input_test(option);
	while (option > 3 || option < 1) {				//Testor for Valid Input
		cout << Tab() << "Error :: Invalid Input\n\n";
		cout << Tab() << "Enter again please: ";
		cin >> option;
		input_test(option);
	}
	system("CLS");
	if (option == 1) {
		cout << "\t\t\t\tEnter the ISBN of Your Book, whose you want to update: ";
		cin >> temp_isbn;
		input_test(temp_isbn);
	}
	if (option == 2) {
		all_books(txt);
		cout << "\t\t\t\tEnter the ISBN of Your Book, whose you want to update: ";
		cin >> temp_isbn;
		input_test(temp_isbn);
	}
	if (option == 3)
	{
		char a = '0';
		do {
			check_book(txt);
			cout << endl <<  Tab() << "want to Search again?(press 1 if yes) ";
			cin >> a;
		}while (a == '1');

		cout << endl << "\t\t\t\tEnter the ISBN of Your Book, whose you want to update: ";
		cin >> temp_isbn;
		input_test(quantity);
		}

	system("CLS");
	//Asking User that what he want to Update 
	cout << endl << Tab() << "Choose You want to update what of the Book? \n\n";
	cout << Tab() << "1) " << Arrow() << " ISBN Number \n\n";
	cout << Tab() << "2) " << Arrow() << " Book Name \n\n";
	cout << Tab() << "3) " << Arrow() << " Author Name \n\n";
	cout << Tab() << "4) " << Arrow() << " Book's Quantity \n\n";
	cout << Tab() << "5) " << Arrow() << " All of these \n\n";
	cin >> update_option;
	input_test(update_option);
	while (update_option > 5 || update_option < 1) {                                 //Testor for Valid Input                                                                         
		cout << Tab() << "Error :: Invalid Input";
		cout << endl << Tab() << "  Enter again please: ";
		cin >> update_option;
		input_test(update_option);
	}

	while (!file1.eof()){
		file1 >> isbn;
		getline(file1, book_name);
		getline(file1, author);
		file1 >> quantity;
		if(temp_isbn != isbn){
			file2 << endl << isbn;
			file2 << book_name << endl;
			file2 << author << endl << quantity;
		}
		else{
			if(update_option == 1) {
				int new_isbn;
				cout << endl << Tab() << "Enter New ISBN of Book: ";
				cin >> new_isbn;
				input_test(new_isbn);
				file2 << endl << new_isbn;
				file2 << book_name << endl;
				file2 << author << endl << quantity;
			}
			else if (update_option == 2) {
				string new_book_name;
				cout << endl << Tab() << "Enter New Name of Book: ";
				getline(cin, new_book_name);
				file2 << endl << isbn;
				file2 << "   "<< new_book_name << endl;
				file2 << author << endl << quantity;
			}
			else if (update_option == 3) {
				string new_author;
				cout << endl << Tab() << "Enter New Author of Book: ";
				getline(cin, new_author);
				file2 << endl << isbn;
				file2 << book_name << endl;
				file2 << new_author << endl << quantity;
			}
			else if (update_option == 4) {
				int new_quantity;
				cout << endl << Tab() << "Enter New Quantity of Book: ";
				cin >> new_quantity;
				input_test(new_quantity);
				file2 << endl <<isbn;
				file2  << book_name << endl;
				file2 << author << endl << new_quantity;
			}
			else {
				int new_isbn;
				string new_book, new_author;
				int new_quantity;
				cout << endl << Tab() << "Enter New ISBN of Book: ";
				cin >> new_isbn;
				input_test(new_isbn);
				cin.ignore();
				cout << endl << Tab() << "Enter New Name of Book: ";
				getline(cin, new_book);
				cout << endl << Tab() << "Enter New Name of Author of Book: ";
				getline(cin, new_author);
				cout << endl << Tab() << "Enter New Quantity of Book: ";
				cin >> new_quantity;
				input_test(new_quantity);
				file2 << endl << new_isbn << "  ";
				file2 << new_book << endl;
				file2 << new_author << endl << new_quantity;
			}
			cout << endl << endl << Tab() << "Successfully Updated\n";
		}
	}
	  	file1.close();
		file2.close();
		remove(txt.c_str());
		rename("temp_file.txt", txt.c_str());
}

//Check Record of Issued Books to Students
void Admin::check_issued_books_record(string txt) {
	ifstream file;
	file.open(txt.c_str());
	cout << endl << endl;
	cout << "        " << left << setw(18) << "  Roll_NO" << left << setw(15) << "ISBN" << left << setw(30) << "Issued Book"  << " Date" << endl << endl << endl;
	while (!file.eof())
	{
		string date;
		file >> isbn;
		file >> ws;
		getline(file, book_name);
		file >> roll_no;
		getline(file, date);
		cout << "        " << left << setw(18) << roll_no << left << setw(15) << isbn << left << setw(30) << book_name  << date << endl << endl;
	}
	file.close();
}

//Issued Book a New Book to Student 
void Admin :: issue_book(string txt) {
	ofstream file;
	char option = '0';

	//Asking User if this student is member of Library? Otherwise Add it first
	cout <<"\t\tIs this student is member of Library?(Press 1 if Yes) ";
	cin >> option;
	if (option != '1') {
		cout << endl << Tab() << "Enter Student Record First Please! \n";
		add_member("Enroll_Student.txt");
	}
	system("CLS");
	file.open(txt.c_str(), ios::app);

	//Details of Issued Book
	cout << endl << Tab() << "Issued Book' Details\n\n";
	cout << Tab() << "ISBN Number of Book: ";
	cin >> isbn;
	input_test(isbn);
	cin.ignore();
	cout << endl << Tab() << "Enter Book Name: ";
	getline(cin, book_name);
	cout << endl << Tab() << "Enter Student Roll_No: ";
	cin >> roll_no;
	cout << endl << Tab() << "Enter Today's Date: ";
	today_date.get_date();
	file << endl << isbn << "   " << book_name << endl << roll_no << " " << today_date.put_day() << "/" << today_date.put_month() << "/" << today_date.put_year();
	file.close();
}

//Deposit a Book which was issued to student previously
void Admin :: deposit_book(string txt) {
	ifstream file1;
	ofstream file2;
	int temp_isbn;
	string date;
	file1.open(txt.c_str());
	file2.open("temp_str.txt");

	cout << endl << endl << Tab() << "Enter Book ISBN: ";
	cin >> temp_isbn;
	input_test(temp_isbn);
	system("CLS");
	main_text();
	while (!file1.eof()) {
		file1 >> isbn;
		file1 >> ws;
		getline(file1, book_name);
		file1 >> roll_no;
		file1 >> date;
		if (temp_isbn == isbn) {
			cout << endl << endl <<setw(50) << "Record\n\n ";
			cout << endl << Tab() << roll_no << endl << endl;
			cout << Tab() << book_name << endl << endl;
			cout << Tab() << date << endl << endl;
			
			//Asking to Admin for Any fine on Student
			cout << "Any Fine on him/her?(Press 1 if Yes) ";
			char a = '0';
			cin >> a;
			if (a == '1') {
				fine_record("Fine_record.txt");
			}
		}
		else {
			file2 << endl << isbn << " " << book_name << endl << roll_no << " " << date;

		}
	}
	file1.close();
	file2.close();
	remove(txt.c_str());
	rename("temp_str.txt", txt.c_str());
}

//Fine to a Student
void Admin :: fine_record(string txt) {
	ofstream file1;
	int fine;
	string reason;
	file1.open(txt.c_str(), ios::app);
	
	//Asking for Fine Amount & Reason
	cout << endl << endl << Tab() << "Add Amount of Fine: ";
	cin >> fine;
	input_test(fine);
	cin.ignore();
	cout << endl << Tab() << "Add Reason of Fine: ";
	getline(cin, reason);

	file1 << endl << roll_no << book_name << endl;
	file1 << fine << endl << reason;
	file1.close();
}

//Check all Previous Fine Record
void Admin::check_fine_record(string txt) {
	ifstream file1;
	file1.open(txt.c_str());
	cout << "\n\n   " << left << setw(17) << "Roll_Number" << setw(30) << "   Issued Book Name" << setw(25) << "   Fine"  << setw(27) << "Reason" << endl << endl << endl << endl << endl;
	while (!file1.eof()){
		int fine;
		string reason;
		file1 >> roll_no; 
		file1 >> ws;
		getline(file1, book_name);
		file1 >> fine;
		file1.ignore();
		getline(file1, reason);
		cout << "   " << left << setw(20) << roll_no << left << setw(30) << book_name << left << setw(20) << fine << reason << endl << endl;
	}
	file1.close();
}

//Student Method: Login a Particular User
bool Student::login_user(string txt){

	//Asking to Student if he is already Member or not?
	cout <<  endl << endl << "\t\t    Are you Already a Member of this Library or not?(Press 1 if You're) ";
	
	char a = '0';
	string temp_password;
	cin >> a;
	if (a != '1'){
		cout << endl << endl <<"\t\t\tPlease Go towards Librarian & Make Sure to Complete Your Registration First\n" << "\t\t\t\t\t\t\t\tThanks\n\n\n";
		return false;
	}
	int count = 3;
	cout << endl << Tab() << "Enter Your Password: ";
	while (count){
		//Asking for Student Password
		cin >> temp_password;
		ifstream file1;
		file1.open(txt.c_str());

		while (!file1.eof()) {
			file1 >> password;
			int x = password.compare(temp_password);
			if (x == 0) {
				file1 >> roll_no;
				file1 >> ws;
				getline(file1, student_name);
				return true;
			}
			else
				file1.ignore(400, '\n');
		}
			system("CLS");
			main_text();
			cout << endl  << endl << Tab() << "   Wrong Password!" << endl;
			cout << endl << endl << Tab() << " Enter Again(Limit: " << --count << "):" ;
			file1.close();
	}
	return false;
}

//Change Password of Student
void Student::change_password(string txt) {
	bool error = false;
	string temp_password;

	//Asking for Old Password
	cout << "\n\n\n\n\n" << Tab() << "Enter Your Old Password: ";
	cin >> temp_password;

	ifstream file3;
	file3.open(txt.c_str());

	while (!file3.eof()) {
		file3 >> password;
		int x = password.compare(temp_password);
		if (x == 0) {
			error = true;
			file3.close();
			break;
		}
		else
			file3.ignore(400, '\n');
	}
	file3.close();
	if (error == true) {
		string new_password;
		ifstream file1;
		ofstream file2;
		file1.open(txt.c_str());
		file2.open("temp_file.txt");
		cout <<  "\n\n\t\t\t" << "Enter New Password (Note: Space is not allowed in Password): ";
		cin >> new_password;
		while (!file1.eof()) {
			file1 >> password;
			file1 >> roll_no;
			getline(file1, student_name);
			int x = password.compare(temp_password);
			if (x == 0) {
				file2 << endl << new_password << endl;
				file2 << roll_no << "  " << student_name;
				cout << "\n\n\n" << Tab() <<  "Successfully Updated\n";
			}
			else {
				file2 << endl << password << endl;
				file2 << roll_no << student_name;
			}
		}
		file1.close();
		file2.close();
		remove(txt.c_str());
		rename("temp_file.txt", txt.c_str());
	}
	else {
		cout << "\n\n" << Tab() <<  "Your Old Password is Wrong\n";
	}
}

//Checking that which books are issued to a student
void Student::check_enroll_books(string txt) {
	ifstream file1;
	file1.open(txt.c_str());

	string date, temp_book, temp_roll;
	int temp_isbn;
	bool error = false;
	
	while (!file1.eof()) {
		file1 >> temp_isbn;
		file1 >> ws;
		getline(file1, temp_book);
		file1 >> temp_roll;
		file1 >> date;
		int x = temp_roll.compare(roll_no);
		if (x == 0) {
			cout << Tab() << "\tIssued Book\n\n\n";
			cout << Tab() << "Name: " <<  temp_book << endl;
			cout << Tab() << "Issued Date: " << date << endl;
			file1.close();
			error = true;
			break;
		}
	}
	if (!error) {
		cout << endl << Tab() << "No one Book is Issued to you Previously\n";
	}
}


int main() {

	//Student Library Member & By it we can have access to Admin member too
	Student Libray;

	//Mostly Used Variables at various places in Main
	int count = 3, option;
	bool error = false;
	
	//Changing Backgroung & text color in Console & Changing of Font
	system("color 8f");
	fontsize(3, 22);
	
	//Main Page Area
	cout << "\n\n\n\n\n\n\n\n\n\n";
	main_text();
	cout << "\n\n\n\n" << Tab() << "Press Enter to Continue";
	cin.get();
	
	while (1){
		system("CLS");
		cout << "\n\n";
		main_text();
		cout << "\n\n\n\n\n" << Tab() << "Are You? \n\n\n" << Tab() << "1) " << Arrow() << " Admin\n\n" << Tab() << "2) " << Arrow() << " Student\n\n\n\n" << Tab() << "Enter Your Option: ";
		cin >> option;
		input_test(option);

		//Testor loop for Input
		while (option > 2 || option < 1) {
			cout << endl << Tab() << "Invalid Input\n" << Tab() << "Enter Your Option again: ";
			cin >> option;
		}
		system("CLS");

		//Admin Area
		if (option == 1) {
			ifstream file;
			file.open("Admin.txt");

			string admin_password;;
			main_text();
			file >> admin_password;
			file.close();
			string fake_password;

			cout << endl << endl << Tab() << "\tLogin" << endl << endl << endl;
			cout << Tab() << "Enter Your Password: ";
			cin >> fake_password;
			int x = fake_password.compare(admin_password);
			if (x == 0) error = true;

			//Admin Password Checker Testor
			while (x != 0 && count > 1) {
				cout << endl << endl << Tab() << "      Wrong Password" << endl << endl;
				cout << Tab() << "Enter again(" << --count << " Limit): ";
				cin >> fake_password;
				int x = fake_password.compare(admin_password);
				if (x == 0) {
					error = true;
					count = 3;
					break;
				}
			}

			//If Limit Excceeds & Password wrong then Returning to main again 
			if (!error) {

				cout << Tab() << "Returning to Main Menu again\n";
				cout << Tab() << "Press Enter to Continue: ";
				count = 3;
				cin.get();
				cin.get();
				system("CLS");
				continue;
			}

			//If Admin Enter Password Successfully
			else {
				cout << endl << Tab() << "Successfully Login" << endl;
				cout << endl << Tab() << "Press Enter to Continue: ";
				cin.get();
				cin.get();
				//Admin Auhtorities Area
				while (1) {
					system("CLS");
					main_text();
					
					//Various Authorities of Admin
					cout << endl << endl << endl << "\t1) " << Arrow() << setw(40) << left << " Issue a Book";
					cout << "\t\t2) " << Arrow() << " Deposit a Book" << endl << endl;
					cout << "\t3) " << Arrow() << setw(40) << left << " Add a New Member in Library";
					cout << "\t\t4) " << Arrow() << " Remove Member" << endl << endl;
					cout << "\t5) " << Arrow() << setw(40) << left << " Add a New Book in Stock";
					cout << "\t\t6) " << Arrow() << " Removal of a Book from Stock" << endl << endl;
					cout << "\t7) " << Arrow() << setw(40) << left << " Update a Book Record";
					cout << "\t\t8) " << Arrow() << " Search a Book" << endl << endl;
					cout << "\t9) " << Arrow() << setw(40) << left << " See all Book in Stock";
					cout << "\t\t10) " << Arrow() << " See all Members of Library" << endl << endl;
					cout << "\t11) " << Arrow() << setw(40) << left << " See Issued Book's Record";
					cout << "\t12) " << Arrow() << " See all Previous Fine Records" << endl << endl;
					cout << "\t13) " << Arrow() << setw(40) << left << " Update Your Password";
					cout << "\t14) " << Arrow() << " Logout" << endl;
					cout << endl << endl << endl << Tab() << "Enter Your Option:";
					cin >> option;
					input_test(option);

					//Testor while Admin enter correct Option or Not
					while (option > 14 || option < 1) {
						cout << Tab() << "Invalid Input!" << endl;
						cout << Tab() << "Enter Your Option again: ";
						cin >> option;
						input_test(option);
					}

					system("CLS");

					//Issued Book Part
					if (option == 1) {
						main_text();
						cout << endl;
						Libray.issue_book("Issued_Book.txt");
						cout << endl << Tab() << "Done! Press any Key to go to Main Menu: ";
						cin.get();
						cin.get();
						continue;
					}

					//Deposit Book Part
					else if (option == 2) {
						main_text();
						cout << endl;
						Libray.deposit_book("Issued_Book.txt");
						cout << endl << "\t\t\tDone! Press any Key to go to Main Menu: ";
						cin.get();
						cin.get();
						continue;
					}

					//Add New Member in Library Part
					else if (option == 3) {
						main_text();
						cout << endl;
						Libray.add_member("Enroll_Student.txt");
						cout << endl << Tab() << "Done! Press any Key to go to Main Menu: ";
						cin.get();
						cin.get();
						continue;
					}

					//Remove a particular member from Library
					else if (option == 4) {
						main_text();
						cout << endl;
						Libray.remove_member("Enroll_Student.txt");
						cout << endl << Tab() << "Done! Press any Key to go to Main Menu: ";
						cin.get();
						cin.get();
						continue;
					}

					//Addition of New Book In Library
					else if (option == 5) {
						main_text();
						cout << endl;
						int book_option;
						cout << endl << endl << "\t\t\t\t\t    Want Add Book in which Section?\n\n";
						books_section(book_option);
						switch (book_option)
						{
						case 1:
							Libray.add_book("English_books.txt");
							break;
						case 2:
							Libray.add_book("Islamic_books.txt");
							break;
						case 3:
							Libray.add_book("Urdu.txt");
							break;
						case 4:
							Libray.add_book("Programming.txt");
							break;
						case 5:
							Libray.add_book("Sllaybus_books.txt");
							break;
						default:
							break;
						}
						cout << endl << "\t\t\tDone! Press any Key to go to Main Menu: ";
						cin.get();
						continue;
					}

					//Deletion of a Book from Library
					else if (option == 6) {
						int book_option;
						main_text();
						cout << endl;
						cout  << "\n\n\t\t\t\t\tWant to Delete Book from which Section?\n\n";
						books_section(book_option);
						switch (book_option)
						{
						case 1:
							Libray.delte_book("English_books.txt");
							break;
						case 2:
							Libray.delte_book("Islamic_books.txt");
							break;
						case 3:
							Libray.delte_book("Urdu.txt");
							break;
						case 4:
							Libray.delte_book("Programming.txt");
							break;
						case 5:
							Libray.delte_book("Sllaybus_books.txt");
							break;
						default:
							break;
						}
						cout << endl << "\t\t\tDone! Press any Key to go to Main Menu: ";
						cin.get();
						cin.get();
						continue;
					}

					//Updation of a Book in Library
					else if (option == 7) {
						main_text();
						cout << endl;
						int book_option;
						cout << "\n\n\t\t\t\t\tWant to Update Book's Record in which Section?\n\n";
						books_section(book_option);\
						system("CLS");
						switch (book_option)
						{
						case 1:
							Libray.update_book("English_books.txt");
							break;
						case 2:
							Libray.update_book("Islamic_books.txt");
							break;
						case 3:
							Libray.update_book("Urdu.txt");
							break;
						case 4:
							Libray.update_book("Programming.txt");
							break;
						case 5:
							Libray.update_book("Sllaybus_books.txt");
							break;
						default:
							break;
						}
						cout << endl << Tab() << "Done! Press any Key to go to Main Menu: ";
						cin.get();
						cin.get();
						continue;
					}

					//Searching of a Book from Particular Section of Library
					else if (option == 8) {
						main_text();
						cout << endl;
						int book_option;
						cout << "\n\n\t\t\t\t\tWant to Search Book in which Section?\n\n";
						books_section(book_option);
						system("CLS");
						switch (book_option)
						{
						case 1:
							Libray.check_book("English_books.txt");
							break;
						case 2:
							Libray.check_book("Islamic_books.txt");
							break;
						case 3:
							Libray.check_book("Urdu.txt");
							break;
						case 4:
							Libray.check_book("Programming.txt");
							break;
						case 5:
							Libray.check_book("Sllaybus_books.txt");
							break;
						default:
							break;
						}
						cout << endl << Tab() << "Done! Press any Key to go to Main Menu: ";
						cin.get();
						cin.get();
						continue;
					}

					//All Books of a Particular Section in Library
					else if (option == 9) {
						main_text();
						cout << endl;
						int book_option;
						cout <<  "\n\n\t\t\t\t\tWant to See all Stocks of Books of which Section?\n\n";
						books_section(book_option);
						system("CLS");
						switch (book_option)
						{
						case 1:
							Libray.all_books("English_books.txt");
							break;
						case 2:
							Libray.all_books("Islamic_books.txt");
							break;
						case 3:
							Libray.all_books("Urdu.txt");
							break;
						case 4:
							Libray.all_books("Programming.txt");
							break;
						case 5:
							Libray.all_books("Sllaybus_books.txt");
							break;
						default:
							break;
						}
						cout << endl << "\t\t\tDone! Press any Key to go to Main Menu: ";
						cin.get();
						cin.get();
						continue;
					}

					//Checking of all Members in Library
					else if (option == 10) {
						main_text();
						cout << endl;
						Libray.check_all_members("Enroll_Student.txt");
						cout << endl << "\t\t\tDone! Press any Key to go to Main Menu: ";
						cin.get();
						cin.get();
						continue;
					}

					//Checking of all Issued Book's Record in Library
					else if (option == 11) {
						main_text();
						cout << endl;
						Libray.check_issued_books_record("Issued_Book.txt");
						cout <<  "\n\n\t\t\tDone! Press any Key to go to Main Menu: ";
						cin.get();
						cin.get();
						continue;
					}

					//Checking of Previous Fine Records of Library 
					else if (option == 12) {
						main_text();
						cout << endl;
						Libray.check_fine_record("Fine_record.txt");
						cout << "\n\n\n\n\t\t\tDone! Press any Key to go to Main Menu: ";
						cin.get();
						cin.get();
						continue;
					}

					//Changing Password of Admin
					else if (option == 13) {
						main_text();
						cout << endl;
						string temp_password;
						cout << "\n\n\n" <<  Tab() << "Enter Your Old Password: ";
						cin >> temp_password;
						int y = temp_password.compare(admin_password);
						if (y == 0){
							cout << endl << Tab() << "Enter New Password(No Space Allowed): ";
							cin >> admin_password;
							ofstream file;
							file.open("Admin.txt");
							file << admin_password;
							file.close();
						}
						else{
							cout << endl << Tab() << "Old Password is Wrong! " << endl;
							cout << endl << Tab() << "Returning to Main Menu again";
							cin.get();
							cin.get();
							continue;
						}
						cout << endl << endl << Tab() << "Password Updated" << endl;
						cout << endl << Tab() << "Done! Press any Key to go to Main Menu: ";
						cin.get();
						cin.get();
						continue;
					}

					//Log_out From Admin Side
					else {
						main_text();
						cout << "\n\n\n\n\n\n";
						cout << Tab() << "Press any key for Continue:";
						cin.get();
						cin.get();
						break;
					}

				}
			}
		}
		else {
			main_text();
			if (Libray.login_user("Student_Password.txt")) {
				cout  << endl << Tab() << " Successfully Login\n" << Tab() << "\tof" << endl << Tab() << Libray.put_name() << "(" << Libray.put_roll_no() << ")" << endl;
				cout << endl <<Tab() <<  "Press Enter to Continue: ";
				cin.get();
				cin.get();

				while (1){
					system("CLS");
					main_text();
					cout << endl << endl;
					cout << Tab() << Libray.put_name() << "(" << Libray.put_roll_no() << ")" << endl << endl << endl;
					cout << endl << Tab() << "1) " << " See all Books in Stock\n\n";
					cout << endl << Tab() << "2) " << " Search a Book in Library Stock\n\n";
					cout << endl << Tab() << "3) " << " See Enrolled books to you in Past\n\n";
					cout << endl << Tab() << "4) " << " Change Password\n\n";
					cout << endl << Tab() << "5) " << " Logout\n\n";

					cout << endl << endl << Tab() << "Enter Your Option:";
					cin >> option;
					input_test(option);

					//Testor while Admin enter correct Option or Not
					while (option > 5 || option < 1) {
						cout << Tab() << "Invalid Input!" << endl;
						cout << Tab() << "Enter Your Option again: ";
						cin >> option;
						input_test(option);
							}
					system("CLS");
					if (option == 1) {
						main_text();
						cout << endl;
						int book_option;
						cout << "\n\n\t\t\t\t\tWant to See all Stocks of Books of which Section?\n\n";
						books_section(book_option);
						system("CLS");
						switch (book_option)
						{
						case 1:
							Libray.all_books("English_books.txt");
							break;
						case 2:
							Libray.all_books("Islamic_books.txt");
							break;
						case 3:
							Libray.all_books("Urdu.txt");
							break;
						case 4:
							Libray.all_books("Programming.txt");
							break;
						case 5:
							Libray.all_books("Sllaybus_books.txt");
							break;
						default:
							break;
						}
						cout << endl << "\t\t\tDone! Press any Key to go to Main Menu: ";
						cin.get();
						cin.get();
						continue;

					}
					else if (option == 2) {
						main_text();
						cout << endl;
						int book_option;
						cout << "\n\n\t\t\t\t\tWant to Search Book in which Section?\n\n";
						books_section(book_option);
						system("CLS");
						switch (book_option)
						{
						case 1:
							Libray.check_book("English_books.txt");
							break;
						case 2:
							Libray.check_book("Islamic_books.txt");
							break;
						case 3:
							Libray.check_book("Urdu.txt");
							break;
						case 4:
							Libray.check_book("Programming.txt");
							break;
						case 5:
							Libray.check_book("Sllaybus_books.txt");
							break;
						default:
							break;
						}
						cout << endl << "\n\t\t\t\tDone! Press any Key to go to Main Menu: ";
						cin.get();
						cin.get();
						continue;
					}

					else if (option == 3) {
						system("CLS");
						main_text();
						Libray.check_enroll_books("Issued_Book.txt");
						cout << endl << Tab() << "Press Enter to continue: ";
						cin.get();
						cin.get();
					}
					else if (option == 4){
						system("CLS");
						main_text();
						Libray.change_password("Student_Password.txt");
						cout << "\t\t\tControl is Returning to Main. You have to Login again with new Password.";
						cout << endl << endl << endl  << Tab() << "Press Enter to continue: ";
						cin.get();
						cin.get();
						break;
					}
					else {
						main_text();
						cout << endl;
						cout << "\n\n\n\n\n" << Tab() << "Press any key for Continue:";
						cin.get();
						cin.get();
						break;
					}

				}
			}
			else {
				cout << endl << endl << endl << Tab() << "Returning to Main Again\n";
				cout  << endl << Tab() << "Press Enter to Continue:";
				cin.get();
				cin.get();
				continue;
			
			}
		}
  
	}
		system("pause");
		return 0;
	
}

//Funtion for Increasing Font of Text in Console
void fontsize(int a, int b) {
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = a;
	lpConsoleCurrentFontEx->dwFontSize.Y = b;
	SetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
}

//Main Text which have to be used multiple times
void main_text() {
	cout << "\n\n\t\t\t\t\t\t"<< left << setw(30) << "******* PUCIT_NC_Library *******";
	cout << "\n" << Tab() << left << setw(30) << "Canal_Road, Lahore\n";
	for (int i = 0; i < 10; i++) {
		cout << "***********";
	}
}

//Book's Section Option (Stock of Books in Library)
void books_section(int &a) {

	//Different catogries of Library
	cout << Tab() << "1) " << Arrow() << " English Books" << endl << endl;
	cout << Tab() << "2) " << Arrow() << " Islamic Books" << endl << endl;
	cout << Tab() << "3) " << Arrow() << " Urdu Books" << endl << endl;
	cout << Tab() << "4) " << Arrow() << " Programming Books" << endl << endl;
	cout << Tab() << "5) " << Arrow() << " Pucit_Sllaybus Books" << endl << endl;
	cout << Tab() << "Enter your Option: ";
	cin >> a;
	input_test(a);

	//Input Testor
	while (a < 1 || a > 5) {
		cout << Tab() << "Invalid Input! Enter again: ";
		cin >> a;
		input_test(a);
	}
}

void input_test(int &input) {
	while (1){
		if (!cin.fail()) break;
		else {
			cout << endl << Tab() << "Wrong Input\n";
			cin.clear();
			cin.ignore(400, '\n');
			cout << endl << Tab() << "Enter Again: ";
			cin >> input;
		}
		system("CLS");
		main_text();
	}
}

