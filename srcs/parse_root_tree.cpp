// ************************************************************************** //
//                                                                            //
//                                                                            //
//   parse_root_tree.cpp                                                      //
//                                                                            //
//   By: Mateo <teorodrip@protonmail.com>                                     //
//                                                                            //
//   Created: 2018/11/23 14:44:58 by Mateo                                    //
//   Updated: 2018/11/24 21:28:29 by Mateo                                    //
//                                                                            //
// ************************************************************************** //

#include "../includes/wiki_scrapping.hpp"
#include <myhtml/api.h>

static void print_tree(myhtml_tree_t* tree, myhtml_tree_node_t *node, data_t *data)
{
  sentence_t sentence = {"", 0, false};
  myhtml_tag_id_t tag_id;

  while (node)
    {
	  tag_id = myhtml_node_tag_id(node);
	  if(tag_id == MyHTML_TAG__TEXT || tag_id == MyHTML_TAG__COMMENT) {
		sentence.doc += myhtml_node_text(node, NULL);
		extract_sentence(&sentence, data->end_char, data);
	  }
	  // print children
	  print_tree(tree, myhtml_node_child(node), data);
	  node = myhtml_node_next(node);
    }
}

void parse_root_tree(myhtml_tree_t *tree, const char *page, const size_t page_len, data_t *data)
{
  myhtml_tree_node_t *node;

  myhtml_parse(tree,
			   MyENCODING_UTF_8,
			   page,
			   page_len);
  node = myhtml_tree_get_document(tree);
  print_tree(tree, myhtml_node_child(node), data);
}
