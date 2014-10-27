// C++98 or C++11
int a = 42;        // still fine, as always

// C++ 11
auto x = begin(v); // no narrowing or non-initialization is possible

// C++98
rectangle       w( origin(), extents() );   // oops, declares a function, if origin and extents are types
complex<double> c( 2.71828, 3.14159 );
int             a[] = { 1, 2, 3, 4 };
vector<int>     v;
for( int i = 1; i <= 4; ++i ) v.push_back(i);

// C++11
rectangle       w   { origin(), extents() };
complex<double> c   { 2.71828, 3.14159 };
int             a[] { 1, 2, 3, 4 };
vector<int>     v   { 1, 2, 3, 4 };
