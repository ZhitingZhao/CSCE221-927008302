#include <fstream>
#include <cctype>
#include <set>
#include <string>
#include <iostream>
using namespace std;

bool isChar(string a){
    if ((a >="A" && a <= "Z") || (a >= "a" && a <= "z")){
        return true;
    }
    return false;
}

int main()
{
    string line, filename, word;
    int pos;
    int lineNum = 1;
    
    ifstream in;
    set<string> idents;
    set<string> reserved;
    string reserveArray[]= {"for", "if","else", "fstream", "set","string",
        "include", "main", "using", "namespace","std", "iostream", "string", 
        "ifstream","char","auto","size","open","while","return","int","endl"};
    
    for (int i = 0; i <22; i++)
        reserved.insert(reserved.end(),reserveArray[i]);

    cout<<"enter the file name: ";
    cin>>filename;

    in.open(filename.c_str());
    getline(in,line);

    while (in)
    {
        // Your implementatio here
//        cout << line << endl;
        pos = line.find("//");  // this line has commit
        if (pos < line.size()){
            line = line.substr(0, pos);
        }
        pos = line.find("#");
        if (pos < line.size()){
            line = "";
        }
        pos = line.find("\""); // inside string constant
        if (pos < line.size()){
            string rest = line.substr(pos+1);
//            cout << rest << endl;
            int ano = rest.find("\"") + pos; // position of another "
            rest = line.substr(0, pos);
//            cout << rest << endl;
            rest.append(line.substr(ano+2));
//            cout << line.substr(ano+2) << endl;
            line = rest;
//            cout << line << endl;
        }
        
        for (int j = 0; j < 22; j++){    //search for every word in reserveArray
            pos = line.find(reserveArray[j]);
            while (pos >= 0 && pos < line.size()){    //find a word in line
                pos += reserveArray[j].length();  //pos now is the position of the end of that found word.
                string finds = line.substr(pos);
                while (!isChar(line.substr(pos,1)) && pos < line.size()){  //find the position of the start of ident
                    pos += 1;
                }
                int sta = pos;
                while (isChar(line.substr(pos, 1))&& pos < line.size()){   //find the position of the end of ident
                    pos += 1;
                }
                word = line.substr(sta, pos-sta);
                line = line.substr(pos);
                pos = line.find(reserveArray[j]);
                bool in = false;
                if (word == ""){
                    in = true;
                }
                for (int k = 0; k < 22 && !in; k++){
                    if (word == reserveArray[k]){
                        in = true;
                    }
                }
                if (!in){
//                    cout << word << endl;
                    idents.insert(idents.end(), word);
//                    cout << lineNum << endl;
//                    cout << endl;
                }
                
            }
        }
        getline(in, line);
        lineNum += 1;
    }

    for (auto x:idents)
        cout<<x<<endl;
    return 0;
}
