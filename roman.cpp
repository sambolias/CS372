//me being ocd

#include <stdio.h>
#include <string>
using std::string;

#include <vector>
using std::vector;

#include <time.h>

bool startsWith5(int num)
{
	for(num; num >=5; num /= 10)
	{
		if(num == 5)return true;
	}

	return false;
}

string roman(int num)
{
	if(num < 1) return "incompatible";

	string ret, sec;

	vector<std::pair<int, string>> romanNums = {{1000, "M"}, {500, "D"}, {100, "C"}, {50, "L"}, {10, "X"}, {5, "V"}, {1, "I"}  };
	
	for (auto i = romanNums.begin(); i != romanNums.end(); i++)
	{
		bool last = false;
		int n1 = i->first,n2;

		if(n1>1)
		{
			int next = 2;
			if(startsWith5(n1))
			{
				next = 1;
			}
			else
			{
				n2 = (i+next)->first;
				sec = (i+next)->second;
			}
		}
		else last = true;

		while(num >= n1) 
		{
			ret += i->second;
			num -= n1;		
		}

		if(num >= n1-n2 && !last)
		{
			ret += sec + i->second;
			num -= (n1 - n2);
		}


	}

	return ret;
}


int main()
{

	srand(time(NULL));
	for (int num = (rand()%10+1); num < 2000; num += (rand()%100 + 1))
	{
		printf("%s is %i\n", roman(num).c_str(), num);
	}
	return 0;
}
