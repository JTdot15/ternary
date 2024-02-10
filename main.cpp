#include <iostream>
#include <cmath>
#include <cstdio>
#include <math.h>
#include <algorithm>
#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <chrono>
#include "mpi.h"
#include <cstdlib>
#include <csignal>


using namespace std;

void mod9(int * mod, int arr2[], int n)
{
    int temp1 = arr2[1];
    int temp0 = arr2[0];

    if (temp1 == 0 && temp0 == 0) {
        mod[0]++;
    }
    else if (temp1 == 0 && temp0 == 1) {
        mod[1]++;
    }
    else if (temp1 == 0 && temp0 == 2) {
        mod[2]++;
    }
    else if (temp1 == 1 && temp0 == 0) {
        mod[3]++;
    }
    else if (temp1 == 1 && temp0 == 1) {
        mod[4]++;
    }
    else if (temp1 == 1 && temp0 == 2) {
        mod[5]++;
    }
    else if (temp1 == 2 && temp0 == 0) {
        mod[6]++;
    }
    else if (temp1 == 2 && temp0 == 1) {
        mod[7]++;
    }
    else if (temp1 == 2 && temp0 == 2) {
        mod[8]++;
    }
    
}
void shiftAdd(int* arr, int n, int& rLength)
{
    if (n < 1)
        return;
    for (int i = n; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = 1;
    rLength++;
}
void divide(int * arr, int n, int& rLength)
{
    if (arr[n] == 1) {
        rLength--;
    }
    int carry = 0;
    for (n; n >= 0; n--) {
        int digit = arr[n] + carry * 3;
        arr[n] = digit / 2;
        carry = digit % 2;
    }
}
void oddEven(int arr[], int n, int& check)
{
    int odd = 0;
    for (int i = 0; i <= n; i++) {
        if (arr[i] == 1) {
            odd++;
        }
    } 
    if (odd % 2 == 0) {
        check = 1;
    } //if even check is set to 1
    else if (odd % 2 > 0) {
        check = 0;
    } //else check is assumed to be odd
}
void checkEmpty(int arr[], int n, int& flag)
{
    for (int i = n; i >= 0; i--) {
        if (arr[i] == 0) {
            flag = 0;
        }
        else if (arr[i] != 0 && i == 0) {
            flag = 2;
            break;
        }
        else {
            flag = 1;
            break;
        }  //flag is 0 for empty and 1 for full and 2 for when num is just 1
    }
}
void isBigger(int arr[], int* maxArr, int rLength, int& maxLength, int& maxNum)
{  
    if (maxLength < rLength) {
        for (int j = rLength ; j > 0; j--) {
            maxArr[j] = arr[j];
        }
        maxLength = rLength;
        maxNum++;
    }
    else if (maxLength == rLength) {
        bool larger = false;
        for (int k = rLength ; k > 0; k--) {
            if (maxArr[k] > arr[k]) {
                break;
            }
            else if (maxArr[k] < arr[k]) {
                larger = true;
                break;
            }
        }
        if (larger) {
            maxNum++;
            for (int j = rLength ; j > 0; j--) {
                maxArr[j] = arr[j];
            }
        }
    }
}


void collatz_sequence(int* arr, int length, int* data) {
    int step = 0;
    //cout << "\nStep initialized.\n";
    int check = 0;
    //cout << "\nCheck initialized.\n";
    int flag = 0;
    //cout << "\nFlag initialized.\n";
    int maxNum = 0;
    //cout << "\nMaxNum initialized.\n";
    int oldMaxNum = 0;
    //cout << "\nOldMaxNum initialized.\n";
    int odd = 0;
    //cout << "\nOdd initialized.\n";
    int even = 0;
    //cout << "\nEven initialized.\n";


    int rLength = length;
    //cout << "\nRLength set to length.\n";
    int maxLength = rLength;
    //cout << "\nMaxLength set to RLength.\n";
    int lengthPlus = length + 20;
    //cout << "\nLengthPlus set to length plus 20.\n";

    int maxMod[9] = {};
    //cout << "\nmaxMod9 aray initialized.\n";
    for (int i = 0; i < 9; i++){
            //cout << "\nEntering for loop to set array arr to be all zeros.\n";
                maxMod[i] = 0;
                //cout << "\nSetting array index: " << i << " : to zero/n";
    }
    int emod[9] = {};
    //cout << "\nevenMod9 array initialized.\n";
    for (int i = 0; i < 9; i++){
            //cout << "\nEntering for loop to set array arr to be all zeros.\n";
                emod[i] = 0;
                //cout << "\nSetting array index: " << i << " : to zero/n";
    }
    int omod[9] = {};
    //cout << "\noddMod9 array initialized.\n";
    for (int i = 0; i < 9; i++){
            //cout << "\nEntering for loop to set array arr to be all zeros.\n";
                omod[i] = 0;
                //cout << "\nSetting array index: " << i << " : to zero/n";
    }
  
    int maxArr[600000] = {};                                                                    //CHANGEME
    //cout << "\nMax array initialized.\n";
    for (int i = lengthPlus; i >= 0; i--) {             //max array
        maxArr[i] = arr[i];
    }
    //cout << "\nMax array filled.\n";

    oddEven(arr, rLength, check);
    //cout << "\nChecked if odd or even.\n";
    if (check == 1) {                               //if even, divide
        divide(arr, rLength, rLength);
        //out << "\nDivided because even.\n";
    }

    else {                                           //if odd, multiply
        shiftAdd(arr, lengthPlus, rLength);
        //cout << "\nAdded because odd.\n";
        mod9(maxMod, arr, lengthPlus);
        //cout << "\nModded by nine for max array because odd.\n";
        isBigger(arr, maxArr, rLength, maxLength, maxNum);   
        //cout << "\nChecked if new number is bigger than current max.\n";    
    }

    while (flag != 2) {
        step++;

        oldMaxNum = maxNum;
        checkEmpty(arr, rLength, flag);
        //cout << "\nChecked array if empty.\n";
        oddEven(arr, rLength, check);
        //cout << "\nArray not empty so checking if odd or even.\n";
        
        isBigger(arr, maxArr, rLength, maxLength, maxNum);
        //cout << "\nChecking if new number is bigger than current max\n";
        if (oldMaxNum < maxNum) {
        //cout << "\noldMaxNum < maxNum.\n";
            mod9(maxMod, arr, lengthPlus);
            //cout << "\nAdded to mod9 max array.\n";
        }        
        
        if (check == 1) { //if even, divide
            //cout << "\nChecked is even.\n";
            mod9(emod, arr, lengthPlus);
            //cout << "\nAdded to mod9 even array.\n";
            divide(arr, rLength, rLength);
            //cout << "\nDivided array.\n";
            even++;
        }
        else if(check == 0) { //if odd, multiply
            //cout << "\nChecked is odd.\n";
            mod9(omod, arr, lengthPlus);
            //cout << "\nAdded to mod9 odd array.\n";
            shiftAdd(arr, lengthPlus, rLength);
            //cout << "\nAdded one to array.\n";
            odd++;
        }     
                
        
    }
    oddEven(arr, rLength, check);
    //cout << "\nChecked if odd or even.\n";
    odd++;
    step++;
    mod9(omod, arr, lengthPlus);
    //cout << "\nArray should be 1 so add to odd mod9 array.\n";
    
    //cout << step << " ";
    data[0] = step;
    //cout << even << " ";
    data[1] = even;
    //cout << odd << " ";
    data[2] = odd;
    //cout << maxNum << " ";
    data[3] = maxNum;
                                    //1 = steps
                                    //2 = even steps
                                    //3 = odd steps
                                    //4 = max steps
                                    //5 - 13 = even mod9s
                                    //14 - 22 = odd mod9s
                                    //23 - 31 = normal mod9s
                                    //32 - 40 = max mod9s
                                    //41 = length
    int j = 0;
    int k = 0;
    int l = 0;
    int m = 0;
    int o = 0;
    for (int i = 4; i <= 12; i++)                             //simple for loop to cout
    {   
        data[i] = emod[j];
        j++;
    }
    
    for (int i = 13; i <= 21; i++)                             //simple for loop to cout
    {   
        data[i] = omod[k];
        k++;
    }
    
    for (int i = 22; i <= 30; i++)
    {
        int value = 0;
        value = emod[l] + omod[m];
        data[i] = value;
        l++;
        m++;
    }
    
    for (int i = 31; i <= 39; i++)                             //simple for loop to cout
    {   
        data[i] = maxMod[o];
        o++;
    }
    
    
    /*
    for (int i = 0; i < 8; i++)                             //simple for loop to cout
    {   
        cout << emod[i] << " ";
    }
    for (int i = 0; i < 8; i++)                             //simple for loop to cout
    {   
        cout << omod[i] << " ";
    }
    for (int i = 0; i < 8; i++)
    {
        int value = 0;
        value = emod[i] + omod[i];
        cout << value << " ";
    }
    for (int i = 0; i < 8; i++)                             //simple for loop to cout
    {   
        cout << maxMod[i] << " ";
    }
   
    cout << "\nLeaving Collatz function.\n";
    
    */
}


int main(int argc, char *argv[]){

    int LL;
    int UL;
    int total;
    ofstream outfile("testrun2results.txt");
    int data[41];
    int count = 0;
    int count2 = 0;
    int i = 0;
    
    LL = atoi(argv[1]);
    UL = atoi(argv[2]);
    total = atoi(argv[3]);
    
    int rank, size; 
    MPI_Status status;

    MPI::Init(argc, argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int totalSize = (size - 1) * total;
    
    if(rank == 0){ 
        cout << "This is LL " << LL << endl;
        cout << "This is UL " << UL << endl;
        cout << "This is total " << total << endl; 

        while (count2 < totalSize) {
        //cout << "\n\nThis is total size: " << totalSize;
        //cout << "\n\nThis is count2 size: " << count2;
            MPI_Recv(data, 41, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            while (i <= 40) {
                if(i == 40){
                    outfile << data[40] << endl;
                    break;
                }
                else
                outfile << data[i] << " ";
                
                i++;
            }
            i = 0;
            count2++;
        }
        outfile.close();
        
        
    }
    int arr[600000] = {};                                                              //CHANGEME
     if(rank > 0){
        //cout << "\nEntering Rank: " << rank << "\n";
        //cout << "\nInitialized count.\n";
        srand(time(0)*(rank + 1)); 
        //cout << "\nSeeded random number generator.\n";
        
        while(count < total){
            //cout << "\n\nTotal is: " << total;
            //cout << "\n\nThis is count: " << count;
            int length = rand() % (UL - LL + 1) + LL;
            
            data[40] = length;
            
            //cout << "\nLength initialized randomly between LL and UL : " << length << "\n";
            length--;
            //cout << "\nLength subtracted by one.\n";
            int lengthPlus = length + 20;   
            //cout << "\nLengthPlus: " << lengthPlus << " initialized and set to length + 20.\n";    
            //int* arr = new int[lengthPlus];
            
            
            
            //cout << "\nDynamic array initalized to lengthPlus\n";
            for (int i = 0; i < lengthPlus; i++){
            //cout << "\nEntering for loop to set array arr to be all zeros.\n";
                arr[i] = 0;
                //cout << "\nSetting array index: " << i << " : to zero/n";
            }
            
            for (int i = 0; i <= length; i++) {
            //cout << "\nEntering for loop to assign random ternary numbers to array\n";
                if (i == length){
                //cout << "\nIf index i equal to legnth.\n";
                    arr[i] = rand() % 3;
                    //cout << "\nAssing random number to index equal to length.\n";
                    if(arr[i] == 0){
                    //cout << "\nIf random number is zero.\n";
                    arr[i] = 1;
                    //cout << "\nAdd one to arr[i] so the beginning of number is not zero.\n";
                    }
                }
                else
                  arr[i] = rand() % 3;
                  //cout << "\nAssigning random ternary number to array index: " << i << "\n";
            }
            //cout << "\n\nRank: " << rank << "The random ternary number of length " << length + 1 << " is: ";
            //for (int i = lengthPlus - 1; i > 0; i--) {
            //    cout << arr[i];
            //}
            //cout << "\n\n";
            //cout << "\n\n<" << count << "|" << rank << ">\n\n";
            
            
            //cout << "\nEntering the collatz function with length: " << length << "\n"; 
            collatz_sequence(arr, length, data);
            //cout << "\nSeeding array.\n";
            MPI_Send(data, 41, MPI_INT, 0, 0, MPI_COMM_WORLD);
            count++;
        }    
    }

    MPI_Finalize();
    return 0;
}