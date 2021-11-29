#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<sstream>
using namespace std;
int data_variable[5][5];
void addline(int boxes[][5], int popsnum) {
    ofstream fout ("data.txt", ios::app);
    if (fout.fail()) {
        cout << "Error in addline! Game Exit" << endl;
        exit(1);
    }
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            fout << data_variable[i][j] << " ";
        }
    }
    fout << popsnum << endl;
    fout.close();
}
void readlastline(int boxes[][5], int &popsnum){
    ifstream fin ("data.txt");
    if (fin.fail()) {
        cout << "Error in readlastline! Game Exit" << endl;
        exit(1);
    }
    string s, t;
    while (getline(fin, s)){

    }
    stringstream linestream;
    linestream.str(s);
    int num;
    for (int i = 0; i < 5; i++){
        for (int k = 0; k < 5; k++){
            linestream>>num;
            boxes[i][k]=num;
        }
    }
    linestream>>num;
    popsnum=num;
    fin.close();
}

bool checkifempty(){
    ifstream fin ("data.txt");
    if (fin.fail()) {
        cout << "Error in checkifempty! Game Exit" << endl;
        exit(1);
    }
    int t;
    if(fin >> t)
        return true;
    else
        return false;
    fin.close();
}

void randselect(int data_variable[][5], int x){
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


void deletedata(){
    ofstream fout("data.txt");
    if (fout.fail()) {
        cout << "Error in deletefile! Game Exit" << endl;
        exit(1);
    }
    fout.close();
}

void deleteline(){
    vector<string> tmp_files;
	
	ifstream winfile( "data.txt" );
	if ( ! winfile )
	{
		cout << "Error in deleteline! Game Exit" << endl;
		exit(1);
	}

	string lineContent;
	while ( getline( winfile, lineContent, '\n' ) )
	{
		tmp_files.push_back( lineContent + "\r\n" );
	}

	winfile.close();

	ofstream offile( "data.txt",ios::out );
	vector<string>::iterator siter = tmp_files.begin();

	copy( tmp_files.begin(), tmp_files.end()-1, ostream_iterator<string>(offile) );

	cout << "Deleteline completed!" << endl;

	offile.close();
}
