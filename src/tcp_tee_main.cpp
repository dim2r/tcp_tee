#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "tcp_tee_parameters.h"
#include <cstring>
#include <fstream>
#include <iostream>

using boost::asio::ip::tcp;
const int max_length = 1024;
typedef boost::shared_ptr<tcp::socket> socket_ptr;

void tcp_session_thread(socket_ptr from_sock, socket_ptr to_sock, std::ofstream*  fs)
{
    try
    {
        for (;;)
        {
            char data[max_length];

            boost::system::error_code error;
            size_t length = from_sock->read_some(boost::asio::buffer(data), error);
            
            fs->write(data, length);
            fs->flush();

            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.

            boost::asio::write(*to_sock, boost::asio::buffer(data, length));
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}

void server(boost::asio::io_service& io_service, const Tcp_tee_Parameters & params)
{
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), params.listen_port));
    tcp::resolver fwd_resolver(io_service);
    
    tcp::resolver::results_type fwd_endpoints = fwd_resolver.resolve(params.forward_address, params.forward_port);
    
    std::ofstream fs1(params.request_log_file, std::ios::out | std::ios::binary | std::ios::app);
    std::ofstream fs2(params.responce_log_file, std::ios::out | std::ios::binary | std::ios::app);


    for (;;)
    {
        socket_ptr sock(new tcp::socket(io_service));
        acceptor.accept(*sock);
        socket_ptr fwd_socket(new tcp::socket(io_service));
        boost::asio::connect(*fwd_socket, fwd_endpoints);
        std::cout << "connection accepted" << std::endl;
        boost::thread t1(boost::bind(tcp_session_thread, sock, fwd_socket,  &fs1));
        boost::thread t2(boost::bind(tcp_session_thread, fwd_socket, sock,  &fs2));
    }
}

int main(int argc, char* argv[])
{
    try
    {
        Tcp_tee_Parameters params(argc, argv);
//        system("chcp 1251");
        boost::asio::io_service io_service;
        server(io_service, params);
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}