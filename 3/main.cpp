#include <raylib.h>
#include <bits/stdc++.h>
using namespace std;

/*
** Authour : Mohamed boukerche 
** Date : 11 December 
** Code : Moha's type game using raylib c++
*/

int screenWidth = GetScreenHeight();
int screenHeight = GetScreenWidth();

enum GameState
{
    MENU,
    PLAYING,
    GAMEOVER
};

int main()
{
    InitWindow(screenWidth, screenHeight, "Moha's Type");
    SetTargetFPS(60);

    GameState state = MENU;

    // Words to type
    // i stole theme from https://quillbot.com/blog/word-finder/long-words/
    // the longest words on English
    vector<string> words = {
        "apple",
        "Antidisestablishmentarianism",
        "Hexakosioihexekontahexaphobia",
        "Floccinaucinihilipilification",
        "Pseudopseudohypoparathyroidism",
        "Eellogofusciouhipoppokunurious",
        "Supercalifragilisticexpialidocious",
        "hippopotomonstrosesquipedaliophobia",
        "Spectrophotofluorometrically",
        "Honorificabilitudinitatibus",
        "Psychoneuroendocrinological",
        "Hydrochlorofluorocarbons",
        "Subcompartmentalization",
        "Counterrevolutionaries",
        "Deinstitutionalization",
        "Electroencephalography",
        "Disproportionableness",
        "Psychoneuroimmunology",
        "Misunderstand",
        "Surreptitious",
        "Hypothetically",

    };
    string currentWord = "";
    string typedWord = "";
    int score = 0;

    srand(time(0));

    // Menu
    int menuOption = 0; // 0: Start, 1: Exit

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (state)
        {
        case MENU:
        {
            const char *titleText = "Moha's Type :1:";
            int titleFont = 40;
            const char *startText = (menuOption == 0) ? "> Start <" : "Start";
            const char *exitText = (menuOption == 1) ? "> Exit <" : "Exit";

            int fontSize = 30;
            int startWidth = MeasureText(startText, fontSize);
            int startX = (GetScreenWidth() - startWidth) / 2;

            int exitWidth = MeasureText(exitText, fontSize);
            int exitX = (GetScreenWidth() - exitWidth) / 2;

            int startY = GetScreenHeight() / 2 - 40;
            int exitY = GetScreenHeight() / 2 + 20;
            int titleWidth = MeasureText(titleText, titleFont);

            int titleX = (GetScreenWidth() - titleWidth) / 2;
            int titleY = GetScreenHeight() / 5;

            // Draw title
            DrawText(titleText, titleX, titleY, titleFont, DARKGRAY);

            DrawText(startText, startX, startY, fontSize, (menuOption == 0 ? BLUE : BLACK));
            DrawText(exitText, exitX, exitY, fontSize, (menuOption == 1 ? BLUE : BLACK));

            if (IsKeyPressed(KEY_DOWN))
            {
                menuOption = (menuOption + 1) % 2;
            }
            if (IsKeyPressed(KEY_UP))
            {
                menuOption = (menuOption + 1) % 2;
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                if (menuOption == 0)
                {
                    state = PLAYING;
                    score = 0;
                    typedWord = "";
                    currentWord = words[rand() % words.size()];
                }
                else
                {
                    CloseWindow();
                    return 0;
                }
            }
        }
        break;

        case PLAYING:
        {
            DrawText("Type the word:", 50, 50, 20, BLACK);
            DrawText(currentWord.c_str(), 50, 80, 40, DARKGRAY);
            DrawText(typedWord.c_str(), 50, 130, 40, BLUE);
            DrawText(TextFormat("Score: %i", score), screenWidth + 600, 50, 30, BLACK);

            int key = GetCharPressed();
            while (key > 0)
            {
                if ((key >= 32) && (key <= 125))
                    typedWord += (char)key;
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && typedWord.length() > 0)
                typedWord.pop_back();

            if (typedWord == currentWord)
            {
                score++;
                typedWord = "";
                currentWord = words[rand() % words.size()];
            }

            if (IsKeyPressed(KEY_ESCAPE))
            {
                state = MENU;
            }
        }
        break;

        default:
            break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
