//todo.cpp <-- small todo program
//written by Trevor Haggerty
// some date stuff here

//--------------------------------------------------------------------
//libraries and namespaces--------------------------------------------
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;


//Object prototypes---------------------------------------------------

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

//-------------------element struct-------------------------------

class Element{
  public:
    //constructor
    Element(); 
    Element(string);

  private: 
    //private members
    int id;
    string entry;
    bool completed;
    Date date;
    int priority;

  public:
    //setters and getters /ut
    int GetId(){return id;};
    string GetEntry(){return entry;};
    bool GetCompleted(){return completed;};
    string GetDate(){return date.Display();};
    int GetPriority(){return priority;}; 

    void SetId(int i){id = i;};
    void SetEntry(string e){entry = e;};
    void SetCompleted(bool c){completed = c;};
    void SetPriority(int p){priority = p;};
    void SetDate(int m,int d,int y){ date.SetDate(m,d,y); };
    void SetDate(){ date.SetDateAuto(); };

    //record entry >>
    friend string &operator>>(string &s, Element &element);
    
    //display entry <<
    friend ostream &operator<<(ostream &out, Element element);

    //Unit testing
    void ClassTest();

};

//*****************Menu class*******************
class Menu{

  public:
    //constructors
    Menu();//ut

  private:

    int state;
    string* optionText;
    string* optionFilter;
    string bufferStr;
    int bufferInt;
    char bufferChar;
    int cursor;

  public:

    //mutators//ut
    void SetState(int s){ state = s; };
    void SetCursor(int c){ cursor = c; };
    void SetBufferStr(string b){ bufferStr = b; };
    void SetBufferInt(int b){ bufferInt = b; };
    void SetBufferChar(char c){ bufferChar = c; };

    //accessors//ut
    int GetState(){return state; };
    int GetCursor(){return cursor; };
    string GetBufferStr(){return bufferStr; };
    char GetBufferChar(){return bufferChar; };
    int GetBufferInt(){return bufferInt; };
    
    string DisplayBuffers();
    string DisplayOptions();
    
    //Prompts
    void Prompt();
    int Stall(bool = false);

    //complex functions//ut
    void Process();

    //unit test
    void ClassTest();

    //destructor
    ~Menu();

};

//*****************Database class*******************
class Database {
  public:
    Database(); 

  private:
    int listSize;
    int listMaxSize;
    Element *dynoList;
    int *idList;
    Date date;

  public:
    //getters
    int GetListSize(){return listSize;}
    int GetListMaxSize(){return listMaxSize;}

    Element GetElem(int);


    int IndexToId(int);   
    int IdToIndex(int);   
    

    string GetDate(){return date.Display();};
    //display
    void Display();

    //setters
    void setListSize(int newSize){listSize = newSize;}
    void setListMaxSize(int newMaxSize){listMaxSize = newMaxSize;}
    void SetDate(int m,int d,int y){ date.SetDate(m,d,y); };
    void SetDate(){ date.SetDateAuto(); };

    int Process();

    //memory management
    int Expand(int); 
    int Contract(int);
    
    //custom prompting for ids
    bool TestUniqueId(int);
    int GenerateUniqueId();

    //Element mutators
    int ReplaceElem(int, Element); 
    int AppendElem(Element);
    int DeleteElem(int);
    int InsertElem(int, Element);
    

    //unit testing function
    void ClassTest();

    
    ~Database();
};





//Testing constants--------------------------------------
const int BAD_IN = -1;
const int BAD_OUT = -2;
const string OVERBOUNDS = "OVERBOUNDS";

const int TEST_INT_A = 912758364;
const int TEST_INT_B = 175897743;
const int TEST_INT_C = 638951181;

const string TEST_STRING_A = "The word echelon sounds faster than it is.  ";
const string TEST_STRING_B = "If I was an error message my name wou-";
const string TEST_STRING_C = "912758364";
const string TEST_STRING_D = "175897743";

//Integer and State constants-------------------------------------------
const int SCREEN_X = 70;

const int INITIAL = 0;
const int MODIFYING = 1;
const int DELETING = 2;
const int DISPLAYING = 3;
const int LOADING = 4;
const int SAVING = 5; 
const int QUITING = 6;
const int RECORDING = 7;

//string modifiers----------------------------------------------
const string GREENTEXT = "\033[32m";
const string REDTEXT = "\033[31m";
const string YELLOWTEXT = "\u001b[38:5:226m";
const string MAGENTATEXT = "\033[95m";
const string BLUETEXT = "\033[34m";
const string EMPTYFORMAT = "\033[0m";
const string BANNER(SCREEN_X ,'-');

//function prototypes---------------------------function prototypes
void ProgramGreeting( Date now );
void ProgramClosing();

int CoreLoop( Database&, Menu&);

string Tokenizer(string, int, string filter = " " );//ut
string RandStr(int);//ut

int RollCall( string , string filter = " " );//ut
int WordCount( string , string filter = " " );
string StringTrimmer(string, string filter = " ");

bool NumberCheck( string );//ut
bool AlphaCheck( string );//ut

void Analyze(string, string, string);//ut

void UnitTest();


//--------------------------MAIN
int main(){
  system("clear");
  srand(time(NULL));

  Menu menu;
  
  Date now;
  
  ProgramGreeting(now);

  Database db;
  menu.Stall();
  
  UnitTest();

  menu.Stall();

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
    cout << setw(SCREEN_X) << right << "coded by Trevor Haggerty" << endl;
    cout << now.Display()<< endl;
    
    cout << GREENTEXT << BANNER << EMPTYFORMAT << endl;

};

//*****************RollCall**********************

int RollCall(string population, string filter){
  
  int result = 0;
  if(population.length() > 0){
    
    for(int i = 0; i < population.length(); i++){
      for(int j = 0; j < filter.length(); j++){
        
        if((char)population[i] == (char)filter[j]){
         result++;
        }
      
      }
    }

  }
  else{
    result = -1;
  }

  return result;
};


//*****************StringTrimmer******************
string StringTrimmer(string text, string filter){
  string result = text;

  //remove the whitespace at the ends
  for(int i = 0; i < filter.length(); i++){
      
    while(text[0] == filter[i]){
      result = result.substr(1,text.length() - 1);
    }
    while(text[text.length()] == filter[i]){
      result = result.substr(0,text.length());
    }
  }

  return result;
}



//*****************WordCount***********************

int WordCount(string text, string filter){

  text = StringTrimmer(text,filter);
  int result = 0;

  bool counting = true;
  int iterator = 0;
  string cursor;

  while (counting){

    cursor = Tokenizer(text,0);

    if(cursor.compare(OVERBOUNDS) != 0 &&
      cursor.compare(to_string(BAD_IN)) != 0 &&
      cursor.compare(to_string(BAD_OUT)) != 0 &&
      cursor.length() < text.length() - 1 ){
        cout << cursor << endl;
        text = text.substr(cursor.length(),text.length() - 1);
        result++;
    }
    else{
      counting = false;
    }

    if (text.length() == 0){
      counting = false;
    };

  }


  
  return result;

}

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
  cout << text.length();
  text = StringTrimmer(text,filter);
  cout << text.length();
  
  string result = "";
  string cursor = "";

  int tempInt = 0;

  if(text.length() > 0 && index <= RollCall(text,filter) && index > 0){
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
    result = OVERBOUNDS;
  }
  else if(result.empty()){
    result = to_string(BAD_IN);
  }
  else{
    result = to_string(BAD_IN);
  }

  return result;
}


//*****************RandStr()******************
string RandStr(int len){
  
  string result = "" ;
  int randomInt = 0;
  
  for (int i = 0; i < len; i++ ){
    randomInt = (rand() % 94) + 33;
    result += (char)randomInt;
  }
  
  return result;
}

//*****************Analyze********************
void Analyze(string expected, string received, string subject){
  
  cout << setw(SCREEN_X) << setfill('-') << left << "testing " + subject ;
  if( expected.compare(received) != 0 ){
    cout << REDTEXT + "FAILURE!!!\n";
  }
  else{
    cout << GREENTEXT + "SUCCESS!!!\n";
  }
  
  cout << subject + " -> expected " << expected << " -> received : " << received << endl;
  cout << EMPTYFORMAT;

}


//*****************CoreLoop*******************
int CoreLoop(Database& db, Menu& menu){


  bool running = true;
  while (running){
    
    menu.Prompt();
    menu.Process();
    
    //db.Process();

    running = (menu.GetState() != QUITING);
    menu.Stall();
  }
  return 0;
};


//*****************ProgramClosing*******************
void ProgramClosing(){
  cout << GREENTEXT << BANNER << EMPTYFORMAT << endl;
    
  cout << "Thank you for using list manager" << endl;
  cout << setw(SCREEN_X) << right << "coded by Trevor Haggerty" << endl;
 
  cout << GREENTEXT << BANNER << EMPTYFORMAT << endl;

};


//*****************UnitTest*******************
void UnitTest(){

  cout << endl << YELLOWTEXT + "TESTING FUNCTIONS" + EMPTYFORMAT << endl;
  
 //----------------------------------------
  int testInt = RollCall(TEST_STRING_D, "7");
  Analyze("3", to_string(testInt),"RollCall");
  
  testInt = NumberCheck(TEST_STRING_D);
  Analyze("1", to_string(testInt),"NumberCheck");
  
  string testString = Tokenizer(TEST_STRING_A, 4);
  Analyze("faster", testString,"Tokenizer");

  testString = RandStr(5);
  Analyze(to_string(5),to_string(testString.length()),"RandStr");

  testInt = WordCount(TEST_STRING_A);
  Analyze("8", to_string(testInt),"WordCount");
  
  cout << YELLOWTEXT + "UNIT TESTING" + EMPTYFORMAT << endl << endl;
  cout << endl << YELLOWTEXT + "TESTING OBJECTS" + EMPTYFORMAT << endl << endl;
  
  Date testDate(TEST_INT_A, TEST_INT_B, TEST_INT_C);
  testDate.ClassTest();

  Menu testMenu;
  testMenu.ClassTest();

  Element testElement;
  testElement.ClassTest();
  string testEntry = TEST_STRING_A;
  testEntry >> testElement;
  cout << testElement;

  Database testDatabase;
  testDatabase.ClassTest();


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
  cout << endl << YELLOWTEXT + "Testing date" + EMPTYFORMAT << endl;

  int result = 0;

  Analyze(to_string(TEST_INT_A),to_string(Month),"Constructor -> Month");
  Analyze(to_string(TEST_INT_B),to_string(Day),"Constructor -> Day");
  Analyze(to_string(TEST_INT_C),to_string(Year),"Constructor -> Year");
  
  //----------------------------------------

  time_t currentTime = time(0);
  tm *timeFormated = localtime(&currentTime);
  SetDateAuto();
  
  Analyze(to_string(timeFormated->tm_mon + 1),to_string(Month),"Automatic setting -> Month");
  Analyze(to_string(timeFormated->tm_mday),to_string(Day),"Automatic setting -> Day");
  Analyze(to_string(timeFormated->tm_year + 1900),to_string(Year),"Automatic setting -> Year");
  
  //----------------------------------------

  SetDate(TEST_INT_C,TEST_INT_A,TEST_INT_B);
  
  Analyze(to_string(TEST_INT_C),to_string(Month),"Manual setting -> Month");
  Analyze(to_string(TEST_INT_A),to_string(Day),"Manual setting -> Day");
  Analyze(to_string(TEST_INT_B),to_string(Year),"Manual setting -> Year");
  
  //----------------------------------------

  string testOutput = Display();

  string testString = to_string(TEST_INT_C);
  testString += " / " + to_string(TEST_INT_A);
  testString += " / " + to_string(TEST_INT_B);

  Analyze(testString,testOutput,"Manual setting -> Year");

}
//*********************Menu implementation************************
//constructor---------------------------------
Menu::Menu(){

  state = INITIAL;
  cursor = INITIAL;
  bufferStr = "";
  bufferInt = 0;

  optionText = nullptr;
  optionText = new string[10];

  optionFilter = nullptr;
  optionFilter = new string[10];
  
  string tempStr = BANNER + "\n";
  tempStr += "MAIN MENU\n";
  tempStr += BANNER + "\n";
  tempStr += "+ 'text' <--- to add a TO DO entry\n";
  tempStr += "- 'id'   <--- to remove a TO DO entry by id\n";
  tempStr += "m 'id'   <--- to modify a TO DO entry by id\n";
  tempStr += "?        <--- to veiw the TO DO entries\n";
  tempStr += "quit     <--- to quit the program\n";


  *(optionText + INITIAL) = tempStr;

  tempStr = "+-m?q";

  *(optionFilter + INITIAL) = tempStr;

  tempStr = "";
  tempStr += "__MODIFICATION HELP__\nt 'text'  <--- to change entry text\n";
  tempStr += "p 'int' <--- to change priority level\n";
  tempStr += "c       <--- to toggle completion\n";
  tempStr += "q       <--- to exit the modification menu\n";

  *(optionText + MODIFYING) = tempStr;

  tempStr = "tpc? quit";

  *(optionFilter + MODIFYING) = tempStr;

  tempStr = "Would you like to save your changes before exiting?";

  *(optionText + QUITING) = tempStr;

  tempStr = "yn yes no";

  *(optionFilter + QUITING) = tempStr;

}

//buffer display function-----------------------------------
string Menu::DisplayBuffers(){

  string result = "string: " + bufferStr;
  result += ", int: " + to_string(bufferInt);
  result += ", char: " + to_string(bufferChar);
  result += ", state: " + to_string(state);
  result += ", cursor: " + to_string(cursor) + "\n";

  cout << result;

  return result;
}
//Main display function-----------------------------------
string Menu::DisplayOptions(){

  string result = *(optionText + state);

  cout << MAGENTATEXT << result << EMPTYFORMAT;
  return result;
}


//Main prompting function-----------------------------------
void Menu::Prompt(){
   
  bool asking = true;



  while(asking){

    //prompt the user
    cout << *(optionText + state) << YELLOWTEXT << "user: "<<EMPTYFORMAT;
    
    bufferInt = INITIAL;
    getline(cin, bufferStr);
    


    {

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

};


//Unit test------------------------------------------ 
void Menu::ClassTest(){
  
  cout << endl << YELLOWTEXT + "Testing Menu" + EMPTYFORMAT << endl;

  int result = 0;
  //----------------------------------------
  
  Analyze(to_string(INITIAL),to_string(GetState()),"Constructor -> State");
  Analyze(to_string(INITIAL),to_string(GetState()),"Constructor -> Cursor");
  Analyze("",GetBufferStr(),"Constructor -> BufferStr");
  Analyze("0",to_string(GetBufferInt()),"Constructor -> BufferInt");
  
  //----------------------------------------
  
  SetState(TEST_INT_C);
  SetBufferStr(TEST_STRING_A);
  SetBufferInt(TEST_INT_A);
  SetBufferChar('T');
  
  Analyze(to_string(TEST_INT_C),to_string(GetState()),"Setters / Getters -> State");
  Analyze(TEST_STRING_A, GetBufferStr(),"Setters / Getters -> BufferStr");
  Analyze(to_string(TEST_INT_A),to_string(GetBufferInt()),"Setters / Getters -> BufferInt");
  Analyze(to_string('T'),to_string(GetBufferChar()),"Setters / Getters -> BufferChar");
  
  SetState(INITIAL);
  //--------------------------------------------
  cout << GREENTEXT << "- Menu.Process()" << EMPTYFORMAT << endl;

  SetState(INITIAL);
  SetBufferStr("quit");
  Process();
  Analyze(to_string(QUITING),to_string(GetState()),"Processing -> quit");

  //----------------------------------------------
  
  SetState(INITIAL);
  SetBufferStr("help");
  Process();
  Analyze(to_string(INITIAL),to_string(GetState()),"Processing -> help");
  //----------------------------------------------
  
  SetState(INITIAL);
  SetBufferStr("?");
  SetBufferChar('?');
  Process();
  Analyze(to_string(DISPLAYING),to_string(GetState()),"Processing -> ?");
  //----------------------------------------------

  SetState(INITIAL);
  SetBufferStr("+ sample entry");
  SetBufferChar('+');
  Process();
  Analyze(to_string(RECORDING),to_string(GetState()),"Processing -> +");
  //----------------------------------------------
  
  SetState(INITIAL);
  SetBufferStr("- 34587");
  SetBufferChar('-');
  Process();
  Analyze(to_string(DELETING),to_string(GetState()),"Processing -> -");
  //----------------------------------------------
  

}


//destructor
Menu::~Menu(){
  delete [] optionText;
}


//********************* -Database-  implementation************************
Database::Database(){
  
  listMaxSize = 0;
  listSize = 0;

  dynoList = nullptr;
  dynoList = new Element[INITIAL];
  
  idList = nullptr;
  idList = new int[INITIAL];

}

//********************* test if UniqueId***************
bool Database::TestUniqueId(int choice){

  bool found = false;
  int cursor;

  for(int i = 0; i < listSize; i++){
    cursor = *(idList + i);

    if (cursor == choice){
        found = true;
    }
  }

  return found;
}

//********************* test if UniqueId***************
int Database::GenerateUniqueId(){
  int choice = rand() % 100000;
  while(TestUniqueId(choice)){
    choice = rand() % 100000;
  }
  return choice;
}

void Database::Display(){
  for (int i = 0; i < listSize; i++){
    cout << *(dynoList + i);
  }
}


int Database::AppendElem(Element addition){
  int result = 0;
  if (listSize + 1 >= listMaxSize){
    Expand(1);
  }
  
  *(dynoList + listSize) = addition;
  *(idList + listSize) = addition.GetId();

  listSize += 1;

  return result;
}


int Database::Expand(int amount){

  int result = 0;

  Element *newArray = nullptr;
  newArray = new Element[listMaxSize + amount];
  
  int *newIdArray = nullptr;
  newIdArray = new int[listMaxSize + amount];


  for (int q = 0; q < listMaxSize; q++){
    *(newArray + q) = *(dynoList + q);
    *(newIdArray + q) = *(idList + q);
  }

  dynoList = newArray;
  idList = newIdArray;

  listMaxSize += amount;

  return result;
}


int Database::Contract(int amount){

  int result = 0;

  Element *newArray = nullptr;
  newArray = new Element[listMaxSize - amount];

  int *newIdArray = nullptr;
  newIdArray = new int[listMaxSize - amount];

  for (int q = 0; q < listMaxSize - amount; q++){
    *(newArray + q) = *(dynoList + q);
    *(newIdArray + q) = *(idList + q);
  }

  dynoList = newArray;
  idList = newIdArray;
  listMaxSize -= amount;
  
  return result;
}


int Database::DeleteElem(int index){
  int result = 0;
  if (listSize != 0 && index >= 0 && index < listSize){

    cout << GREENTEXT << "Deleting Element" << EMPTYFORMAT <<endl;
      
    int result = 0;

    Element *newArray = nullptr;
    newArray = new Element[listMaxSize - 1];
  
    int *newIdArray = nullptr;
    newIdArray = new int[listMaxSize - 1];


    for (int q = 0; q < index; q++){
      *(newArray + q) = *(dynoList + q);
      *(newIdArray + q) = *(idList + q);
    }
    for (int q = index + 1; q < listMaxSize ; q++){
    *(newArray + q - 1) = *(dynoList + q);
    *(newIdArray + q - 1) = *(idList + q);
    }

    dynoList = newArray;
    idList = newIdArray;

    listMaxSize -= 1;
    listSize -= 1;
  }
  else{
    result = BAD_IN;
  }

  return result;
}


int Database::InsertElem(int index, Element addition){
  
  int result = 0;

  Element *newArray = nullptr;
  newArray = new Element[listMaxSize + 1];
  
  int *newIdArray = nullptr;
  newIdArray = new int[listMaxSize + 1];


  for (int q = 0; q < index; q++){
    *(newArray + q) = *(dynoList + q);
    *(newIdArray + q) = *(idList + q);
  }

  *(newArray + index) = addition;
  *(newIdArray + index) = addition.GetId();

  for (int q = index + 1; q < listMaxSize + 1; q++){
    *(newArray + q) = *(dynoList + q - 1);
    *(newIdArray + q) = *(idList + q - 1);
  }

  dynoList = newArray;
  idList = newIdArray;

  listMaxSize += 1;
  listSize += 1;

  return result;
}


Element Database::GetElem(int index){

  Element temp = *(dynoList + index);
  return temp;

}


int Database::IndexToId(int index){
  
  int result = -1;

  if(index >= 0 && index < listSize){
    
    result = *(idList + index);
  }

  return result;

}


int Database::IdToIndex(int id){
  
  int result = -1;
  
  for(int i = 0; i < listSize; i++){
    if (id == *(idList + i)){
      result = i;
    }

  }
  return result;
}

int Database::ReplaceElem(int index, Element element){
  if (index < listSize && index >= 0 && listSize > 0){
    *(dynoList + index) = element;
  }
  return 0;
}
 
int Database::Process(){
  int result = 0;


  return result;
}

//----------unit testing---------------------
void Database::ClassTest(){

  cout << endl<< YELLOWTEXT + "Testing Database" + EMPTYFORMAT << endl;

  //testing the constructor
  Analyze(to_string(0),to_string(listMaxSize),"listMaxSize");
  Analyze(to_string(0),to_string(listSize),"listSize");

  Element testElement;
  string testEntry = "";
  


  //----------------------------
  cout << "- Testing Expand" + EMPTYFORMAT << endl;
  Expand(3);

  Analyze(to_string(3),to_string(listMaxSize),"listMaxSize");
  Analyze(to_string(0),to_string(listSize),"listSize");

  //----------------------------
  cout <<  "- Testing Contract" + EMPTYFORMAT << endl;
  Contract(3);

  Analyze(to_string(0),to_string(listMaxSize),"listMaxSize");
  Analyze(to_string(0),to_string(listSize),"listSize");

  //testing append 3 times--------------------------------
  cout << "- Testing AppendElem" + EMPTYFORMAT << endl;
  
  int counter = 0;


  for(int i = 0; i < 5; i++){

    cout << endl << GREENTEXT << "- Testing AppendElem " << i << EMPTYFORMAT << endl;

    testElement.SetId(GenerateUniqueId());
    testElement.SetCompleted(false);
    testEntry = RandStr(40);
    testEntry >> testElement;
  
    
    cout << testElement;

    AppendElem(testElement);
    counter+=1;

    Analyze(to_string(counter),to_string(listSize),("element " + to_string(counter))+"-> listSize ");
    Analyze(to_string(counter),to_string(listMaxSize),("element " + to_string(counter))+"-> listMaxSize ");
    Display();
  }
  //testing insertion
  cout << GREENTEXT << "- Testing InsertElem" + EMPTYFORMAT << endl;
  
  for(int i = 0; i < 2; i++){
    cout <<endl<< GREENTEXT << "- Testing InsertElem " << i << EMPTYFORMAT << endl;
    
    testElement.SetId(GenerateUniqueId());
    testElement.SetCompleted(true);
    testEntry = RandStr(40);
    testEntry >> testElement;
    cout << testElement;

    InsertElem(1,testElement);
    counter+=1;

    Analyze(to_string(counter),to_string(listSize),("element " + to_string(counter)) + "-> listSize ");
    Analyze(to_string(counter),to_string(listMaxSize),("element " + to_string(counter)) + "-> listMaxSize ");
  
    Display();
  }
    

  testElement.SetId(TEST_INT_A);
  testElement.SetCompleted(true);
  testEntry = TEST_STRING_A;
  testEntry >> testElement;
  

  InsertElem(1,testElement);
  counter += 1;

  //get element
  Analyze(TEST_STRING_A, GetElem(1).GetEntry(), "element entry getter");
  Analyze(to_string(true),to_string(GetElem(1).GetCompleted()), "element completion getter");

  //get id



  //----------------------------------------------   
  for(int i = 0; i < 4; i++){
    cout << endl << GREENTEXT << "- Testing DeleteElem " << i << EMPTYFORMAT << endl;
    DeleteElem(0);
    counter-=1;

    Analyze(to_string(counter),to_string(listSize),("element " + to_string(counter))+"-> listSize ");
    Analyze(to_string(counter),to_string(listMaxSize),("element " + to_string(counter))+"-> listMaxSize ");
    Display();
  }

  DeleteElem(0);
  counter -= 1 ;
  Analyze(to_string(counter),to_string(listSize),("element " + to_string(counter))+"-> listSize ");
  Analyze(to_string(counter),to_string(listMaxSize),("element " + to_string(counter))+"-> listMaxSize ");
  
}

//destructor---------------------------------
Database::~Database(){
  delete [] dynoList;
  delete [] idList;
}

//********************* -Element-  implementation************************
//constructor---------------------------------
Element::Element(){

  id = 0;
  entry = "";
  completed = false;
  priority = 0;
  date.SetDateAuto();

}

Element::Element(string inEntry){

  id = 0;
  entry = inEntry;
  completed = false;
  priority = 0;
  date.SetDateAuto();

}

//overloaded >> operator
string &operator>>(string& s, Element &element){
  element.entry = s;
  return s;
};

//overloaded
ostream &operator<<(ostream& out, Element element){
  if(element.priority >= 9){
    cout << REDTEXT;
  }
  else if(element.priority >= 7){
    cout << YELLOWTEXT;
  }
  else if(element.priority >= 5){
    cout << BLUETEXT;
  }
  if (element.completed){
    cout << GREENTEXT << "COMPLETED!" ;
  }

  cout << setfill(' ');
  cout << left << "Id:" << right << setw(5) << element.id; 
  cout << left << " -> " << element.entry; 
  cout << " |  " << setw(5) << left<< element.date.Display();
  cout << " | Priority: " << setw(5) << left<< element.priority << EMPTYFORMAT;
  cout << endl;
  return out;
}

//Unit test------------------------------------------ 
void Element::ClassTest(){
  
  Date testdate;
  
  cout << endl<< YELLOWTEXT + "Testing Element" + EMPTYFORMAT << endl;
  
  //test constructors--------------------------------------
  Analyze(to_string(0),to_string(id),"Constructor -> id");
  Analyze(to_string(0),to_string(priority),"Constructor -> priority");
  Analyze("",entry,"Constructor -> entry");
  Analyze(testdate.Display(),date.Display(),"Constructor -> date");
  Analyze(to_string(false),to_string(completed),"Constructor -> completed");

  //test setters/getters-----------------------------------  SetIndex(TEST_INT_A);
  SetId(TEST_INT_B);
  SetPriority(2);
  SetEntry(TEST_STRING_A);
  SetCompleted(false);
  SetDate(1,1,1);
  
  Analyze(to_string(TEST_INT_B),to_string(GetId()),"Setters/Getters -> id");
  Analyze(to_string(2),to_string(GetPriority()),"Setters/Getters -> priority");
  Analyze(TEST_STRING_A,GetEntry(),"Setters/Getters -> entry");
  Analyze("1 / 1 / 1",date.Display(),"Setters/Getters -> date");
  Analyze(to_string(false),to_string(completed),"Setters/Getters -> completed");
  //test setters/getters-----------------------------------  SetIndex(TEST_INT_A);
  
  
}


