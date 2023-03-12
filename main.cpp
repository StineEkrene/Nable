#include "Graphic.h"
#include "Words.h"

int main()
{
	srand(time(0));
	vector<string> theWords = readWords("wordle-nyt-answers-alphabetical.txt");
	Graphic w(theWords);
	w.wait_for_close();

}

