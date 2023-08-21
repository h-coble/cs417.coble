#pragma once

#include<fstream>;
class IndexCard
{
	private:
		string keyword;
		int index;
	public:
		//Constructors and Destructor
		IndexCard() : index(-1), keyword("") {};
		IndexCard(int x, string title) : keyword(title), index(x) {};
		~IndexCard(){};

		//Get and set
		string getKeyword()
		{
			return keyword;
		}
		int getIndex()
		{
			return index;
		}
		void setKeyword(string newWord)
		{
			keyword = newWord;
		}
		void setIndex(int newIndex)
		{
			index = newIndex;
		}
		void printCard()
		{
			std::cout << "Index: " << index << "\tKeyword: " << keyword << std::endl << std::endl;
		}
		void printCardtoFile(ofstream fileOut)
		{
			fileOut << "Index: " << index << "\tKeyword: " << keyword << std::endl << std::endl;
		}
		bool operator<(IndexCard const& other)
		{
			if (index < other.index)
				return true;
			else
				return false;
		}
};