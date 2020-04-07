#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <iostream>
using namespace std;

int main()
{
    string line, filename;
    map <string,int> coronamap;

    ifstream in;
    cout<<"enter the file name: ";
    cin>>filename;

    in.open(filename.c_str());
    getline(in,line);

    string partOf;

    while (in)
    {
        // your implementation here for building coronamap
        int pos = line.find(" ", 0);
        string country = line.substr(0, pos);
        int population = stoi(line.substr(pos));
        coronamap.insert(pair<string, int>(country, population));
        getline(in, line);
    }
    
    // your implementation here to print the country with max cases
    // E.g. Most confirmed cases are in USA

    int max = 0;
    string maxC;
    for (auto& x:coronamap){
        if (x.second > max){
            max = x.second;
            maxC = x.first;
        }
    }
    cout << "Most confirmed cases are in " << maxC << endl;
    
    return 0;
}
