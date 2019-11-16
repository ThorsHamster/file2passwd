%module pyfile2passwd


// Add necessary symbols to generated header
%{
#include "../src/file2passwd.hpp"
%}

%include "../src/file2passwd.hpp"