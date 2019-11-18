%module pyfile2passwd

%include "std_string.i"
// Add necessary symbols to generated header
%{
#include "file2passwd.hpp"
%}

%include "file2passwd.hpp"