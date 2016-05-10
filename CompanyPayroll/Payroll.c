/**
* CompanyPayroll
*
* FIT ICTAP Procedural Programming Assignment
*
* Author Philip Woulfe
* Version 1.0
* 2016-10-05
* Create a program to calculate company payroll
*/

#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <windows.h>

/* Declare enums */
typedef enum {
	HR = 1,
	IT = 2,
	PRODUCTION = 3,
	SALES_AND_MARKETING = 4
} Department_t;

typedef enum {
	ASSOCIATE = 1,
	SENIOR = 2,
	MANAGER = 3,
} Rate_t;

typedef struct {
	char name[50];
	Department_t dept;
	Rate_t rate;
	bool currentEmployee;

} Employee_t;

/* Display Header */
void displayHeader(void);

/* Clear command screen */
void clearScreen(void);

/* Load text with character delay */
void printText(char *text);

/* Create a new employee*/
void newEmployee(char *name, Department_t dept, Rate_t rate);

/* Changes employee's department */
void changeDept(char *name, Department_t dept);

/* Change employee's pay rate */
void changeRate(char *name, Rate_t rate);

/* Terminate or rehire employees */
void setCurrentEmployee(char *name, bool b);

/* Save current employees to file */
void saveEmployeesToFile(Employee_t empArr[]);

/* Processes wages for employees */
//void processWages(Employee_t empArr[]);
void processWages(); //TODO reimplement previous code


int main(int argc, char* argv[])
{
	clearScreen();
	displayHeader();

	// ensure proper usage
	if (argc != 1)
	{
		printf("Usage: ./payroll (No arguments)\n");
		return 1;
	}

	printText("Loading employee records...\n");

	// remember filenames
	char *infile = "EmployeeList.csv";

	// open input file 
	FILE* inptr = fopen(infile, "r+");
	if (inptr == NULL)
	{
		/* Create message string */
		char *message = "Could not open ";
		char *messageFull = malloc(strlen(message) + 1 + strlen(infile) + "...\n");
		strcpy(messageFull, message);
		strcat(messageFull, infile);
		strcat(messageFull, "...\n");

		printText(messageFull);
		
		printText("Creating File...\n");
		Sleep(2000);
		
		inptr = fopen(infile, "w");
		
		printText("File Created...\n");

		// free memory
		free(messageFull);
	}
	else {
		printText("Employee records loaded...\n");
	}

	processWages();

	clearScreen();
	displayHeader();





	// close infile
	fclose(inptr);



	// temprary to keep program open
	getchar();

	// that's all folks
	return 0;
}

/* Displays the header for the program */
void displayHeader(void) {
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
	printf("*      _        _   _______   __       _____                         *\n");
	printf("*     | |  __  | | |   _   | |  |     |  ___|                        *\n");
	printf("*     | | /  \\ | | |  | |  | |  |     | |_                           *\n");
	printf("*     | |/ /\\ \\| | |  |_|  | |  |___  |  _|                          *\n");
	printf("*     |___/  \\___| |_______| |______| |_|                            *\n");
	printf("*                                                                    *\n");
	printf("*      _____   _____  __   __  _____   _______   __       __    TM   *\n");
	printf("*     |  _  | |  _  | \\ \\ / / |  _  | |   _   | |  |     |  |        *\n");
	printf("*     | |_| | | |_| |  \\   /  | |_| | |  | |  | |  |     |  |        *\n");
	printf("*     |  ___| |  _  |   | |   |  _ <  |  |_|  | |  |___  |  |___     *\n");
	printf("*     |_|     |_| |_|   |_|   |_| |_| |_______| |______| |______|    *\n");
	printf("*                                                                    *\n");
	printf("*                                © Copyright Wolf Accounting 2016    *\n");
	printf(" * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
}

/* Clears the command screen */
void clearScreen(void) {
	system("cls");
}

/* Prints text to console 1 character at a time */
void printText(char *text) {

	for (int i = 0; text[i] != '\0'; i++) {
		printf("%c", text[i]);
		fflush(stdout);
		Sleep(50);
	}

	Sleep(1000);
}

/* Processes wages for employees and save to file */
//void processWages(Employee_t empArr[]) {
void processWages() { //TODO reimplement previous line
	


	// get date
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	char year[5];
	sprintf(year, "%d", tm.tm_year + 1900);

	char month[3];
	sprintf(month, "%d", tm.tm_mon + 1);

	char day[3];
	sprintf(day, "%d", tm.tm_mday);

	// create output file name
	char *outfile = malloc(sizeof("Payroll_" + sizeof(year) + sizeof("-") + sizeof(month) + sizeof("-") + sizeof(day) + sizeof(".csv") + 1));
	
	outfile = strcpy(outfile, "Payroll_");
	
	// add year
	outfile = strcat(outfile, year); 
	outfile = strcat(outfile, "-");
	
	// add month
	outfile = strcat(outfile, month);
	outfile = strcat(outfile, "-");
	// add day
	outfile = strcat(outfile, day);
	outfile = strcat(outfile, ".csv");

	printText("Creating output file...\n");
	
	// create output file
	FILE* outptr = fopen(outfile, "w");
	if (outptr == NULL)
	{
		// TODO reimplement somehow
		//fclose(inptr); 

		// create error message
		char *message = "Could not create ";
		char *messageFull = malloc(strlen(message) + 1 + strlen(outfile) + "...\n");
		strcpy(messageFull, message);
		strcat(messageFull, outfile);
		strcat(messageFull, "...\n");

		printText(messageFull);
		
		Sleep(2000);
		
		printText("Exiting program...\n");
		//fprintf(stderr, "Could not create %s.\n", outfile);
		return 3;
	}
	else {
		printText("Output file created...\n");
	}
	
	// close outfile
	fclose(outptr);
	
	// free memory
	free(outfile);

}