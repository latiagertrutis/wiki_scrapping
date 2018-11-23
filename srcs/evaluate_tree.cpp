// ************************************************************************** //
//                                                                            //
//                                                                            //
//   evaluate_tree.cpp                                                        //
//                                                                            //
//   By: Mateo <teorodrip@protonmail.com>                                     //
//                                                                            //
//   Created: 2018/11/22 21:46:03 by Mateo                                    //
//   Updated: 2018/11/23 15:03:32 by Mateo                                    //
//                                                                            //
// ************************************************************************** //

#include "../includes/wiki_scrapping.hpp"


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
		  parse_root_tree(tree, page.c_str(), page.length());
		  exit(1);
		  myhtml_tree_clean(tree);
		}
	  std::cout <<"\n";
	}
  myhtml_tree_destroy(tree);
  myhtml_destroy(myhtml);
}
