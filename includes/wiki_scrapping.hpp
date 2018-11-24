/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   wiki_scrapping.h                                                         */
/*                                                                            */
/*   By: Mateo <teorodrip@protonmail.com>                                     */
/*                                                                            */
/*   Created: 2018/11/20 10:23:16 by Mateo                                    */
//   Updated: 2018/11/24 20:23:00 by Mateo                                    //
/*                                                                            */
/* ************************************************************************** */

#ifndef WS_H
#define WS_H

#include <nlohmann/json.hpp>
#include <vector>
#include <xlnt/xlnt.hpp>
#include <string>
#include <myhtml/api.h>
#include <iostream>
#include <fstream>

#define BASE_URL "https://en.wikipedia.org/w/api.php?action=opensearch&format=json&limit="

using json = nlohmann::json;

typedef struct data_s
{
  std::string   keywords_path;
  std::string	container;
  std::string	end_char;
  std::string	output;
  std::string	output_path;
  std::ofstream output_file;
  unsigned int	search_limit;
  unsigned int  flags;//0x1 for raw html
  size_t        buff;
} data_t;

typedef struct sentence_s
{
  std::string doc;
  size_t start;
  bool cont_digit;
} sentence_t;

void	get_search(const std::string url, json *j_search);
void	get_page(const std::string url, std::string *page);
void	evaluate_raw(const data_t *data, const xlnt::worksheet *ws);
void	evaluate_tree(data_t *data, const xlnt::worksheet *ws);
void	extract_sentence(sentence_t *sentence, const std::string end_sentence, data_t *data);
void	parse_root_tree(myhtml_tree_t *tree, const char *page, const size_t page_len, data_t *data);
void    update_output(const std::string str, data_t *data);

#endif
