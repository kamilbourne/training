# C++ Projects
1. [FizzBuzz](#FizzBuzz)

## FizzBuzz
- About
	- small project that became whole day work - was applying for position and i have took the example test, then i was playing with FizzBuzz problem when number is divided by 3 write Fizz, when by 5 write "Buzz", when both write "FizzBuzz". I wrote it that next line mark will be given at the end of the iteration, so when it is divisible by 3, it will just write, next check if by 5, the if both are incorrect then it is number - extra bool flag to *print_int*. Checked with Gemini later, and the test was to check first both (3 and 5), then 3, then 5. I thought that my approach is more elegant and using less cpu. Then came let me use args, then maybe try with printing on the screen, then i re-wrote everything to have ability to choose ms, us, or just seconds. **Conclusion** CPU : method with flag, Data: method with more conditions. **Plus** there is a problem with compiling it under linux *(atomic) library*, after removing it it can be compiled without any problems and surprise surprise on linux the compiled program takes only couple hundred kilobytes (Lubuntu). 
	- **To Do**: 
			- make number of threads as a paremeter, good idea for benchmark.
			- rewrite chronos within the functions. 
			- make threads to return data. 
			- make threads to run one type of test, or selected types. 
			- add detection of threads available in the system. 
