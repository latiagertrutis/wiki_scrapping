// ************************************************************************** //
//                                                                            //
//                                                                            //
//   parse_root_tree.cpp                                                      //
//                                                                            //
//   By: Mateo <teorodrip@protonmail.com>                                     //
//                                                                            //
//   Created: 2018/11/23 14:44:58 by Mateo                                    //
//   Updated: 2018/11/23 14:59:08 by Mateo                                    //
//                                                                            //
// ************************************************************************** //

#include <myhtml/api.h>

static void print_node_attr(myhtml_tree_node_t *node)
{
    myhtml_tree_attr_t *attr = myhtml_node_attribute_first(node);

    while (attr) {
        const char *name = myhtml_attribute_key(attr, NULL);

        if(name) {
            printf(" %s", name);

            const char *value = myhtml_attribute_value(attr, NULL);

            if(value)
                printf("=\"%s\"", value);
        }

        attr = myhtml_attribute_next(attr);
    }
}

static void print_tree(myhtml_tree_t* tree, myhtml_tree_node_t *node, size_t inc)
{
    while (node)
    {
        for(size_t i = 0; i < inc; i++)
            printf("\t");

        // print current element
        const char *tag_name = myhtml_tag_name_by_id(tree, myhtml_node_tag_id(node), NULL);

        if(tag_name)
            printf("<%s", tag_name);
        else
            // it can not be
            printf("<!something is wrong!");

        // print node attributes
        print_node_attr(node);

        if(myhtml_node_is_close_self(node))
            printf(" /");

        myhtml_tag_id_t tag_id = myhtml_node_tag_id(node);

        if(tag_id == MyHTML_TAG__TEXT || tag_id == MyHTML_TAG__COMMENT) {
            const char* node_text = myhtml_node_text(node, NULL);
            printf(">: %s\n", node_text);
        }
        else {
            printf(">\n");
        }

        // print children
        print_tree(tree, myhtml_node_child(node), (inc + 1));
        node = myhtml_node_next(node);
    }
}

void parse_root_tree(myhtml_tree_t *tree, const char *page, const size_t page_len)
{
  myhtml_tree_node_t *node;

  myhtml_parse(tree,
			   MyENCODING_UTF_8,
			   page,
			   page_len);
  node = myhtml_tree_get_document(tree);
  print_tree(tree, myhtml_node_child(node), 0);
}
