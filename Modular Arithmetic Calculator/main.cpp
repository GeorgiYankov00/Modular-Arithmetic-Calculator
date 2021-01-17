#include <iostream>
#include <math.h>
#include <cstdlib>
#include "Header.h";
using namespace std;
int main() {
	//sz e modula
	int sz, ele1, ele2, menu;
	cout << "Enter the size of the ring: ";
	cin >> sz;
	//suzdavane na dvumeren masiv;za 5 zadacha
	int* array = new int[sz];

	//suzdavane na masiv ot reciprochni chisla
	int** reciprocal = new int* [Counter(sz)];

	//suzdavane na masiv ot vzaimno prosti chisla s modula;za 11 zadacha
	int* primearray = new int[Counter(sz)];

	//vsichki primitivni koreni; za 12 zadacha
	int* primerootarr = new int[sz];

	//!!!MENU
	do {
		cout << "Enter which exercise do you want to see: " << endl;
		cin >> menu;


		switch (menu)
		{
		case 1:
			//funkciq za zapulvane na ostatuchniq prusten
			FillArray(array, sz);
			//otpechatvane na elementite na masiva
			for (unsigned i = 0; i < sz; ++i) {
				cout << array[i] << "\t";
			}
			cout << endl;
			break;


		case 2:
			//funkciq za subirane
			cout << "Enter which elements of the array you would like to see the addition with: \n";
			do {
				cin >> ele1;
				cin >> ele2;
				//proverka dali sa v granicite na masiva
			} while (CheckEle(ele1, ele2, sz));
			cout << array[ele1 - 1] << " + " << array[ele2 - 1] << " =(mod " << sz << ") " << AddMod(array, sz, ele1, ele2) << endl;
			break;

		case 3:
			//funkciq za izvajdane
			cout << "Enter which elements of the array you would like to see the subtraction with: \n";
			do {
				cin >> ele1;
				cin >> ele2;

			} while (CheckEle(ele1, ele2, sz));

			cout << array[ele1 - 1] << " - " << array[ele2 - 1] << " =(mod " << sz << ") " << SubstractMod(array, sz, ele1, ele2) << endl;


		case 4:
			//funkciq za umnojenie
			cout << "Enter which elements of the array you would like to see the multiplication with: \n";
			do {
				cin >> ele1;
				cin >> ele2;

			} while (CheckEle(ele1, ele2, sz));
			cout << array[ele1 - 1] << " * " << array[ele2 - 1] << " =(mod " << sz << ") " << MultiMod(array, sz, ele1, ele2) << endl;
			break;


		case 5:
			//dvoika reciprochni v masiv
			IsModPrime(sz);

			for (unsigned i = 0; i < Counter(sz); i++) {
				reciprocal[i] = new int[2];
			}
			//zapulvane na dvumeren masiv s dvoiki reciprochni
			ModInv(reciprocal, sz);
			//pechatane
			cout << "These are all of the reciprocal values in Zn:" << endl;
			for (int i = 0; i < Counter(sz); i++)
			{
				cout << "The reciprocal of " << "1/" << reciprocal[i][0] << " is " << reciprocal[i][1] << endl; \
			}
			break;


		case 6:
			//proverka v masiva dali daden element ima reciprocha stoinost
			cout << "Enter an element in the range of the modulo to see its reciprocal: ";
			do {
				cin >> ele1;
			} while (ele1 > sz);
			if (CheckForRec(reciprocal, ele1, sz)) cout << "The reciprocal of " << ele1 << " is " << CheckForRec(reciprocal, ele1, sz) << endl;
			else cout << "No reciprocal found." << endl;
			break;


		case 7:
			//variant 2 za reciprochni, chrez Bezu i Evklid
			cout << "Enter an element in the size of the array to find if it has a reciprocal value: ";
			cin >> ele1;
			if (ReciprocalByBezu(sz, ele1) == -1) cout << "There is no reciprocal value for " << ele1 << endl;
			else cout << "The reciprocal value of " << ele1 << " is " << ReciprocalByBezu(sz, ele1) << endl;
			break;


		case 8:
			//zadacha s delenie
			cout << "Enter two elements in the range of the ring to see if it is possible to do division with them: ";
			do {
				cin >> ele1;
				cin >> ele2;
			} while (CheckEle(ele1, ele2, sz));
			if (ModDivision(reciprocal, ele1, ele2, sz) != -1) cout << "The division between " << ele1 << " and " << ele2 << " is possible and the result is " << ModDivision(reciprocal, ele1, ele2, sz) << endl;
			else cout << "The division between " << ele1 << " and " << ele2 << " is not possible.Result is " << ModDivision(reciprocal, ele1, ele2, sz) << endl;
			break;


		case 9:
			//funkcii za stepenuvane
			int power, base;
			cout << "Enter the base and the power you'd like to see it being raised to: " << endl;
			cin >> base >> power;
			cout << "The result of " << base << " raised to the power of " << power << " by mod (" << sz << ")" << " is: " << FastPow(sz, base, power) << endl;
			break;


		case 10:
			//funkcii za stepenuvane vtori variant
			cout << "Enter the base and power to see bitwise fast power: ";
			cin >> base >> power;
			cout << "The result of " << base << " to the power of " << power << " by modulo of " << sz << " is " << BinaryPow(sz, base, power) << endl;
			break;


		case 11:
			//funkciq, koqto proverqva dali chislo e primitiven koren
			FillPrimeArray(primearray, sz);
			cout << "\nEnter a number in the range of the array to see if it is a prime root: ";
			cin >> ele1;
			if (IsNumPrimRoot(primearray, ele1, sz)) cout << "The number " << ele1 << " from modulo " << sz << " is a prime root." << endl;
			else cout << "The number " << ele1 << " from modulo " << sz << " is not a prime root" << endl;
			break;


		case 12:
			//funkciq, koqto namira vsichki primitivni koreni
			FindPrimeRoot(primerootarr, primearray, sz);
			if (FindPrimeRoot(primerootarr, primearray, sz)) cout << "There are no prime roots in this modulo.";
			else
			{
				cout << "The prime roots of " << sz << " are: ";
				for (unsigned i = 0; i < Counter(sz); i++) {
					if (primerootarr[i] < 0) break;
					cout << primerootarr[i] << " | ";

				}
			}
			break;


		case 13:
			//funkciq za namirane na dlog
			int number;
			cout << "\nEnter the base and the number to find the discrete logharitm: ";
			cin >> base >> number;
			if (FindDiscreteLog(primearray, sz, base, number) == -1) cout << " The dlog of base " << base << " and number " << number << " can not be calculated. Result is " << FindDiscreteLog(primearray, sz, base, number) << endl;
			else cout << "The dlog of number " << number << " and base " << base << " is " << FindDiscreteLog(primearray, sz, base, number) << endl;
			break;


		case 14:
			//funkciq koqto proverqva dali Zn e Fn
			if (IsModPrime(sz)) cout << "Modulo n= " << sz << " is a Prime number and the ring Zn is called a field and it is marked with Fn.";
			else cout << "Modulo " << sz << " is not a prime number." << endl;
			break;

		}
	} while (menu != 0);
	//osvobojdavane na pametta
	FreeMem(reciprocal, primerootarr, primearray, array, sz);

	return 0;

}
