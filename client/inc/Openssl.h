//
// Openssl.h for Spider client in /home/rochon_k/rendu/cpp_spider/client
// 
// Made by Kevin ROCHON
// Login   <rochon_k@epitech.net>
// 
// Started on  Tue Nov  2 19:46:30 2016 Kevin ROCHON
// Last update Tue Nov  2 19:46:48 2016 Kevin ROCHON
//

#ifndef OPENSSL_H_
# define OPENSSL_H_

#include "AOpenssl.h"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <iostream>
#include <string>

class Openssl : public AOpenssl
{
private:
	RSA			*rsa;
	int			rsa_size;
	std::string	PrivateKey;
	std::string	PublicKey;
public:
	Openssl();
	~Openssl();
	int			generateKey();
	char		*cipher(char	*Data);
	char		*unCipher(char	*Data);
	std::string	getPrivateKey();
	std::string	getPublicKey();
};

#endif /* !OPENSSL_H_ */