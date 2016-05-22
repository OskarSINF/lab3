#include "Slav.h"
#include <fstream>
#include <iterator>
#include <string>
using namespace std;

vector <string> Slav::names;
int Slav::_counter = 0;

void Slav::init()
{
	srand(time(NULL));
	ifstream file("names.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(names));
	file.close();
}

Slav::Slav()
{
	static int amountOfNames = (init(), names.size());  // Leniwe inicjowanie- obiekt tworzont jest jednorazowo( static) 
	_name = names[rand() % amountOfNames];				// i w momencie, gdy jest on potrzebny- w dalszej czesci programu,			
	_id = _counter++;									// gdy bedzie potrzebna ta wartosc nie bedzie ona obliczana jeszcze raz,
														// ale zwaracany bedzie wynik obliczony za pierwszym razem	
}

string Slav::description()
{
	return string("  ") + _name + " [" + to_string(_id+1) +"]";
}

gender Slav::specifyTheGender()
{
	if(_name[_name.length()-1]=='a')
		return female;
	else 
		return male;
}