/** This hangman game coded by the efforts of the Cabrillo College
    CS11 Students. Spring 2018 Semester Watsonville Campus */

#include <iostream>
#include <fstream>
#include <vector>

class Hangman {
public:
  Hangman();
  Hangman(std::string);
  Hangman(std::ifstream& ifile);
  ~Hangman();
  void play();
  static const std::string DEFAULTWORD;
  static const int WRONGALLOWED;
private:
  std::string* gallows;
  std::vector<std::string> _words;
  std::string guessWord, wordState, currGuess, graveYard;
  int numWrong, numRight, wordSize;
  bool gameWon;
  void init(std::string);
  void setGallows();
  void setWordState();
  void printGallows();
  void printWordState();
  void printGraveYard();
  bool validInput();
  bool inGraveYard();
  bool gameOver();
  void checkLetter();
};

const std::string Hangman::DEFAULTWORD = "testword";
const int Hangman::WRONGALLOWED = 6;

Hangman::Hangman() {
  init(DEFAULTWORD);
}

Hangman::Hangman(std::string chosenWord){
  init(chosenWord);
}

Hangman::Hangman(std::ifstream& ifile) {
  if (ifile.fail()) {
    std::cout << "Unable to open file!" << std::endl;
    exit(-1);
  }

  std::string word = "";
  while (ifile >> word) {
    _words.push_back(word);
  }
}

Hangman::~Hangman(){
  delete[] gallows;
  }

void Hangman::init(std::string word){
  guessWord = word;
  wordSize = guessWord.length();
  numRight = numWrong = 0;
  gameWon = false;
  graveYard = "";
  setGallows();
  setWordState();
}


void Hangman::setGallows(){
  gallows = new std::string[WRONGALLOWED + 1];
  std::string top = " ---\n |  |\n";
  std::string head = " |  O\n";
  std::string body = " | -|-\n";
  std::string feet = " |_/ \\_\n";
  std::string base = "/ \\\n";
  gallows[0] = top
    + head.substr(0, 2) + "\n"
    + body.substr(0, 2) + "\n"
    + feet.substr(0, 2) + "\n"
    + base;
  gallows[1] = top
    + head
    + body.substr(0, 2) + "\n"
    + feet.substr(0, 2) + "\n"
    + base;
  gallows[2] = top + head
    + body.substr(0, 4) + "\n"
    + feet.substr(0, 2) + "\n"
    + base;
  gallows[3] = top + head
    + body.substr(0, 5) + "\n"
    + feet.substr(0, 2) + "\n"
    + base;
  gallows[4] = top + head + body
    + feet.substr(0, 2) + "\n"
    + base;
  gallows[5] = top + head + body
    + feet.substr(0, 4) + "\n"
    + base;
  gallows[6] = top + head + body + feet + base;
}

void Hangman::setWordState(){
  wordState = "";
    for(int i = 0; i < wordSize; i++){
      wordState += "_";
    }
}

void Hangman::printGallows(){
  std::cout << gallows[numWrong];
}

void Hangman::printWordState(){
  std::cout << "Secret Word: ";
  for(int i = 0; i < wordSize; i++){
    std::cout << wordState[i] << " ";
  }
  std::cout << std::endl;
}

void Hangman::printGraveYard(){
  int size = graveYard.length();
  std::cout << "Letters Chosen: ";
  for(int i = 0; i < size; i++){
    std::cout << graveYard[i] << " ";
  }
  std::cout << std::endl;
}

bool Hangman::validInput(){
  return currGuess.length() == 1 && isalpha(currGuess[0]) && !inGraveYard();
}

bool Hangman::inGraveYard(){
  bool contains = false;
  currGuess = tolower(currGuess[0]);
  int size = graveYard.length();
  for(int i = 0; i < size; i++){
    if(currGuess[0] == graveYard[i]){
      contains = true;
      std::cout << "Letter has already been chosen!\n";
    }
  }
  return contains;
}

bool Hangman::gameOver(){
  gameWon = numRight == wordSize;
  return numWrong == WRONGALLOWED || gameWon;
}

void Hangman::checkLetter(){
  bool contains = false;
  for(int i = 0; i < wordSize; i++){
    if(currGuess[0] == guessWord[i]){
      contains = true;
      wordState[i] = currGuess[0];
      numRight++;
    }
  }
  if(!contains){
    numWrong++;
  }
}

void Hangman::play(){
  std::cout << "Let's play a game!\n";
  while(!gameOver()){
    printGallows();
    printWordState();
    printGraveYard();
    do {
      std::cout << "Please enter a single letter: ";
      std::cin >> currGuess;
    } while (!validInput());
    graveYard += currGuess;
    checkLetter();
  }
  if(gameWon){
    printWordState();
    std::cout << "Congratulations on the win!\n";
  } else {
    printGallows();
    std::cout << "Better luck next time.\n";
  }
}

int main() {
  Hangman bob;
  bob.play();
  return 0;
}
