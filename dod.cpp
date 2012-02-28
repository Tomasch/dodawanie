#include <list>
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <cstring>

using namespace std;

list<int> wczytaj(char *argv, int s) {
	list<int> lista;
	char buf[3];
	buf[2]=0;
	int liczba, a=0;
	if(s%2==0) {
		buf[0]=argv[0];
		buf[1]=0;
		stringstream ss;
		ss << hex << buf;
		ss >> liczba;
		lista.push_back(liczba);
		a=1;
	}
	for(; argv[a]&&argv[a+1] ; a+=2) {
		buf[0]=argv[a];
		buf[1]=argv[a+1];
		stringstream ss;
		ss << hex << buf;
		ss >> liczba;
		lista.push_back(liczba);
	}
	return lista;
}

void drukuj(list<int> l) {
	for( list<int>::iterator iter=l.begin(); iter != l.end(); ++iter )
	    cout << hex << *iter;
	cout << endl;
}

list<int> dodaj(list<int> l1, list<int> l2) {
	list<int> l;
	list<int>::reverse_iterator i1=l1.rbegin(), i2=l2.rbegin();
	int quot=0;
	for(;i1!=l1.rend()&&i2!= l2.rend();++i1,++i2) {
		if(*i1+*i2+quot>=256) {
			div_t z=div((*i1+*i2+quot), 256);
			l.push_front(z.rem);
			quot=z.quot*256;
		}
		else {
			l.push_front(*i1+*i2+quot);
			quot=0;
		}
	}
	for(;i1!=l1.rend();++i1) //dodaje pozostałe z i1 jeśli takie istnieją
		l.push_front(*i1);
	for(;i2!=l2.rend();++i2) //dodaje pozostałe z i2 jeśli takie istnieją
		l.push_front(*i2);
	if(quot)
		l.push_front(quot);
	return l;
}

void pomnoz(list<int> l1, list<int> l2) {

}

int main(int argc, char *argv[]) {
	if(argc<2) {
		cout << "Nie wpisałeś argumentów (dwóch liczb w x)" << endl;
		exit (0);
	}
	int a=0;
	while(argv[1][a++]){}
	list<int> l = wczytaj(argv[1], a);
	drukuj(l);
	list<int> l2 = wczytaj(argv[2], 7);
	drukuj(l2);
	list<int> l3=dodaj(l, l2);
	cout << "wynik to ";
	drukuj(l3);
	cout << endl;
	return 0;
}

