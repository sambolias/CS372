#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
using std::vector;

#include <string>
using std::string;

//The kata is worded poorly...I don't technically need to support delimiters
//because it says not to test for incorrect inputs
//so this is following it as literally as I can
//I added check 2 digit for my own amusement 

bool isNum(char c)
{
	return ( (int) c >= 48 && (int) c <= 57 );
}


int add(string expr)
{
	const int MAX = 1000;	//max amount allowed
	int n=0, dn=0;
	char last;
	vector<string> negs;

	for( auto c : expr)
	{

		if( isNum(c) ) //is a number
		{
			dn*=10;		//dn allows for multi digit numbers - resets if any delimiter is hit
			dn += (int) c - 48;
			if( last == '-' ) negs.push_back( "-" + string(&c,1) );	//string ctor needs to know length or it reads past addr of c
		}
		else 
		{
			(dn < MAX) ? n+=dn : dn=0;
			dn=0;
		}
		last = c;
	}

	(dn < MAX) ? n+=dn : dn=0;	//last digit stored - doesn't hit above else
	
	if(negs.size())
	{
		string e = "The following negative inputs were forbidden: ";

		for(auto i : negs)
		{
			e += i + " ";	//list negative inputs
		}
		throw (e);
	}

	return n;
}


TEST_CASE("kata test" , "[add]")
{
	SECTION("Testing multiple additions")
	{
		REQUIRE( add("0") == 0);	//test function
		REQUIRE( add("1") == 1);	//test single 
		REQUIRE( add("1,2") == 3);	//test multiple adds
		REQUIRE( add("1,2,3") == 6);
	}
	SECTION("Testing delimiters - random chars ignored")
	{
		REQUIRE( add("1\n,2,//;f3st/?4") == 10);	//was not clear on delimiters...anything other than number is ignored
	}
	SECTION("Testing negative exception")
	{
		REQUIRE_THROWS_WITH(add("1,2,3,-4"), "The following negative inputs were forbidden: -4 ");
	}
	SECTION("Check numbers with more than 1 digit")
	{

		REQUIRE(add("42,1,12") == 55);
	}
	SECTION("Ignores n > 1000")
	{
		REQUIRE(add("2,1001") == 2);
	}



}
