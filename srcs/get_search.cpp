// ************************************************************************** //
//                                                                            //
//                                                                            //
//   get_search.cpp                                                           //
//                                                                            //
//   By: Mateo <teorodrip@protonmail.com>                                     //
//                                                                            //
//   Created: 2018/11/20 10:36:56 by Mateo                                    //
//   Updated: 2018/11/20 12:33:24 by Mateo                                    //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
  ((std::string *)userdata)->append(ptr, size * nmemb);
  return (size * nmemb);
}

void get_search(const char *url, json *j_search)
{
  CURL			*curl;
  CURLcode		res;
  std::string	info;

  if (!(curl = curl_easy_init()))
	{
	  std::cerr << "Error: unable to init CURL\n";
	  exit(EXIT_FAILURE);
	}
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &info);
  res = curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  if (res)
	{
	  std::cerr << "Error: performing curl\n";
	  exit(EXIT_FAILURE);
	}
  *j_search = json::parse(info);
}
