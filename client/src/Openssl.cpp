//
// Openssl.cpp for Spider client in /home/rochon_k/rendu/cpp_spider/client
// 
// Made by Kevin ROCHON
// Login   <rochon_k@epitech.net>
// 
// Started on  Tue Nov  2 19:48:03 2016 Kevin ROCHON
// Last update Tue Nov  2 19:48:27 2016 Kevin ROCHON
//

#include "stdafx.h"
#include "Openssl.h"

Openssl::Openssl()
{

}

Openssl::~Openssl()
{

}

int	Openssl::generateKey()
{
	const int	kBits = 2048;
	const int	kExp = 65537;
	int			keylen;
	char		*pem_key;

	if ((this->rsa = RSA_generate_key(kBits, kExp, 0, 0)) == NULL)
	{
		std::cout << "Failed to generate rsa" << std::endl;
		return (-1);
	}
	BIO		*bio;
	if ((bio = BIO_new(BIO_s_mem())) == NULL)
	{
		std::cout << "Failed to generate bio" << std::endl;
		return (-1);
	}

	//get the private key
	PEM_write_bio_RSAPrivateKey(bio, this->rsa, NULL, NULL, 0, NULL, NULL);
	keylen = BIO_pending(bio);
	if ((pem_key = reinterpret_cast<char *>(calloc(keylen + 1, 1))) == NULL)
	{
		std::cout << "Calloc failed" << std::endl;
		return (-1);
	}
	BIO_read(bio, pem_key, keylen);

	this->PrivateKey = pem_key;

	//get the public key
	PEM_write_bio_RSAPublicKey(bio, this->rsa);
	keylen = BIO_pending(bio);
	if ((pem_key = reinterpret_cast<char *>(calloc(keylen + 1, 1))) == NULL)
	{
		std::cout << "Calloc failed" << std::endl;
		return (-1);
	}
	BIO_read(bio, pem_key, keylen);

	this->PublicKey = pem_key;

	BIO_free_all(bio);
	free(pem_key);

	return 0;
}

std::string Openssl::cipher(std::string Data, RSA *PublicKey)
{
	return (Data);
}

std::string Openssl::unCipher(std::string Data, RSA *PrivateKey)
{
	return (Data);
}

std::string	Openssl::getPrivateKey()
{
	return (this->PrivateKey);
}

std::string	Openssl::getPublicKey()
{
	return (this->PublicKey);
}

int main()
{
	Openssl	op;

	op.generateKey();
	std::cout << op.getPublicKey();
	return 0;
}