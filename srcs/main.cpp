// ************************************************************************** //
//                                                                            //
//                                                                            //
//   main.cpp                                                                 //
//                                                                            //
//   By: Mateo <teorodrip@protonmail.com>                                     //
//                                                                            //
//   Created: 2018/11/20 10:28:41 by Mateo                                    //
//   Updated: 2018/11/20 14:43:44 by Mateo                                    //
//                                                                            //
// ************************************************************************** //

#include "../includes/wiki_scrapping.hpp"

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  xlnt::workbook wb;
  xlnt::worksheet	ws;
  json j_search;
  std::string url;

  wb.load(FILE_PATH);
  ws = wb.active_sheet();
  for (auto row : ws.rows())
	{
	  url = BASE_URL + row[0].to_string();

	}
}
