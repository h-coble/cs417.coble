//structHash.cpp in repo
#include<string>
#include<functional>
#include<iostream>

struct S
{
	std::string firstName;
	std::string lastName;
	std::string address;
};

class hashS
{
	public:
		//return type found from cppreference:
		//https://en.cppreference.com/w/cpp/utility/hash
		std::size_t operator()(S& info)
		{
			//Hash each string
			std::size_t first_name = std::hash<std::string>{}(info.firstName);
			std::size_t last_name = std::hash<std::string>{}(info.lastName);
			std::size_t address_ = std::hash<std::string>{}(info.address);

			//XOR them together
			return (first_name ^ last_name ^ address_);
		}
};

int main()
{
	hashS hash;
	S me;
	me.firstName = "Hayden";
	me.lastName = "Coble";
	me.address = "Highway 251";

	std::cout << hash(me) <<std::endl;

	return 0;
}