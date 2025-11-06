#include <iostream>
#include <fstream>

using namespace std;

void openFile(ifstream &file, string prompt);
void readInventory(string names[], int quantities[], int &readCnt);
void displayInventory(string names[], int quantities[], int readCnt);
void createPotions(string names[], int quantities[], int &inventorySize);

int main(){
    //2 parallel arrays
    string names[10];
    int quantities[10];
    //every file will have different amount of line
    //this will keep track of the amount of line to print format correctly
    int linesCount = 0;
    //ask for the inventory file
    ifstream inventoryFile;
    readInventory(names, quantities, linesCount);
    displayInventory(names, quantities, linesCount);


    createPotions(names, quantities, linesCount);
}  

void openFile(ifstream &file, string prompt){
    //print out and ask for file
    //user input for file that is opening
    //error check
    bool hasOpen = false;
    do{
        cout << prompt;
        string fileInput;
        cin >> fileInput;

        file.open(fileInput);

        if(!file.is_open()){
            cin.clear();
            cin.ignore(1000, '\n');
        }else{
            hasOpen = true;
        }
    }while(!hasOpen);
}
//only reads the inventory
void readInventory(string names[], int quantities[], int &readCnt){
    ifstream inventoryOpened;
    openFile(inventoryOpened, "Inventory File: ");
    string currentLine;
    getline(inventoryOpened, currentLine);
    while(getline(inventoryOpened, currentLine) && readCnt < 10){
        //cout << currentLine << endl;
        names[readCnt] = currentLine.substr(0, currentLine.find(','));
        quantities[readCnt] = stoi(currentLine.substr(currentLine.find(',') + 1));
        readCnt++;
    }
}

void displayInventory(string names[], int quantities[], int readCnt){
    for(int i = 0; i < readCnt; i++){
        cout << (i + 1) << ") " << names[i] << ": " << quantities[i] << endl;
    }
}

void createPotions(string names[], int quantities[], int &inventorySize){
    ifstream potionsFile;
    openFile(potionsFile, "Potions File: ");
    
    int baseIndex = 0;
    int rootIndex = 0;
    int newtIndex = 0;
    int berriesIndex = 0;

    for (int i = 0; i < inventorySize; i++) {
        if (names[i] == "potion base") 
            baseIndex = i;
        else if (names[i] == "limpwurt root") 
            rootIndex = i;
        else if (names[i] == "eye of newt") 
            newtIndex = i;
        else if (names[i] == "white berries") 
            berriesIndex = i;
    }
    string potionString;
    while(getline(potionsFile, potionString)){
        //there are 3 potions possible(attack, strength, defense)
        //attack check
        //needs 1 base, 2 eye of newt
        if(potionString.substr(0, potionString.find(' ')) == "attack"){
            int attackRequest = 0;
            attackRequest = stoi(potionString.substr(potionString.find(' ') + 1));
            cout <<  attackRequest << " atack potions requested" << endl;
            //check resources and values for one potion
            if(quantities[baseIndex] < 1){
                cout << "Error: Not enough potion base to make attack potions" << endl;
                continue;
            }
            if(quantities[newtIndex] < 2){
                cout << "Error: Not enough eye of newt to make attack potions" << endl;
                continue;
            }
            //check if theres enough to make qty potions.
            //where you make potions up to the amount of resources you have. 
            //check the base limit
            int basePotionLimit = 0;
            int potionLimit = 0;
            int potionsMixing = 0;
            //setting  base potion limit
            if(quantities[baseIndex] < (attackRequest * 1)){
                basePotionLimit = quantities[baseIndex];
                cout << basePotionLimit << endl;
            }
            //setting potion limit with ingrediants available. 
            if(quantities[newtIndex] < (attackRequest * 2)){
                potionLimit = quantities[newtIndex] / 2;
                cout << potionLimit << endl;
            }

            if(basePotionLimit < potionLimit){
                cout << "Limited by " << basePotionLimit << " base potions" << endl; 
            }else if(potionLimit < basePotionLimit){
                cout << "Limited by " << potionLimit << " eye of newt" << endl;
            }


            if(basePotionLimit < potionLimit){
                cout << "Limited by " << basePotionLimit << " base potions" << endl; 
                potionsMixing = basePotionLimit;
            }else if(potionLimit < basePotionLimit){
                cout << "Limited by " << potionLimit << " eye of newt" << endl;
                potionsMixing = potionLimit;
            }else{
                potionsMixing = attackRequest;
            }



































            //needs 1 base, 1 limpwurt root
        }else if(potionString.substr(0, potionString.find(' ')) == "strength"){
            int strengthRequested = 0;
            strengthRequested = stoi(potionString.substr(potionString.find(' ') + 1));
            cout << strengthRequested << " strength potions requested" << endl;


            //needs 1 base, 10 white berries
        }else if(potionString.substr(0, potionString.find(' ')) == "defense"){
            int defenseRequested = 0;
            defenseRequested = stoi(potionString.substr(potionString.find(' ') + 1));
            cout << defenseRequested << " defense potions requested" << endl;



        }
    }
}

