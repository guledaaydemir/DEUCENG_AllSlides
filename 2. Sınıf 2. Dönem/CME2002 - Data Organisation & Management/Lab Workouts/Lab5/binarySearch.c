#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define RECORD_COUNT 10



struct _Person {
	char name[22];
	char ID[10];
	float score1;
	float score2;
	float score3;
};

typedef struct _Person Person;

typedef struct _SearchReturnData
{
	Person personData;
	int index;
} SearchReturnData;


int personNumber;
int comparePersons(const void* a, const void* b){
	return (strcmp(((Person*)a)->ID, ((Person*)b)->ID));
}

float avg(const Person p){
	return (p.score1+p.score2+p.score3)/3;
}

void generateRandomString(char* target, char* dictionary, int maxLength, int minLength){
	int length = minLength + rand()%(maxLength-minLength);
	int dictLength = strlen(dictionary);
	int i;
	for(i=0; i<length; i++){
		int dictIdx = rand()%dictLength;
		target[i] = dictionary[dictIdx];
	}
		
	.............
}

void generatePerson(Person* person){
	generateRandomString(person->name, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 22, 5);
	generateRandomString(person->ID,"0123456789",10,9);
	person->score1 = rand()%100;
	person->score2 = rand()%100;
	person->score3 = rand()%100;
	//printf("name is %s, id is %s, score1 is:%f \n", person->name, person->ID, person->score1);
}



void generateRandomSortedDataFile(){
	srand(time(NULL));
	FILE* fp;
	fp = fopen("randomdata.dat", "wb");
	if(!fp)
		return;
	Person person[RECORD_COUNT];
	int i;
	for(i=0; i<RECORD_COUNT; i++){
		generatePerson(&person[i]);
	}
	qsort(person, RECORD_COUNT, sizeof(Person), comparePersons);
	
	printf("Writing %d bytes. Second record's ID is:%s.\n", sizeof(Person)*RECORD_COUNT, person[1].ID);
		
	fseek(fp, 0, SEEK_SET);
	fwrite(person, sizeof(Person), RECORD_COUNT, fp);
	fclose(fp);

}

SearchReturnData binaryFileSearch(FILE* fp, const char ID[10], int firstIdx, int lastIdx){
	printf("Running Binary Search %d %d\n", firstIdx, lastIdx);
	Person first, last, middle;
	SearchReturnData returnData;
	
	// Calculate the middle Index
	int middleIdx = ...............;

	// Read first record and return if it is the searched one.
	fseek(fp, firstIdx*(sizeof(Person)), SEEK_SET);
	fread(.....................................);
	if(strcmp(first.ID,ID) == 0)
	{
		returnData.personData = first;
		returnData.index = firstIdx;
		return returnData;
	}
	// Read last record and return if it is the searched one.
	fseek(fp, lastIdx*sizeof(Person), SEEK_SET);
	fread(........................................);
	if(strcmp(last.ID,ID) == 0)
	{
		returnData.personData = last;
		returnData.index = lastIdx;
		return returnData;
	}
	// Recursion exit condition, If middle index is equal to first or last index
	// required comparisons are already made, so record is not found.
	// Create and return an empty person.
	if(middleIdx==firstIdx || middleIdx == lastIdx) {
		SearchReturnData d;
		return d;
	}

	// Read the middle record and return if it is the searched one.
	fseek(.....................................);
	fread(&middle, sizeof(Person), 1, fp);
	if(strcmp(middle.ID,ID) == 0)
	{
		returnData.personData = middle;
		returnData.index = middleIdx;
		return returnData;
	}
	// Determine the record position and recursively call with appropriate attributes.
	if(strcmp(middle.ID,ID)>0) {
		return binaryFileSearch(....................................);
	} 
	else {
		return binaryFileSearch(....................................);
	}
}

SearchReturnData findRecordByID(char ID[10]) {
    // Open the file
    FILE* inputFile;
    inputFile = fopen("randomdata.dat", "rb");

    // Calculate initial first and last indexes.
    int firstIdx = 0;
	
    fseek(............................);
    int lastIdx = (ftell(inputFile)/sizeof(Person))-1;

    // Initiate the search.
    SearchReturnData result = binaryFileSearch(inputFile, ID, firstIdx, lastIdx);
    fclose(inputFile);
    return result;
}

void printFile()
{
	printf("personNumber: %d\n", personNumber);
	FILE* inputFile;
    	inputFile = fopen("randomdata.dat","rb");
	fseek(inputFile, 0, SEEK_SET);
	int i;	    
	for(i=0;i<personNumber;i++)
        {
		Person bufferPerson;
		fread(&bufferPerson,sizeof(Person),1,inputFile);
		printf("name is %s, id is %s, score1 is:%f \n", bufferPerson.name, bufferPerson.ID, bufferPerson.score1);
		
	}
	fclose(inputFile);
}

void deleteRecordByID(SearchReturnData *whoData) 
{
    // Open the file
    FILE* inputFile;
    inputFile = fopen("randomdata.dat", "rb+");
printf("----------------------- deletetion\n");
    fseek(inputFile, 0, SEEK_SET);
    fseek(inputFile, (whoData->index)*sizeof(Person), SEEK_SET);
    int i;	
    for(i=whoData->index+1;i<personNumber;i++)
    {
		...................................
    } 
    personNumber--;
    fclose(inputFile);
}

void printMenu(int* answer){

	//print the user menu
	printf("You can perform the following tasks: \n");
	printf("(1) Generate Sorted Random Data File \n");
	printf("(2) Find Record by ID \n");
	printf("(3) Delete Record by ID \n");
	printf("(4) List File Data \n");
	printf("-------------------------------------\n");
	printf("(5) Quit \n");
	printf("Please Select one... \n");
	scanf("%d",answer);
}

int main(){

	int answer;
	SearchReturnData who;
	personNumber = RECORD_COUNT;
	
	ab:
        
	//print the user menu and read user answer
	printMenu(&answer);

	while(answer>5 || answer<1)
	{
		printf("\nEnter a valid choice by pressing ENTER key again");
		printMenu(&answer);
	}

	switch(answer)
	{
		case 1: generateRandomSortedDataFile();
			printFile();
			goto ab;
			break;
		case 2: printf("Enter the id that you want to search :");
			char id[10];
			scanf("%s", id);
			who = findRecordByID(id);
			
			printf("---Person of interest--- \n name is: %s \n ID is: %s index is %d \n", who.personData.name, who.personData.ID,who.index);
			goto ab;
			break;
		case 3: printf("Enter the id that you want to delete:");
			char id2[10];
			scanf("%s", id2);
			//printFile();
			who = findRecordByID(id2);
			printf("----------------------------");
			//printFile();
				printf("Person %s with %s has been found in the list with index %d\n",who.personData.name,who.personData.ID,who.index);
				deleteRecordByID(&who);
			printf("after deletion---------------");			
			printFile();
			goto ab;
                        break;
		case 4: printf("List of the sorted File \n");
			printFile();
                        goto ab;
			break;	
			
			
		case 5: printf("Program is terminating \n");
			break;
	}

}
