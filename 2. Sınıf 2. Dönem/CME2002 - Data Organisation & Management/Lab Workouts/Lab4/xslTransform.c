#include <string.h>
#include <libxslt/transform.h>


int main(int argc, char **argv) {

        const char  *XMLFile = "collection.xml";
        const char  *XSLFile = "collection.xsl";

	xsltStylesheetPtr cur = NULL;
	xmlDocPtr doc, res;

	cur = xsltParseStylesheetFile((const xmlChar *)XSLFile);
	doc = xmlParseFile(XMLFile);
	res = xsltApplyStylesheet(cur, doc, NULL);
        
	xsltSaveResultToFile(argc > 1 ? (fopen(argv[1], "w")) : stdout, res, cur); 

	xsltFreeStylesheet(cur);
	xmlFreeDoc(res);
	xmlFreeDoc(doc);

        xsltCleanupGlobals();
        xmlCleanupParser();
	return(0);

}

