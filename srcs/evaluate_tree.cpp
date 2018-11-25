// ************************************************************************** //
//                                                                            //
//                                                                            //
//   evaluate_tree.cpp                                                        //
//                                                                            //
//   By: Mateo <teorodrip@protonmail.com>                                     //
//                                                                            //
//   Created: 2018/11/22 21:46:03 by Mateo                                    //
//   Updated: 2018/11/25 14:14:36 by Mateo                                    //
//                                                                            //
// ************************************************************************** //

#include "../includes/wiki_scrapping.hpp"


void evaluate_tree(data_t *data, const xlnt::worksheet *ws)
{
  std::string	base_url;
  std::string	url;
  std::string	page_url;
  std::string	page_description;
  std::string	page;
  std::string	keyword;
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
	  keyword = row[0].to_string();
	  url = base_url + keyword;
	  get_search(url, &j_search);
	  update_output("\"" + keyword + "\":[", data);
	  if (j_search.size() >= 4 && (len = j_search[3].size()) > 0)
		{
		  for (i = 0; i < len; i++)
			{
			  page_url = j_search[3][i];
			  page_description = j_search[2][i];
			  update_output("[\"" + page_url + "\",\"" + page_description + "\",[", data);
			  get_page(page_url, &page);
			  parse_container_tree(tree, page.c_str(), page.length(), data);
			  update_output("],", data);
			  exit(1);
			  myhtml_tree_clean(tree);
			}
		}
	  update_output("],", data);
	}
  myhtml_tree_destroy(tree);
  myhtml_destroy(myhtml);
}
