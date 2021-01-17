#pragma once
#ifndef H_SUBSETS_H
#define H_SUBSETS_H
int FillArray(int*, int);
int AddMod(int*, int, int, int);
int SubstractMod(int*, int, int, int);
int MultiMod(int*, int, int, int);
bool CheckEle(int, int, int);
bool IsModPrime(int);
int ModInv(int**, int);
int Counter(int);
int NOD(int, int);
int CheckForRec(int**, int, int);
int ReciprocalByBezu(int, int);
int ModDivision(int**, int, int, int);
//funkcii za stepenuvane
//1 variant
int FastPow(int, int, int);
int BinaryPow(int, int, int);
int FillPrimeArray(int*, int);
bool IsNumPrimRoot(int*, int, int);
int FindPrimeRoot(int*, int*, int);
int FindDiscreteLog(int*, int, int, int);
void FreeMem(int**, int*, int*, int*, int);

#endif

