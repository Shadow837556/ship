#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>

using namespace std;

struct complex_
{
    double Re;
    double Im;
};

void look (const complex_* number)
{
    cout << "\nRe: " << number->Re;
    cout << "\nIm: " << number->Im;
}

complex_ sum (const complex_* number_1, const complex_* number_2)
{
    complex_ res;
    res.Re = number_1->Re + number_2->Re;
    res.Im = number_1->Im + number_2->Im;
    return res;
}

complex_ mult (const complex_* number_1, const complex_* number_2)
{
    complex_ res;
    res.Re = number_1->Re*number_2->Re - number_1->Im*number_2->Im;
    res.Im = number_1->Re*number_2->Im + number_1->Im*number_2->Re;
    return res;
}

double module (const complex_* number)
{
    return sqrt(pow(number->Re, 2) + pow(number->Im, 2));
}

double arg (const complex_* number)
{
    return atan2(number->Re, number->Im);
}

complex_ pairing_1 (const complex_* number)
{
    complex_ res;
    res.Im = -number->Im;
    res.Re = number->Re;
    return res;
}

void pairing_2 (complex_* number)
{
    number->Im = -number->Im;
}

int compare_module (const void* n1, const void* n2)
{
    complex_* number_1 = (complex_*) n1;
    complex_* number_2 = (complex_*) n2;
    if ( module(number_1) < module(number_2) ) return -1;
    if ( module(number_1) == module(number_2) ) return 0;
    if ( module(number_1) > module(number_2) ) return 1;
}

bool Mand (const complex_* number, int max_ = 10000 )
{
    complex_ see; see.Re = 0; see.Im = 0;
    for ( int i = 0; i < max_; i++ )
    {
        see = mult(&see, &see);
        see = sum(&see, number);
        ///see.Re = see.Re*see.Re - see.Im*see.Im + number->Re;
        ///see.Im = 2*see.Re*see.Im + number->Im;
        if ( module(&see) > 2 ) return false;
    }
    return true;
}

int main( int argc, char* argv[] )
{
    /**complex_ num_1; complex_ num_2;
    cout << "Enter the complex number 1: "; cin >> num_1.Re >> num_1.Im;
    cout << "Enter the complex number 2: "; cin >> num_2.Re >> num_2.Im;
    cout << "\nLook number 1:"; look(&num_1);
    cout << "\n\nLook number 2:"; look(&num_2);
    complex_ summa = sum(&num_1, &num_2);
    cout << "\n\nResult sum: "; look(&summa);
    cout << "\n\nModule number 1 is " << module(&num_1);
    cout << "\nArg number 1 is " << arg(&num_1);
    complex_ pair_ = pairing_1(&num_1);
    cout << "\n\nAfter pairing number 1:"; look(&pair_);
    pairing_2(&num_2);
    cout << "\n\nAfter pairing number 2:"; look(&num_2);*/

    /**complex_ arr[6];
    for ( int i = 0; i < 6; i++ )
    {
        arr[i].Re = rand();
        arr[i].Im = rand();
    }
    cout << "Before :\n";
    for ( int i = 0; i < 6; i++ )
    {
        cout << module(&arr[i]) << endl;
        //look(&arr[i]); cout << endl;
    }
    qsort(arr, 6, sizeof(complex_), compare_module);
    cout << "\n\nAfter (module):\n";
    for ( int i = 0; i < 6; i++ )
    {
        cout << module(&arr[i]) << endl;
        //look(&arr[i]); cout << endl;
    }*/

    double x_max = 1; double x_min = -2; double y_max = 1; double y_min = -1;
    double x_step = 0.05; double y_step = 0.05; int max_ = 10000;

    if ( argc == 8 )
    {
        x_max = atof(argv[1]); x_min = atof(argv[2]); x_step = atof(argv[3]);
        y_max = atof(argv[4]); y_min = atof(argv[5]); y_step = atof(argv[6]);
        max_ = atoi(argv[7]);
    }

    int n = (x_max - x_min)/x_step + 1; int m = (y_max - y_min)/y_step + 1;

    complex_ grid[n][m] = {};
    for ( int i = 0; i < n; i++ )
        for ( int j = 0; j < m; j++ )
        {
            grid[i][j].Re = x_min + i*x_step;
            grid[i][j].Im = y_max - j*y_step;
        }
    /**cout << grid[0][0].Re << "  " << grid[0][0].Im << endl;
    cout << grid[n-1][0].Re << "  " << grid[n-1][0].Im << endl;
    cout << grid[0][m-1].Re << "  " << grid[0][m-1].Im << endl;
    cout << grid[n-1][m-1].Re << "  " << grid[n-1][m-1].Im << endl;*/
    /**cout << Mand(&grid[0][0]) << endl;
    cout << Mand(&grid[31][21]);*/
    for ( int i = 0; i < m; i++ )
        {
            for ( int j = 0; j < n; j++ )
            {
                if ( Mand(&grid[j][i]) ) cout << "*";
                else cout << " ";
            }
            cout << endl;
        }
    /**ofstream outFile; outFile.open("picture.txt");
    for ( int i = 0; i < m; i++ )
        {
            for ( int j = 0; j < n; j++ )
            {
                if ( Mand(&grid[j][i], max_) ) outFile << "*";
                else outFile << " ";
            }
            outFile << endl;
        }*/

    cout << "\n\n";
    return 0;
}
