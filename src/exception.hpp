#ifndef SRC_EXCEPTION_HPP_
#define SRC_EXCEPTION_HPP_

#include <exception>

struct FileDoesNotExistException : public std::exception
{
	const char * what () const throw ()
    {
    	return "File does not exist.";
    }
};

#endif /* SRC_EXCEPTION_HPP_ */