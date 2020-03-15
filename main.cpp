#include <iostream>
#include <fstream>
#include<vector>
#include<set>
#include<fstream>

using namespace std;

typedef pair <int,int> pairs;
vector<pairs>s1;
vector<pairs>s2;

int check_r(int i, int j, int x[][7])
{
//check the right cell
    if (x[i][j+1]==46)
        return true;
    else
        return false;
}

int check_l(int i, int j, int x[][7])
{
    //check the left cell
    if (x[i][j-1]==46)
        return true;
    else
        return false;
}

int check_d(int i, int j, int x[][7])
{
//check the bottom cell
    if (x[i+1][j]==46)
        return true;
    else
        return false;
}

int checky(int i,int j,int x[][7], int counter)
{
/*
check the available cells around our cells
move to the available cell
then call this function agian
we keep recursion this function unitl there
is no available cells to move to
*/
    if(check_r(i,j,x))
        {
            x[i][j]=counter;
            /* the previous line is used to handle
            the case of visited cells */
            s1.push_back(make_pair(i,j));
            counter++;
            j++;
            checky(i,j,x,counter);
        }
    else if(check_l(i,j,x))
        {
            x[i][j]=counter;
            s1.push_back(make_pair(i,j));
            counter++;
            j--;
            checky(i,j,x,counter);
        }
    else if (check_d(i,j,x))
        {
            x[i][j]=counter;
            s1.push_back(make_pair(i,j));
            counter++;
            i++;

            checky(i,j,x,counter);
        }
    else
        {
            x[i][j]=counter;
            s1.push_back(make_pair(i,j));
            return counter;
        }
}

int main()
{

int x[5][7];
char y;
//read from the txt file and arrange them in an array
 ifstream infile;
 infile.open("labi.txt");
 for (int i=0; i<5; i++)
{
    for (int j=0; j<7; j++)
    {
        infile>>y;
        x[i][j]=y;
    }
}
infile.close();

int finale=0;
int max_counter=0;

//look for the starting of the path
for (int i=0; i<7; i++)
{

    int counter = 0;
    if (x[0][i]=='.')
    {
       //complete the path till the end
       finale = checky(0,i,x,counter);
    }
    // if the path is longer the previous one or not
    if ((finale+1)>max_counter)
    {
        s2=s1;
        max_counter=finale+1;
    }
    s1.clear();
}

cout<<max_counter<<endl;

//put the ascii for '.' in all possible paths
for (int i=0; i<5; i++)
{
    for (int j=0; j<7; j++)
    {
        if(0<=x[i][j] && x[i][j]<=20)
        {
            x[i][j]=46;
        }
    }
}


int c=0;

//put the numbers for the longest path
for (auto it=s2.begin(); it != s2.end(); it++)
{
    x[(*it).first][(*it).second]=c;
    c++;
}

//print every thing as a character except for numbers
for (int i=0; i<5; i++)
{
    for (int j=0; j<7; j++)
    {
        if (0<=x[i][j] && x[i][j]<=20)
            cout<<x[i][j]<<" ";
        else
            cout<<char(x[i][j])<<" ";
    }
    cout<<endl;
}

}
