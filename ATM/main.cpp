#include"AMT.h"
#include<iostream>
#include<fstream>
#include<cstring>

#if 0
int main()
{
	AMT cash_machine;
	string transfer;
	
	while (true)
	{
		getline(cin, transfer, '\n');
		transform(transfer.begin(), transfer.end(), transfer.begin(), toupper);

		if (transfer.find("EXIT") != std::string::npos)
			return 0;

		cash_machine.proccesing(transfer);
	}
}
#else 
int main()
{
	ifstream in("test.txt");
	AMT cash_machine;
	string transfer;
	while (true)
	{
		getline(in, transfer, '\n');
		transform(transfer.begin(), transfer.end(), transfer.begin(), toupper);

		if (transfer.find("EXIT") != std::string::npos)
			return 0;
		cash_machine.proccesing(transfer);
	}
	system("pause");
}
#endif

