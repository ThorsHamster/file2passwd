%module pyfile2passwd

%include "std_string.i"
// Add necessary symbols to generated header
%{
#include "file2passwd_interface.hpp"
%}

%include "file2passwd_interface.hpp"