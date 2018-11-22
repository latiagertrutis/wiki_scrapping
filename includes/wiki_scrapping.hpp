/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   wiki_scrapping.h                                                         */
/*                                                                            */
/*   By: Mateo <teorodrip@protonmail.com>                                     */
/*                                                                            */
/*   Created: 2018/11/20 10:23:16 by Mateo                                    */
//   Updated: 2018/11/22 22:13:57 by Mateo                                    //
/*                                                                            */
/* ************************************************************************** */

#ifndef WS_H
#define WS_H

#include <nlohmann/json.hpp>
#include <vector>
#include <xlnt/xlnt.hpp>
#include <string>

#define BASE_URL "https://en.wikipedia.org/w/api.php?action=opensearch&format=json&limit="

using json = nlohmann::json;

typedef struct data_s
{
  std::string   keywords_path;
  std::string	container;
  unsigned int	search_limit;
  unsigned int  flags;//0x1 for raw html
} data_t;

void	get_search(const std::string url, json *j_search);
void	get_page(const std::string url, std::string *page);
void	evaluate_raw(const data_t *data, const xlnt::worksheet *ws);
void	evaluate_tree(const data_t *data, const xlnt::worksheet *ws);

#endif
