// ************************************************************************** //
//                                                                            //
//                                                                            //
//   main.cpp                                                                 //
//                                                                            //
//   By: Mateo <teorodrip@protonmail.com>                                     //
//                                                                            //
//   Created: 2018/11/20 10:28:41 by Mateo                                    //
//   Updated: 2018/11/21 22:05:13 by Mateo                                    //
//                                                                            //
// ************************************************************************** //

#include "../includes/wiki_scrapping.hpp"
#include <boost/regex.hpp>
#include <myhtml/api.h>

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  xlnt::workbook wb;
  xlnt::worksheet	ws;
  json j_search;
  std::string url;
  std::string page;
  boost::regex exp("[,\n\\.][^,\\.\n]*[[:digit:]][^,\n\\.]*[,\n\\.]");
  boost::smatch match;

  myhtml_t* myhtml = myhtml_create();
  myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
  myhtml_tree_t* tree = myhtml_tree_create();
  myhtml_tree_init(tree, myhtml);

  wb.load(FILE_PATH);
  ws = wb.active_sheet();
  //Search for all keywords, may be is possible to do it in just 1 request?
  for (auto row : ws.rows())
	{
	  url = BASE_URL + row[0].to_string();
	  get_search(url, &j_search);
	  get_page(j_search[3][0], &page);
	  myhtml_parse(tree, MyENCODING_UTF_8, page.c_str(), page.length());
	  myhtml_collection_t *collection = myhtml_get_nodes_by_name(tree, NULL, "p", 1, NULL);

	  if (collection && collection->list && collection->length)
		{
		  myhtml_tree_node_t *text_node;
		  myhtml_tree_node_t *text_node_child;
		  char* text;
		  for (size_t i = 0; i < collection->length; i++)
			{
			  text_node = myhtml_node_child(collection->list[i]);
			  while (text_node)
				{
				  text = (char *)myhtml_node_text(text_node, NULL);
				  if (text)
					std::cout << "Res: " << text << "\n";
				  if ((text_node_child = myhtml_node_child(text_node)))
					{
					  text = (char *)myhtml_node_text(text_node_child, NULL);
					  if (text)
						std::cout << "Res: " << text << "\n";

					}
				  text_node = myhtml_node_next(text_node);
				}
			}
		}

	  // if(collection && collection->list && collection->length) {
      //   myhtml_tree_node_t *text_node = myhtml_node_child(collection->list[2]);

      //   if(text_node) {
	  // 	  const char* text = myhtml_node_text(text_node, NULL);

	  // 	  if(text)
	  // 		printf("Title: %s\n", text);
	  // 	}
	  // }


	  // try {
	  // 	boost::sregex_iterator next(page.begin(), page.end(), exp);
	  // 	boost::sregex_iterator end;
	  // 	while (next != end) {
	  // 	  boost::smatch match = *next;
	  // 	  std::cout<< "Res: \n" << match.str() << "\n\n";
	  // 	  next++;
	  // 	}
	  // } catch (boost::regex_error& e) {
	  // 	// Syntax error in the regular expression
	  // }
	  exit(1);
	}
}
