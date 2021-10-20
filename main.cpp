//todo.cpp <-- small todo program
//written by Trevor Haggerty
// some date stuff here

//libraries and namespaces-------------------------------------------
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

//struct prototypes--------------------------------------------------
struct element{
  
  string id;
  string entry;
  string date;

};


//class prototypes---------------------------------------------------

//*****************Date class*******************
class Date{
  
  public:
    //constructors
    Date();
    Date(int, int, int);
  
  private:
    //members
    int Month;
    int Day;
    int Year;

  public:
    
    //mutators
    void SetDate(int, int, int);
    void SetDateAuto();
    
    //accessors
    string Display();
    
    //unit test
    void ClassTest();

};


//*****************Database class*******************
class Database{













};


//*****************Menu class*******************
class Menu{

  public:
    //constructors
    Menu();


  private:

    int state;

    string* optionText;
    
    string bufferStr;
    int bufferInt;
    char bufferChar;

  public:

    //mutators
    void SetState(int s){ state = s; };
    void SetBufferStr(string b){ bufferStr = b; };
    void SetBufferInt(int b){ bufferInt = b; };
    void SetBufferChar(char c){ bufferChar = c; };

    //accessors
    int GetState(){return state; };
    string GetBufferStr(){return bufferStr; };
    char GetBufferChar(){return bufferChar; };
    int GetBufferInt(){return bufferInt; };
    
    string DisplayBuffers();
    
    string DisplayOptions();
    
    //Prompts
    void Prompt(string= "", string = "");
    int Stall(bool = false);

    //complex functions
    void Process();

    //unit test
    void ClassTest();

    //destructor
    ~Menu();

};








//Unit testing constants--------------------------------------
const int BAD_IN = -1;
const int BAD_OUT = -2;

const int TEST_INT_A = 912758364;
const int TEST_INT_B = 175897743;
const int TEST_INT_C = 638951181;

const string TEST_STRING_A = "The word echelon sounds faster than it is.";
const string TEST_STRING_B = "If I was an error message my name wou-";
const string TEST_STRING_C = "912758364";
const string TEST_STRING_D = "175897743";

//Integer constants-------------------------------------------
const int INITIAL_SIZE = 0;
const int SCREEN_X = 50;

//string modifiers----------------------------------------------
const string GREENTEXT = "\033[32m";
const string REDTEXT = "\033[31m";
const string YELLOWTEXT = "\u001b[38:5:226m";
const string EMPTYFORMAT = "\033[0m";
const string BANNER(SCREEN_X ,'-');

//function prototypes---------------------------function prototypes
void ProgramGreeting( Date now );
void ProgramClosing();

int CoreLoop( Database&, Menu&);

string Tokenizer(string, int, string filter = " " );
int RollCall( string , string );
bool NumberCheck( string );
bool AlphaCheck( string );


void UnitTest();


//--------------------------MAIN
int main(){
  
  Date now;
  Menu menu;
  
  ProgramGreeting(now);

  menu.Stall();
  
  UnitTest();

  menu.Stall();

  Database db;
  CoreLoop(db, menu);

  menu.Stall();

  ProgramClosing();

  return 0;
}


//function implementation---------------------------------------

//*****************ProgramGreeting*******************
void ProgramGreeting(Date now) {

    cout << GREENTEXT << BANNER << EMPTYFORMAT << endl;
    
    cout << "Welcome to the TO DO list manager" << endl;
    cout << setw(50) << right << "coded by Trevor Haggerty" << endl;
    cout << now.Display()<< endl;
    
    cout << GREENTEXT << BANNER << EMPTYFORMAT << endl;

};


//*****************RollCall**********************

int RollCall(string population, string filter){
  
  int result = 0;

  for(int i = 0; i < population.length(); i++){
    for(int j = 0; j < filter.length(); j++){
      if((char)population[i] == (char)filter[j]){
        result++;
      }
    }
  }

  return result;
};
//*****************NumberCheck****************
bool NumberCheck(string inputString){
  bool result = isdigit(inputString[0]);
  if(inputString.length() > 0 && inputString.length() < 9){
  
    for(int i = 0; i < inputString.length(); i++){
      if (!isdigit(inputString[i])){
        result = false;
      }
    }
  }
  return result;
}

//*****************AlphaCheck****************
bool AlphaCheck(string inputString){
  bool result = isalnum(inputString[0]);
  if(inputString.length() > 0 && inputString.length() < 9){
  
    for(int i = 0; i < inputString.length(); i++){
      if (!isalnum(inputString[i])){
        result = false;
      }
    }
  }
  return result;
}

//*****************Tokenizer*******************
string Tokenizer(string text, int index, string filter){
  
  string result = "";
  string cursor = "";
  int tempInt = 0;

  if(text.length() > 0 && index < text.length() && index >= 0){
    int count = 0;
    
    for(int i = 0; i < text.length(); i++){
      
      cursor = text[i];
      
      if(RollCall(cursor, filter) >= 1){
        count++;
      }
      else if(count == index){
        result += text[i];
      }

    }

  }
  else if(index >= text.length()){
    return "OVERBOUNDS";
  }
  else{
    result = to_string(BAD_IN);
  }

  return result;
}



//*****************CoreLoop*******************
int CoreLoop(Database& db, Menu& menu){

  menu.DisplayOptions();

  bool running = true;
  while (running){
    
    menu.Prompt("User : ", "");
    menu.DisplayBuffers();
    menu.Process();
    menu.DisplayBuffers();
    running = (menu.GetState() >= 0);
  }
  return 0;
};


//*****************ProgramClosing*******************
void ProgramClosing(){
  cout << GREENTEXT << BANNER << EMPTYFORMAT << endl;
    
  cout << "Thank you for using list manager" << endl;
  cout << setw(50) << right << "coded by Trevor Haggerty" << endl;
 
  cout << GREENTEXT << BANNER << EMPTYFORMAT << endl;

};


//*****************UnitTest*******************
void UnitTest(){
  
  cout << YELLOWTEXT + "UNIT TESTING" + EMPTYFORMAT << endl << endl;
  cout << YELLOWTEXT + "TESTING OBJECTS" + EMPTYFORMAT << endl << endl;
  
  Date testDate(TEST_INT_A, TEST_INT_B, TEST_INT_C);
  testDate.ClassTest();

  Menu testMenu;
  testMenu.ClassTest();

  cout << YELLOWTEXT + "TESTING FUNCTIONS" + EMPTYFORMAT << endl << endl;
  
//----------------------------------------
  cout << setw(SCREEN_X) << setfill('-') << left << "testing rollcall" ;
  
  int testInt = RollCall(TEST_STRING_D, "7");
  if( testInt != 3 ){
    cout << REDTEXT + "FAILURE!!!\n";
  }
  else{
    cout << GREENTEXT + "SUCCESS!!!\n";
  }
  
  cout << "RollCall(TEST_STRING_D, 7 ) -> expected " << 3 << " -> received : " << testInt << endl;
  cout << EMPTYFORMAT;
//----------------------------------------
  cout << setw(SCREEN_X) << setfill('-') << left << "testing NumberCheck" ;
  
  testInt = NumberCheck(TEST_STRING_D);
  if( testInt != 1 ){
    cout << REDTEXT + "FAILURE!!!\n";
  }
  else{
    cout << GREENTEXT + "SUCCESS!!!\n";
  }
  
  cout << "NumberCheck(TEST_STRING_D) -> expected " << 1 << " -> received : " << testInt << endl;
  cout << EMPTYFORMAT;

//----------------------------------------
  cout << setw(SCREEN_X) << setfill('-') << left << "testing Tokenizer" ;
  
  string testString = Tokenizer(TEST_STRING_A, 4);
  if( testString.compare("faster") != 0 ){
    cout << REDTEXT + "FAILURE!!!\n";
  }
  else{
    cout << GREENTEXT + "SUCCESS!!!\n";
  }
  
  cout << "Tokenizer(TEST_STRING_A, 5) -> expected " << "faster" << " -> received : |" << testString <<"|"<< endl;
  cout << EMPTYFORMAT;


};


//*********************Date implementation************************
//constructor--------------------------------------------
Date::Date(){
  SetDateAuto();
  
}


//constructor overload---------------------------------------
Date::Date( int mm, int dd, int yy ){
  
  SetDate(mm, dd, yy);

}


//Main setter--------------------------------------------
void Date::SetDate( int mm, int dd, int yy ){
  
  Month = mm;
  Day = dd;
  Year = yy;

}


//automatic setter--------------------------------------------
void Date::SetDateAuto(){
  
  time_t currentTime = time(0);
  tm *timeFormated = localtime(&currentTime);

  Month = timeFormated->tm_mon + 1; // shift by one to correct number
  Day = timeFormated->tm_mday;
  Year = timeFormated->tm_year + 1900; // adding 1900 because of how digital dates work

};


//Main getter function--------------------------------------------
string Date::Display(){

  string result = to_string(Month) + " / ";
  result += to_string(Day);
  result += " / ";
  result += to_string(Year);
  
  return result;

}


//Unit testing----------------------------------------------------
void Date::ClassTest(){
  cout << YELLOWTEXT + "Testing date" + EMPTYFORMAT << endl;

  int result = 0;
  cout << setw(SCREEN_X) << setfill('-') << left << "testing Constructor";
  if( Month != TEST_INT_A || Day != TEST_INT_B || Year != TEST_INT_C){
    cout << REDTEXT + "FAILURE!!!\n";
  }
  else{
    cout << GREENTEXT + "SUCCESS!!!\n";
  }
  cout << "Month -> expected " << TEST_INT_A << " -> received : " << Month << endl;
  cout << "Day -> expected " << TEST_INT_B << " -> received : " << Day << endl;
  cout << "Year -> expected " << TEST_INT_C <<" -> received : " << Year << EMPTYFORMAT << endl;
  
  //----------------------------------------

  time_t currentTime = time(0);
  tm *timeFormated = localtime(&currentTime);

   cout << setw(SCREEN_X) <<left<< "testing Automatic Setter";
  SetDateAuto();
  if( Month != (timeFormated->tm_mon + 1) || Day != timeFormated->tm_mday || Year != (timeFormated->tm_year + 1900)){
    cout << REDTEXT + "FAILURE!!!\n";
    
  }
  else{
    cout << GREENTEXT + "SUCCESS!!!\n";
  }
  cout << "Month -> expected " << (timeFormated->tm_mon + 1) << " -> received : " << Month << endl;
  cout << "Day -> expected " << timeFormated->tm_mday << " -> received : " << Day << endl;
  cout << "Year -> expected " << (timeFormated->tm_year + 1900) << " -> received : " << Year << EMPTYFORMAT << endl;

  //----------------------------------------
   cout << setw(SCREEN_X) <<left<< "testing Manual Setter";
  SetDate(TEST_INT_C,TEST_INT_A,TEST_INT_B);
  if( Month != TEST_INT_C || Day != TEST_INT_A || Year != TEST_INT_B){
    cout << REDTEXT + "FAILURE!!!\n";
    
  }
  else{
    cout << GREENTEXT + "SUCCESS!!!\n";
  }
  cout << "Month -> expected " << TEST_INT_C << " -> received : " << Month << endl;
  cout << "Day -> expected " << TEST_INT_A << " -> received : " << Day << endl;
  cout << "Year -> expected " << TEST_INT_B << " -> received : " << Year << EMPTYFORMAT << endl;

  //----------------------------------------
  cout << setw(SCREEN_X) << left << "testing Display";
  string testOutput = Display();

  string testString = to_string(TEST_INT_C);
  testString += " / " + to_string(TEST_INT_A);
  testString += " / " + to_string(TEST_INT_B);

  if ( testOutput.compare(testString) != 0){
    cout << REDTEXT + "FAILURE!!!\n" ;
  }
  else{
    cout << GREENTEXT + "SUCCESS!!!\n" ;
  }
  cout <<  "Date -> expected " + testString;
  cout << "-> received : " << testOutput << EMPTYFORMAT << endl;
  cout << setfill(' ');
}





//*********************Menu implementation************************
//constructor---------------------------------
Menu::Menu(){

  state = 0;
  bufferStr = "";
  bufferInt = 0;

  optionText = nullptr;
  optionText = new string[10];
  string tempStr = "__HELP__\n+ 'text' <--- to add a TO DO entry\n";
  tempStr += "- 'id'   <--- to remove a TO DO entry by id\n";
  tempStr += "?        <--- to veiw the TO DO entries\n";
  tempStr += "quit     <--- to quit the program\n";
  tempStr += "help     <--- to veiw this menu\n";

  *(optionText) = tempStr;

}

//buffer display function-----------------------------------
string Menu::DisplayBuffers(){
  string result = "string: " + bufferStr;
  result += ", int: " + to_string(bufferInt);
  result += ", char: " + to_string(bufferChar) + "\n";
  cout << result;
  return result;
}
//Main display function-----------------------------------
string Menu::DisplayOptions(){
  string result = *(optionText + state);

  cout << result;
  return result;
}

//Main prompting function-----------------------------------
void Menu::Prompt(string contents, string filter){
   
  bool asking = true;

  while(asking){

    cout << YELLOWTEXT << contents << EMPTYFORMAT;
    
    getline(cin, bufferStr);

    if(NumberCheck(bufferStr)){   
      if(bufferStr.length() < 8){ 
        bufferInt=(stoi(bufferStr));
        asking = false;
      }  
      
    }
    
    if(bufferStr.length() > 0){
        bufferChar = bufferStr[0];
        asking = false;
    }
  }
}

//stalling for input function-----------------------------------
int Menu::Stall(bool b){

  string s;
  
  cout << YELLOWTEXT << "Please enter anything to continue\n" << EMPTYFORMAT;
  getline(cin, s);
  
  if ( !b ){
    system("clear");
  }
  
  return 0;
}


//Member processing function--------------------------------------
void Menu::Process(){

  if(state == 0){
    if(bufferChar == '+'){

    }
    else if(bufferChar == '-'){

    }
    else if(bufferChar == '?'){

    }
    
    if(bufferStr.compare("quit") == 0 || bufferStr.compare("Quit") == 0 ){
      state = -3;
    }
    
    if(bufferStr.compare("quit") == 0 || bufferStr.compare("Quit") == 0 ){
      state = -3;
    }
    
  }
  else if(state == 1){

  }
  else if(state == 2){

  }
  
 
};
//--------------------------------------------------------






//Unit test------------------------------------------ 
void Menu::ClassTest(){
  

  cout << YELLOWTEXT + "Testing Menu" + EMPTYFORMAT << endl;

  int result = 0;
  //----------------------------------------
  
  cout << setw(SCREEN_X) << setfill('-') << left << "testing Constructor" ;
  
  if( state != 0 || bufferStr.length() != 0 || bufferInt != 0){
    cout << REDTEXT + "FAILURE!!!\n";
  }
  else{
    cout << GREENTEXT + "SUCCESS!!!\n";
  }
  
  cout << "state -> expected " << TEST_INT_A << " -> received : " << state << endl;
  cout << "buffer string -> expected " << TEST_STRING_B << " -> received : " << bufferStr << endl;
  cout << "buffer integer -> expected " << TEST_INT_B << " -> received : " << bufferInt << endl;
  cout << EMPTYFORMAT;

  //----------------------------------------
  cout << setw(SCREEN_X) << setfill('-') << left << "testing setters" ;
  
  SetState(TEST_INT_C);
  SetBufferStr(TEST_STRING_A);
  SetBufferInt(TEST_INT_A);
  
  if( state != TEST_INT_C || bufferStr != TEST_STRING_A || bufferInt != TEST_INT_A){
    cout << REDTEXT + "FAILURE!!!\n";
  }
  else{
    cout << GREENTEXT + "SUCCESS!!!\n";
  }
  
  cout << "state -> expected " << TEST_INT_C << " -> received : " << state << endl;
  cout << "buffer string -> expected " << TEST_STRING_A << " -> received : " << bufferStr << endl;
  cout << "buffer integer -> expected " << TEST_INT_A << " -> received : " << bufferInt << endl;
  cout << EMPTYFORMAT;

  //---------------------------------------------
  
  cout << setw(SCREEN_X) << setfill('-') << left << "testing Stalling function\n" ;
  int testValue = Stall(true);

  if(testValue){
    cout << setw(SCREEN_X) << setfill('-') << left << "tested Stalling function" ;
    cout << REDTEXT + "FAILURE!!!\n";
  }
  else{
    cout << setw(SCREEN_X) << setfill('-') << left << "tested Stalling function" ;
    cout << GREENTEXT + "SUCCESS!!!\n";
  }
  
  cout << "input-> expected " << testValue << " -> received : " << testValue<< endl;
  cout << EMPTYFORMAT;

  //----------------------------------------------
  cout << setw(SCREEN_X) << setfill('*') << right <<  "testing Processing function\n" ;
  cout << setw(SCREEN_X) << setfill('-') << left << "testing Mode 0" ;

  SetBufferStr(TEST_STRING_A);
  SetBufferInt(TEST_INT_A);
  
  SetState(0);
  Process();

  if(GetBufferStr().compare(TEST_STRING_C) != 0){
     cout << REDTEXT + "FAILURE!!!\n";
  }
  else{
    cout << GREENTEXT + "SUCCESS!!!\n";
  }
  
  cout << " SetbufferStr-> expected " << TEST_STRING_C << " -> received : " << GetBufferStr()<< endl;
  cout << EMPTYFORMAT;

  //----------------------------------------------

  //----------------------------------------------
  

}


//destructor
Menu::~Menu(){
  delete [] optionText;
}







//********************* -classnamehere-  implementation************************
//constructor---------------------------------
//setter---------------------------------------------
//getter---------------------------------------------
//complex functions----------------------------------
//Unit test------------------------------------------ 



