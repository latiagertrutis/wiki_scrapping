// ************************************************************************** //
//                                                                            //
//                                                                            //
//   main.cpp                                                                 //
//                                                                            //
//   By: Mateo <teorodrip@protonmail.com>                                     //
//                                                                            //
//   Created: 2018/11/20 10:28:41 by Mateo                                    //
//   Updated: 2018/11/23 14:38:47 by Mateo                                    //
//                                                                            //
// ************************************************************************** //

#include "../includes/wiki_scrapping.hpp"
#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include <myhtml/api.h>

static void init_options(const int argc, const char **argv, data_t *data)
{
  boost::program_options::options_description desc("Options");
  boost::program_options::variables_map vm;

  try
	{
	  desc.add_options()
		("help,h", "Help screen")
		("raw,r", "Evalue raw HTML, overrides -c flag")
		("file,f",
		 boost::program_options::value<std::string>()->default_value("resources/keywords.xlsx"),
		 "File containing Keywords (default resources/keywords.xlsx)")
		("end_char,e",
		 boost::program_options::value<std::string>()->default_value(".?!"),
		 "Chain of characters to mark end of sentnce, numeric, alphabetic and space characters will not be considered (default \".?!\")")
		("limit_search,l",
		 boost::program_options::value<unsigned int>()->default_value(10),
		 "Search limit on Wikipedia (default 10)")
		("container,c",
		 boost::program_options::value<std::string>()->default_value("p"),
		 "Container to start searching (default p)");
	  boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
	  boost::program_options::notify(vm);
	  if (vm.count("help"))
		{
		  std::cout << desc << "\n";
		  exit(EXIT_SUCCESS);
		}
	  else
		{
		  if (vm.count("file"))
			data->keywords_path = vm["file"].as<std::string>();
		  if (vm.count("limit_search"))
			data->search_limit = vm["limit_search"].as<unsigned int>();
		  if (vm.count("raw"))
			data->flags |= 0x1;
		  if (vm.count("end_char"))
			data->end_char = vm["end_char"].as<std::string>();
		  else if (vm.count("container"))
			data->container = vm["container"].as<std::string>();
		}
	}
  catch (const boost::program_options::error &error)
	{
	  std::cerr << error.what() << "\n";
	  exit(EXIT_FAILURE);
	}
}

static void init_keywords(const std::string path, xlnt::workbook *wb, xlnt::worksheet *ws)
{
  try
	{
	  wb->load(path);
	}
  catch (xlnt::exception const &error)
	{
	  std::cerr << error.what() << "\n";
	  exit(EXIT_FAILURE);
	}
  *ws = wb->active_sheet();
}

int main(int argc, char **argv)
{
  data_t data;
  xlnt::workbook	wb;
  xlnt::worksheet	ws;

  init_options((const int)argc, (const char **)argv, &data);
  init_keywords(data.keywords_path, &wb, &ws);
  evaluate_tree(&data, &ws);
  return (0);


  json j_search;
  std::string url;
  std::string page;


  myhtml_t* myhtml = myhtml_create();
  myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
  myhtml_tree_t* tree = myhtml_tree_create();
  myhtml_tree_init(tree, myhtml);

  //Search for all keywords, may be is possible to do it in just 1 request?
  for (auto row : ws.rows())
	{
	  return 0;

	  url = BASE_URL + row[0].to_string();
	  get_search(url, &j_search);
	  get_page(j_search[3][0], &page);
	  myhtml_parse(tree, MyENCODING_UTF_8, page.c_str(), page.length());
	  myhtml_collection_t *collection = myhtml_get_nodes_by_name(tree, NULL, "p", 1, NULL);

	  if (collection && collection->list && collection->length)
		{
		  myhtml_tree_node_t *text_node;
		  myhtml_tree_node_t *text_node_child;
		  char* text;
		  for (size_t i = 0; i < collection->length; i++)
			{
			  text_node = myhtml_node_child(collection->list[i]);
			  while (text_node)
				{
				  text = (char *)myhtml_node_text(text_node, NULL);
				  if (text)
					std::cout << "Res: " << text << "\n";
				  if ((text_node_child = myhtml_node_child(text_node)))
					{
					  text = (char *)myhtml_node_text(text_node_child, NULL);
					  if (text)
						std::cout << "Res: " << text << "\n";

					}
				  text_node = myhtml_node_next(text_node);
				}
			}
		}

	  // if(collection && collection->list && collection->length) {
      //   myhtml_tree_node_t *text_node = myhtml_node_child(collection->list[2]);

      //   if(text_node) {
	  // 	  const char* text = myhtml_node_text(text_node, NULL);

	  // 	  if(text)
	  // 		printf("Title: %s\n", text);
	  // 	}
	  // }


	  // try {
	  // 	boost::sregex_iterator next(page.begin(), page.end(), exp);
	  // 	boost::sregex_iterator end;
	  // 	while (next != end) {
	  // 	  boost::smatch match = *next;
	  // 	  std::cout<< "Res: \n" << match.str() << "\n\n";
	  // 	  next++;
	  // 	}
	  // } catch (boost::regex_error& e) {
	  // 	// Syntax error in the regular expression
	  // }
	  exit(1);
	}
}
