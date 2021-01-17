#include "Header.h"
#include <iostream>
#include <math.h>
using namespace std;
int FillArray(int* array, int sz)
{
	for (unsigned i = 0; i < sz; i++)
	{
		array[i] = i;
	}

	return 0;
}
int AddMod(int* array, int sz, int ele1, int ele2)
{
	FillArray(array, sz);
	int sum = 0;
	sum = array[ele1 - 1] + array[ele2 - 1];
	return  sum >= sz ? sum - sz : sum;
}
int SubstractMod(int* array, int sz, int ele1, int ele2)
{
	FillArray(array, sz);
	return (array[ele1 - 1] - array[ele2 - 1] + sz) % sz;
}
int MultiMod(int* array, int sz, int ele1, int ele2)
{
	FillArray(array, sz);
	//long long zashtoto razmera na proizvedenieto move da nadvishi granicite na int
	return ((long long)array[ele1 - 1] * array[ele2 - 1]) % sz;
}

bool CheckEle(int ele1, int ele2, int sz) {
	//proverka dali elementite sa v granicite na masiva
	return (ele1 > sz || ele2 > sz);
}
//proverka dali mod e prosto
bool IsModPrime(int sz)
{
	if (sz == 1) return false;
	if (sz == 2) return true;
	for (unsigned i = 2; i <= sqrt(sz); i++) {
		if (sz % i == 0) return false;

	}
	return true;
}
//algoritum na evklid
int NOD(int a, int b)
{
	if (a == 0)
		return b;
	return NOD(b % a, a);
}
//broqch za zadelqneto na pametta
int Counter(int sz) {
	int cnt = 1;
	//ako modula e prosto chislo
	if (IsModPrime(sz))
	{

		return sz - 1;
	}
	//ako modula ne e prosto chislo
	else
	{
		for (unsigned i = 2; i < sz; i++) {
			if (NOD(i, sz) == 1) {
				cnt++;
			}

		}
		return cnt;
	}
}
int ModInv(int** reciprocal, int sz)
{
	unsigned cnt = 0;
	if (IsModPrime(sz)) {

		for (unsigned i = 1; i < sz; i++)
		{
			for (unsigned u = 1; u < sz; u++)
			{

				if ((u * i) % sz == 1)
				{

					reciprocal[cnt][0] = i;
					reciprocal[cnt][1] = u;
					cnt++;
					continue;
				}
			}

		}
	}
	else
	{
		for (unsigned i = 1; i < sz; i++)
		{
			if (i % sz == 1)
			{
				for (unsigned i = 1; i < sz; i++)
				{
					for (unsigned u = 1; u < sz; u++)
					{

						if ((u * i) % sz == 1)
						{

							reciprocal[cnt][0] = i;
							reciprocal[cnt][1] = u;
							cnt++;
							continue;
						}
					}

				}
			}
			else continue;
		}
	}
	return 0;
}
int CheckForRec(int** reciprocal, int ele1, int sz)
{
	for (unsigned i = 0; i < Counter(sz); i++)
	{
		if (reciprocal[i][0] == ele1) return reciprocal[i][1];
		continue;
	}
	return 0;
}
//metod za reciprochni s bezu
int ReciprocalByBezu(int sz, int ele1) {

	int sum, recip;
	unsigned cnt = 0;
	int x = (sz > ele1) ? sz : ele1;
	int y = (sz < ele1) ? sz : ele1;
	int tmp = x % y;
	while (tmp) {
		x = (tmp > y) ? tmp : y;
		y = (tmp < y) ? tmp : y;
		tmp = x % y;
		cnt++;
	}
	if (cnt > 0) {
		//suzdavane na tablica na bezu
		int** bezutable = new int* [4];
		for (unsigned int i = 0; i < 4; i++) {
			bezutable[i] = new int[cnt + 2];
		}
		x = (sz > ele1) ? sz : ele1;
		y = (sz < ele1) ? sz : ele1;


		bezutable[0][0] = x;
		bezutable[0][1] = y;
		bezutable[1][0] = 0;
		bezutable[2][0] = 1;
		bezutable[2][1] = 0;
		bezutable[3][0] = 0;
		bezutable[3][1] = 1;
		int j = 2;
		tmp = x % y;
		while (tmp) {
			bezutable[0][j] = tmp;
			bezutable[1][j - 1] = x / y;
			x = (tmp > y) ? tmp : y;
			y = (tmp < y) ? tmp : y;
			tmp = x % y;
			j++;
		}
		bezutable[1][j - 1] = x / y;

		for (unsigned int i = 2; i < 4; i++) {
			for (unsigned int j = 2; j < cnt + 2; j++) {
				if (i == 2)
					bezutable[i][j] = bezutable[i - 1][j - 1] * bezutable[i][j - 1] + bezutable[i][j - 2];
				else
					bezutable[i][j] = bezutable[i - 2][j - 1] * bezutable[i][j - 1] + bezutable[i][j - 2];
			}
		}

		sum = pow(-1, cnt + 2) * bezutable[3][cnt + 1]; //-2

		if (sum < 0)
			sum += sz;


		recip = (ele1 * sum) % sz;
		if (recip == 1) {
			return sum;
		}

		for (unsigned int i = 0; i < 4; i++) {
			delete[] bezutable[i];
		}
		delete[] bezutable;
		bezutable = nullptr;
	}

	return -1;
}
//funkciq za delenie ako e vuzmojno
int ModDivision(int** reciprocal, int ele1, int ele2, int sz)
{


	for (unsigned i = 0; i < Counter(sz); i++)
	{
		if (reciprocal[i][0] == ele2) return (ele1 * (CheckForRec(reciprocal, ele2, sz))) % sz;

	}
	return -1;
}
//funkcii za stepenuvane
int FastPow(int sz, int base, int power) {
	//sum shte e za zapazvane na stoinostta ot povdigane na stepen, newpow shte e promenlivata koqto e rezultat ot m(mod k)
	int k = 0, sum, newPow;

	//cikul, koito da namira stoinostta na k
	for (unsigned i = 2; i < power; i++) {
		//vremenna promenliva v koqto shte se zapazva rezultata
		int x = pow(base, i);

		if ((x % sz) == 1) {
			k = i;
			break;
		}
	}

	//m(mod) k
	newPow = power % k;
	sum = pow(base, newPow);
	return sum % sz;
}
//variant 2 za stepenuvane
int BinaryPow(int sz, int base, int power) {
	//broqch za razmer na masiv

	int counter = 0, tmp = power;
	while (power != 0)
	{
		power /= 2;
		counter++;
	}
	//vremenna promenliva za da se zapazi stoinostta na stepenta
	power = tmp;
	int* bits = new int[counter];

	for (unsigned i = 0; i < counter; i++)
	{
		bits[i] = power % 2;
		power = power / 2;
	}

	//masiv za stepenite na dvoikata
	int* bitpower = new int[counter - 1];
	bitpower[0] = 2;


	for (unsigned i = 1; i < counter - 1; i++)
	{
		int sum = pow(bitpower[i - 1], 2);
		bitpower[i] = (int)pow(bitpower[i - 1], 2) % sz;
	}
	//reshenie

	int sum = 1;
	for (unsigned i = 0; i < counter; i++) {

		if (bits[i] == 1)
		{

			sum *= bitpower[i - 1];
		}
	}
	if (bitpower != nullptr)
	{
		delete[]bitpower;
		bitpower = NULL;
	}
	if (bits != nullptr)
	{
		delete[]bits;
		bits = NULL;
	}


	//abs stoinost zashtoto ako chisloto e naprimer 33 i se predstavq kato 100001 ,poslednata 1 nqma da ima stoinost v masivut i shte vrushta rezultatatut sus znak -
	return abs(sum % sz);

}

//primitivni koreni i dlog
int FillPrimeArray(int* primearray, int sz) {
	//vinagi 1 e purvi element v masiva ot vzaimno prosti chisla
	primearray[0] = 1;
	for (unsigned i = 2, cnt = 1; i < sz; i++) {
		//proverka dali chislata sa vzaimno prosti s modula i vkarvaneto im v masiva ako sa 
		if ((NOD(i, sz)) == 1)
		{

			primearray[cnt] = i;
			cnt++;

		}

	}
	return 0;
}

bool IsNumPrimRoot(int* primearray, int ele1, int sz)
{
	//broqch za cikula, kogato stane raven na razmera na masiva znachi imame primitiven koren
	int counter = 0;

	for (unsigned i = 0, j = 1; j < sz; j++)
	{

		long long value = pow(ele1, j);

		if (primearray[i] == value % sz)
		{
			i++;
			counter++;
			//zanulqvame stepenta za da zapochnem otnacholo proverkata s vtori element ot masiva
			j = 0;
		}
		if (counter == Counter(sz))
		{
			return true;

		}


	}

	if (counter != Counter(sz)) return false;
}
int FindPrimeRoot(int* primerootarr, int* primearray, int sz)
{
	int cnt = 0;
	//ot 2 zashtoto nqma kak 1 da e primitiven koren
	for (unsigned i = 2; i < sz; i++)
	{
		if (IsNumPrimRoot(primearray, i, sz))
		{
			primerootarr[cnt] = i;
			cnt++;
		}


	}
	if (cnt == 0) return 1;
	else return 0;


}
int FindDiscreteLog(int* primearray, int sz, int base, int number)
{
	//po uslovie 
	if (number == 1) return 0;

	int sum = 0;
	//proverka dali chisloto e primitiven koren, za da se nameri dlog

	if (IsNumPrimRoot(primearray, base, sz)) {


		for (unsigned i = 1; i < Counter(sz); i++)
		{
			sum = pow(base, i);
			sum %= sz;
			if (sum == number) return i;

		}
	}
	else return -1;

}
void FreeMem(int** reciprocal, int* primerootarr, int* primearray, int* array, int sz) {
	if (primerootarr != nullptr)
	{
		delete[] primerootarr;
		primerootarr = NULL;
	}

	if (primearray != nullptr)
	{
		delete[] primearray;
		primearray = NULL;
	}
	if (array != nullptr)
	{
		delete[] array;
		array = NULL;
	}
	if (reciprocal != nullptr) {
		for (unsigned i = 0; i < sz; i++) {
			delete[] reciprocal[i];
		}
		delete[]reciprocal;
		reciprocal = NULL;
	}
}






