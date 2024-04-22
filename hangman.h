#ifndef HANGMAN_H
#define HANGMAN_H

#include <string>
#include <vector>
#include <queue>

using namespace std;

    // define functions
    class HangmanGame {
    public:
        HangmanGame();
        void play();

    private:
        string pickRandomWord(const vector<string>& words);
        bool isLetter(char c);
        void updateWordTemplate(const string& word, char letter);
        void displayHangmanState(int attempts);
        void initializeWords();

        vector<string> easyWords;
        vector<string> hardWords;
        vector<string> spanishEasyWords;
        vector<string> spanishHardWords;
        string word;
        string wordTemplate;
        int remainingAttempts;
        queue<string> hangmanStates;
    };



#endif // HANGMAN_H
