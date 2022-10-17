#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define TextContentSize 50
//functions prototypes
static void openTemplateFile(char templateFileName[]);
static void openVariableFile(char variableFileName[]);
static void compare_data_and_template(xmlNode * rootV_node, xmlNode * rootT_node);
bool isFound(xmlNode * curV_Node, char *tagName);
static void createNewFolder();
static void createNewFile_in_Folder( char * fileContents[], int len);
	//Input variables
    bool isT=false; //for template.xml
    bool isV=false; //for variable.xml
    bool isO=false; //for output folder
    bool isCorrect=true;
	//content holder variables
    char templateParam[50]; //for template.xml or /home/usr...
    char variableParam[50]; //for variable.xml or /home/usr...
    char outputFolderName[25];   //for output folder name 
    char outputFileName[50];   // for outputs file names
    char tagContent[50];
    int count=0;
    int opt;
    int i =0; // for for loops
    struct stat st = {0}; //for creating file 
    static xmlNode * rT_node=NULL; //for templates root element
    static xmlNode * rV_node=NULL; //for variables root element

int main(int argc, char *argv[])
{
    bool isCaseInsensitive = false;

    enum { TEMPLATE,VARIABLE,OUTPUT} inputs;

    while ((opt = getopt(argc, argv, "tvo")) != -1) {
        switch (opt) {
        case 't':
                inputs = TEMPLATE;
		strcpy(templateParam, argv[optind]);
		isT=true;
		 break;
        case 'v': 
        	inputs = VARIABLE;
		strcpy(variableParam, argv[optind]);
		isV=true; 
		break;
        case 'o': 
		inputs = OUTPUT;
		strcpy(outputFolderName, argv[optind]);
		isO=true;
	 	break;
        default:
            fprintf(stderr, "Usage: %s [-tvo] [file...]\n", argv[0]);
            exit(EXIT_FAILURE);
        }//end of switch
	
    }//end of while
	// -t -v -o logical existing control
	if((isT==false) || (isV==false) || (isO==false)){ // if one of them is false, the input is incomplete
		printf("Input format is not compatible ! Please check !\n");
		return 0;
	}
	//opening files
	openVariableFile(variableParam);
	openTemplateFile(templateParam);
	createNewFolder();
	//comparing the both files if true its open a new file in a folder
	compare_data_and_template(rV_node,rT_node);
	
    return 0;
}
static void openTemplateFile(char templateFileName[]){
	xmlDoc *doc = NULL;
	xmlNode *root_element = NULL;
	const char *Filename = templateFileName;
	doc = xmlReadFile(Filename, NULL, 0);

	if (doc == NULL)
	{
		printf("error: could not parse file %s\n", Filename);
	}
	else
	{
		/* Get the root element node*/
		root_element = xmlDocGetRootElement(doc);
		rT_node=root_element;
	}
}
static void openVariableFile(char variableFileName[]){
	xmlDoc *doc = NULL;
	xmlNode *root_element = NULL;
	const char *Filename = variableFileName;
	doc = xmlReadFile(Filename, NULL, 0);

	if (doc == NULL)
	{
		printf("error: could not parse file %s\n", Filename);
	}
	else
	{
		/* Get the root element node*/
		root_element = xmlDocGetRootElement(doc);
		rV_node=root_element;
	}

}

//getting the templates contents for text file and if the node is element node then goes to isfound function to get the content of that element
static void compare_data_and_template(xmlNode * rootV_node, xmlNode * rootT_node){

	char *arrayForTextContents[TextContentSize];
	char *arrayForTagName = malloc(sizeof(char));
	xmlNode *curT_node=NULL;
	xmlNode *curV_node=rootV_node->children->next; // root nodes first two childrrens are text node and then element node  
	//comparing
	do{
		for(curT_node=rootT_node->children; curT_node;curT_node=curT_node->next){ //takes the templates nodes
		
			if(curT_node->type==XML_TEXT_NODE){
				arrayForTextContents[count]=malloc(strlen(curT_node->content));
				strcpy(arrayForTextContents[count],curT_node->content);
			count++;
			}
			else if(curT_node->type==XML_ELEMENT_NODE){
				strcpy(arrayForTagName,curT_node->name);	
				if(isFound(curV_node,arrayForTagName)){
					arrayForTextContents[count]=malloc(strlen(tagContent));
					strcpy(arrayForTextContents[count],tagContent);
					memset(&tagContent[0], 0, sizeof(tagContent));
					count++;		
				}else {isCorrect=false;}
			}
		}
		
		if(isCorrect){ // if everything is true, then make a file in a folder
			createNewFile_in_Folder(arrayForTextContents,count);
		}
		else isCorrect=true;
		curV_node=curV_node->next;
		while(curV_node){ // goes to another siblings in variable file
			if(curV_node->type!=XML_ELEMENT_NODE)
				{curV_node=curV_node->next;}
			else break;
		}
		memset(&arrayForTextContents[0], 0, sizeof(arrayForTextContents)); // resets
		count=0;
	}while(curV_node); 
	
	
}

//looks for a same template tags names with variables one record tags and if same gets the content of that variable
bool isFound(xmlNode * curV_Node, char *tagName){
	xmlAttr *attributes = curV_Node->properties;
	xmlNode *cur_node = NULL;
	strcpy(outputFileName,attributes ->children-> content);
	for (cur_node = curV_Node->children; cur_node; cur_node = cur_node->next) { 
		if (cur_node->type == XML_ELEMENT_NODE) {
			if(!strcmp(cur_node->name,tagName)){
				strcpy(tagContent,cur_node->children->content);
				return true;
			}else if(!strcmp(attributes->name,tagName)){
				strcpy(tagContent,attributes ->children-> content);
				return true;
			}
		}
	}
	return false ;

}

//Create new folder
static void createNewFolder(){
	if (stat(outputFolderName, &st) == -1) {
	    mkdir(outputFolderName, 0755);
	}

	
}

//Creating a file in a Folder 
static void createNewFile_in_Folder( char * fileContents[], int len){
	char *fullFileAddress = malloc(sizeof(char));
	strcpy(fullFileAddress, outputFolderName);
	strcat(fullFileAddress,"/");
	strcat(fullFileAddress,outputFileName); //outs/29800.txt
	FILE *fp = fopen(fullFileAddress, "w");
	if(fp==NULL){printf("ERROR opening file!");return;}
	for(i=0;i<len;i++){
		fprintf(fp,fileContents[i]);	
	}
	fclose(fp);
}


