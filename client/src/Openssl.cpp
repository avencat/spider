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

	this->PrivateKey = RSA_generate_key(kBits, kExp, 0, 0);
	BIO	*bio = BIO_new(BIO_s_mem());

	PEM_write_bio_RSAPrivateKey(bio, this->PrivateKey, NULL, NULL, 0, NULL, NULL);
	keylen = BIO_pending(bio);
	pem_key = reinterpret_cast<char *>(calloc(keylen + 1, 1));
	BIO_read(bio, pem_key, keylen);

	this->save_key = pem_key;

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

std::string	Openssl::getSave_key()
{
	return (this->save_key);
}

int main()
{
	Openssl	op;

	op.generateKey();
	std::cout << op.getSave_key();
	return 0;
}
