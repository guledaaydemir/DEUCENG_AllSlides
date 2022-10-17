#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


int personNumber;//how many person that we have in person* person
bool isWelcome; // for dirty flag 

typedef struct _Person {
	int index;
	bool isDelete;
	char name[20];
	char surname[10];
	char address[10];
	char addNote[10];
}Person;


int comparePersons(const void* a, const void* b){ //comparing PK name and surname
	int nameCompare= (strcmp(((Person*)a)->name, ((Person*)b)->name));
	if(nameCompare==0)
		return (strcmp(((Person*)a)->surname, ((Person*)b)->surname));
	else
		return nameCompare;
}

void listRecords(Person * person){//lists the record by person 
	char letter[1];	
	printf("Please enter a letter:");
	scanf("%s",letter);
	letter[0]=toupper(letter[0]); //needs to be upper letter, or ascıı code changes..
	int count=0;
	int i =0;
	for(i=0;i<personNumber;i++){
		if(person[i].name[0]==letter[0]){
			printf("...........\nname :%s\nsurname: %s\nhome: %s\nadditional note: %s\n",person[i].name,person[i].surname,person[i].address,person[i].addNote);
		count++;
		}
	}
	printf("-------\n");
	if(count==0) printf("there is no data with starting %c\n",letter[0]);
}

void findRecord(Person* person){//finding the record by index number
	int b;
	printf("Enter index =>");
	scanf("%d",&b);
	int a ;
	bool isFound=false;
	for(a=0;a<personNumber;a++){
		if(person[a].index==b && person[a].isDelete==false){
			printf("...........\nname :%s\nsurname: %s\nhome: %s\nadditional note: %s\n..........\n",person[a].name,person[a].surname,person[a].address,person[a].addNote); isFound=true;}	
	}
	if(!isFound) printf("There is no data with primary key %d",b);
}
void addNewRecord(Person* person){//adding a new record to person array and at the end of the data file
	char nameX[20];
	char surnameX[10];
	char addressX[10];
	char addX[10];
	bool isFound=false;
	printf("ADDING A NEW RECORD\n------------\n");
	printf("Enter name:");
	scanf("%s",&nameX);
	nameX[0]=toupper(nameX[0]);
	printf("Enter surname:");
	scanf("%s",&surnameX);
	surnameX[0]=toupper(surnameX[0]);
	printf("Enter address:");
	scanf("%s",&addressX);
	printf("Enter addNote:");
	scanf("%s",&addX);
	//control for same name & surname
	int a;
	for(a=0;a<personNumber;a++){
		if(!(strcmp(person[a].name,nameX)) && !(strcmp(person[a].surname,surnameX)) && person[a].isDelete==false){
			printf("\n\nERROR ADDING A NEW RECORD ALLREADY EXISTS\n");
			printf("...........\nname :%s\nsurname: %s\nhome: %s\nadditional note: %s\n..........\n",person[a].name,person[a].surname,person[a].address,person[a].addNote);
			isFound=true;}
	}
	//if there is not have the same name and surname we add it 
	if(!isFound){
		FILE * indexFile=fopen("index.dat","wb");
		if(!indexFile) return;
		fseek(indexFile,0,SEEK_SET);
		fputs("*",indexFile);
		FILE * dataFile=fopen("data.dat","ab");
		if(!dataFile) { return;}
		
		strcpy(person[personNumber].name,nameX);
		strcpy(person[personNumber].surname,surnameX);
		strcpy(person[personNumber].address,addressX);
		strcpy(person[personNumber].addNote,addX);
		person[personNumber].index=personNumber;
		person[personNumber].isDelete=false;
		
		fwrite(&person[personNumber],sizeof(Person),1,dataFile);
		personNumber++;
		fclose(dataFile);
		fclose(indexFile);
		
		isWelcome=false;
		printf("\n---Added Succesfully---\n");
	}

}
int fsize(FILE *fp){ // getting the size of file to find the how many data file has person struct
	int prev=ftell(fp);
	fseek(fp, 0L, SEEK_END);
	int sz=ftell(fp);
	fseek(fp,prev,SEEK_SET); //go back to where we were
	return sz;
}

void makeArray(Person * person){ // making the new Person array looking to data file
	FILE* dataFile =fopen("data.dat","rb");
	if(!dataFile) printf("HATA");
	fseek(dataFile,0,SEEK_SET);
	int size=fsize(dataFile);
	size=size/sizeof(Person);
	personNumber=size;
	int i;
	for(i=0; i<personNumber; i++){	
		fread(&person[i],sizeof(Person),1,dataFile);
		fseek(dataFile,sizeof(Person),SEEK_CUR);
	}
	fclose(dataFile);
}
void writeToIndexFile(Person* person){ // at the end of the properly closing the terminal we can see our data in idex file by order.
	FILE* indexFile = fopen ("index.dat","ab+");
	if(!indexFile) return;

	fseek(indexFile, 0, SEEK_SET);
	int j =0;
	for(j=0;j<personNumber;j++){
		fputs(person[j].name,indexFile);
		fputs(" ",indexFile);
		fputs(person[j].surname,indexFile);
		fputs(" ",indexFile);
		fprintf(indexFile, "%d", person[j].index); 
		fputs("\n",indexFile);
	}

	fclose(indexFile);
}void updateData(Person * person ){ // updating the data file when the case update or delete selected if we closed program too
	FILE * dataFile = fopen ("data.dat","rb+");
	if(!dataFile) return;
	//making a new person array from data file
	Person* person2=malloc(sizeof(Person));
	int size=fsize(dataFile);
	size=size/sizeof(Person);
	int oldData=size;
	int a;
	for(a=0; a<oldData; a++){	
		fread(&person2[a],sizeof(Person),1,dataFile);
		fseek(dataFile,sizeof(Person),SEEK_CUR);
	}

	//comparing the ram array and the data file array to update datafile
	int i;
	int j;
	bool isFound=false;
	
	for(i=0; i<oldData; i++){	
		fseek(dataFile, 0, SEEK_SET);
		fread(&person2[j],sizeof(Person),1,dataFile);
		for(j=0;j<personNumber;j++){
			
			if(person2[i].index==person[j].index) { // if we found the same index, we update it.
				strcpy(person2[i].name,person[j].name);
				strcpy(person2[i].surname,person[j].surname);
				strcpy(person2[i].address,person[j].address);
				strcpy(person2[i].addNote,person[j].addNote);
				person2[i].isDelete=false;
				fwrite(&person2[i],sizeof(Person),1,dataFile);
				isFound=true;
			}
			
		}
		if(!isFound){ //if we can not found from ram array, thats mean that person is deleted. so we say data file that that person is deleted.
			person2[i].isDelete=true;
			fwrite(&person2[i],sizeof(Person),1,dataFile);
		}
		fseek(dataFile,sizeof(Person),SEEK_CUR);
		isFound=false;
	}
	fclose(dataFile);
	
}
void checkDirtyFlag(Person * person){
	FILE* indexFile = fopen("index.dat","rb+");
	if(!indexFile) return ;
	rewind(indexFile);
	char c;
	if(!feof(indexFile)){
		c = fgetc (indexFile);
		if(c=='*' && isWelcome) {// closed but we need to make new array from datafile

			makeArray(person);
			fseek(indexFile,-1,SEEK_CUR);
			fputs("-",indexFile);
			isWelcome=false;
		} 
		else if (c=='*' && !isWelcome){ // going to close properly, we need to update the data
		fseek(indexFile,-1,SEEK_CUR);
		fputs("-",indexFile);
		writeToIndexFile(person);
		updateData(person);
		} 
		else if (c=='-' && isWelcome){ // closed properly making array from data file 
		makeArray(person);              // I get segmentation here? but it works other computers
		isWelcome=false;
		}
	}
	else if(isWelcome) { // if its the first time that we are running the program
		fseek(indexFile,0,SEEK_SET);
		fputs("-",indexFile);
		isWelcome=false;
	}
	fclose(indexFile);
}


void printArray(Person* person){//printing array after sorting the person aray..
	qsort(person, personNumber, sizeof(Person), comparePersons);
	int a;
	if(personNumber==0) printf("\n\nWelcome.. Please add data \n");
	else{
		for(a=0;a<personNumber ;a++){
			if(person[a].isDelete==false){
				printf("%s %s %d\n",person[a].name,person[a].surname,person[a].index);
			}

		}
	}
}
void printUpdate(int* answer){ //menu for which part of the data the user want to change

	//print the user menu
	printf("\nSelect which option do you want to change \n");
	printf("(1) name \n");
	printf("(2) surname \n");
	printf("(3) home \n");
	printf("(4) additional note \n");
	printf("(5) Return menu\n");	
	printf("Enter Your Choice: \n");
	scanf("%d",answer);
}
void updateRecord(Person* person){ // updating the ram array with the menu 
	char nameX[20];
	char surnameX[10];
	char addressX[10];
	char addX[10];
	bool isFound=false;
	bool isChange=false;
	int b;
	printf("Enter index =>");
	scanf("%d",&b);
	int a ;
	for(a=0;a<personNumber;a++){
		if(person[a].index==b) //if found we can update it
		{
			isFound=true;
			int answer;
			ab:
			printUpdate(&answer);
			while(answer>5 || answer<1)
			{
				printf("\nEnter a valid choice by pressing ENTER key again");
				printUpdate(&answer);
			}

			switch(answer)
			{
				case 1: printf("\nEnter new name:");
					scanf("%s",&nameX);
					nameX[0]=toupper(nameX[0]);
					strcpy(person[a].name,nameX);
					isChange=true;
					goto ab;
					break;
				case 2: printf("\nEnter new surname:");
					scanf("%s",&surnameX);
					surnameX[0]=toupper(surnameX[0]);
					strcpy(person[a].surname,surnameX);
					isChange=true;
					goto ab;
					break;
				case 3: printf("\nEnter new address:");
					scanf("%s",&addressX);
					strcpy(person[a].address,addressX);
					isChange=true;
					goto ab;
				        break;
				case 4: printf("\Enter new additional note");
					scanf("%s",&addX);
					strcpy(person[a].addNote,addX); 
					isChange=true;
				        goto ab;
					break;	
				case 5: printf("Returning the Main Menu \n");
					break;
			}
		}
	}
	if(!isFound) printf("There is no data with primary key %d",b);

}

void deleteRecord(Person* person){ // deleting from the ram array.. data file deletion will be end of the program
	int b;
	printf("Enter primary key =>");
	scanf("%d",&b);
	int a ;
	bool isFound=false;
	for(a=0;a<personNumber;a++){
		if(person[a].index==b)
		{
			isFound=true;
			person[a]=person[personNumber];// adding the last one here and sort it again in printArray // dont need to shift
			personNumber--;
			printf("\n---- Deleted Succesfully----\n");
			break;
		}	
	}
	if(!isFound) printf("There is no data with primary key %d",b);
}

void printMenu(int* answer){

	//print the user menu
	printf("\nMy address Book Application \n");
	printf("Main Menu\n");
	printf("==========\n");
	printf("(1) Add New Record \n");// DONE 
	printf("(2) Update A Record \n");//DONE 
	printf("(3) Delete Record \n"); // DONE 
	printf("(4) Find Record \n");	//DONE
	printf("(5) List.Records \n");	//DONE
	printf("(6) Quit \n");		//DONE
	printf("Enter Your Choice: \n");
	scanf("%d",answer);
}
int main(){
	isWelcome=true;
	int answer;
	personNumber=0;
	Person *personArray=malloc(sizeof(Person));
	
	checkDirtyFlag(personArray);
	ab:
	printArray(personArray);
	printMenu(&answer);
	isWelcome=false;
	while(answer>6 || answer<1)
	{
		printf("\nEnter a valid choice by pressing ENTER key again");
		printMenu(&answer);
	}

	switch(answer)
	{
		case 1: addNewRecord(personArray);
			goto ab;
			break;
		case 2: updateRecord(personArray);
			goto ab;
			break;
		case 3: deleteRecord(personArray);
			goto ab;
                        break;
		case 4: findRecord(personArray); 
                        goto ab;
			break;	
		case 5:	
			listRecords(personArray); //enters A
                        goto ab;
			break;	
		case 6: checkDirtyFlag(personArray);
			printf("Program is terminating \n");
			break;
	}
	return 0;
}