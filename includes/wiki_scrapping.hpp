/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   wiki_scrapping.h                                                         */
/*                                                                            */
/*   By: Mateo <teorodrip@protonmail.com>                                     */
/*                                                                            */
/*   Created: 2018/11/20 10:23:16 by Mateo                                    */
//   Updated: 2018/11/20 14:37:10 by Mateo                                    //
/*                                                                            */
/* ************************************************************************** */

#ifndef WS_H
#define WS_H

#include <nlohmann/json.hpp>
#include <vector>
#include <xlnt/xlnt.hpp>
#include <string>

#define BASE_URL "https://en.wikipedia.org/w/api.php?action=opensearch&fulltext=1&limit=10&format=json&search="
#define FILE_PATH "resources/keywords.xlsx"

using json = nlohmann::json;

void	get_search(const char *url, json *j_search);

#endif
