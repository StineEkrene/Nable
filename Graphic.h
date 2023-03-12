#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"

enum class State {Incorrect, Correct, WrongPlacement, NotGuessed};


class Graphic : public AnimationWindow
{
private:
    static constexpr int pad = 50; //Padding, avstand mellom ende og knapper, evtuell avstand mellom knapper
    static constexpr int btnW = 100; // Knapp bredde
    static constexpr int btnH = 50; // Knapp høyde
    static constexpr int fieldW = 500; 
    static constexpr int fieldH = 50;
    static constexpr int fieldPad = 100;
    Fl_Button quit_button;
    Fl_Button play_again;
    Fl_Button enter;
    Fl_Input guess;

    static constexpr int boxsize = 80;
    static constexpr Point startpoint = {768/2,4*pad};

    State** boxes;

    vector<string> listOfWords;

    int guessNumber = 0;
    string guessWord;
    string secretWord;
    string** letters;

public:
    Color StateToColor(State state); 
    Graphic(vector<string> words);
    ~Graphic();

    void makeGuess();
    void correction(string g); 
    void correctColors();
    void writeLetters(); 

    static void cb_quit(Fl_Widget*, void* pw);
    static void cb_play_again(Fl_Widget*, void* pw);
    static void cb_enter(Fl_Widget*, void* pw);
};


