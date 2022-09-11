/****************************** INCLUDE FILES *********************************/
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <boost/program_options.hpp>
#include <boost/asio.hpp>
#include <boost/format.hpp>
#include <boost/thread.hpp>

/********************************* NAMESPACES *********************************/
namespace po = boost::program_options;

/**
 *  Client class
 */
struct Client
{
    boost::asio::io_service& io_service;
    boost::asio::ip::tcp::socket socket;

    Client(boost::asio::io_service& svc, std::string const& host, std::string const& port)
        : io_service(svc), socket(io_service)
    {
        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::iterator endpoint = resolver.resolve(boost::asio::ip::tcp::resolver::query(host, port));
        boost::asio::connect(this->socket, endpoint);
    };

    void send(std::string const& message) {
        socket.send(boost::asio::buffer(message));
    }

    void recv(boost::asio::streambuf &i_sb) {
        boost::system::error_code ec;
        boost::asio::read(socket, i_sb, ec);
    }
};

void client_thread(const int name,
                   std::string const ipv4,
                   const int port) {
    boost::asio::io_service svc;
    boost::asio::streambuf i_sb;

    Client client(svc, ipv4, std::to_string(port));
    int stream_id = rand() % 10000 + 1;

    std::cout << boost::format("__client_%d__ Sending request for %d ...\n") % name % stream_id;
    client.send(std::to_string(stream_id));
    client.recv(i_sb);
    std::cout << boost::format("__client_%d__ Received: %s\n") % name % &i_sb;
}

/************************************ MAIN ************************************/
int main(int ac, char* av[]) {
    boost::thread_group tg;
    int port;
    int n_threads;
    std::string ipv4;

    po::options_description desc("Options");
    desc.add_options()
        ("help", "produce help message")
        ("ipv4", po::value<std::string>(&ipv4)->default_value("127.0.0.1"),
            "Server IPv4 address")
        ("port", po::value<int>(&port)->default_value(9080),
            "Server port number")
        ("n_threads", po::value<int>(&n_threads)->default_value(1),
            "Number of client threads")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    std::cout << "Server address: " << vm["ipv4"].as<std::string>() << ":"
              << vm["port"].as<int>() << "\n";
    std::cout << "Client Threads: " << vm["n_threads"].as<int>() << "\n";

    /* init rand seed */
    srand (time(NULL));

    for (int index = 0; index < n_threads; index++) {
        std::cout << "Starting client thread: " << index << "\n";
        tg.add_thread(new boost::thread(client_thread,
                                        index,
                                        ipv4,
                                        port));
    }

    tg.join_all();

    return 0;
}
