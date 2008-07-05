/* Using XML in Vala Sample Code */

using GLib;
using Xml;

public errordomain XmlError {
    FILE_NOT_FOUND,
    XML_DOCUMENT_EMPTY
}

public class XmlSample : GLib.Object {
    //line indentation
    private uint indent = 0;

    public void print_indent (string node_name, string node_content, char token = '+') {
        string str_indent = string.nfill(this.indent * 2, ' ');
        stdout.printf("%s%c%s: %s\n", str_indent, token, node_name, node_content);
    }

    public void parse_file (string path) throws XmlError {
        //parse the document from path
        Xml.Doc* xml_doc = Parser.parse_file (path);
        if (xml_doc == null) {
            throw new XmlError.FILE_NOT_FOUND ("file "+ path + " not found or permissions missing");
        }

        //get the root node. notice the dereferencing operator -> instead of .
        Xml.Node* root_node = xml_doc->get_root_element ();
        if (root_node == null) {
            //free the document manually before throwing because the garbage collector can't work on pointers
            delete xml_doc;
            throw new XmlError.XML_DOCUMENT_EMPTY ("the xml'"+ path + "' is empty");
        }

        print_indent ("XML document", path, '-');

        //get the root node's name
        string root_node_name = root_node->name;
        print_indent ("Root node", root_node_name);

        //let's parse those nodes
        parse_node (root_node);

        //free the document
        delete xml_doc;
    }

    public void parse_node (Xml.Node* node) {
        this.indent++;
        //loop over the passed node's children
        for (Xml.Node* iter = node->children; iter != null; iter = iter->next) {
            //spaces btw. tags are also nodes, discard them
            if (iter->type != ElementType.ELEMENT_NODE)
                continue;

            string node_name = iter->name; //get the node's name
            string node_content = iter->get_content (); //get the node's content with <tags> stripped
            print_indent (node_name, node_content);

            //now parse the node's properties (attributes) ..
            parse_properties(iter);

            //followed by its children nodes
            parse_node(iter);
        }
        this.indent--;
    }

    public void parse_properties (Xml.Node* node) {
        //loop over the passed node's properties (attributes)
        for (Xml.Attr* prop = node->properties; prop != null; prop = prop->next) {
            string attr_name = prop->name;

             //notice the ->children which points to a Node* (Attr doesn't feature content)
            string attr_content = prop->children->content;
            print_indent (attr_name, attr_content, '|');
        }
    }

    public static int main (string[] args) {
        if (args.length != 2) {
            stderr.printf ("Argument required!\n");
            return 1;
        }

        var sample = new XmlSample ();

        //initialisation, not instantiation since the parser is a static class
        Parser.init ();

        try {
            //parse the file listed in the first passed argument
            sample.parse_file (args[1]);
        }
        catch (XmlError err) {
            //print errors while parsing
            stderr.printf ("error: %s\n", err.message);
        }
        finally {
            //do the parser cleanup to free the used memory
            Parser.cleanup ();
        }
        return 0;
    }
}