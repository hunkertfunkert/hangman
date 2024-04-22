#include "hangman.h"

#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

HangmanGame::HangmanGame() {
    initializeWords();

    //choose between easy and hard mode, if an invalid answer is given then give an error message and retry
    char mode;
    bool validMode = false;
    while (!validMode) {
        cout << "Choose mode: Easy (E) or Hard (H): ";
        cin >> mode;
        if (mode == 'E' || mode == 'e' || mode == 'H' || mode == 'h') {
            validMode = true;
        } else {
            cout << "Invalid mode. Please choose Easy (E) or Hard (H)." << endl;
        }
    }

    //choose between english and spanish words for the game, same error idea as last time
    char language;
    bool validLanguage = false;
    while (!validLanguage) {
        cout << "Choose language: English (E) or Spanish (S): ";
        cin >> language;
        if (language == 'E' || language == 'e' || language == 'S' || language == 's') {
            validLanguage = true;
        } else {
            cout << "Invalid language. Please choose English (E) or Spanish (S)." << endl;
        }
    }


    if (language == 'E' || language == 'e') {
        if (mode == 'E' || mode == 'e') {
            word = pickRandomWord(easyWords);
        } else if (mode == 'H' || mode == 'h') {
            word = pickRandomWord(hardWords);
        }
    } else if (language == 'S' || language == 's') {
        if (mode == 'E' || mode == 'e') {
            word = pickRandomWord(spanishEasyWords);
        } else if (mode == 'H' || mode == 'h') {
            word = pickRandomWord(spanishHardWords);
        }
    }
        wordTemplate = std::string(word.length(), '_');
        remainingAttempts = 7;

        //initializing the hangman states for the game
        hangmanStates.push("+- - -+\n|     |\n      |\n      |\n      |\n      |\n=========");
        hangmanStates.push("+- - -+\n|     |\n0     |\n      |\n      |\n      |\n=========");
        hangmanStates.push("+- - -+\n|     |\n0     |\n|     |\n      |\n      |\n=========");
        hangmanStates.push("  +- - -+\n  |     |\n  0     |\n/ |     |\n        |\n        |\n=========");
        hangmanStates.push("  +- - -+\n  |     |\n  0     |\n/ | \\   |\n        |\n        |\n=========");
        hangmanStates.push("  +- - -+\n  |     |\n  0     |\n/ | \\   |\n /      |\n        |\n=========");
        hangmanStates.push("  +- - -+\n  |     |\n  0     |\n/ | \\   |\n / \\    |\n        |\n=========");
    }

    void HangmanGame::play() {
        cout << "THE HANGMAN GAME\n";
        cout << "  +- - -+\n  |     |\n  0     |\n/ | \\   |\n / \\    |\n        |\n=========\n";
        cout << "Guess the word: " << wordTemplate << "\n";

        vector<char> guessedLetters;

        //while loop to count down remaining attempts and check if game is already won
        while (remainingAttempts > 0 && wordTemplate != word) {
            char letter;
            cout << "Enter a letter: ";
            cin >> letter;

            //checks if input is a valid letter for the game
            if (!isLetter(letter)) {
                cout << "Please enter a valid letter.\n";
                continue;
            }

            //checks if the letter has already been correctly guessed, gives a little message instead of another "correct guess!"
            bool alreadyGuessed = false;
            for (char guessedLetter : guessedLetters) {
                if (guessedLetter == letter) {
                    alreadyGuessed = true;
                    cout << "You've already guessed '" << letter << "' correctly.\n";
                    break;
                }
            }
            if (alreadyGuessed) {
                continue;
            }

            //give the player a hint when nearing the end of the game
            if (remainingAttempts == 3) {
                int randomIndex = rand() % word.length();
                char randomLetter = word[randomIndex];
                cout << "Hint, the word contains the letter '" << randomLetter << "'." << endl;
            }

            //checks guessed letter vs the letter from the selected random words
            if (word.find(letter) != string::npos) {
                updateWordTemplate(word, letter);
                cout << "Correct guess!\n";
                guessedLetters.push_back(letter);
            } else {
                --remainingAttempts;
                cout << "Incorrect guess! Remaining attempts: " << remainingAttempts << "\n";
                // Display the hangman state
                if (!hangmanStates.empty()) {
                    displayHangmanState(6 - remainingAttempts);
                }
            }

            cout << "Current progress: " << wordTemplate << "\n";
        }

        //win or lose after attempts have run out
        if (wordTemplate == word) {
            cout << "Congratulations! You guessed the word: " << word << "\n";
            cout << "                  .       |         .    .\n";
            cout << "            .  *         -*-          *\n";
            cout << "                 \\        |         /   .\n";
            cout << ".    .            .      /^\\     .              .    .\n";
            cout << "   *    |\\   /\\    /\\  / / \\ \\  /\\    /\\   /|    *\n";
            cout << " .   .  |  \\ \\/ /\\ \\ / /     \\ \\ / /\\ \\/ /  | .     .\n";
            cout << "         \\ | _ _\\/ _ _ \\_\\_ _ /_/_ _\\/ _ _\\_/\n";
            cout << "           \\  *  *  *   \\ \\/ /  *  *  *  /\n";
            cout << "            ` ~ ~ ~ ~ ~  ~\\/~ ~ ~ ~ ~ ~ '\n";
            cout << "                   YOU          WIN             \n";
        } else {
            cout << "No more attempts. The correct word was: " << word << "\n";
        }
    }

//selects a random word from the chosen set of words
string HangmanGame::pickRandomWord(const vector<string>& words) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, words.size() - 1);
    int index = distrib(gen);
    return words[index];
}

//valid letter logic
bool HangmanGame::isLetter(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    //
    void HangmanGame::updateWordTemplate(const std::string& word, char letter) {
        for (size_t i = 0; i < word.length(); ++i) {
            if (word[i] == letter) {
                wordTemplate[i] = letter;
            }
        }
    }

    //displays the hangman for the correct number of attempts the player is on
    void HangmanGame::displayHangmanState(int attempts) {
    if (!hangmanStates.empty()) {
        cout << hangmanStates.front() << endl;
        hangmanStates.pop();
    }
}

//initialize list of words for each potential mode
void HangmanGame::initializeWords() {
    //english easy mode words
    easyWords = {"hangman", "pies", "clion", "oats", "hello", "algorithm", "wellbeing", "structures", "challenge", "vocabulary", "knowledge", "exercise", "solution", "entertainment", "minecraft", "village", "community", "experience", "intelligence", "technology"};
    //english hard mode words
    hardWords = {"extraterrestrial", "unbelievable", "onomatopoeia", "haphazard", "phenomenon", "juxtaposition", "exponential", "polyglot", "serendipity", "facetious", "grandiloquent", "onomastic", "quintessential", "serenity", "ephemeral", "plethora", "obfuscate", "quizzical", "rapscallion", "sesquipedalian"};
    //spanish easy mode words
    spanishEasyWords = {"hola", "perro", "gato", "casa", "amigo", "fiesta", "familia", "jugar", "colegio", "libro", "comer", "agua", "telefono", "grande", "amor", "feliz", "mundo", "paz", "trabajo", "escuela"};
    //spanish hard mode words
    spanishHardWords = {"extraordinario", "imposible", "onomatopeya", "azaroso", "fenomeno", "yuxtaposicion", "exponencial", "poliglota", "serendipia", "faceto", "grandilocuente", "onomastico", "quintaesencia", "serenidad", "efimero", "profusion", "obscuro", "curioso", "travesura", "sesquipedal"};
        }
