// ************************************************************************** //
//                                                                            //
//                                                                            //
//   main.cpp                                                                 //
//                                                                            //
//   By: Mateo <teorodrip@protonmail.com>                                     //
//                                                                            //
//   Created: 2018/11/20 10:28:41 by Mateo                                    //
//   Updated: 2018/11/25 19:04:38 by Mateo                                    //
//                                                                            //
// ************************************************************************** //

#include "../includes/wiki_scrapping.hpp"
#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include <myhtml/api.h>
#include <iostream>

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
		("output,o",
		 boost::program_options::value<std::string>()->default_value("output.json"),
		 "output of the program (default \"output.json\")")
		("limit_search,l",
		 boost::program_options::value<unsigned int>()->default_value(10),
		 "Search limit on Wikipedia (default 10)")
		("buffer,b",
		 boost::program_options::value<size_t>()->default_value(2048),
		 "Buffer to store sentences in memory before write them on file (default 2048)")
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
		  if (vm.count("output"))
			data->output_path = vm["output"].as<std::string>();
		  if (vm.count("limit_search"))
			data->search_limit = vm["limit_search"].as<unsigned int>();
		  if (vm.count("buffer"))
			data->buff = vm["buffer"].as<size_t>();
		  if (vm.count("end_char"))
			data->end_char = vm["end_char"].as<std::string>();
		  if (vm.count("raw"))
			data->flags |= 0x1;
		  else if (vm.count("container"))
			data->container = vm["container"].as<std::string>();
		  data->output = "{";
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

static void init_output_file(data_t *data)
{
  data->output_file.open(data->output_path, std::ofstream::out | std::ofstream::trunc);
  if (!data->output_file.is_open())
	{
	  std::cerr << "Error: creating file\n";
	  exit (EXIT_FAILURE);
	}
}

int main(int argc, char **argv)
{
  data_t data;
  xlnt::workbook	wb;
  xlnt::worksheet	ws;

  init_options((const int)argc, (const char **)argv, &data);
  init_output_file(&data);
  init_keywords(data.keywords_path, &wb, &ws);
  evaluate_tree(&data, &ws);
  data.output_file << data.output + "}";
  data.output_file.close();
  return (0);
}
