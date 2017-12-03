#ifndef DISCOL_H
#define DISCOL_H


#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <bitset>
#include <map>

#define DEBUG 0


void checkArgs(char *argv[], int argc, bool &encrypt, bool &decrypt, std::string &keyString, bool &intermediateTable, bool &backfill, int &N, bool &help);
void omitSpacing(std::string &inputs);
void select(std::string arguments, bool &encrypt, bool &decrypt, std::string &keyString, bool &intermediateTable, bool &backfill, int &N, bool &help);
void makeAlphaNumeric(std::string &inputs);
void nonAlphaNumStdErr(std::string &inputs, bool decrypt);
void toUpperCase(std::string &keyString);
void maxKeyLength(std::string &keyString);
void setMatrix(std::vector<std::vector<char> > &matrix, std::string keyString);
void sortKey(std::string &strSortedKey, std::string &keyString);
void makePair(std::vector<std::pair<char, int> > &pear1, std::vector<std::pair<char, int> > &pear2, std::string &keyString, std::string &strSortedKey);
void xEncrypt(std::vector<std::vector<char> > &matrix, std::vector<std::pair<char, int> > pear1, std::vector<std::pair<char, int> > pear2, std::string &keyString, std::string &strSortedKey, std::string inputs, bool intermediateTable, int N, bool backfill);
void xDecrypt(std::vector<std::vector<char> > &matrix, std::vector<std::pair<char, int> > pear1, std::vector<std::pair<char, int> > pear2, std::string &keyString, std::string &strSortedKey, std::string inputs, bool intermediateTable, int N, bool backfill);
void fillMatrixEncrypt(std::string &inputs, int &row, int &column, int &counter, std::vector<std::vector<char> > &matrix, std::vector<std::pair<char, int> > &pear2);
void fillMatrixDecrypt(std::string &inputs, int &row, int &column, int &counter, std::vector<std::vector<char> > &matrix, std::vector<std::pair<char, int> > &pear1, std::vector<std::pair<char, int> > &pear2);
void intTable(int row, int column, std::vector<std::vector<char> > &matrix, std::vector<std::pair<char, int> > pear1);
void readOutEncrypt(std::vector<std::vector<char> > &matrix, std::vector<std::pair<char, int> > pear2, int row, int column, int N);
void readOutDecrypt(std::vector<std::vector<char> > &matrix, int row, int column, int N);
void executeBackfill(std::vector<std::vector<char> > &matrix, int row, int column, std::string inputs, int counter);

#endif
