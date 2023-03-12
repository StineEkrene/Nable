#include "Graphic.h"

Graphic::Graphic(vector<string> words) :AnimationWindow{ 50, 50, 1024, 768, "Nable"}, listOfWords{words},
        quit_button{1024 - btnW -pad, btnH + pad ,btnW,btnH,"Quit"},
        play_again{1024 - btnW -pad, btnH + 3*pad ,btnW,btnH,"Play again"},
        enter{1024 - btnW -pad, btnH + 5*pad ,btnW,btnH,"Enter"},
        guess{768/2 - 70 , 768 - 2*btnH ,btnW*3,btnH,"Guess"}
{
        int randomIndex = rand()%(listOfWords.size());
        secretWord = listOfWords.at(randomIndex); 

        this->draw_text({768/2,2*pad}, "NABLE", Color::black, 50, Graph_lib::Font::helvetica_bold);
        this->color(Color::white);

        boxes = new State* [6];
        for (int i = 0; i < 6; i++)
        {
            boxes[i] = new State[5];
            for (int j = 0; j < 5; j++)
            {
                boxes[i][j] = State::NotGuessed; 
            }
            
        }

        letters = new string* [6];
        for (int i = 0; i < 6; i++)
        {
            letters[i] = new string[5];
            for (int j = 0; j < 5; j++)
            {
                letters[i][j] = "";
            }
        }
        
        this->correctColors();
        add(guess);
        add(enter);     enter.callback(cb_enter,this);

        
}

Graphic::~Graphic()
{
    for (int i = 0; i < 5; i++)
    {
        delete[] boxes[i];
        boxes[i] = nullptr;

        delete[] letters[i];
        letters[i] = nullptr;
    }
    
    delete[] boxes;
    boxes = nullptr;
    delete[] letters;
    letters = nullptr;
}

Color Graphic::StateToColor(State state){
    Color color = Color::light_gray;
    switch (state)
    {
    case State::Incorrect:
        color = Color::dark_gray; 
        break;
    
    case State::Correct:
        color = Color::green; 
        break;
    
    case State::WrongPlacement:
        color = Color::yellow; 
        break;

    case State::NotGuessed:
        color = Color::light_gray; 
        break;
    
    default:
        break;
    }
    return color;
}

void Graphic::makeGuess(){
    guessWord = guess.value();
    for_each(guessWord.begin(), guessWord.end(), [](char & c) {c = toupper(c);});
    guess.value("");
    correction(guessWord);
    correctColors();
    for (int i = 0; i < 5; i++)
    {
        letters[guessNumber][i] = guessWord[i];
    }
    writeLetters();
    guessNumber ++;
    
}

void Graphic::correction(string g){
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (g[i] == secretWord[j])
            {
                if (i==j)
                {
                    boxes[guessNumber][i] = State::Correct;
                    break;
                }else
                {
                    boxes[guessNumber][i] = State::WrongPlacement;
                }
                      
            }
        }
        if (boxes[guessNumber][i] == State::NotGuessed)
        {
            boxes[guessNumber][i] = State::Incorrect;
        }
 
    } 
}

void Graphic::correctColors(){
    for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 5; j++)
            {
               this->draw_rectangle({768/2 - 50 - boxsize +  boxsize*j + 5*j, 2*pad + 10 + boxsize*i+5*i},boxsize,boxsize,StateToColor(boxes[i][j]));
            }
                
        }
}

void Graphic::writeLetters(){
    for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                this->draw_text({768/2 - boxsize +  boxsize*j + 5*j - 25 , 2*pad + 10 + boxsize*i+5*i + 55},letters[i][j],Color::white,45,Font::helvetica_bold_italic);
            }
    }
}



void Graphic::cb_enter(Fl_Widget*, void* pw){
    static_cast<Graphic*> (pw)->makeGuess();
}

/*
void wordle::cb_quit(Fl_Widget*, void* pw);
void wordle::cb_play_again(Fl_Widget*, void* pw);
void wordle::cb_enter(Fl_Widget*, void* pw);*/
