%module pyfile2passwd

%include "std_string.i"
%ignore File2Passwd::inject_test_seam; 
// Add necessary symbols to generated header
%{
#include "file2passwd.hpp"
%}

%include "file2passwd.hpp"