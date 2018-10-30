#pragma once
#ifndef AMT_H
#define AMT_H

#include<map>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm> 
#include<regex>
#include<vector>
using namespace std;
typedef unsigned int uint;

struct Note
{
	uint val;		  //   достоинство валюты
	uint amt;		  //   количество 
	uint use;
	uint min;
	Note(uint val = 0, uint amt = 0, uint use = 0,
		uint min = 0) :val(val), amt(amt), use(use), min(min) {};
	bool operator < (const Note&) const;
	bool operator > (const Note&) const;
	bool operator == (const Note&) const;
	bool operator != (const Note&) const;
};

class AMT
{

	map<string, vector<Note>> currencies;
	map<string, uint > currencyAmount;

	void findsum(vector<Note>& mn, size_t n,
		uint& alluse, uint allsum);
	
	void set(const string&, uint, uint);
	void get(const string&, uint );

public:

	void proccesing(string&);
	void show_currencies();

};
#endif // !AMT_H
