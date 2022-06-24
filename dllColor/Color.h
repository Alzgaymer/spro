#pragma once
#include <ctime>
#include <stdlib.h>
#define DLLEXP extern "C" __declspec(dllexport)
DLLEXP void RandomTextColour(HDC);