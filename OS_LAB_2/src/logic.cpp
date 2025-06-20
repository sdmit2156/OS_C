#include "logic.h"
#include <windows.h>
#include <vector>
#include <iostream>
using namespace std;

int g_min = 0;
int g_max = 0;
double g_average = 0.0;

DWORD WINAPI min_max(LPVOID arra) {
    vector<int>* arr = static_cast<vector<int>*>(arra);
    g_min = (*arr)[0];
    g_max = (*arr)[0];

    for (size_t i = 1; i < arr->size(); ++i) {
        if ((*arr)[i] < g_min) g_min = (*arr)[i];
        Sleep(7);
        if ((*arr)[i] > g_max) g_max = (*arr)[i];
        Sleep(7);
    }

    return 0;
}

DWORD WINAPI average(LPVOID arra) {
    vector<int>* arr = static_cast<vector<int>*>(arra);
    int sum = 0;

    for (size_t i = 0; i < arr->size(); ++i) {
        sum += (*arr)[i];
        Sleep(12);
    }

    g_average = static_cast<double>(sum) / arr->size();
    return 0;
}

vector<int> run_main(const vector<int>& input) {
    int n = input.size();
    vector<int> arr = input;

    HANDLE hMinMax = CreateThread(NULL, 0, min_max, &arr, 0, NULL);
    HANDLE hAverage = CreateThread(NULL, 0, average, &arr, 0, NULL);

    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);

    CloseHandle(hMinMax);
    CloseHandle(hAverage);

    for (int& num : arr) {
        if (num == g_min || num == g_max) {
            num = static_cast<int>(g_average);
        }
    }

    return arr;
}
