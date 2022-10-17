#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

static void print_element_names(xmlNode * a_node);

int main()
{	
	xmlDoc *doc = NULL;
	xmlNode *root_element = NULL;
	const char *Filename = "note.xml";
	doc = xmlReadFile(Filename, NULL, 0);

	if (doc == NULL)
	{
		printf("error: could not parse file %s\n", Filename);
	}
	else
	{
		/* Get the root element node*/
		root_element = xmlDocGetRootElement(doc);

		print_element_names(root_element);
		
		/*free the document*/
		xmlFreeDoc(doc);
	}
	/*Free the global variables that may have been allocated by the parser.*/
	xmlCleanupParser();
	
	return (0);
}
/* Recursive function that prints the XML structure */

static void print_element_names(xmlNode * a_node)
{
	xmlNode *cur_node = NULL;
	for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
		if (cur_node->type == XML_ELEMENT_NODE) {
			printf("Node Type: Element, name: %s \n Its children's type is: %d \n Its children's 	content is: %s \n", cur_node->name, cur_node->children->type, cur_node->children->content);
		}
		print_element_names(cur_node->children);
	}
}
