#pragma once

#include "DList.h"
#include "free_functions.h"
#include "main_functions.h"

// Random board functions
void pickRan(short board[][SIZE], Array*** possible_solutions);
void randomCell(short board[][SIZE], Array*** possibilities, Cell cl);
