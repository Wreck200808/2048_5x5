#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;
int data_variable[5][5];
void write_to_file() {
    ofstream fout("data.txt");
    if (fout.fail()) {
        cout << "Error in file opening! Game Exit" << endl;
        exit(1);
    }
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            fout << data_variable[i][j];
            fout << endl;
        }
        fout << endl;
    }
}
void extract_from_data(){
    ifstream fin ("data.txt");
    if (fin.fail()) {
        cout << "Error in file opening! Game Exit" << endl;
        exit(1);
    }
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
                fin >> data_variable[i][j];
            }
        }
    }
bool checkifempty(){
    ifstream fin ("data.txt");
    if (fin.fail()) {
        cout << "Error in file opening! Game Exit" << endl;
        exit(1);
    }
    int t;
    if(fin >> t)
        return true;
    else
        return false;
}
void randselect(int data_variable[5][5], int x){
    int empty[25][2], empty_num=0, random;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if(data_variable[i][j]==0){
                empty[empty_num][0]=i;
                empty[empty_num][1]=j;
                empty_num+=1;
            }
        }
    }
    if(x==0){
        srand(time(NULL));
        random=rand() % empty_num;
        data_variable[empty[random][0]][empty[random][1]] = rand()%2+1;
    }
    else{
        data_variable[empty[random][0]][empty[random][1]] = 3;
    }
}
