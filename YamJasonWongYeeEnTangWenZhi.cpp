#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#define numberOfAdmins 3
#define MaxStudents 21
#define MaxNominees 5
using namespace std;

struct StudentType
{
	char MyKad[13];
	char StudentID[11];
	bool nominateChance;
	bool voteChance;
};
struct NomineeType
{
	char n_MyKad[13];
	char n_StudentID[11];
	string program;
	int yearOfStudy;
	int vote;
	int femalevote;
	int malevote;
};

void mainScreen();
void AdminLogin();
void welcomeAdmin();
void RegisterStudent(StudentType student[], int* studentNum);
void displayRegisterTitle();
int adminScreen();
void adminMenu();
int studentScreen();
void studentMenu();
void studentLogin(StudentType student[], int* currentStudent);
int checkDuplicate(NomineeType nominee[], int nomineeNo);
void vote(int number_of_nominee, NomineeType nominee[], StudentType student[], int* currentStudent);
void nominate(NomineeType nominee[], int* nomineeNum, StudentType student[], int* currentStudent);
int checkuser(StudentType student[], NomineeType nominee[], int nomineeNo);
void displayNominee(NomineeType nominee[]);
void winnerDeclaration(NomineeType nominee[], int topNominee);
void result(NomineeType nominee[]);
void statistics(NomineeType nominee[], StudentType student[]);
void farewellStudents();
void detailedAnalysisScreen(NomineeType nominee[]);
void readNominationFile(NomineeType nominee[]);
void readStudentFile(StudentType student[]);
void updateStudentFile(StudentType student[]);
void updateNominationFile(NomineeType nominee[]);
int checkDuplicateStudent(StudentType student[], int studentNo);
int readNumStudentsFile();
int readNumNomineeFile();
void clearStudentFile();



int main()
{
	int choice, number_of_students, number_of_nominee, currentStudent;
	StudentType student[MaxStudents];
	NomineeType nominee[MaxNominees];


	do {
		system("cls");
		number_of_students = readNumStudentsFile();
		number_of_nominee = readNumNomineeFile();

		cout << "Number of registered student: " << number_of_students << endl;
		cout << "Number of registered Nominee: " << number_of_nominee << endl;

		//cout << "Number of registered nominee: " << number_of_nominee << endl;

		mainScreen();
		cout << "Please enter a number ( 1-3 ) : ";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
			//Admin section
			 //validate
			AdminLogin();
			switch (adminScreen())
			{
			case 1:
			{
				RegisterStudent(student, &number_of_students);
				break;
			}
			case 2:
				result(nominee);
				break;
			case 3:
				statistics(nominee, student);
				break;
			case 4:
				detailedAnalysisScreen(nominee);
				break;
			case 5:
				break;

			}
			break;

		case 2:
		{

			studentLogin(student, &currentStudent);
			switch (studentScreen())
			{
			case 1:
				nominate(nominee, &number_of_nominee, student, &currentStudent);
				break;
			case 2:
				vote(number_of_nominee, nominee, student, &currentStudent);
				system("pause");
				break;
			case 3:
				break;
			}

			break;

		}
		case 3:
		{
			cout << "You are exiting......" << endl;
			break;
		}

		}

	} while (choice != 3);
	return 0;
}

//Main screen
void mainScreen()
{

	cout << "------------------------------------------------------------------------------------------------" << endl;
	cout << "                                     MAIN MENU                                                  " << endl;
	cout << "------------------------------------------------------------------------------------------------\n\n";
	cout << "[1] Admin login" << endl;
	cout << "[2] Student login" << endl;
	cout << "[3] Exit" << endl << endl;
	cout << "------------------------------------------------------------------------------------------------\n\n";

}

//AdminLogin
void AdminLogin()
{
	bool isValidAdmin;
	char gotoMainMenu;
	bool reKeyIn;
	string AdminUsername, AdminPassword;
	string usernameArray[3] = { "Wong Yee En","Yam Jason","Tang Wen Zhi" }; // Array database for usernames of admins
	string passwordArray[3] = { "1111","2222","3333" };// Array database for passwords of admins

	//Enter the loop at least once
	do
	{
		system("cls");
		cin.ignore();
		welcomeAdmin(); //Display Welcome Screen to Admin
		cout << "Enter username : "; //Prompt and read Admin Username
		getline(cin, AdminUsername);

		cout << "Enter password : ";//Prompt and read Admin Password
		getline(cin, AdminPassword);

		// Comparing the input with array database
		for (int i = 0; i < numberOfAdmins; i++)
		{
			//If the input matches with database
			if (AdminUsername == usernameArray[i] && AdminPassword == passwordArray[i])
			{
				//She or He is one of the admins
				isValidAdmin = true;
				break;
			}

			else
				//She or He is not one of the admins
				isValidAdmin = false;

		}
		//When She or He is not one of the admins
		if (isValidAdmin == false)
		{
			//She or He is not able to log in 
			cout << "\nLogin failed" << endl;
			cout << "Either the user didn't exist or the user or password is incorrect." << endl;
			//Prompt and get whether She or He wants to go back to main menu / re-enter 
			cout << "Enter 'Y' to go to the main menu, others to re-enter :";
			cin >> gotoMainMenu;
			//If input is 'Y'/ 'y'
			if (gotoMainMenu == 'Y' || gotoMainMenu == 'y')
			{
				system("cls");
				main();// Go to main function
			}
			//If the input is not 'Y' / 'y'
			else {
				reKeyIn = true;  // Set to let the admin re-enter later
			}

		}
		//When She or He is admin
		else
		{
			// Set admin don't have to re-enter later
			reKeyIn = false;
			break;
		}

		//If re-enter is true, loop again
	} while (reKeyIn == true);

}

//Student Screen
int studentScreen() {
	int studentChoice;
	system("cls");

	//Display Student Menu
	studentMenu();

	//Prompt and get choice
	cout << "Please enter a number ( 1-3 ) : ";
	cin >> studentChoice;

	//Prompt and get choice again if the input is not within the range of 1 - 3
	while (studentChoice > 3 || studentChoice < 1)
	{
		cout << "Invalid choice!" << endl;
		cout << "Enter again: ";
		cin >> studentChoice;
	}
	system("cls");
	return studentChoice;
}

//Student Menu
void studentMenu()
{
	cout << "------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "                                     WELCOME TO THE STUDENT MENU!                               " << endl << endl;
	cout << "------------------------------------------------------------------------------------------------" << endl;
	cout << "Student Menu" << endl;
	cout << "------------------------------------------------------------------------------------------------\n\n";
	cout << "[1] Nominate" << endl;
	cout << "[2] Vote" << endl;
	cout << "[3] Exit" << endl;
	cout << "------------------------------------------------------------------------------------------------\n\n";
}

int adminScreen() {
	int adminChoice;
	system("cls");

	//Display Admin Menu
	adminMenu();

	//Prompt and get choice
	cout << "Please enter a number ( 1-5 ) : ";
	cin >> adminChoice;

	//Prompt and get choice again if the input is not within the range of 1 - 3
	while (adminChoice > 5 || adminChoice < 1)
	{
		cout << "Invalid choice!" << endl;
		cout << "Enter again: ";
		cin >> adminChoice;
	}
	system("cls");
	return adminChoice;
}

void adminMenu()
{
	cout << "------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "                                     WELCOME TO THE ADMIN MENU!                                 " << endl << endl;
	cout << "------------------------------------------------------------------------------------------------" << endl;
	cout << "Admin Menu" << endl;
	cout << "------------------------------------------------------------------------------------------------\n\n";
	cout << "[1] Register student" << endl;
	cout << "[2] Result" << endl;
	cout << "[3] Statistic" << endl;
	cout << "[4] Detailed Analysis" << endl;
	cout << "[5] Exit" << endl;
	cout << "------------------------------------------------------------------------------------------------\n\n";
}

void RegisterStudent(StudentType student[], int* studentNum)
{
	int i, newNumStudents;
	bool MyKadformat = false; // Initialize MyKadformat to false 
	bool IDformat = false; // Initialize MyKadformat to false 
	bool studentCheck = false;// Initialize studentCheck to false 

	//Display Register Title
	displayRegisterTitle();
	//If the students
	if (MaxStudents - *studentNum == 0)
		system("pause");
	// If the number of students in file is not equal to maximum students to be registered.

	//
	clearStudentFile();

	cin.ignore(100, '\n');

	//Loop 
	for (i = 0; i < MaxStudents; i++)
	{
		cout << "\nStudent " << i + 1 << endl;
		do
		{
			//MyKad Input and Validation
			//Enter this loop at least once 
			do
			{

				//Prompt and get student's MyKad number
				cout << "Enter student's MyKad number :";
				cin.getline(student[i].MyKad, 13);

				//MyKad Validation
				//It must be 12 characters
				if (strlen(student[i].MyKad) != 12)
				{
					//Set MyKadformat to false if there are no 12 characters
					MyKadformat = false;
				}

				else
				{
					//Set MyKadformat to true if there are 12 characters
					MyKadformat = true;
					//Use loop to check each character in MyKad Number
					for (int j = 0; j < 12; j++)
					{
						//If one of the characters in MyKad Number is not a digit
						if (isdigit(student[i].MyKad[j]) == 0)
						{
							//Set MyKadformat to false
							MyKadformat = false;
							break;
						}

					}
				}
				//If MyKadformat is false
				if (MyKadformat == false)
					//Display the correct format
					cout << "Incorrect entry. It must be 12 digits without dashes '-'." << endl;

				//Loop again while MyKadformat is false.
			} while (MyKadformat == false);

			//Student ID Input and Validation
			//Enter this loop at least once 
			do
			{
				//Prompt and get student's Student ID
				cout << "Enter student's Student ID :";
				cin.getline(student[i].StudentID, 11);

				//Student ID Validation 
				//It must be 10 characters
				if (strlen(student[i].StudentID) != 10)
					//Set IDformat to false if there are no 10 characters
					IDformat = false;
				else
				{
					//Set IDformat to true if there are 10 characters
					IDformat = true;
					if (isdigit(student[i].StudentID[0]) == 0 || isdigit(student[i].StudentID[1]) == 0)
						//Set IDformat to false if the first and second character are not digits
						IDformat = false;
					else
					{
						//Set IDformat to true if the first and second character are digits
						IDformat = true;
						//Loop from the third character to the fifth character of Student ID
						//to check whether they are alphabets in uppercase
						for (int k = 2; k < 5; k++)
						{
							if (isalpha(student[i].StudentID[k]) == 0 || isupper(student[i].StudentID[k]) == 0)
							{
								//If the characters are not alphabets or in uppercase
								//Set IDformat to false 
								IDformat = false;
								break;
							}
							else
							{
								//If the characters are alphabets and in uppercase
								//Set IDformat to true
								IDformat = true;
								//Check the 6th to 10th characters using loop
								for (int s = 5; s < 10; s++)
								{
									//If any of the charaters is not a digit
									if (isdigit(student[i].StudentID[s]) == 0)
									{
										//Set IDformat to false
										IDformat = false;
										break;
									}
								}
							}
						}

					}

				}
				//Display correct format if IDformat is false.
				if (IDformat == false)
					cout << "Incorrect.It must be in full alphanumeric e.g. 22WMR12345." << endl;
				//Loop again when IDformat is false
			} while (IDformat == false);


			//Read number of students in the file
			newNumStudents = readNumStudentsFile();

			// If the input is duplicate with the any one of the record in database
			if (checkDuplicateStudent(student, newNumStudents) == 1)
			{
				//Set studentCheck to false
				studentCheck = false;
			}
			else
			{
				//Set studentCheck to true if there is no duplication
				studentCheck = true;
			}

			//Loop again when the studentCheck is false
		} while (studentCheck == false);



		student[i].nominateChance = true; //Set student's nominate chance to true in array
		student[i].voteChance = true;//Set student's vote chance to true in array
		cout << "Registered!" << endl;
		system("pause");

		//Append RegisterStudent text file 
		ofstream outData;
		outData.open("RegisterStudent.txt", ios_base::app | ios_base::out);
		//The file cant be opened
		if (!outData)
		{
			//Display error message
			cout << "Error opening file";

		}
		else
		{
			//Write from array to file
			outData << student[i].MyKad << " " << student[i].StudentID << " " << student[i].nominateChance << " " << student[i].voteChance << endl;

		}
		//Close file
		outData.close();


	}
	system("cls");
}

void displayRegisterTitle()
{
	cout << "------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "                                     REGISTER STUDENTS' INFORMATION                             " << endl << endl;
	cout << "------------------------------------------------------------------------------------------------" << endl;
	cout << "Max student to register: " << MaxStudents << endl;
}

void studentLogin(StudentType student[], int* currentStudent)
{
	bool MyKadformat = false, IDformat = false, isValidStudent = false, reKeyIn = false;
	char MyKad[13], StudentID[11], gotoMainMenu;


	do
	{
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "                                     WELCOME STUDENT !                                          " << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl;

		//Input MyKad at least once
		do
		{
			cin.ignore(100, '\n');
			//Prompt and get MyKad number
			cout << "Enter MyKad number:";
			cin.getline(MyKad, 13);

			//MyKad Validation
			//If there are no 12 characters in MyKad 
			if (strlen(MyKad) != 12)
			{
				//Set MyKadformat to false
				MyKadformat = false;
			}

			else
			{
				//Set MyKadformat to true if there are 12 characters in MyKad 
				MyKadformat = true;
				//Loop to check every character
				for (int j = 0; j < 12; j++)
				{
					//If one of the character is not digit
					if (isdigit(MyKad[j]) == 0)
					{
						//Set MyKadformat to false
						MyKadformat = false;
						break;
					}

				}
			}
			//If Mykadformat is false
			if (MyKadformat == false)
				//Display error message with correct format of Mykad number
				cout << "Incorrect entry. It must be 12 digits without dashes '-'." << endl;
			//Loop again when MyKadformat is false 
		} while (MyKadformat == false);

		//Student ID Input and Validation
		do
		{
			//Prompt and get Student ID
			cout << "Enter student's Student ID :";
			cin.getline(StudentID, 11);

			//Student ID Validation 
			//If there are no 10 characters in Student ID
			if (strlen(StudentID) != 10)
				//Set IDformat to false
				IDformat = false;
			else
			{
				//If there are 10 characters
				//Set IDfformat to true
				IDformat = true;
				//If the one of the 1st and 2nd characters is not digit
				if (isdigit(StudentID[0]) == 0 || isdigit(StudentID[1]) == 0)
					//Set IDformat to false
					IDformat = false;
				else
				{
					//Set IDformat to true if the both 1st and 2nd characters are digits
					IDformat = true;
					//Loop to check the 3rd to 5th characters
					for (int k = 2; k < 5; k++)
					{
						//If one of the character is not alphabet or is not in uppercase`
						if (isalpha(StudentID[k]) == 0 || isupper(StudentID[k]) == 0)
						{
							//Set IDformat to false
							IDformat = false;
							break;
						}
						else
						{
							//Set IDformat to true if 3rd to 5th characters are alphabets in uppercase
							IDformat = true;
							//Loop from the 6th to 10th characters 
							for (int s = 5; s < 10; s++)
							{
								//If they are not digits
								if (isdigit(StudentID[s]) == 0)
								{
									//Set IDformat to false
									IDformat = false;
									break;
								}
							}
						}
					}

				}

			}
			//If IDformat is false
			if (IDformat == false)
				//Display error message and show the correct format of Student ID
				cout << "Incorrect.It must be in full alphanumeric e.g. 22WMR12345." << endl;
			//Loop again when IDformat is false
		} while (IDformat == false);



		//compare with database
		//Read students' file
		ifstream inData;
		inData.open("RegisterStudent.txt");
		//If cant open the text file
		if (!inData)
		{
			//Display error message
			cout << "Error opening data file" << endl;
		}
		else
		{
			//Enter loop if open the file succesfully
			//Loop to check whether the input matches with data in the database 
			for (int i = 0; i < MaxStudents; i++)
			{
				inData >> student[i].MyKad >> student[i].StudentID >> student[i].nominateChance >> student[i].voteChance;
				//If any of the record in database matches with the input 's MyKad and StudentID
				if (strcmp(MyKad, student[i].MyKad) == 0 && strcmp(StudentID, student[i].StudentID) == 0)
				{
					isValidStudent = true;//Set isValidStudent to true
					*currentStudent = i; // Let the matched student's position in file into pointer variable *currentStudent
					break;
				}
				else
				{
					//Set isValidStudent to false if there is not matching 
					isValidStudent = false;
				}

			}
		}
		//close file
		inData.close();

		//if does not match with database
		if (isValidStudent == false)
		{
			//Display login failed message
			cout << "\nLogin failed" << endl;
			cout << "Either the user didn't exist or the user or password is incorrect." << endl;
			cout << "Enter 'Y' to go to the main menu, others to re-enter :"; //Prompt and get gotoMainMenu
			cin >> gotoMainMenu;
			//If input is 'Y' / 'y'
			if (gotoMainMenu == 'Y' || gotoMainMenu == 'y')
			{
				system("cls");
				//Go to main function 
				main();
			}
			else {
				//If input is other than 'Y' & 'y'
				//Set reKeyIn to true 
				reKeyIn = true;
			}

		}

		else
		{
			//If match with database
			//Set reKeyIn to false
			reKeyIn = false;
			break;
		}
		//Loop again when reKeyIn is true 
	} while (reKeyIn == true);

}
//Nominate function
void nominate(NomineeType nominee[], int* nomineeNum, StudentType student[], int* currentStudent)
{
	//Initialize i to number of registered nominee
	int i = *nomineeNum;
	bool MyKadformat = false;
	bool IDformat = false;
	bool yearOfStudyformat = false;
	bool nomineeCheck = false;

	cout << "------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "                                     NOMINATE A STUDENT                                         " << endl << endl;
	cout << "------------------------------------------------------------------------------------------------" << endl;
	cout << "Max student to nominate: " << MaxNominees << endl;
	//If number of registered nominee has reached the maximum number of nominees (include abstain record in file)
	if (i == MaxNominees + 1)
	{
		//Display warning message
		cout << "Max nominee has been reached!" << endl;

	}
	//If the logged in student 's nominate chance is true (havent nominate)
	else if (student[*currentStudent].nominateChance == 1)
	{

		cout << "You are allowed to nominate!" << endl;

		//MyKad Input and Validation
		do
		{

			cin.ignore();
			do
			{

				//MyKad Input
				cout << "Enter nominee's MyKad number :";
				cin.getline(nominee[i].n_MyKad, 13);

				//MyKad Validation
				//If there are no 12 characters in MyKad 
				if (strlen(nominee[i].n_MyKad) != 12)
				{
					//Set MyKadformat to false
					MyKadformat = false;
				}

				else
				{
					//Set MyKadformat to true if there are 12 characters in MyKad
					MyKadformat = true;
					//Loop to check every character in MyKad
					for (int j = 0; j < 12; j++)
					{
						//If one of the character in MyKad is not a digit
						if (isdigit(nominee[i].n_MyKad[j]) == 0)
						{
							//Set MyKadformat to false
							MyKadformat = false;
							break;
						}

					}
				}
				//If MyKadformat is false
				if (MyKadformat == false)
					//Display warning message 
					cout << "Incorrect entry. It must be 12 digits without dashes '-'." << endl;

				//Loop again while MyKadformat is false
			} while (MyKadformat == false);

			//Student ID Input and Validation
			do
			{
				//Student ID Input
				cout << "Enter student's Student ID :";
				cin.getline(nominee[i].n_StudentID, 11);

				//Student ID Validation 
				//If there are no 10 characters in Student ID
				if (strlen(nominee[i].n_StudentID) != 10)
					//Set IDformat to false
					IDformat = false;
				else
				{
					//Set IDformat to true if there are 10 characters
					IDformat = true;
					//If one of the 1st and 2nd characters is not a digit
					if (isdigit(nominee[i].n_StudentID[0]) == 0 || isdigit(nominee[i].n_StudentID[1]) == 0)
						//Set IDformat to false
						IDformat = false;
					else
					{
						//Set IDformat to true if both of the 1st and 2nd characters are digits
						IDformat = true;
						//Loop to check from the 3rd to 5th characters 
						for (int k = 2; k < 5; k++)
						{
							//If one of the character is not alphabet in uppercase
							if (isalpha(nominee[i].n_StudentID[k]) == 0 || isupper(nominee[i].n_StudentID[k]) == 0)
							{
								//Set IDformat to false
								IDformat = false;
								break;
							}
							else
							{
								//Set IDformat to true if the characters are alphabets in uppercase
								IDformat = true;
								//Loop from 6th to 10th characters 
								for (int s = 5; s < 10; s++)
								{
									//If one of the characters is not a digit
									if (isdigit(nominee[i].n_StudentID[s]) == 0)
									{
										//Set IDformat to false
										IDformat = false;
										break;
									}
								}
							}
						}

					}

				}
				//If IDformat is false
				if (IDformat == false)
					//Display error message and show correct format of Student ID
					cout << "Incorrect.It must be in full alphanumeric e.g. 22WMR12345." << endl;
				//Loop again while IDformat false
			} while (IDformat == false);

			//Prompt and get nominee's program
			cout << "Nominee's program: ";
			getline(cin, nominee[i].program);

			//Enter this loop at least once
			do
			{
				//Prompt and get Nominee 's year of study
				cout << "Nominee's year of study: ";
				cin >> nominee[i].yearOfStudy;
				//If input is less than 1
				if (nominee[i].yearOfStudy < 1)
				{
					//Set yearOfStudyformat to false
					yearOfStudyformat = false;
				}
				else
				{
					//Set yearOfStudyformat to true if the input is not less than 1
					yearOfStudyformat = true;
				}
				//Loop again if yearOfStudy is false
			} while (yearOfStudyformat == false);

			//check if the details entered is from registered student, need to be from registered student
			//if not from registered user, will loop again.
			if (checkuser(student, nominee, i) == 0)
			{
				nomineeCheck = false;
			}
			//check if the details entered is from nomination list student, cannot be a duplicate.
			//if duplicate, loop again
			else if (checkDuplicate(nominee, i) == 1)
			{
				nomineeCheck = false;
			}
			else
			{
				nomineeCheck = true;
			}

		} while (nomineeCheck == false);



		//Set the logged in student's nominate chance to false
		student[*currentStudent].nominateChance = 0;

		//Append nomination list
		ofstream outData;
		outData.open("NominationList.txt", ios_base::app | ios_base::out);
		//If cant open the text file
		if (!outData)
		{
			//Display error message
			cout << "Error opening files. ";
		}
		else
		{
			cout << "Nominated successfully!" << endl;
			//set votes received to 0
			nominee[i].vote = 0;
			nominee[i].femalevote = 0;
			nominee[i].malevote = 0;

			//make a profile for abstain when nomineeNum is 4 ( which means when there are 5 nominees in file)
			if (i == 4)
			{
				//set the vote of sixth nominee (which represents abstain) to zero
				nominee[5].vote = 0;
				//Write the data from array to file 
				outData << nominee[i].n_MyKad << " " << nominee[i].n_StudentID << " " << nominee[i].program << " " << nominee[i].yearOfStudy << " " << nominee[i].vote << " " << nominee[i].femalevote << " " << nominee[i].malevote << endl;
				//including the vote of sixth nominee
				outData << nominee[5].vote << endl;
			}
			else
			{
				//If there are no 5 nominees in file
				//Write the data from array to file 
				outData << nominee[i].n_MyKad << " " << nominee[i].n_StudentID << " " << nominee[i].program << " " << nominee[i].yearOfStudy << " " << nominee[i].vote << " " << nominee[i].femalevote << " " << nominee[i].malevote << endl;
			}

		}
		outData.close();


		//update RegisterStudent.txt nominate chance
		updateStudentFile(student);


	}
	else
	{
		//If the logged in student's nominate chance is not available
		//Display warning message
		cout << "You are not allowed to nominate!" << endl;
	}
	system("pause");


}
//Check nominee is one of the registered student
int checkuser(StudentType student[], NomineeType nominee[], int nomineeNo)
{
	bool nomineeIsUser = false;
	//Read RegisterStudent text file
	ifstream inData;
	inData.open("RegisterStudent.txt");
	//If cant open the text file
	if (!inData) {
		//Display error message
		cout << "Error opening files.";
	}
	else {
		//Loop from the first student to the last student in file
		for (int i = 0; i < MaxStudents; i++)
		{
			//Read every students' record in file
			inData >> student[i].MyKad >> student[i].StudentID >> student[i].nominateChance >> student[i].voteChance;

		}
		inData.close();

		for (int i = 0; i < MaxStudents; i++)
		{
			//If there is any record from database matches with input
			if (strcmp(nominee[nomineeNo].n_MyKad, student[i].MyKad) == 0 || strcmp(nominee[nomineeNo].n_StudentID, student[i].StudentID) == 0)
			{
				//Set nomineeIsUser to true which means nominee is one of the registered students
				nomineeIsUser = 1;
				break;
			}
			else
			{
				//Set nomineeIsUser to false which means nominee is not one of the registered students
				nomineeIsUser = 0;
			}
		}
		//If nominee is not one of the user
		if (nomineeIsUser == 0)
		{
			cout << "Invalid student!" << endl << endl;
		}


	}

	//Return true if nominee is one of the registered students
	if (nomineeIsUser == 1)
		return 1;
	//Return false if nominee is not one of the registered students
	else
		return 0;
}
//Check the new nominee is not duplicate with the nominee in database
int checkDuplicate(NomineeType nominee[], int nomineeNo)
{
	bool duplicate = false;
	//If the number of nominees in file is more than zero
	if (nomineeNo > 0)
	{
		//Read NominationList text file
		ifstream inData;
		inData.open("NominationList.txt");

		if (!inData) {
			cout << "Error opening files.";
		}
		else {
			//Loop from the first nominee in the file up to the nominee in front of the new nominated nominee
			for (int i = 0; i < nomineeNo; i++)
			{
				//Read each of the nominee's records
				inData >> nominee[i].n_MyKad >> nominee[i].n_StudentID >> nominee[i].program >> nominee[i].yearOfStudy >> nominee[i].vote >> nominee[i].femalevote >> nominee[i].malevote;
				//If there is a match of MyKad and StudentID between input and database
				if (strcmp(nominee[nomineeNo].n_MyKad, nominee[i].n_MyKad) == 0 || strcmp(nominee[nomineeNo].n_StudentID, nominee[i].n_StudentID) == 0)
				{
					//Set duplicate to true
					duplicate = true;
					cout << "Nominee entered is a duplicate. Registration failed." << endl << endl;
					break;
				}
				else
				{
					//Set duplicate to false if there is no matching of MyKad and StudentID between input and database
					duplicate = false;
				}
			}

		}
		inData.close();
	}
	else
	{
		//Set duplicate to false if the number of nominee in file is not more than zero
		duplicate = false;
	}


	if (duplicate == true)
		return 1;
	else
		return 0;
}

void vote(int number_of_nominee, NomineeType nominee[], StudentType student[], int* currentStudent)
{

	int choice;
	char lastDigitMyKad = student[*currentStudent].MyKad[11]; // last digit of the logged in student's MyKad
	int convertedlastDigitMyKad = (int)lastDigitMyKad; // change the data type from character to integer
	cout << "------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "                                     CAST YOUR VOTE                                             " << endl << endl;
	cout << "------------------------------------------------------------------------------------------------" << endl;
	//if the number of nominees in file is not equal to the (maximum number of nominees plus one record of abstain)
	if (number_of_nominee != MaxNominees + 1)
	{
		cout << "Voting session has not started yet!" << endl;
	}
	else
	{
		//read NominationList from text file
		readNominationFile(nominee);

		//read RegisterStudent from text file;
		readStudentFile(student);
		//Display the nominees' details 
		displayNominee(nominee);

		//If the voting chance of logged in student is true
		if (student[*currentStudent].voteChance == 1)
		{
			//Display warning message
			cout << "Once a vote is cast, no amendment or changing of vote is allowed." << endl;
			//Prompt and get choice(vote) from user
			cout << "Cast your vote by entering a correct number (candidate number label) based on the number of candidates displayed on the screen \n";

			cout << "Enter your vote: ";
			cin >> choice;
			//any number that is not one of the candidate labels will get turned to 6 (which means the sixth record in file)
			if (choice < 1 || choice > 5)
			{
				choice = 6;
			}

			cout << "You have voted for candidate " << choice << endl;


			//update vote count to struct array
			choice -= 1;
			//Increment the vote of nominee that got voted by 1 
			nominee[choice].vote += 1;
			//Set the logged in student 's vote chance to false
			student[*currentStudent].voteChance = 0;

			//Differentiate gender of voters
			//If the vote is not for abstain 
			if (choice != 5)
			{
				//if the remainder of last digit of MyKad is zero when divided by 2
				if (convertedlastDigitMyKad % 2 == 0)
				{
					//Increment the female vote of voted nominee by 1
					nominee[choice].femalevote++;

				}
				else
				{
					//if the remainder of last digit of MyKad is not zero when divided by 2
					//Increment the male vote of voted nominee by 1
					nominee[choice].malevote++;

				}
			}
			else
			{
				//If the vote is not for abstain 
				cout << "YOU CHOSE TO ABSTAIN!" << endl;
			}

			//update vote chance in register student list
			updateStudentFile(student);


			//update vote count in nominationlist file
			//update nominate result
			updateNominationFile(nominee);

			system("cls");
			//Display farewell screen
			farewellStudents();


		}
		else
		{
			//If the voting chance of logged in student is false
			cout << "You are not allowed to vote twice!" << endl;

		}


	}
}

//Display nominees for students to know the nominee's details & labels
void displayNominee(NomineeType nominee[])
{
	//Loop all the nominees in database
	for (int i = 0; i < 5; i++)
	{
		cout << i + 1 << ". \t" << setw(15) << left << "Mykad" << ": " << nominee[i].n_MyKad << endl;
		cout << "  \t" << setw(15) << left << "Student ID" << ": " << nominee[i].n_StudentID << endl;
		cout << "  \t" << setw(15) << left << "Program" << ": " << nominee[i].program << endl;
		cout << "  \t" << setw(15) << left << "Year of study" << ": " << nominee[i].yearOfStudy << endl << endl;
	}
	cout << "Enter any number that is not 1-5 to ABSTAIN" << endl << endl;
}

//Voting result
void result(NomineeType nominee[])
{
	int total_votes = 0, topNominee, highest_vote;

	//read result from Nomination file
	readNominationFile(nominee);

	//Calculate total votes 
	for (int i = 0; i < 6; i++)
	{
		total_votes += nominee[i].vote;
	}
	cout << "Total Votes Received: " << total_votes << endl;

	//If total votes (including abstain) has reached the maximum number of students
	if (total_votes == MaxStudents)
	{
		//set nominee 1 as the nominee that has the most vote
		highest_vote = nominee[0].vote;
		for (int i = 1; i < 5; i++)
		{
			if (nominee[i].vote == highest_vote)
			{
				//set to 999 if there is a tie
				topNominee = 999;
			}
			else if (nominee[i].vote > highest_vote)
			{
				highest_vote = nominee[i].vote;
				topNominee = i + 1;
			}
		}

		//dicclare the winner
		winnerDeclaration(nominee, topNominee);
	}
	else
	{
		//Display voting session havent started yet if  total votes (including abstain) havent reached the maximum number of students
		cout << "Winner will be declared once all students have voted!" << endl;
	}
	system("pause");
}
void winnerDeclaration(NomineeType nominee[], int topNominee)
{
	//If there is a tie
	if (topNominee == 999)
	{
		//Display tie meesage
		cout << "-------------------------------------------------------------------------------------------------" << endl << endl;
		cout << "There is an event of a tie." << endl;
		cout << "Another voting session will be held again at another time to be  determined by the administrators" << endl << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl << endl;
	}
	else
	{
		//If there is a winner
		//Display winner declaration
		cout << "------------------------------------------------------------------------------------------------" << endl << endl;
		cout << "The winner is candidate " << topNominee << endl << endl;
		cout << left << setw(15) << "MyKad No" << ":" << nominee[topNominee - 1].n_MyKad << endl; // topNominee - 1 means the position of winner in database
		cout << left << setw(15) << "Student ID" << ":" << nominee[topNominee - 1].n_StudentID << endl;
		cout << left << setw(15) << "Program" << ":" << nominee[topNominee - 1].program << endl;
		cout << left << setw(15) << "Year Of Study" << ":" << nominee[topNominee - 1].yearOfStudy << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl << endl;
	}

	system("pause");
}

void statistics(NomineeType nominee[], StudentType student[])
{
	int totalFemaleVotes = 0, totalMaleVotes = 0, totalvotes = 0;

	cout << "------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "                                          Statistics                                            " << endl << endl;
	cout << "------------------------------------------------------------------------------------------------" << endl;

	//read result from Nomination file
	readNominationFile(nominee);

	//accumulate votes (does not include abstain)
	for (int i = 0; i < 5; i++)
	{
		totalvotes += nominee[i].vote;
		totalFemaleVotes += nominee[i].femalevote;
		totalMaleVotes += nominee[i].malevote;
	}

	cout << "Total Votes Received: " << totalvotes << endl;

	//abstain
	cout << "Total number of students who did not vote: " << nominee[5].vote << endl;
	//percentage of students voted
	cout << "Percentage of students voted " << fixed << setprecision(2) << (double)totalvotes / (totalvotes + nominee[5].vote) * 100.0 << "%" << endl;
	//total votes received by each candidate
	for (int i = 0; i < 5; i++)
	{
		cout << "Votes received by candidate " << i + 1 << " : " << nominee[i].vote << endl;
	}
	// breakdown of votes by gender

	//total female voters
	cout << "Number of female voters:" << totalFemaleVotes << endl;
	//total male voters
	cout << "Number of male voters:" << totalMaleVotes << endl;
	system("pause");


}

void welcomeAdmin()
{
	cout << "------------------------------------------------------------------------------------------------" << endl;
	cout << "                                       Welcome ,administrator !                                 " << endl;
	cout << "------------------------------------------------------------------------------------------------" << endl;
}
void farewellStudents()
{


	cout << "---------------------------------------------------------------------------------" << endl;
	cout << "                                Thanks for your voting !                         " << endl;
	cout << "                                                                                 " << endl;
	cout << "                               / \\                  / \\                          " << endl;
	cout << "                              /   \\                /   \\                         " << endl;
	cout << "                                                                                 " << endl;
	cout << "                                                                                 " << endl;
	cout << "                              |||||||||||||||||||||||||||                        " << endl;
	cout << "                                                                                 " << endl;
	cout << "                                    Have a nice day                              " << endl;
	cout << "---------------------------------------------------------------------------------" << endl;
}

void detailedAnalysisScreen(NomineeType nominee[])
{

	int choice, labelOfNominee, actualNumOfNomineeInFile;
	// actualNumOfNomineeInFile means the position of the nominee in database as the first nominee is in zero index so we have to minus 1 from the label of nominee
	int totalvotes = 0;
	//Menu for detailed analysis
	cout << "------------------------------------------------------------------------------------------------" << endl;
	cout << "                                       DETAILED ANALYSIS FOR EACH NOMINEE                       " << endl;
	cout << "------------------------------------------------------------------------------------------------" << endl << endl;
	//Several analysis option including exit from this page
	cout << "[1] Percentage of votes for each nominee" << endl;
	cout << "[2] Number of female voters" << endl;
	cout << "[3] Number of male voters" << endl;
	cout << "[4] Exit" << endl;
	cout << "------------------------------------------------------------------------------------------------" << endl;

	//read result from Nomination file
	readNominationFile(nominee);

	//Calculate total votes received ( excludes abstain)
	for (int i = 0; i < 5; i++)
	{
		totalvotes += nominee[i].vote;
	}

	do
	{
		cout << endl;
		//Prompt and get choice
		cout << left << setw(40) << "Enter your choice" << ": ";
		cin >> choice;
		//If choice is not equal to 4
		if (choice != 4)
		{
			//Prompt and get label of nominee
			cout << left << setw(40) << "Enter the label of candidates" << ": ";
			cin >> labelOfNominee;
			//While labelOfNominee is not in the range of 1 to 5
			while (labelOfNominee > 5 || labelOfNominee < 1)
			{
				//Display error message and prompt the labelOfNominee again
				cout << "Invalid label. Please enter again. " << endl;
				cout << "\nEnter the label of candidates:";
				cin >> labelOfNominee;
			}
			//Calculate the actualNumOfNomineeInFile (position of the nominee in database)
			actualNumOfNomineeInFile = labelOfNominee - 1;


			switch (choice)
			{
			case 1:
			{
				cout << left << setw(36) << "The percentage of votes for nominee" << setw(4) << labelOfNominee << ": " << fixed << setprecision(2) << (nominee[actualNumOfNomineeInFile].vote / static_cast<double>(totalvotes)) * 100.0 << "%" << endl;
				break;
			}
			case 2:
			{
				cout << left << setw(36) << "Number of female voters for nominee" << setw(4) << labelOfNominee << ": " << nominee[actualNumOfNomineeInFile].femalevote << endl;
				break;
			}
			case 3:
			{
				cout << left << setw(36) << "Number of male voters for nominee" << setw(4) << labelOfNominee << ": " << nominee[actualNumOfNomineeInFile].malevote << endl;
				break;
			}
			case 4:
				cout << "You are exiting" << endl;
				break;
			default:
				cout << "Invalid choice" << endl;
			}
		}
		//Loop again if the choice is not equal to 4
	} while (choice != 4);


}

void readNominationFile(NomineeType nominee[])
{
	ifstream inData;
	inData.open("NominationList.txt");
	for (int i = 0; i < MaxNominees; i++)
	{
		inData >> nominee[i].n_MyKad >> nominee[i].n_StudentID >> nominee[i].program >> nominee[i].yearOfStudy >> nominee[i].vote >> nominee[i].femalevote >> nominee[i].malevote;

	}
	inData >> nominee[5].vote;
	inData.close();
}
void readStudentFile(StudentType student[])
{
	ifstream inData;
	inData.open("RegisterStudent.txt");
	for (int i = 0; i < MaxStudents; i++)
	{
		inData >> student[i].MyKad >> student[i].StudentID >> student[i].nominateChance >> student[i].voteChance;

	}
	inData.close();
}
void updateStudentFile(StudentType student[])
{
	ofstream outData;
	outData.open("RegisterStudent.txt");
	if (!outData)
	{
		cout << "Error opening data file" << endl;
	}
	else
	{
		for (int i = 0; i < MaxStudents; i++)
		{
			outData << student[i].MyKad << " " << student[i].StudentID << " " << student[i].nominateChance << " " << student[i].voteChance << endl;
		}
	}
	outData.close();
}
void updateNominationFile(NomineeType nominee[])
{
	ofstream outData;
	outData.open("NominationList.txt");
	if (!outData)
	{
		cout << "Error opening data file" << endl;
	}
	else
	{
		for (int i = 0; i < MaxNominees; i++)
		{
			outData << nominee[i].n_MyKad << " " << nominee[i].n_StudentID << " " << nominee[i].program << " " << nominee[i].yearOfStudy << " " << nominee[i].vote << " " << nominee[i].femalevote << " " << nominee[i].malevote << endl;
		}
		outData << nominee[5].vote << endl;
	}
	outData.close();
}
int checkDuplicateStudent(StudentType student[], int studentNo)
{
	bool duplicate = false;
	//If the number of students in file is more than zero
	if (studentNo > 0)
	{
		//read from student file
		ifstream inData;
		inData.open("RegisterStudent.txt");

		if (!inData) {
			cout << "Error opening files.";
		}
		else {
			//Loop every students infront of the new students who is being registered
			for (int i = 0; i < studentNo; i++)
			{
				inData >> student[i].MyKad >> student[i].StudentID >> student[i].nominateChance >> student[i].voteChance;

				//If there is a matching of MyKad and StudentID between input and database
				if (strcmp(student[studentNo].MyKad, student[i].MyKad) == 0 || strcmp(student[studentNo].StudentID, student[i].StudentID) == 0)
				{
					//Set duplicate to true
					duplicate = true;
					//Display error message
					cout << "Student entered is a duplicate. Registration failed." << endl << endl;
					break;
				}
				else
				{
					duplicate = false;
				}
			}

		}
		inData.close();
	}
	else
	{
		//Set duplicate to false if the number of students in file is not more than zero
		duplicate = false;
	}


	if (duplicate == true)
		return 1;
	else
		return 0;
}
//Read number of students in file
int readNumStudentsFile()
{
	int number_of_students = 0;
	string line;

	ifstream studentfile("RegisterStudent.txt");
	while (getline(studentfile, line))
		++number_of_students;
	return number_of_students;
}
//Read number of nominees in file
int readNumNomineeFile()
{
	int number_of_nominee = 0;
	string line;

	ifstream nomineefile("NominationList.txt");
	while (getline(nomineefile, line))
		++number_of_nominee;
	return number_of_nominee;
}
void clearStudentFile()
{
	ofstream outData;
	outData.open("RegisterStudent.txt");
	if (!outData)
	{
		cout << "Error opening data file" << endl;
	}

	outData.close();
}
