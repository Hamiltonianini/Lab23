#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream file (filename);
    string results;
    int num1, num2, num3;
    
    while(getline(file, results)){
        char n[1000];
        char format[] = "%[^:]:%d %d %d";
        sscanf(results.c_str(),format, n, &num1, &num2, &num3);
        int sum = num1 + num2 + num3;

        names.push_back(n);
        scores.push_back(sum);
        grades.push_back(score2grade(sum));
    }
}

void getCommand(string &command, string &key){
    string line;
    char a[1000], b[1000];
    cout << "Please input your command:" << endl;
    getline(cin,line);
    
    sscanf(line.c_str(), "%s, %s", a, b);
    int space = line.find(' ');
    command = line.substr(0,space);
    key = line.substr(space + 1);

}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, const string &key){
    bool search = false;
    int nameSize = names.size();
    cout << "---------------------------------" << endl;
    
    for(int i=0; i<nameSize; i++){
        if(key == toUpperStr(names[i])){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            search = true;
        }
    }
    
    if(search==false){
        cout << "Cannot found." << endl;
    }
    
    cout << "---------------------------------" << endl;
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool search = false;
    int gradeSize = grades.size();
    cout << "---------------------------------" << endl;
    
    for(int i=0; i<gradeSize; i++){
        if(key[0] == grades[i]){
            cout << names[i] << " (" << scores[i] << ")" << endl;
            search = true;
        }
    }
    
    if(search==false){
        cout << "Cannot found." << endl;
    }
    
    cout << "---------------------------------" << endl;

}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
