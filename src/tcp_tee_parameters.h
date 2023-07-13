#pragma once

#include <string>
#include <boost/program_options.hpp>
using namespace std::literals;
namespace po = boost::program_options;

struct Tcp_tee_Parameters {
	int listen_port  ;
	std::string listen_address  ;
	std::string request_log_file  ;

	std::string forward_port  ;
	std::string forward_address ;
	std::string responce_log_file  ;
	
	boost::program_options::options_description desc;

	Tcp_tee_Parameters(int argc, const char* const argv[]) :
		listen_port{ 8080 },
		forward_port{ "80" },
		listen_address{ "0.0.0.0"sv },
		forward_address{ "127.0.0.1"sv },
		request_log_file{"request.log"sv},
		responce_log_file{ "responce.log"sv } 
	{
		desc.add_options()           //
			("help,h", "Show help")  // 
			("listen_port,l", po::value(&listen_port)->value_name("listen_port"s), "listen tcp port, default 8080")  //
			("forward_address,a", po::value(&forward_address)->value_name("forward_address"s), "forward ipv4 address, default 127.0.0.1")  //
			("forward_port,p", po::value(&forward_port)->value_name("forward_port"s), "forward tcp port, default 80")  //
			("request_log_file,L", po::value(&request_log_file)->value_name("request_log_file"s), "request_log_file default request.log")  //
			("responce_log_file,O", po::value(&responce_log_file)->value_name("responce_log_file"s), "request_log_file default responce.log")  //

			;

		po::variables_map vm;
		//po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
		po::store(po::parse_command_line(argc, argv, desc), vm);

		po::notify(vm);
	}
};