#include <iostream>
#include <fstream>

using namespace std;

void openFile(ifstream &file, string prompt);
void readInventory(string names[], int quantities[], int &readCnt);
void displayInventory(string names[], int quantities[], int readCnt);
void createPotions(string names[], int quantities[], int &inventorySize);

int main() {
    // 2 parallel arrays
    string names[10];
    int quantities[10];
    // every file will have different amount of line
    // this will keep track of the amount of line to print format correctly
    int arraysLength = 0;
    // ask for the inventory file
    ifstream inventoryFile;
    readInventory(names, quantities, arraysLength);
    displayInventory(names, quantities, arraysLength);
    createPotions(names, quantities, arraysLength);
    //createPotions(names, quantities, linesCount);
}

void openFile(ifstream &file, string prompt) {
    // print out and ask for file
    // user input for file that is opening
    // error check
    bool hasOpen = false;
    do {
        cout << prompt;

        string fileInput;
        cin >> fileInput;
        file.open(fileInput);

        if(file.is_open()) {
            hasOpen = true;
            continue;
        }
        cout << "Error: Invalid filename" << endl;

    } while (!hasOpen);
}

void readInventory(string names[], int quantities[], int &readCnt){
    ifstream currentFile;
    openFile(currentFile, "Inventory File: ");
    //grab data and split it
    string currentFileLine;
    //ignor the first line
    getline(currentFile, currentFileLine);

    while(getline(currentFile, currentFileLine)){
        //move name into names array
        names[readCnt] = currentFileLine.substr(0, currentFileLine.find(','));
        //move values into quantities array
        quantities[readCnt] = stoi(currentFileLine.substr(currentFileLine.find(',') + 1));
        //readCnt acts as the index, the number of things in the array will be
        //readCnt + 1
        readCnt++;
    }
}

void displayInventory(string names[], int quantities[], int readCnt){
    for(int i = 0; i < readCnt; i++){
        cout << i+1 << ") " << names[i] << ": " << quantities[i] << endl;
    }   
}

void createPotions(string names[], int quantities[], int &inventorySize){
    ifstream potionsFile;
    openFile(potionsFile, "Potions File: ");
    //find the index of potion base
    int potionsBaseIndex = 0;
    int rootIndex = 0;
    int newtIndex = 0;
    int whiteBerriesIndex = 0;
    //get the index of the each ingredient
    for(int i = 0; i < inventorySize; i++){
        if(names[i] == "potion base"){
            potionsBaseIndex = i;
        }else if(names[i] == "limpwurt root"){
            rootIndex = i;
        }else if(names[i] == "eye of newt"){
            newtIndex = i;
        }else if(names[i] == "white berries"){
            whiteBerriesIndex = i;
        }
    }

    //read the potion requests from the txt file
    string potionsRequest;
    while(getline(potionsFile, potionsRequest)){
        //set the current potion requested and the amount requested
        string currentPotion;
        currentPotion = potionsRequest.substr(0, potionsRequest.find(' '));
        int currentPotionAmountRequested;
        currentPotionAmountRequested = stoi(potionsRequest.substr(potionsRequest.find(' ') + 1));
        
        cout << currentPotionAmountRequested << " " << currentPotion << " potions requested" << endl;

        const int eyeOfNewt = 2;
        const int limpwurtRoot = 1;
        const int whiteBerries = 10;
        
        int ingredientForOne = 0;
        string currentMixinName;

        if(currentPotion == "attack"){
            ingredientForOne = eyeOfNewt;
            currentMixinName = "eye of newt";
            if(quantities[potionsBaseIndex] < 1){
                cout << "Error: Not enough potion base to make " 
                     << currentPotion << "potions" << endl;
                continue;
            }
            if(quantities[newtIndex] < ingredientForOne){
                cout << "Error: Not enough " << currentMixinName 
                     << " to make " << currentPotion << " potions" << endl;
                continue;
            }
            int actualLimit = currentPotionAmountRequested;

            int potionBaseLimit = quantities[potionsBaseIndex];
            int limit = currentPotionAmountRequested;
            if(quantities[newtIndex] < (ingredientForOne*currentPotionAmountRequested)){
                limit = quantities[newtIndex] / ingredientForOne;
            }
            if(potionBaseLimit < limit){
                actualLimit = potionBaseLimit;
            }else if(limit < potionBaseLimit){
                actualLimit = limit;
            }else if(potionBaseLimit == limit && quantities[potionsBaseIndex] < currentPotionAmountRequested && quantities[newtIndex] < (ingredientForOne*currentPotionAmountRequested)){
                actualLimit = limit;
            }

            if(actualLimit < currentPotionAmountRequested){
                if(potionBaseLimit < limit){
                    cout << "Limited by " << potionBaseLimit << " base potions" << endl;
                }else if(limit < potionBaseLimit){
                    cout << "Limited by " << limit << " " << currentMixinName << endl;
                }
            }

            quantities[potionsBaseIndex] -= actualLimit;
            quantities[newtIndex] -= actualLimit * ingredientForOne;
            cout << "Mixing " << actualLimit << " " << currentPotion << endl;

            //add this potion to the array to print out with the print function
            













        }else if(currentPotion == "strength"){
            ingredientForOne = limpwurtRoot;
            currentMixinName = "limpwurt root";
            if(quantities[potionsBaseIndex] < 1){
                cout << "Error: Not enough potion base to make " 
                     << currentPotion << "potions" << endl;
                continue;
            }
            if(quantities[rootIndex] < ingredientForOne){
                cout << "Error: Not enough " << currentMixinName 
                     << " to make " << currentPotion << " potions" << endl;
                continue;
            }
        }else if(currentPotion == "defense"){
            ingredientForOne = whiteBerries;
            currentMixinName = "white berries";
            if(quantities[potionsBaseIndex] < 1){
                cout << "Error: Not enough potion base to make " 
                     << currentPotion << "potions" << endl;
                continue;
            }
            if(quantities[whiteBerriesIndex] < ingredientForOne){
                cout << "Error: Not enough " << currentMixinName 
                     << " to make " << currentPotion << " potions" << endl;
                continue;
            }
        }
    }       
}