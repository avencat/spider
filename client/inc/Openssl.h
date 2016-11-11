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

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <iostream>
#include <string>
#include "stdafx.h"

class Openssl
{
private:
	RSA *PrivateKey;
	RSA *PublicKey;
	std::string	save_key;
public:
	Openssl();
	~Openssl();
	int	generateKey();
	std::string cipher(std::string Data, RSA *PublicKey);
	std::string unCipher(std::string Data, RSA *PrivateKey);
	std::string	getSave_key();
};

#endif /* !OPENSSL_H_ */