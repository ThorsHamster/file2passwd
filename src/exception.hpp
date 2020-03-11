#include <exception>

struct FileDoesNotExistException : public std::exception
{
	const char * what () const throw ()
    {
    	return "File does not exist.";
    }
};
