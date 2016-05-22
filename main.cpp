// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Slav.h"

#include <iterator>

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);

void containers(Slav *, int);
void adapters(Slav *, int);
void genderOfSlavs(Slav *, int);

int main(int argc, char const *argv[])
{
	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description(); 
	cout<<endl;

	containers(slavs, n);
	adapters(slavs, n);
	genderOfSlavs(slavs,n);

	delete [] slavs;
}

void containers(Slav * slavs, int n)
{
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;
	
	printf("# Containers\n");
	REPORT_CONTAINERS;
	printf("## vector\n");

	// Umieść Słowian w losowej kolejności w wektorze.
	srand(time(NULL));
	vectorOfSlavs.push_back(&slavs[0]);

	for(int i=1;i<n;i++)
		vectorOfSlavs.insert(vectorOfSlavs.begin()+rand()%(i+1),&slavs[i]);
	
	// Wykorzystując iterator i funkcję description(), wyświetl wszystkich Słowian w wektorze
	
	vector<Slav *>::iterator itV;
	for(itV=vectorOfSlavs.begin();itV!=vectorOfSlavs.end();itV++)
		cout<<(*itV)->description();
	cout<<endl;

	REPORT_CONTAINERS;
	printf("## set_size\n");

	// // Przenieś wszystkich Słowian z wektoru do zbioru.
	for(int i=0;i<n;i++)
		setOfSlavs.insert(vectorOfSlavs[i]);
	
	vectorOfSlavs.clear();
	REPORT_CONTAINERS;
	printf("## map\n");

	// Stwórz słownik tworzący pary Słowian, z tych znajdujących się w zbiorze, czyszcząc zbiór

	set<Slav *>::iterator itS;

	for(itS=setOfSlavs.begin();itS!=setOfSlavs.end();itS++)
		mapOfSlavs[*itS]=(*++itS);
	setOfSlavs.clear();

	// Wykorzystując iterator, wyświetl wszystkie pary Słowian
	map<Slav *,Slav *>:: iterator itM;
	
	for(itM=mapOfSlavs.begin(); itM!=mapOfSlavs.end(); itM++)
 	cout<<(itM->first)->description()<<" &"<<(itM->second)->description()<<endl;
	REPORT_CONTAINERS;
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("# Adapters\n");
	REPORT_ADAPTERS;
	printf("## queue\n");

	// Umieść Słowian w kolejce.
	for(int i=0;i<n;i++)
		queueOfSlavs.push(&slavs[i]);

	REPORT_ADAPTERS;

	printf("## stack\n");
	// Przenieś Słowian z kolejki do stosu.
	while(!queueOfSlavs.empty())
	{
		stackOfSlavs.push(queueOfSlavs.front());
		queueOfSlavs.pop();
	}

	REPORT_ADAPTERS;

	// Wyświetl Słowian zdejmowanych ze stosu.

	while(!stackOfSlavs.empty())
	{
		cout<<stackOfSlavs.top()->description();	
		stackOfSlavs.pop();
	}
	cout<<endl;

	REPORT_ADAPTERS;
}

void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());
}

void genderOfSlavs(Slav * slavs, int n)
{
	map <gender, vector<Slav *> >mapOfGender;
	for(int i=0;i<n;i++)
	{
		if(slavs[i].specifyTheGender()==female)
				mapOfGender[female].push_back(&slavs[i]);
		else
				mapOfGender[male].push_back(&slavs[i]);
	}

	cout<<"#Wojownicy :"<<endl;
	vector<Slav *>::iterator itM;
	for(itM=mapOfGender[male].begin();itM!=mapOfGender[male].end();itM++)
		cout<<(*itM)->description();

	if(mapOfGender[male].empty())
		cout<<"  Nie wylosowano zadnych wojownikow.";
	cout<<endl;

	cout<<"#Niewiasty :"<<endl;
	vector<Slav *>::iterator itF;
	for(itF=mapOfGender[female].begin();itF!=mapOfGender[female].end();itF++)
		cout<<(*itF)->description();

	if(mapOfGender[female].empty())
		cout<<"  Nie wylosowano zadnych kobiet.";
	cout<<endl;

	mapOfGender.clear();

}