#include <list>
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <cstring>

using namespace std;

list<int> wczytaj(string arg, int s) {
	list<int> lista;
	char buf[3];
	buf[2]=0;
	int liczba, a=0;
	if(s%2==0) {
		buf[0]=arg[0];
		buf[1]=0;
		stringstream ss;
		ss << hex << buf;
		ss >> liczba;
		lista.push_back(liczba);
		a=1;
	}
	for(; arg[a]&&arg[a+1] ; a+=2) {
		buf[0]=arg[a];
		buf[1]=arg[a+1];
		stringstream ss;
		ss << hex << buf;
		ss >> liczba;
		lista.push_back(liczba);
	}
	return lista;
}

void drukuj(list<int> l) {
	for( list<int>::iterator iter=l.begin(); iter != l.end(); ++iter ) {
		//cout << " ";
		if(*iter<16)
			cout << "0";
		cout << hex << *iter;
	}
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
			quot=z.quot;
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

list<int> pomnozRaz(list<int> l, int a) {
	div_t z={0,0};
	for( list<int>::reverse_iterator iter=l.rbegin(); iter != l.rend(); ++iter ) {
		z=div(*iter*a+z.quot, 256);
		*iter=z.rem;
	}
	if(z.quot)
		l.push_front(z.quot);
	return l;
}
/*
10ad5
*
e7590

 */

list<int> pomnoz(list<int> l1, list<int> l2) {
	if(l1.size()<l2.size()) l1.swap(l2);
	int offset=0;
	list<int> w, p;
	for( list<int>::reverse_iterator i2=l2.rbegin(); i2 != l2.rend(); ++i2, offset++ ) {
			p=pomnozRaz(l1, *i2);
			p.resize(p.size()+offset, 0);
			//cout << "razy " << *i2 << ": ";
			//drukuj(p);
			w=dodaj(w, p);
	}
	return w;
}

char porownaj(list<int> l1, list<int> l2) {
	if(l1.size()<l2.size())
		return '<';
	else if(l1.size()>l2.size())
		return '>';
	else { //l1.size()==l2.size()
		for( list<int>::iterator i1=l1.begin(), i2=l2.begin(); i1 != l1.end()&&i2 != l2.end(); ++i1, ++i2 ) {
			if(*i1<*i2)
				return '<';
			else if(*i1>*i2)
				return '>';
		}
		return '=';
	}
}

int main(int argc, char *argv[]) {
	string a1, a2, op;
	cin >> a1 >> op >> a2;
	list<int> l1 = wczytaj(a1, a1.size()+1);
	list<int> l2 = wczytaj(a2, a2.size()+1);
	if(op.compare("?")==0)
		cout<<porownaj(l1, l2) << endl;
	else if(op.compare("*")==0)
		drukuj(pomnoz(l1, l2));
	return 0;
}
