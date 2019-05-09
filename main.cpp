/*----------------------------------------------------------------------------------------------------------------------------------------------
Implementation of Evil Hangman
CS 330: Shyan Yen
*///--------------------------------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <Windows.h>
#include <algorithm>
#include <map>
#include <limits>
#include <cctype>

using namespace std;

string player;
string words;
string guess;
string secretWord;
string blanks = "";
string famWord = "";
vector<string> dictionary; //dictionary of words vector
vector<string> wordList; //list of possible words from wordLength created from dictionary vector
vector<string> guessList; //hold all guesses to see if player already guessed the letter
vector<string> mistakes; //use size to count # of mistakes to continue/end game & print at end
vector<string> rightAns; //player's correct guesses to print at end
int i = 0;
int counter = 0;
int height = 4; //2D array row
int width = 3; //2D array column
int wordLength; //user chooses length of secret word
bool gameOver;
bool matchedLetter;
char emptyMan[4][3] = {{' ',' ',' '},
                       {' ',' ',' '},
                       {' ',' ',' '},
                       {'_','_','_'}};
char builtMan[4][3] = {{' ','O',' '},
                       {'/','|','\\'},
                       {' ','|',' '},
                       {'/',' ','\\'}};

void rules();
void assignLength();
void findWords();
void ranWord();
void hangMan();
void getGuess();
vector<string> findMaxFamilyWords(vector<string> words, string letter, string& family);
string pattern(string word, string letter);
string checkGuess(string family, string guess, bool& found);
void fillBlank();

int main()
{
    ifstream dict_file("dictionary.txt");

    while(getline(dict_file, words))
    {
        string new_line;
        new_line = words + "\n";
        dictionary.push_back(words);
    }
        if (dictionary.size() == 0)
        {
            cerr << "Unable to open file dictionary.txt";
            exit(1);
        }
    dict_file.close();

    rules();
    assignLength();
    findWords();
    hangMan();
    fillBlank();
    return 0;
}

void rules()
{
    cout << "Enter your name, player: ";
    cin >> player;

    cout << "Enter desired length of word (minimum 4, max 29): ";
    cin >> wordLength;
}

void checkGame()
{
    if (mistakes.size() == 6)
    {
        gameOver = true;
    }
    else
    {
        gameOver = false;
    }
}

void assignLength()
/*----------------------------------------------------------------------------------------------------------------------------------------------
Bases of user's choice of length assign
the number of dashes to represent the
secret word.
Verify that user enters a number that
is in range.
*///--------------------------------------------------------------------------------------------------------------------------------------------
{

    while (cin.fail() || (!cin.fail() && (wordLength < 4 || wordLength > 29)))
    {
        cout << "Please enter a valid number within given range: " << endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> wordLength;
    }

    string blanks(wordLength, '-');
    cout << "Secret word: " + blanks << endl;
}


void findWords()
/*----------------------------------------------------------------------------------------------------------------------------------------------
Append words based off of user's wordLength from
dictionary vector to new vector called wordList
which will hold all words with length wordLength.
*///--------------------------------------------------------------------------------------------------------------------------------------------
{
    for (int i = 0; i < dictionary.size(); i++)
    {
       if (dictionary[i].length() == wordLength)
       {
          wordList.push_back(dictionary[i]);
       }
    }
}

void baseMan()
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            cout << emptyMan[i][j] << ' ';
        }
        cout << "" << endl;
    }
}

void wholeMan()
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            cout << builtMan[i][j] << ' ';
        }
        cout << "" << endl;
    }
}

void hangMan()
{
    if (mistakes.size() == 0)
    {
        cout << "Hangman: " << endl;
        baseMan();
        cout << "" << endl;
    }

    if (mistakes.size() == 1)
    {
        cout << "Hangman: " << endl;
        emptyMan[0][1] = builtMan[0][1];
        baseMan();
        cout << "" << endl;
    }

    if (mistakes.size() == 2)
    {
        cout << "Hangman: " << endl;
        emptyMan[0][1] = builtMan[0][1];
        emptyMan[1][1] = builtMan[1][1];
        emptyMan[2][1] = builtMan[2][1];
        baseMan();
        cout << "" << endl;
    }

    if (mistakes.size() == 3)
    {
        cout << "Hangman: " << endl;
        emptyMan[0][1] = builtMan[0][1];
        emptyMan[1][1] = builtMan[1][1];
        emptyMan[2][1] = builtMan[2][1];
        emptyMan[1][0] = builtMan[1][0];
        baseMan();
        cout << "" << endl;
    }

    if (mistakes.size() == 4)
    {
        cout << "Hangman: " << endl;
        emptyMan[0][1] = builtMan[0][1];
        emptyMan[1][1] = builtMan[1][1];
        emptyMan[2][1] = builtMan[2][1];
        emptyMan[1][0] = builtMan[1][0];
        emptyMan[1][2] = builtMan[1][2];
        baseMan();
        cout << "" << endl;
    }

    if (mistakes.size() == 5)
    {
        cout << "Hangman: " << endl;
        emptyMan[0][1] = builtMan[0][1];
        emptyMan[1][1] = builtMan[1][1];
        emptyMan[2][1] = builtMan[2][1];
        emptyMan[1][0] = builtMan[1][0];
        emptyMan[1][2] = builtMan[1][2];
        emptyMan[3][0] = builtMan[3][0];
        baseMan();
        cout << "" << endl;
    }

    if (mistakes.size() == 6)
    {
        cout << "Hangman: " << endl;
        wholeMan();
        cout << "" << endl;

        cout << "You lose, sorry " + player + " :(" << endl;
        srand(time(0));

        secretWord = wordList[rand()%wordList.size()];
        cout << "The secret word was '" + secretWord + "'" << endl;

        cout << "Wrong guesses: " << endl;
        for (i = 0; i < mistakes.size(); i++)
        {
            cout << " '" << mistakes[i] << "' ";
        }

        cout << '\n' << "Correct guesses: " << endl;
        for (i = 0; i < rightAns.size(); i++)
        {
            cout << " '" << rightAns[i] << "' ";
        }
    }
}

void getGuess()
/*----------------------------------------------------------------------------------------------------------------------------------------------
Retrieve player guess and see if user has
already guessed the letter before/limit the
user to only entering a single letter.
*///--------------------------------------------------------------------------------------------------------------------------------------------
{
    cout << "Enter your guess " + player + ": ";
    getline(cin, guess); //in case user enters input with word space word, extracts/stores into one string
    if (counter == 0)
    {
        getline(cin, guess);
        counter++;
    }

    bool rejected = true;

    while(rejected)
    {
        while (!isalpha(guess[i]) || guess[i] == ' ' || guess.size() > 1 )
        {
            if (!isalpha(guess[i]) || guess[i] == ' ')
            {
                cout << "Enter a letter from the alphabet please: ";
            }
            else if (guess.size() > 1)
            {
                cout << "Enter a single letter only please: ";
            }
            getline(cin, guess);
        }

        if(guess[0] >='A' && guess[0] <= 'Z')
        {
            guess = guess[0] + 32; //convert cap to no cap
        }

        if (find(guessList.begin(), guessList.end(), guess) != guessList.end())
        {
            cout << "You already guessed this letter, try again." << endl;
            cout << "Enter guess: ";
            getline(cin, guess);
        }
        else
        {
            rejected = false;
        }
    }
    guessList.push_back(guess);
}

string pattern(string word, string guess)
{
    string family = "";

    for (int i = 0; i < word.size(); i++)
    {
        if (word[i] == guess[0])
        {
            family += guess;
        }
        else
        {
            family += "-";
        }
    }
    return family;
}

vector<string> findMaxFamilyWords(vector<string> words, string guess, string& family) //map pattern to words -> create word family
{
    map <string, vector <string> > wordFamilyDictionary; //map pattern to list of words
    string familyGroupPattern;

    for (int i = 0; i < words.size(); i++) //find words that contain player's guess to create word families
    {
        if ((words[i].find(guess) != std::string::npos))
        {
            familyGroupPattern = pattern(words[i], guess); //if found, pattern is created
        }
        else
        {
            familyGroupPattern = string(wordLength, '-'); //empty blanks
        }

        if (wordFamilyDictionary.find(familyGroupPattern) != wordFamilyDictionary.end()) //check map to see if pattern exists as key
        {
            wordFamilyDictionary[familyGroupPattern]; //if not in already, add new pattern to map
        }
        wordFamilyDictionary[familyGroupPattern].push_back(words[i]); //pushing word into key
    }

    int maxLength = 0;
    vector<string> largestFamilyList; //map key with largest pattern
    string largestFamily;

    for (map<string, vector<string> >::iterator it = wordFamilyDictionary.begin(); it != wordFamilyDictionary.end(); ++it)
    {
        string key = it->first; //pulling key at iterator
        int tempLength = wordFamilyDictionary[key].size(); //find length of wordFamily at key
        if (tempLength > maxLength) //determine largest word family group
        {
            maxLength = tempLength;
            largestFamilyList = wordFamilyDictionary[key];
            largestFamily = key; //key added to largest pattern
        }
    }

    family = largestFamily; //set to pattern with most words
    return largestFamilyList;

}

string checkGuess(string famWord, string blanks, bool& matchedLetter)
{

    matchedLetter = false;

    for (int i = 0; i < wordLength; i++)
    {
        if (blanks[i] == '-' && famWord[i] != '-') //if blank empty and guess found, update position
        {
            blanks[i] = famWord[i]; //set to blank
            matchedLetter = true;
        }
    }
    return blanks;
}

void fillBlank()
/*----------------------------------------------------------------------------------------------------------------------------------------------
Fill in blank variable based off of user's guesses
and update hangman visual. Call getGuess function
to continue prompting user for guesses while their
mistakes are under the maximum allowed. Append the
player's correct and incorrect guesses to vectors.
*///--------------------------------------------------------------------------------------------------------------------------------------------
{

    checkGame();

    if (gameOver == true)
    {
        Sleep(1000);
        exit(1);
    }

    blanks = string(wordLength, '-');

    while (!gameOver)
    {
        if (blanks.find("-") == string::npos) //checks to see if no more dashes left
        {
            cout << "You win " + player + "! :)" << endl;

            cout << "Wrong guesses: " << endl;
            for (i = 0; i < mistakes.size(); i++)
            {
                cout << " '" << mistakes[i] << "' ";
            }

            cout << '\n' << "Correct guesses: " << endl;
            for (i = 0; i < rightAns.size(); i++)
            {
                cout << " '" << rightAns[i] << "' ";
            }
            break;
        }

        getGuess();

        wordList = findMaxFamilyWords(wordList, guess, famWord);

        blanks = checkGuess(famWord, blanks, matchedLetter);

        if(!matchedLetter)
        {
            cout << "You guessed incorrectly " + player + "!" << endl;
            mistakes.push_back(guess);
            cout << blanks << endl;
            cout << " " << endl;
            hangMan();
        }
        else
        {
            cout << "You guessed correctly " + player + "!" << endl;
            rightAns.push_back(guess);
            cout << " " << endl;
            cout << blanks << endl;
        }
        checkGame();
    }
}
