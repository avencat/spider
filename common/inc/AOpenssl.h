//
// Openssl.h for Spider client in /home/rochon_k/rendu/cpp_spider/client
// 
// Made by Kevin ROCHON
// Login   <rochon_k@epitech.net>
// 
// Started on  Tue Nov  12 22:16:30 2016 Kevin ROCHON
// Last update Tue Nov  12 22:16:48 2016 Kevin ROCHON
//

#include <string>

#ifndef AOPENSSL_H_
# define AOPENSSL_H_

class AOpenssl
{
public:
	AOpenssl();
	virtual ~AOpenssl();
	virtual int		generateKey() = 0;
	virtual char	*cipher(char	*Data) = 0;
	virtual char	*unCipher(char	*Data) = 0;
};

#endif /* !AOPENSSL_H_ */