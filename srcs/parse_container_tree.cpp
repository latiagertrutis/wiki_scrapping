// ************************************************************************** //
//                                                                            //
//                                                                            //
//   parse_container_tree.cpp                                                 //
//                                                                            //
//   By: Mateo <teorodrip@protonmail.com>                                     //
//                                                                            //
//   Created: 2018/11/25 13:57:41 by Mateo                                    //
//   Updated: 2018/11/26 01:00:51 by Mateo                                    //
//                                                                            //
// ************************************************************************** //

#include "../includes/wiki_scrapping.hpp"
#include <myhtml/api.h>

static void print_tree(myhtml_tree_t* tree, myhtml_tree_node_t *node, data_t *data, sentence_t *sentence, unsigned int depth)
{
  myhtml_tag_id_t tag_id;

  if (depth <= 0)
	return ;
  while (node)
    {
	  tag_id = myhtml_node_tag_id(node);
	  if(tag_id == MyHTML_TAG__TEXT || tag_id == MyHTML_TAG__COMMENT) {
		sentence->doc += myhtml_node_text(node, NULL);
		extract_sentence(sentence, data->end_char, data);
	  }
	  // print children
	  print_tree(tree, myhtml_node_child(node), data, sentence, depth - 1);
	  node = myhtml_node_next(node);
    }
}

void parse_container_tree(myhtml_tree_t *tree, const char *page, const size_t page_len, data_t *data)
{
  myhtml_collection_t *col;
  size_t i;
  sentence_t sentence = {"", 0, false};

  myhtml_parse(tree,
			   MyENCODING_UTF_8,
			   page,
			   page_len);
  col = NULL;
  if (!(col = myhtml_get_nodes_by_name(tree, NULL, data->container.c_str(), data->container.length(), NULL)))
	return ;
  for (i = 0; i < col->length; i++)
	print_tree(tree, myhtml_node_child(col->list[i]), data, &sentence, data->recursion);
  myhtml_collection_destroy(col);
}
