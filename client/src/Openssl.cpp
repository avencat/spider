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
	this->rsa_size = RSA_size(this->rsa);
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

char	*Openssl::cipher(char *Data)
{
	int		res;
	char	*encrypted;

	if ((encrypted = reinterpret_cast<char *>(malloc(this->rsa_size))) == NULL)
	{
		std::cout << "Malloc failed" << std::endl;
		return (Data);
	}

	if ((res = RSA_public_encrypt(strlen(Data) + 1, (unsigned char*)Data, (unsigned char*)encrypted, this->rsa, RSA_PKCS1_OAEP_PADDING)) == -1)
	{
		std::cout << "Error encrypting message" << std::endl;
		return (Data);
	}
	//RSA_private_encrypt(flen, Data, encrypted, this->rsa, 0);

	return (encrypted);
}

char	*Openssl::unCipher(char	*Data)
{
	int		res;
	char	*decrypted;

	if ((decrypted = reinterpret_cast<char *>(malloc(this->rsa_size))) == NULL)
	{
		std::cout << "Malloc failed" << std::endl;
		return (Data);
	}
	if ((res = RSA_private_decrypt(strlen(Data) + 1, (unsigned char*)Data, (unsigned char*)decrypted, this->rsa, RSA_PKCS1_OAEP_PADDING)) == -1)
	{
		std::cout << "Error decrypting message" << std::endl;
		return (Data);
	}
	//RSA_public_decrypt();
	return (decrypted);
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
	char *test;

	op.generateKey();
	test = op.cipher("Hello World");
	std::cout << op.cipher(test);
	//op.getPrivateKey();
	return 0;
}