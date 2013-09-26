#ifndef EXT__TEST__BENCHMARK_H
#define EXT__TEST__BENCHMARK_H

#include <iostream>
#include <Windows.h>

#define Benchmark(description,lambda)     \
	do{                                                              \
	LARGE_INTEGER time_start;                       \
    LARGE_INTEGER time_over;                       \
    double freq;                                                \
    LARGE_INTEGER f;                                      \
    QueryPerformanceFrequency(&f);             \
    freq = (double)f.QuadPart;                         \
    QueryPerformanceCounter(&time_start);   \
	lambda();                                                      \
	QueryPerformanceCounter(&time_over);   \
	std::cout <<description<<" "<< ((time_over.QuadPart - time_start.QuadPart))  / freq << "s" << std::endl;\
	}while(0);

#endif