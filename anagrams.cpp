/******************************************************************************
| Lane Moseley - 11/20/18 - Anagram Finder                                    |
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

using namespace std;


// prototypes
void findAnagram ( vector<string> &dct, vector<string> &anagrams,
                   vector<int> &index, vector<bool> &used,
                   string &str, int pos );
bool getDictionary ( vector<string> &dictionary );
template<class TY> bool openFile ( TY &stream, string fname );


int main ( )
{
    string word = "";            // holds the word
    vector<string> dct;          // stores the dictionary
    vector<string> anagrams;     // stores found anagrams
    vector<int> indexes;         // holds permuted indexes
    vector<bool> used;           // tracks used indexes during permutation
    int count = 1;               // counter for output formatting
    
    
    cout << "Loading dictionary..." << endl;
    
    if ( !getDictionary ( dct ) )
    {
        return 1;
    }
    
    cout << "Dictionary loaded." << endl << endl;
    
    cout << "Enter a word (or ctr-z to stop): ";
    
    while ( getline ( cin, word ) )
    {
        // matching vector size to word size
        indexes.resize ( word.size(), 0 );
        used.resize ( word.size(), false );
        
        // searching for anagrams
        findAnagram ( dct, anagrams, indexes, used, word, 0 );
        
        if ( anagrams.empty() )
        {
            // no results found
            cout << "\nNo anagrams found for \"" << word << "\"\n" << endl;
            cout << "Enter a word (or ctr-z to stop): ";
        }
        
        else
        {
            // outputting results
            cout << "\nAnagrams for \"" << word << "\": " << endl;
            
            for ( auto x : anagrams )
            {
                cout << x << ( count % 5 == 0 ? "\n" : "\t" );
                ++count;
            }
            
            // resetting vectors
            anagrams.clear();
            indexes.clear();
            used.clear();
            word.clear();
            
            cout << ( ( ( count - 1 ) % 5 == 0 ) ? "\n" : "\n\n" )
                 << "Enter a word (or ctr-z to stop): ";
                 
            // resetting counter
            count = 1;
        }
    }
    
    return 0;
}



// supporting functions
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