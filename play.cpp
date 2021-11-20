//Written by Lu Xiaoyi
//
//The boxes shows as below
// ---- ---- ---- ---- ----
//|    |    |    |    |    |
// ---- ---- ---- ---- ----
//|    |    |    |    |    |
// ---- ---- ---- ---- ----
//|    |    |    |    |    |
// ---- ---- ---- ---- ----
//|    |    |    |    |    |
// ---- ---- ---- ---- ----
//|    |    |    |    |    |
// ---- ---- ---- ---- ----

#include <iostream>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
using namespace std;


void detspace(int rows, int columns, int &upspace, int &downspace, int &leftspace){
    if (columns / 2 == 1){
        upspace = (columns - 13) / 2;
        downspace = (columns - 13) / 2;
    }
    else {
        upspace = (columns - 12) / 2;
        downspace = (columns - 14) / 2;
    }
    if (rows / 2 == 1){
        leftspace = (columns - 25) / 2;
    }
    else{
        leftspace = (columns - 26) / 2;
    }
}


string opform(int x){
    if (x == 0){
        return("    ");
    }
    else if (x <= 3){
        return("  " + to_string(x) + " ");
    }
    else if (x <= 6){
        return(" " + to_string(x) + " ");
    }
    else if (x <= 9){
        return(" " + to_string(x));
    }
    else if (x <= 13){
        return(to_string(x));
    }
    else{
        return("2^" + to_string(x));
    }
}


void turnleft(int boxes[5][5]){
    int newboxes[5][5];
    for ( int i = 0; i < 5; i++ ){
        for ( int j = 0; j < 5; j++ ){
            newboxes[4-j][i] = boxes[i][j];
        }
    }
    for ( int i = 0; i < 5; i++ ){
        for ( int j = 0; j < 5; j++ ){
            boxes[i][j] = newboxes[i][j];
        }
    }
}

void turnright(int boxes[5][5]){
    int newboxes[5][5];
    for ( int i = 0; i < 5; i++ ){
        for ( int j = 0; j < 5; j++ ){
            newboxes[j][4-i] = boxes[i][j];
        }
    }
    for ( int i = 0; i < 5; i++ ){
        for ( int j = 0; j < 5; j++ ){
            boxes[i][j] = newboxes[i][j];
        }
    }
}

void turnaround(int boxes[5][5]){
    int newboxes[5][5];
    for ( int i = 0; i < 5; i++ ){
        for ( int j = 0; j < 5; j++ ){
            newboxes[4-i][4-j] = boxes[i][j];
        }
    }
    for ( int i = 0; i < 5; i++ ){
        for ( int j = 0; j < 5; j++ ){
            boxes[i][j] = newboxes[i][j];
        }
    }
}


void pile(int boxes[5][5]){
    for ( int i = 0; i < 5; i++ ){
        for ( int k = 0; k < 4; k++ ){
            for ( int j = 0; j < 4; j++ ){
                if (boxes[i][j] == 0 & boxes[i][j+1] != 0){
                    boxes[i][j] = boxes[i][j];
                    boxes[i][j+1] = 0;
                }
            }
        }
    }
}


void upopr(int boxes[5][5]){
    pile(boxes);
    for ( int i = 0; i < 5; i++ ){
        for ( int j = 0; j < 4; j++ ){
            if (boxes[i][j] == boxes[i][j+1] & boxes[i][j] != 0){
                boxes[i][j] = boxes[i][j] + 1;
                boxes[i][j+1] = 0;
            }
        }
    }
    pile(boxes);
}




void play(){


    int boxes[5][5]; //boxes is used to store current status
    int columns, rows; //columns and rows of this terminal
    int propnums, propson = 0;
    int upspace, downspace, leftspace;
    char keytype = '0';
    string opr;


    if (checkifempty == true){
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                boxes[i][j] = 0;
            }
        }
        randselect(boxes[5][5], 0);
        randselect(boxes[5][5], 0);
        propnums = 3;
        addline(3);
        addline(boxes[5][5]);
    }


    else{
        readlastline(boxes[5][5]);
    }


    while (keytype != 'e'){


        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        rows = w.ws_row;
        columns = w.ws_col;


        if ( rows < 25 | columns < 15 ) {
            cout << "please adjust the window" << endl;
            cout << "larger than 25*15" << endl;
            for( int i = 0; i < columns - 3 ; i++ ){
                cout << endl;
            }
        }


        else {
            cout << "Props remain: " << propnums << endl;
            detspace(rows, columns, upspace, downspace, leftspace);
            for ( int i = 0; i < upspace; i++){
                cout << endl;
            }
            for ( int i = 0; i < leftspace; i++){
                cout << " ";
            }
            cout << " ---- ---- ---- ---- ----" << endl;
            for ( int i = 0; i < 5; i++){
                for ( int j = 0; j < leftspace; j++){
                    cout << " ";
                }
                for ( int j = 0; j < 5; j++){
                    cout << "|" << opform(boxes[i][j]);
                }
                cout << "|" << endl;
                for ( int k = 0; k < leftspace; k++){
                    cout << " ";
                }
                cout << " ---- ---- ---- ---- ----" << endl;
            }
            for ( int i = 0; i < downspace; i++){
                cout << endl;
            }
            if (propson == 0){
                cout << "Your operation: ";
            }
            else if (propson == 1){
                cout << "Your operation with props: ";
            }
            else if (propson == 2){
                cout << "Wrong input, your operation: ";
                propson = 0;
            }
            else{
                cout << "Props cancelled, your operation: ";
                propson = 0;
            }
        }


        cin >> opr;
        if (opr == "w"){
            upopr(boxes);
            randselect(boxes[5][5], propson);
            propson = 0;
        }
        else if (opr == "a"){
            turnright(boxes);
            upopr(boxes);
            turnleft(boxes);
            randselect(boxes[5][5], propson);
            propson = 0;
        }
        else if (opr == "d"){
            turnleft(boxes);
            upopr(boxes);
            turnright(boxes);
            randselect(boxes[5][5], propson);
            propson = 0;
        }
        else if (opr == "s"){
            turnaround(boxes);
            upopr(boxes);
            turnright(boxes);
            randselect(boxes[5][5], propson);
            propson = 0;
        }
        else if (opr == "q"){
            if (propson == 0){
                if (propnums > 0){
                    propson = 1;
                    propnums--;
                }
                else{
                    propson = -1;
                }
            }
            else{
                propson = 0;
                propnums++;
            }
        }
        else if (opr == "e"){
            exit(0);
        }
        else{
            propson = 2;
        }
    }



}