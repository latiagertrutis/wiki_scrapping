// ************************************************************************** //
//                                                                            //
//                                                                            //
//   extract_sentence.cpp                                                     //
//                                                                            //
//   By: Mateo <teorodrip@protonmail.com>                                     //
//                                                                            //
//   Created: 2018/11/23 13:23:05 by Mateo                                    //
//   Updated: 2018/11/25 21:41:58 by Mateo                                    //
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
  for (i = sentence->start; i < doc_len; i++)
	{
	  current = sentence->doc.at(i);
	  if (isalpha(current) || current == ' ')
		continue ;
	  if (current == '\"' || current == '\\')
		{
		  sentence->doc.insert(i,"\\");
		  doc_len++;
		  i++;
		  continue ;
		}
	  if (!isprint(current))
		{
		  sentence->doc[i] = ' ';
		  continue ;
		}
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
				}
			  doc_len = doc_len - (i + 1);
			  sentence->doc = sentence->doc.substr(i + 1, doc_len);
			  i = -1;
			  sentence->cont_digit = false;
			  break ;
			}
		}
	}
  sentence->start = i;
}
