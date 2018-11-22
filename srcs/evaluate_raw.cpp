// ************************************************************************** //
//                                                                            //
//                                                                            //
//   evaluate_raw.cpp                                                         //
//                                                                            //
//   By: Mateo <teorodrip@protonmail.com>                                     //
//                                                                            //
//   Created: 2018/11/22 19:58:52 by Mateo                                    //
//   Updated: 2018/11/22 21:43:16 by Mateo                                    //
//                                                                            //
// ************************************************************************** //

#include "../includes/wiki_scrapping.hpp"

void evaluate_raw(const data_t *data, const xlnt::worksheet *ws)
{
  (void)data;
  std::string	base_url;
  std::string	url;
  std::string	page_url;
  std::string	page;
  json			j_search;
  unsigned int  i;
  size_t len;

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
		  std::cout << page << "\n";
		}
		  std::cout <<"\n";
	}
}
