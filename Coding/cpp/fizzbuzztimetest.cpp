//Testing the solution with if and double condition vs setting bool var for printing in c++
#include <iostream>
#include <chrono>
#include <string>
#include <stdexcept>
#include <thread>
#include <atomic>
using namespace std;
//list of functionsb
void fizzbuzz1(unsigned int n);
void fizzbuzz2(unsigned int n);
void fizzbuzz1assign(unsigned int n);
void fizzbuzz2assign(unsigned int n);
void fizzbuzz1print(unsigned int n);
void fizzbuzz2print(unsigned int n);
void fizzbuzz1clean(unsigned int n);
void fizzbuzz2clean(unsigned int n);
void wyswietl_pomoc(const char* nazwa_programu);
void wyswietl_wstep();
//Const
const char* nazwa_programu = "FizzBuzzTimeTest";
//Global VAR
bool wstep = false;
bool tests[4] = {false,true,true,true}; //print,org,assign,clean
bool zeZmienna = true;
bool threads = false;
thread t1, t2, t3, t4, t5, t6, t7, t8; 
int threadsnum = 0;
string nazwaTestu[2]  = {"",""};
string wyjatekPrint = "";
unsigned long long int N = 100000;
std::atomic<unsigned long long int> global_sink = 0;
string timefactorstr = "mikrosekund";
int timefactorint = 0;
int main(int argc, char* argv[]){
	if(argc > 1 )
	{
		string arg = "";
		for (int i = 1; i < argc; ++i)
		{
			arg = argv[i];
			if (arg == "--help" || arg == "-h")
			{
				wyswietl_pomoc(argv[0]);
				return 0;
			}
			else if (arg == "--print" || arg == "-p")
			{
				tests[0] = true;
			}
			else if (arg == "--wstep" || arg == "-w")
			{
				wstep = true;
			}
			else if (arg == "--noorg" || arg == "-no")
			{
				tests[1] = false;
			}
			else if (arg == "--noassign" || arg == "-na")
			{
				tests[2] = false;
			}
			else if (arg == "--noclean" || arg == "-nc")
			{
				tests[3] = false;
			}
			else if (arg == "--microseconds" || arg == "-u")
			{
				timefactorstr = "mikrosekund";
				timefactorint = 0;
			}
			else if (arg == "--milliseconds" || arg == "-m")
			{
				timefactorstr = "miilisekund";
				timefactorint = 1;
			}
			else if (arg == "--seconds" || arg == "-s")
			{
				timefactorstr = "sekund";
				timefactorint = 2;
			}
			else if (arg == "--threads" || arg == "-t")
			{
				threads = true;
			}
			else
			{
				try
				{
					unsigned long long int temp_n = stoul(arg);
					N = static_cast<unsigned long long int>(temp_n);
				}
				catch (const invalid_argument& e)
				{
					std::cerr << "Blad: " << arg << " Nie jest poprawnym argumentem ani poprawna liczba calkowita\n";
					wyswietl_pomoc(nazwa_programu);
					return 1;
				}
				catch (const out_of_range& e) 
				{
					std::cerr << "Blad: Liczba " << arg << " jest poza zasiegiem\n";
					wyswietl_pomoc(nazwa_programu);
					return 1;
				}
			}
		}
	}
	if(N == 0)
	{
		std::cerr << "Blad: Liczba dla ktorej beda wykonane testy musi byc wieksza od 0\n";
		wyswietl_pomoc(nazwa_programu);
		return 1;
	}
	if(!tests[0] && !tests[1] && !tests[2] && !tests[3])
	{
		cout << "Serio?" << endl;
		return 0;
	}
	else 
	{
		if(wstep){wyswietl_wstep();}
		cout << "Test uruchomione dla \tN=" << N << endl << endl; 
	}
	if(!threads)
	{
		auto startglobal = std::chrono::high_resolution_clock::now();
		for(int i=0; i <= sizeof(tests)-1; i++)
		{
			for (int j=0; j<=1; j++)
			{

				if(tests[i])
				{
					auto start = std::chrono::high_resolution_clock::now();
					switch(i)
					{
						case 0:
						{
							if(zeZmienna) 
							{								
								fizzbuzz1print(N);
								zeZmienna = false;
								nazwaTestu[j] = "FizzBuzz ze zmienna na ekranie:\t\t\t";
							}
							else
							{
								fizzbuzz2print(N);
								zeZmienna = true;
								nazwaTestu[j] = "FizzBuzz z waurunkami na ekranie:\t\t";
							}
							break;
						} 
						case 1: 
						{
							if(zeZmienna) 
							{
								fizzbuzz1(N);
								zeZmienna = false;
								nazwaTestu[j] = "FizzBuzz ze zmienna oryginalny:\t\t\t";
							}
							else
							{
								fizzbuzz2(N);
								zeZmienna = true;
								nazwaTestu[j] = "FizzBuzz z waurunkami oryginalny:\t\t";
							}
							break;
						}
						case 2: 
						{
							if(zeZmienna) 
							{
								fizzbuzz1assign(N);
								zeZmienna = false;
								nazwaTestu[j] = "FizzBuzz ze zmienna przypisywanie:\t\t";
							}
							else
							{
								fizzbuzz2assign(N);
								zeZmienna = true;
								nazwaTestu[j] = "FizzBuzz z waurunkami przypisywanie:\t\t";
							}
							break;
						}
						case 3: 
						{
							if(zeZmienna) 
							{
								fizzbuzz1clean(N);
								zeZmienna = false;
								nazwaTestu[j] = "FizzBuzz ze zmienna clean:\t\t\t";
							}
							else
							{
								fizzbuzz2clean(N);
								zeZmienna = true;
								nazwaTestu[j] = "FizzBuzz z waurunkami clean:\t\t\t";
							}
							break;
						}
					}
					auto end = chrono::high_resolution_clock::now();
					auto duration = end - start;
					auto czasmicro = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
					auto czassec = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
					auto czasmili = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
					switch(timefactorint)
					{
						case 0:
						{
							if(i!=0)
							{
								cout << nazwaTestu[j] << czasmicro << " " << timefactorstr << endl;
							}
							else if (i==0 && j==0)
							{
								string czas = to_string(czasmicro);
								wyjatekPrint = nazwaTestu[j].append(czas).append(" ").append(timefactorstr).append("\n");
							}
							else
							{
								cout << wyjatekPrint;
								cout << nazwaTestu[j] << czasmicro << " " << timefactorstr << endl;
							}
							break;
						}
						case 2:
						{
							if(i!=0)
							{
								cout << nazwaTestu[j] << czassec << " " << timefactorstr << endl;
							}
							else if (i==0 && j==0)
							{
								string czas = to_string(czassec);
								wyjatekPrint = nazwaTestu[j].append(czas).append(" ").append(timefactorstr).append("\n");
							}
							else
							{
								cout << wyjatekPrint;
								cout << nazwaTestu[j] << czassec << " " << timefactorstr << endl;
							}
							break;
						}
						case 1:
						{
							if(i!=0)
							{
								cout << nazwaTestu[j] << czasmili << " " << timefactorstr << endl;
							}
							else if (i==0 && j==0)
							{
								string czas = to_string(czasmili);
								wyjatekPrint = nazwaTestu[j].append(czas).append(" ").append(timefactorstr).append("\n");
							}
							else
							{
								cout << wyjatekPrint;
								cout << nazwaTestu[j] << czasmili << " " << timefactorstr << endl;
							}
							break;
						}
					}
				}
			}
		}	
		if(tests[3]){cout << "\nSuma Kontrolna: \t\t\t\t" << global_sink << "\n";}
		auto endglobal = chrono::high_resolution_clock::now();
		auto durationglobal = endglobal - startglobal;
		auto czasglobalmicro = std::chrono::duration_cast<std::chrono::microseconds>(durationglobal).count();
		auto czasglobalsec = std::chrono::duration_cast<std::chrono::seconds>(durationglobal).count();
		auto czasglobalmili = std::chrono::duration_cast<std::chrono::milliseconds>(durationglobal).count();
		if(timefactorint==0){cout << "Calkowity czas wykonania:\t\t\t" << czasglobalmicro << " " << timefactorstr << endl;}
		else if(timefactorint==1){cout << "Calkowity czas wykonania:\t\t\t" << czasglobalmili << " " << timefactorstr << endl;}
		else {cout << "Calkowity czas wykonania:\t\t\t" << czasglobalsec << " " << timefactorstr << endl;}
		return 0;
	}
	else
	{
		auto startglobal = std::chrono::high_resolution_clock::now();
		//thread t1(fizzbuzz1print, N);							
		//thread t2(fizzbuzz2print, N);
		thread t3(fizzbuzz1, N);
		thread t4(fizzbuzz2, N);
		thread t5(fizzbuzz1assign, N);	
		thread t6(fizzbuzz2assign, N);				
		thread t7(fizzbuzz1clean, N);							
		thread t8(fizzbuzz2clean, N);	
		//t1.join();		
		//t2.join();
		t3.join();
		t4.join();	
		t5.join();		
		t6.join();
		t7.join();
		t8.join();						
		if(tests[3]){cout << "\nSuma Kontrolna: \t\t\t\t" << global_sink << "\n";}
		auto endglobal = chrono::high_resolution_clock::now();
		auto durationglobal = endglobal - startglobal;
		auto czasglobalmicro = std::chrono::duration_cast<std::chrono::microseconds>(durationglobal).count();
		auto czasglobalsec = std::chrono::duration_cast<std::chrono::seconds>(durationglobal).count();
		auto czasglobalmili = std::chrono::duration_cast<std::chrono::milliseconds>(durationglobal).count();
		if(timefactorint==0){cout << "Calkowity czas wykonania:\t\t\t" << czasglobalmicro << " " << timefactorstr << endl;}
		else if(timefactorint==1){cout << "Calkowity czas wykonania:\t\t\t" << czasglobalmili << " " << timefactorstr << endl;}
		else {cout << "Calkowity czas wykonania:\t\t\t" << czasglobalsec << " " << timefactorstr << endl;}
		return 0;	
	}
}

void fizzbuzz1(unsigned int n)
{
	bool print = true; 
	for(int i=1; i<=n; i++)
	{
		print = true;
		if(i % 3 == 0)
		{
			//cout << "Fizz";
			print = false;
		}
		if(i % 5 == 0)
		{
			//cout << "Buzz";
			print = false;
		}
		if (print)
		{ 
			//cout << i; 
		}
		//cout << endl;
	}
}

void fizzbuzz2(unsigned int n)
{
	for(int i=1; i<=n; i++)
	{
		if(i % 3 == 0 && i % 5 ==0)
		{
			//cout << "FizzBuzz\n";
		}
		else if (i % 3 == 0)
		{
			//cout << "Fzzz\n";
		}
		else if (i % 5 == 0)
		{
			//cout << "Buzz\n";
		}
		else
		{
			//cout << i << "\n";
		}
	}
}

void fizzbuzz1print(unsigned int n)
{
	bool print = true; 
	for(int i=1; i<=n; i++)
	{
		print = true;
		if(i % 3 == 0)
		{
			cout << "Fizz";
			print = false;
		}
		if(i % 5 == 0)
		{
			cout << "Buzz";
			print = false;
		}
		if (print)
		{ 
			cout << i; 
		}
		cout << endl;
	}
}

void fizzbuzz2print(unsigned int n)
{
	string drukuj = "";
	for(int i=1; i<=n; i++)
	{
		if(i % 3 == 0 && i % 5 ==0)
		{
			cout << "FizzBuzz\n";
		}
		else if (i % 3 == 0)
		{
			cout << "Fzzz\n";
		}
		else if (i % 5 == 0)
		{
			cout << "Buzz\n";
		}
		else
		{
			cout << i << "\n";
		}
	}
}

void fizzbuzz1assign(unsigned int n)
{
	string drukuj = "";
	bool print = true; 
	for(int i=1; i<=n; i++)
	{
		print = true;
		if(i % 3 == 0)
		{
			//cout << "Fizz";
			drukuj = "Fizz";
			print = false;
		}
		if(i % 5 == 0)
		{
			//cout << "Buzz";
			drukuj = "Buzz";
			print = false;
		}
		if (print)
		{ 
			//cout << i; 
			drukuj = to_string(i);
		}
		//cout << endl;
	}
}

void fizzbuzz2assign(unsigned int n)
{
	string drukuj = "";
	for(int i=1; i<=n; i++)
	{
		if(i % 3 == 0 && i % 5 ==0)
		{
			//cout << "FizzBuzz\n";
			drukuj = "FizzBuzz";
		}
		else if (i % 3 == 0)
		{
			//cout << "Fzzz\n";
			drukuj = "Fizz";
		}
		else if (i % 5 == 0)
		{
			//cout << "Buzz\n";
			drukuj = "Buzz";
		}
		else
		{
			//cout << i << "\n";
			drukuj = to_string(i);
		}
	}
}

void fizzbuzz1clean(unsigned int n)
{
	unsigned long counter = 0;
	bool print = true; 
	for(int i=1; i<=n; i++)
	{
		print = true;
		if(i % 3 == 0)
		{
			counter += 3; //Fizz
			print = false;
		}
		if(i % 5 == 0)
		{
			counter += 5; //Buzz
			print = false;
		}
		if (print)
		{ 
			counter += 1; //Liczba
		}
	}
	global_sink += counter;
}

void fizzbuzz2clean(unsigned int n)
{
	unsigned long counter = 0;
	for(int i=1; i<=n; i++)
	{
		if(i % 3 == 0 && i % 5 ==0)
		{
			counter += 15; //FizzBuzz
		}
		else if (i % 3 == 0)
		{
			counter += 3; //Fizz
		}
		else if (i % 5 == 0)
		{
			counter += 5; //Buzz
		}
		else
		{
			counter += 1; //liczba
		}
	}
	global_sink += counter;
}
void wyswietl_wstep()
{
	cout << "Cel Zadania: Jak liczba jest podzielna przez 3 wyswietl Fizz, jak przez 5 Buzz, jak przez 3 i 5 wyswietl FizBuzz\n";
	cout << "Wykonujac to zadanie zrobilem je troche inaczej jak nakazuje logika, dalem jak 3, to wyswietl Fizz, jak 5 Buzz, ale ustawiaj flage zeby nie drukowalo liczby, wydrukuj liczbe jak nie jest podzielna przez nic i po kazdym obrocie petli drukuj znak konca linii. Gemini natomiast podeszlo do tego troche inaczej bo najpierw wykonuje porownanie czy jest podzielna liczba przez 3 i 5, a pozniej znowu czy jest podzielna przez 3, a jak nie to czy jest podzielna przez 5, jak nie jest to wydrukuj liczbe. To podejscie wydalo mi sie dosyc marnotrawne dlatego napisalem testy ktore maja sprawdzic ktore podejscie jest bardziej wydajne, jedno tez z pomoca gemini\n";
	cout << "Niby marnowanie czasu ale jednak ciekawie jest sprawdzic wydajnosc danego rozwiazania plus przypomniec sobie podstawy c++\n";
}

void wyswietl_pomoc(const char* nazwa_programu)
{
	cout << "Uzycie: " << nazwa_programu << " <Liczba> [Opcje] \n\n";
	cout << "Argumenty:\n";
	cout << "<Liczba>\t\t-Liczba calkowita (domyslnie: 100000) dla ktorej zostana wykonane testy\n";
	cout << "[Opcje]:\n";
	cout << "--help, -h\t\t - Wyswietla ten komunikat pomocy\n";
	cout << "--wstep, -w\t\t - Wyswietla informacje wstepne\n";
	cout << "--print, -p\t\t - Wyswietla wszystkie kroki dla obu wersji, debug, domyslnie wylaczone\n";
	cout << "--noorg, -no\t\t - nie uruchamiaj testow dla oryginalnego kodu\n";
	cout << "--noassign, -na\t\t - nie uruchamiaj testow dla kodu z przypisaniem lancuchow znakow\n";
	cout << "--noclean, -nc\t\t - nie uruchamiaj testow dla czystego kodu z optymializacja black hole\n";
	cout << "--microseconds, -u\t\t - wyswietla czas w mikrosekundach\n";
	cout << "--milliseconds, -m\t\t - wyswietla czas w milisekundach\n";
	cout << "--seconds, -s\t\t - wyswietla czas w sekundach\n";
}

// if(print)//original loops - with printing
	// {
	// 	auto start1print = std::chrono::high_resolution_clock::now();
	// 	fizzbuzz1print(N);
	// 	auto end1print = chrono::high_resolution_clock::now();
	// 	auto duration1print = end1print - start1print;
	// 	auto microseconds1print = std::chrono::duration_cast<std::chrono::microseconds>(duration1print).count();
	// 	auto start2print = chrono::high_resolution_clock::now();
	// 	fizzbuzz2print(N);
	// 	auto end2print = std::chrono::high_resolution_clock::now();
	// 	auto duration2print = end2print - start2print;
	// 	auto microseconds2print = std::chrono::duration_cast<std::chrono::microseconds>(duration2print).count();
	// 	cout << "Czas wykonania fizzbuzz ze zmienna (fizzbuzz1print):\t " << microseconds1print << " mikrosekund\n";
	// 	cout << "Czas wykonania fizzbuzz2 z warunkami (fizzbuzz2print):\t " << microseconds2print << " mikrosekund.\n";
	// }
	// if(org)	//original loops - withouth printing
	// {
	// 	auto start1 = std::chrono::high_resolution_clock::now();
	// 	fizzbuzz1(N);
	// 	auto end1 = chrono::high_resolution_clock::now();
	// 	auto duration1 = end1 - start1;
	// 	auto microseconds1 = std::chrono::duration_cast<std::chrono::microseconds>(duration1).count();
	// 	auto start2 = chrono::high_resolution_clock::now();
	// 	fizzbuzz2(N);
	// 	auto end2 = std::chrono::high_resolution_clock::now();
	// 	auto duration2 = end2 - start2;
	// 	auto microseconds2 = std::chrono::duration_cast<std::chrono::microseconds>(duration2).count();
	// 	cout << "Czas wykonania fizzbuzz ze zmienna (fizzbuzz1):\t\t " << microseconds1 << " mikrosekund\n";
	// 	cout << "Czas wykonania fizzbuzz2 z warunkami (fizzbuzz2):\t " << microseconds2 << " mikrosekund.\n";
	// }
	// if(assign)//with string assign operations and converions to string
	// {
	// 	auto start1assign = std::chrono::high_resolution_clock::now();
	// 	fizzbuzz1assign(N);
	// 	auto end1assign = chrono::high_resolution_clock::now();
	// 	auto duration1assign = end1assign - start1assign;
	// 	auto microseconds1assign = std::chrono::duration_cast<std::chrono::microseconds>(duration1assign).count();
	// 	auto start2assign = chrono::high_resolution_clock::now();
	// 	fizzbuzz2assign(N);
	// 	auto end2assign = std::chrono::high_resolution_clock::now();
	// 	auto duration2assign = end2assign - start2assign;
	// 	auto microseconds2assign = std::chrono::duration_cast<std::chrono::microseconds>(duration2assign).count();
	// 	cout << "Czas wykonania fizzbuzz ze zmienna (fizzbuzz1assign):\t " << microseconds1assign << " mikrosekund\n";
	// 	cout << "Czas wykonania fizzbuzz2 z warunkami (fizzbuzz2assign):\t " << microseconds2assign << " mikrosekund.\n";
	// }
	// if(clean)//clean loops with tricks to not remove the ifs or other parts of code for optimisation
	// {
	// 	auto start1clean = std::chrono::high_resolution_clock::now();
	// 	fizzbuzz1clean(N);
	// 	auto end1clean = chrono::high_resolution_clock::now();
	// 	auto duration1clean = end1clean - start1clean;
	// 	auto microseconds1clean = std::chrono::duration_cast<std::chrono::microseconds>(duration1clean).count();
	// 	auto start2clean = chrono::high_resolution_clock::now();
	// 	fizzbuzz2clean(N);
	// 	auto end2clean = std::chrono::high_resolution_clock::now();
	// 	auto duration2clean = end2clean - start2clean;
	// 	auto microseconds2clean = std::chrono::duration_cast<std::chrono::microseconds>(duration2clean).count();
	// 	cout << "Czas wykonania fizzbuzz ze zmienna (fizzbuzz1clean):\t " << microseconds1clean << " mikrosekund\n";
	// 	cout << "Czas wykonania fizzbuzz2 z warunkami (fizzbuzz2clean):\t " << microseconds2clean << " mikrosekund.\n";
	// }