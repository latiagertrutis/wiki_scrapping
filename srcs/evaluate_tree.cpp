// ************************************************************************** //
//                                                                            //
//                                                                            //
//   evaluate_tree.cpp                                                        //
//                                                                            //
//   By: Mateo <teorodrip@protonmail.com>                                     //
//                                                                            //
//   Created: 2018/11/22 21:46:03 by Mateo                                    //
//   Updated: 2018/11/22 22:15:58 by Mateo                                    //
//                                                                            //
// ************************************************************************** //

#include "../includes/wiki_scrapping.hpp"
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

void evaluate_tree(const data_t *data, const xlnt::worksheet *ws)
{
  (void)data;
  std::string	base_url;
  std::string	url;
  std::string	page_url;
  std::string	page;
  json			j_search;
  unsigned int  i;
  size_t len;
  myhtml_t* myhtml = myhtml_create();
  myhtml_tree_t* tree = myhtml_tree_create();
  myhtml_tree_node_t *node;

  myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
  myhtml_tree_init(tree, myhtml);
  base_url = BASE_URL + std::to_string(data->search_limit) + "&search=";
  for (auto row : ws->rows())
	{
	  url = base_url + row[0].to_string();
	  get_search(url, &j_search);
	  if (j_search.size() < 4 || (len = j_search[3].size()) <= 0)
		continue ;
	  for (i = 0; i < len; i++)
		{
		  page_url = j_search[3][i];
		  get_page(page_url, &page);
		  myhtml_parse(tree,
					   MyENCODING_UTF_8,
					   page.c_str(),
					   page.length());
		  node = myhtml_tree_get_document(tree);
		  print_tree(tree, myhtml_node_child(node), 0);
		  exit(1);
		  myhtml_tree_clean(tree);
		}
	  std::cout <<"\n";
	}
  myhtml_tree_destroy(tree);
  myhtml_destroy(myhtml);
}
