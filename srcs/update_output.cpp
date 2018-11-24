// ************************************************************************** //
//                                                                            //
//                                                                            //
//   update_output.cpp                                                        //
//                                                                            //
//   By: Mateo <teorodrip@protonmail.com>                                     //
//                                                                            //
//   Created: 2018/11/24 19:14:31 by Mateo                                    //
//   Updated: 2018/11/24 19:39:01 by Mateo                                    //
//                                                                            //
// ************************************************************************** //

#include "../includes/wiki_scrapping.hpp"

void update_output(const std::string str, data_t *data)
{
  data->output += str;
  if (data->output.length() >= data->buff)
	{
	  data->output_file << data->output;
	  data->output = "";
	}
}
