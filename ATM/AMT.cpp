#include "AMT.h"

void AMT::set(const string &currency, uint val, uint amt)
{
	Note note(val, amt);
	if (currencies.empty())
	{
		currencies[currency].push_back(note);
		currencyAmount.insert(make_pair(currency, val*amt)); // общая сумма выбранной валюты 
	}
	else
	{
		auto mapIter = currencies.find(currency);
		if (mapIter != currencies.end())					 // если такая валюта уже есть 
		{

			for (auto VecIter = mapIter->second.begin(); VecIter != mapIter->second.end(); ++VecIter)
			{
				if (VecIter->val == val) // =
				{
					VecIter->amt += amt;
					break;
				}
				else if (VecIter->val < val) // val < listIter->val
				{
					mapIter->second.insert(VecIter, note);
					break;
				}
				else if (VecIter == mapIter->second.end() - 1) // if doesn't contain such value
				{
					mapIter->second.push_back(note);
					break;
				}
			}
			currencyAmount[currency] += val * amt;
		}
		else
		{
			currencies[currency].push_back(note);
			currencyAmount.insert(make_pair(currency, val*amt));
		}
	}
}

void AMT::get(const string &currency, uint amt)
{
	uint amountCopy = amt;

	uint alluse = 1;
	uint sum = 0;
	if (currencies.empty())
	{
		cout << " Insufficient funds in wallet of this currency! " << endl;
	}
	else
	{
		auto mapIter = currencies.find(currency);
		if (mapIter != currencies.end() && (currencyAmount[currency] >= amt))
		{
			for (auto VecIter = mapIter->second.begin(); VecIter != mapIter->second.end(); ++VecIter)
			{
				alluse += VecIter->amt;
			}
			findsum(currencies.find(currency)->second, 0, alluse, amt);

			for (auto VecIter = mapIter->second.begin(); VecIter != mapIter->second.end(); ++VecIter)
			{

				if (VecIter->min)
				{
					int dsum = VecIter->val*VecIter->min;
					sum += dsum;
				}
			}
			if (sum != amt) cout << " Insufficient funds in wallet of this currency!1 " << endl;
			else
			{
				currencyAmount[currency] -= amt;
				for (auto VecIter = mapIter->second.begin(); VecIter != mapIter->second.end(); ++VecIter)
				{
					if (VecIter->min)
					{
						VecIter->amt -= VecIter->min;
						VecIter->use = 0;
					}
				}
			}
		}
		else cout << "currency not found!" << endl;
	}
}


void AMT::findsum(vector<Note>& mn, size_t n, uint& alluse, uint allsum)
{
	uint use = 0, sum = 0;
	for (size_t i = 0; i != n; i++)
	{
		use += mn[i].use;
		sum += mn[i].val*mn[i].use;
	}
	for (size_t l = 0; l <= mn[n].amt && use + l < alluse; l++)
	{
		mn[n].use = l;
		int dsum = l * mn[n].val;
		if (sum + dsum == allsum)
		{
			alluse = use + l;
			for (size_t i = 0; i < mn.size(); i++)
			{
				mn[i].min = mn[i].use;
				//cout << "**номинал:" << (*mn)[i].nom << " количество:" << (*mn)[i].min << " сумма:" << dsum << endl;
			}
			break;
		}
		if (sum + dsum > allsum) break;
		if (n < mn.size() - 1) findsum(mn, n + 1, alluse, allsum);
	}
	mn[n].use = 0;
}

void AMT::proccesing(string &transfer)
{
	cmatch result;


	if (transfer[0] == '+')
	{
		transfer.erase(0, 1);
		regex regular("([A-Z]{3}) (\\d{1,6}) (\\d{1,10})");
		if (regex_match(transfer.c_str(), result, regular))
		{

			string str = result[1];
			int value = stoi(result[2]);
			int amt = stoi(result[3]);

			set(result[1], stoi(result[2]), stoi(result[3]));
		}
		else
			cout << " error sintax!" << endl;


		show_currencies();
	}
	else if (transfer[0] == '-')
	{
		transfer.erase(0, 1);
		regex regular("([A-Z]{3}) (\\d{1,10})");
		if (regex_match(transfer.c_str(), result, regular))
		{
			get(result[1], stoi(result[2]));

		}
		else
			cout << "sintax error!" << endl;

		show_currencies();
	}
	else cout << "ERROR" << endl;
}

void AMT::show_currencies()
{
	cout << "***************************************************" << endl;
	for (auto fIter : currencies)
	{
		cout << "currency: " << fIter.first << " amount:" << currencyAmount[fIter.first] << endl;
		for (auto sIter : fIter.second)
		{
			cout << "  " << sIter.val << ' ' << sIter.amt << endl;
		}
	}
	cout << "***************************************************" << endl;
}

bool Note::operator<(const Note& other) const
{
	return val < other.val;
}

bool Note::operator>(const Note &other) const
{
	return val > other.val;
}

bool Note::operator==(const Note &other) const
{
	return val == other.val;
}

bool Note::operator!=(const Note &other) const
{
	return val != other.val;
}
