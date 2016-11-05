
#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::tcp;

int main()
{
	// Création du service principal et du résolveur.
	boost::asio::io_service ios;

	// On veut se connecter sur la machine locale, port 7171
	tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 4242);

	// On crée une socket // (1)
	tcp::socket socket(ios);

	// Tentative de connexion, bloquante // (2)
	socket.connect(endpoint);

	// Création du buffer de réception // (3)
	boost::array<char, 128> buf;
	while (1)
	{
		boost::system::error_code error;
		socket.send(boost::asio::buffer("PING"));
		std::cout << "I'll read some" << std::endl;
		// Réception des données, len = nombre d'octets reçus // (4)
		int len = socket.read_some(boost::asio::buffer(buf), error);

		std::cout << "I've read some" << std::endl;

	  boost::asio::deadline_timer t(ios, boost::posix_time::seconds(5)); // Commence à compter dès sa création
	  t.wait();

		if (error == boost::asio::error::eof) // (5)
		{
			std::cout << "\nTerminé !" << std::endl;
			break;
		}

		// On affiche (6)
		std::cout.write(buf.data(), len);
	}

	return 0;
}
