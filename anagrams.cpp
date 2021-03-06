/******************************************************************************
| Lane Moseley - 11/20/18 - Anagram Solver                                    |
|                                                                             |
| Description: This program uses brute force permutation to find all anagrams |
|              of a given word. The results are output for the user. Any .txt |
|              file with newline separated values can be used in place of the |
|              current dictionary.                                            |
|                                                                             |
******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "textBox.h"

using namespace std;


// prototypes
void clean ( vector<string> &v, string term );
bool compare ( string left, string right );
void findAnagram ( vector<string> &dct, vector<string> &anagrams,
                   vector<int> &index, vector<bool> &used,
                   string &str, int pos );
bool getDictionary ( vector<string> &dictionary );
template<class TY> bool openFile ( TY &stream, string fname );


int main ( )
{
    vector<string> anagrams;     // stores found anagrams
    vector<string> dct;          // stores the dictionary
    vector<int> indexes;         // holds permuted indexes
    string label = "";                
    vector<bool> used;           // tracks used indexes during permutation
    string word = "";

    cout << "Loading dictionary..." << endl;
    
    if ( !getDictionary ( dct ) )
    {
        return 1;
    }
    
    cout << "Dictionary loaded." << endl << endl;
    
    cout << "Enter a lowercase word (or ctr-z to stop): ";
    
    while ( getline ( cin, word ) )
    {
        // matching vector size to word size
        indexes.resize ( word.size(), 0 );
        used.resize ( word.size(), false );
        
        // searching for anagrams
        findAnagram ( dct, anagrams, indexes, used, word, 0 );
        clean ( anagrams, word );
        
        if ( anagrams.empty() )
        {
            // no results found
            cout << "No anagrams found for \"" << word << "\"\n" << endl;
            cout << "Enter a lowercase word (or ctr-z to stop): ";
        }
        
        else
        {
            // outputting results
            label = "Anagrams for \"" + word + "\": ";
            textBox ( label, anagrams, 6 );
            
            // resetting vectors
            anagrams.clear();
            indexes.clear();
            used.clear();
            word.clear();
            
            cout << "\nEnter a lowercase word (or ctr-z to stop): ";
        }
    }
    
    return 0;
}



// Supporting Functions ///////////////////////////////////////////////////////

// sorts and eliminates duplicates in a string vector
void clean ( vector<string> &v, string term )
{
    vector<string>::iterator curr, next;
    
    if ( v.empty() )
    {
        return;
    }
    
    // sorting vector
    sort ( v.begin(), v.end(), compare );
    
    // eliminating duplicates
    curr = v.begin();
    next = curr + 1;
    
    while ( v.size() > 1 &&  curr + 1 != v.end() )
    {
        if ( *curr == term || *curr == *next )
        {
            v.erase ( next );
            
            curr = v.begin();
            next = curr + 1;
        }
        
        else
        {
            ++curr;
            ++next;
        }
    }
}



// compares two values
bool compare ( string left, string right )
{
    return left < right;
}



void findAnagram ( vector<string> &dct, vector<string> &anagrams,
                   vector<int> &index, vector<bool> &used,
                   string &str, int pos )
{
    string duplicate;
    int i;
    int len = int ( str.size() );
    
    if ( pos == len )
    {
        duplicate = str;
        
        // forming permuted string
        for ( i = 0; i < len; ++i )
        {
            duplicate[index[i]] = str[i];
        }
        
        // searching dictionary
        if ( binary_search ( dct.begin(), dct.end(), duplicate )
                && duplicate != str )
        {
            anagrams.push_back ( duplicate );
        }
        
        return;
    }
    
    for ( i = 0; i < len; ++i )
    {
        if ( !used[i] )
        {
            // permuting index
            index[pos] = i;
            
            used[i] = true;
            
            findAnagram ( dct, anagrams, index, used, str, pos + 1 );
            
            used[i] = false;
        }
    }
    
    return;
}



// loads and sorts .txt dictionary
bool getDictionary ( vector<string> &dictionary )
{
    ifstream din;
    string temp;
    
    // opening dictionary file
    if ( !openFile ( din, "dictionary.txt" ) )
    {
        return false;
    }
    
    // reading dictionary into vector
    while ( din >> temp )
    {
        dictionary.push_back ( temp );
    }
    
    // sorting dictionary
    sort ( dictionary.begin(), dictionary.end() );
    
    din.close();
    
    return true;
}



template<class TY> bool openFile ( TY &stream, string fname )
{
    stream.open ( fname );
    
    if ( !stream.is_open() )
    {
        cout << "Error: \"" << fname << "\" failed to open";
        
        return false;
    }
    
    return true;
}