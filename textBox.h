#include <iostream>
#include <string>
#include <vector>

using namespace std;

void printBottom ( int width );
void printData ( string &datastr, int pad, int width );
void printLabel ( string &label, int pad, int width );
void printLine ( int width );
void printTop ( int width );
void textBox ( string &label, vector<string> &data, int pad );