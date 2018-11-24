// ************************************************************************** //
//                                                                            //
//                                                                            //
//   extract_sentence.cpp                                                     //
//                                                                            //
//   By: Mateo <teorodrip@protonmail.com>                                     //
//                                                                            //
//   Created: 2018/11/23 13:23:05 by Mateo                                    //
//   Updated: 2018/11/24 21:00:33 by Mateo                                    //
//                                                                            //
// ************************************************************************** //

#include "../includes/wiki_scrapping.hpp"

void extract_sentence(sentence_t *sentence, const std::string end_sentence, data_t *data)
{
  size_t doc_len;
  size_t end_len;
  char   current;
  size_t i;
  size_t j;

  doc_len = sentence->doc.length();
  end_len = end_sentence.length();
  for (i = 0; i < doc_len; i++)
	{
	  current = sentence->doc.at(i);
	  if (isalpha(current) || current == ' ')
		continue ;
	  if (!sentence->cont_digit && isdigit(current))
		{
		  sentence->cont_digit = true;
		  continue ;
		}
	  for (j = 0; j < end_len; j++)
		{
		  if (current == end_sentence.at(j))
			{
			  if (sentence->cont_digit)
				{
				update_output("\"" + sentence->doc.substr(0, i + 1) + "\",", data);
				std:: cout << sentence->doc.substr(0, i + 1) <<"__FIN__\n";
				}
			  doc_len = doc_len - (i + 1);
			  sentence->doc = sentence->doc.substr(i + 1, doc_len);
			  i = 0;
			  sentence->cont_digit = false;
			  break ;
			}
		}
	}
  sentence->start = i - 1;
}
