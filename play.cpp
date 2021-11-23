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
#include <cstdio>
#include <unistd.h>
#include <string>
using namespace std;

//calculate the space after detecting the rows and columns
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

//output the form of numbers in boxes
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

//rotate the boxes in anticlockwise by 90 degrees
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

//rotate the boxes in clockwise by 90 degrees
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

//rotate the boxes in clockwise by 180 degrees
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

//slide all numbers upward without adding up
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

//calculate the outcome while slide upward
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


bool detectfail(int boxes[5][5]){
    int failcount = 0;
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if (boxes[i][j] == 0){
                failcount = failcount + 1;
            }
        }
    }
    if (failcount == 0){
        return true;
    }
    else{
        return false;
    }
}

//play execution
void play(){

    //variables
    int boxes[5][5]; //boxes is used to store current status
    int columns, rows; //columns and rows of this terminal
    int propsnum, propson = 0; //the remaining numbers of props and the state of propsusage
    int upspace, downspace, leftspace; //space numbers when showing boxes
    char keytype = '0';
    string opr;
    bool iffail = false; //show whether you are fail

    //check if it is a new game before staring up
    //if it is a new game
    if (checkifempty == true){
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                boxes[i][j] = 0;
            }
        }
        randselect(boxes, 0);
        randselect(boxes, 0);
        propsnum = 3;
        addline(boxes, 3);
    }

    //if continue the original one
    else{
        readlastline(boxes, propsnum);
    }

    //the loop for game
    while (keytype != 'e'){

        //detect the size of terminal
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        rows = w.ws_row;
        columns = w.ws_col;

        //check if fail and show boxes or tips
        if (iffail){
            cout << "You have failed!" << endl;
            cout << "Z:BACK X:AGAIN" << endl;
            for( int i = 0; i < columns - 3 ; i++ ){
                cout << endl;
            }
        }
        else{
            //warning if the terminal is smaller than 25*15
            if ( rows < 25 | columns < 15 ) {
                cout << "please adjust the window" << endl;
                cout << "larger than 25*15" << endl;
                for( int i = 0; i < columns - 3 ; i++ ){
                    cout << endl;
                }
            }

            //show the boxes
            else {
                cout << "Props remain: " << propsnum << endl;
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
        }


        //operate the boxes
        cin >> opr;
        if (opr == "w"){
            upopr(boxes);
            iffail = detectfail(boxes);
            if (iffail == false){
                randselect(boxes, propson);
                if (propson == 1){
                    propsnum--;
                }
            }
            propson = 0;
            addline(boxes, propsnum);
        }
        else if (opr == "a"){
            turnright(boxes);
            upopr(boxes);
            turnleft(boxes);
            iffail = detectfail(boxes);
            if (iffail == false){
                randselect(boxes, propson);
                if (propson == 1){
                    propsnum--;
                }
            }
            propson = 0;
            addline(boxes, propsnum);
        }
        else if (opr == "d"){
            turnleft(boxes);
            upopr(boxes);
            turnright(boxes);
            iffail = detectfail(boxes);
            if (iffail == false){
                randselect(boxes, propson);
                if (propson == 1){
                    propsnum--;
                }
            }
            propson = 0;
            addline(boxes, propsnum);
        }
        else if (opr == "s"){
            turnaround(boxes);
            upopr(boxes);
            turnright(boxes);
            iffail = detectfail(boxes);
            if (iffail == false){
                randselect(boxes, propson);
                if (propson == 1){
                    propsnum--;
                }
            }
            propson = 0;
            addline(boxes, propsnum);
        }
        else if (opr == "q"){
            if (propson == 0){
                if (propsnum > 0){
                    propson = 1;
                }
                else{
                    propson = -1;
                }
            }
            else{
                propson = 0;
            }
        }
        else if (opr == "e"){
            keytype = 'e';
        }
        else if (opr == "z"){
            deleteline();
            readlastline(boxes, propsnum);
        }
        else if (opr == "x"){
            deletedata();


            for (int i = 0; i < 5; i++){
                for (int j = 0; j < 5; j++){
                    boxes[i][j] = 0;
                }
            }
            randselect(boxes, 0);
            randselect(boxes, 0);
            propsnum = 3;
            addline(boxes, 3);
        }
        else{
            propson = 2;
        }
    }


}