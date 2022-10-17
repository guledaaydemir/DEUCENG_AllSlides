#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int
main(int argc, char **argv)
{
	xmlDocPtr doc = NULL;	/* document pointer */
	xmlNodePtr root_node = NULL, node = NULL, node1 = NULL;/* node pointers */
	xmlDtdPtr dtd = NULL;	/* DTD pointer */
	char buff[256];
	int i, j;

	/* Creates a new document, a node and set it as a root node */
	doc = xmlNewDoc(BAD_CAST "2.0");
	root_node = xmlNewNode(NULL, BAD_CAST "root");
	xmlDocSetRootElement(doc, root_node);

	/* xmlNewChild() creates a new node, which is "attached" as child node of root_node node. */
	xmlNewChild(root_node, NULL, BAD_CAST "node1",
	BAD_CAST "content of node 1");
	
	/* The same as above, but the new child node doesn't have a content */
	xmlNewChild(root_node, NULL, BAD_CAST "node2", NULL);

	/* xmlNewProp() creates attributes, which is "attached" to an node. It returns xmlAttrPtr, which isn't used here. */
	node = xmlNewChild(root_node, NULL, BAD_CAST "node3",BAD_CAST "this node has attributes");
	xmlNewProp(node, BAD_CAST "attribute", BAD_CAST "yes");
	xmlNewProp(node, BAD_CAST "foo", BAD_CAST "bar");

	/* Here goes another way to create nodes. xmlNewNode() and xmlNewText creates a node and a text node separately. They are "attached" by xmlAddChild() */
	node = xmlNewNode(NULL, BAD_CAST "node4");
	node1 = xmlNewText(BAD_CAST "other way to create content (which is also a node)");
	xmlAddChild(node, node1);
	xmlAddChild(root_node, node);

	/* A simple loop that "automates" nodes creation */
	for (i = 5; i < 7; i++) {
		sprintf(buff, "node%d", i);
		node = xmlNewChild(root_node, NULL, BAD_CAST buff, NULL);
		for (j = 1; j < 4; j++) {
			sprintf(buff, "node%d%d", i, j);
			node1 = xmlNewChild(node, NULL, BAD_CAST buff, NULL);
			xmlNewProp(node1, BAD_CAST "odd", BAD_CAST((j % 2) ? "no" : "yes"));
		}
	}

	/* Dumping document to stdio or file */
	xmlSaveFormatFileEnc(argc > 1 ? argv[1] : "-", doc, "UTF-8", 1);

	/*free the document */
	xmlFreeDoc(doc);

	/*Free the global variables that may have been allocated by the parser. */
	xmlCleanupParser();

	xmlMemoryDump();
	return(0);
}
