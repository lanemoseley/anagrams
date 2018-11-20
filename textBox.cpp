#include "textBox.h"

// functions for displaying the text box //////////////////////////////////////
void printBottom ( int width )
{
    unsigned char bl_corner = 200;
    unsigned char br_corner = 188;
    unsigned char flat = 205;
    int i;

    cout << bl_corner;
    
    for ( i = 0; i < width + 1; ++i )
    {
        cout << flat;
    }
    
    cout << br_corner << endl;
}



void printData ( string &datastr, int pad, int width )
{
    int count = 1;
    int j = 0;
    int i;
    unsigned char vert = 186;
    
    while ( j < datastr.size() )
    {
        cout << vert << " ";
        
        for ( i = 0; i < width; ++i )
        {
            if ( i < pad / 2 )
            {
                cout << " ";
            }
            
            else if ( j < datastr.size() && datastr[j] != ' ' && count <= 5 )
            {
                cout << datastr[j];
                ++j;
            }
            
            else if ( j < datastr.size() && datastr[j] == ' ' )
            {
                cout << " ";
                ++j;
                ++count;
            }
            
            else
            {
                cout << " ";
            }
        }
        
        count = 1;
        cout << vert << endl;
    }
}



void printLabel ( string &label, int pad, int width )
{
    int i, j;
    unsigned char vert = 186;
    
    j = 0;
    cout << vert << " ";
    
    for ( i = 0; i < width; ++i )
    {
        if ( i < pad / 2 )
        {
            cout << " ";
        }
        
        else if ( j < label.size() )
        {
            cout << label[j];
            ++j;
        }
        
        else
        {
            cout << " ";
        }
    }
    
    cout << vert << endl;
}



void printLine ( int width )
{
    int i;
    unsigned char vert = 186;
    
    cout << vert;
    
    for ( i = 0; i < width + 1; ++i )
    {
        cout << " ";
    }
    
    cout << vert << endl;
}



void printTop ( int width )
{
    unsigned char tl_corner = 201;
    unsigned char tr_corner = 187;
    unsigned char flat = 205;
    int i;

    cout << tl_corner;
    
    for ( i = 0; i < width + 1; ++i )
    {
        cout << flat;
    }
    
    cout << tr_corner << endl;
}



void textBox ( string &label, vector<string> &data, int pad )
{
    string datastr;
    string padding;
    int i, width;
    
    // forming data string
    for ( i = 0; i < data.size(); ++i )
    {
        if ( i == data.size() - 1 )
        {
            datastr += data[i];
        }
        
        else
        {
            datastr = datastr + data[i] + ", ";
        }
    }
    
    // forming pad string
    for ( i = 0; i < pad / 2; ++i )
    {
        padding += " ";
    }
    
    // setting block width
    width = int ( label.size() ) + pad;
    
    if ( data.size() < 5 &&
            width < ( int ( data[0].size( ) ) + 2 )  * int ( data.size() ) + pad )
    {
        width = ( int ( data[0].size( ) ) + 2 ) * int ( data.size() ) + pad;
    }
    
    else if ( data.size() > 4 &&
              width < ( int ( data[0].size() ) + 2 ) * 5 + pad )
    {
        width = ( int ( data[0].size() ) + 2 ) * 5 + pad;
    }
    
    printTop ( width );
    printLabel ( label, pad, width );
    printLine ( width );
    printData ( datastr, pad, width );
    printBottom ( width );
}