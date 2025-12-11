#include "raylib.h"
#include<bits/stdc++.h>
using namespace std;


/*
** Authour : Mohamed boukerche 
** Date : 11 December 
** Code : Moha's type game using raylib c++
*/



const int FONT_SIZE_BASE = 30;
const float GAME_DURATION_SECONDS = 60.0f; 
const int LETTER_SPACING_PIXELS = 5; // Try 5 to 3 pixels if too wide 


// i stole those Colors from redit
const Color COLOR_DEFAULT = { 163, 177, 198, 255 }; // Light Grayish Blue
const Color COLOR_CORRECT = { 102, 191, 137, 255 }; // Green
const Color COLOR_INCORRECT = { 255, 102, 102, 255 }; // Red
const Color COLOR_CURSOR    = { 255, 203, 0, 255 };  // Yellow
const Color COLOR_BACKGROUND = { 44, 51, 62, 255 }; // Dark Slate


enum class GameScreen {
    MENU = 0,
    PLAYING,
    GAME_OVER,
    EXITING
};


int screenHeight = GetScreenHeight();
int screenwidth = GetScreenWidth();

class RayTypeGame {
public:
    RayTypeGame(int width, int height, const string& title):
         screenWidth(width), screenHeight(height), currentScreen(GameScreen::MENU) 
    {
        SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
        InitWindow(screenWidth, screenHeight, title.c_str());
        SetTargetFPS(60);
        srand(time(NULL));
        ResetGame();
    }

    ~RayTypeGame() {
        CloseWindow();
    }

    void Run() {
        while (!WindowShouldClose() && currentScreen != GameScreen::EXITING) {
            Update();
            Draw();
        }
    }

private:
   
    int screenWidth;
    int screenHeight;
    GameScreen currentScreen;
     // make chat-gpt genrate 150 quotes 
     // damn that's huge i'll make it in json file or txt           (next time lol)
    const vector<string> quotes = {
    "Believe in progress, even when the steps feel really small.",
    "Every challenge teaches something you will need later in life.",
    "Confidence grows when you choose effort over fear every time.",
    "Small habits eventually build the strongest and longest lasting results.",
    "Success begins when excuses end and real action finally starts.",
    "Keep moving forward because standing still never changed anything important.",
    "Your only real competition is who you were yesterday.",
    "Great things grow from quiet and consistent effort over time.",
    "It is okay to rest, just do not completely stop trying.",
    "Dreams become real when your actions finally match them.",
    "Learn to appreciate progress instead of demanding instant perfection.",
    "One brave decision can change your entire direction in life.",
    "Make today meaningful with one simple intentional action.",
    "The best ideas arrive when your mind stays curious enough.",
    "Patience builds results that rushing could never produce.",
    "Keep going even when motivation has completely disappeared.",
    "You are stronger than the thoughts trying to stop you.",
    "Consistency beats talent when talent stops showing up daily.",
    "It is normal to struggle, but it is not normal to quit.",
    "A small win today builds confidence for tomorrow.",
    "Improvement starts the moment you stop fearing mistakes.",
    "Do not rush life, important things grow naturally with time.",
    "Effort today becomes confidence you will use tomorrow.",
    "You learn faster when failure becomes your main teacher.",
    "Every minute spent learning builds your future self.",
    "Your mindset decides more than your situation ever will.",
    "Growth feels uncomfortable because you are becoming someone new.",
    "Chase progress, not perfection because perfection kills momentum.",
    "You change your life by changing your everyday choices.",
    "When overwhelmed, just take one clear step forward.",
    "Be proud of small victories because they build huge ones.",
    "Nothing improves without patience and repeated effort.",
    "Every master was once a beginner unsure of everything.",
    "Do not compare chapters because everyone moves differently.",
    "You become unstoppable once you trust your own effort.",
    "If you cannot do a lot, then just do something.",
    "One hour of focus beats ten hours of distraction.",
    "Growth happens slowly until it suddenly appears all at once.",
    "Believe in the version of you that keeps trying.",
    "You have survived everything that tried to break you.",
    "The best investment is time spent building yourself.",
    "Fear is loud while courage is quiet but stronger.",
    "A new beginning starts with a single brave choice.",
    "Every day gives another chance to quietly improve.",
    "Discipline is choosing what you want most over now.",
    "Do not wait for motivation; create it through action.",
    "Momentum grows when you show up consistently each day.",
    "Life rewards effort much more than hesitation does.",
    "You grow faster when you start before feeling ready.",
    "Keep learning because curiosity strengthens the mind endlessly.",
    "What you practice today shapes who you become tomorrow.",
    "Your future self depends on the choices you make now.",
    "Quiet effort often creates the biggest and strongest transformations.",
    "Do not underestimate how far tiny habits can take you.",
    "Courage means doing it even while feeling afraid.",
    "Make progress so clear that doubt becomes silent.",
    "Every failure carries information you will use later.",
    "You do not need permission to start improving yourself.",
    "Work patiently because great things take longer than expected.",
    "Every tough moment becomes strength once you overcome it.",
    "Give your goals the effort they truly deserve.",
    "Believe in the process even if results are slow.",
    "A single new habit can redirect your whole future.",
    "Trust yourself because you know more than you think.",
    "Stay patient because the best results grow invisibly first.",
    "You become powerful when you learn to control reactions.",
    "Do not give up; tomorrow might be your turning point.",
    "You are capable of far more than fear allows.",
    "A focused mind can create opportunities everywhere.",
    "Confidence grows every time you keep a promise.",
    "Work quietly until your progress speaks loudly for you.",
    "The hardest part is usually starting the very first time.",
    "Growth begins the moment comfort finally ends.",
    "Stay curious because learning keeps your mind alive.",
    "Success belongs to those who keep trying longer.",
    "Choose discipline even when motivation completely disappears.",
    "Every skill improves with patience and dedicated practice.",
    "Your habits shape your future without asking permission.",
    "Believe in possibilities more than your limitations.",
    "Effort you invest today becomes confidence tomorrow.",
    "Action creates clarity when thinking becomes overwhelming.",
    "You can learn anything with enough time and consistency.",
    "Keep pushing because breakthroughs hide behind difficulty.",
    "Do not stop now; progress compounds with every step.",
    "Better days grow from choices you make today.",
    "Consistency turns average effort into exceptional results.",
    "Your journey matters even if nobody notices yet.",
    "You control how the next chapter will begin.",
    "Strong results grow from months of quiet discipline.",
    "Focus only on what you can control right now.",
    "Choose progress even when comfort feels tempting today.",
    "Every day offers a chance to rewrite your story.",
    "Learn from yesterday but never live there.",
    "A little effort every day becomes unstoppable momentum.",
    "Trust the process because good things take time.",
    "A calm mind makes better decisions every time.",
    "You are allowed to start again anytime you choose.",
    "Work patiently because rushing ruins the beauty of growth.",
    "Do not quit; your breakthrough may be very close.",
    "Keep improving because even small steps matter.",
    "Every attempt brings you closer to mastery eventually.",
    "Progress becomes addicting once you notice improvement.",
    "Strength grows from battles you once feared losing.",
    "The future is built by actions instead of wishes.",
    "Practice creates progress but never perfection.",
    "You can restart whenever you feel the need.",
    "When you feel stuck, simply reset and continue.",
    "The toughest days teach the strongest lessons.",
    "Hard work becomes easier once it becomes routine.",
    "What you repeat daily determines everything.",
    "Every small step forward still counts as progress.",
    "Be patient since change lasts longer than motivation.",
    "Do not fear mistakes; fear ending your effort.",
    "Big results grow from tiny repeated decisions.",
    "The path becomes clearer after each attempt.",
    "Focus today so your tomorrow becomes easier.",
    "Your growth is worth every uncomfortable moment.",
    "You become unstoppable by showing up consistently.",
    "Trust your progress even if it feels slow.",
    "Nothing great grows from avoiding difficulty.",
    "Push gently but consistently every single day.",
    "Hard beginnings create powerful transformations later.",
    "Your effort today shapes tomorrow’s opportunities.",
    "One step forward replaces a hundred worries.",
    "Improvement starts with honesty about your habits.",
    "Learn slowly because deep knowledge takes time.",
    "Every tiny win builds long-term confidence.",
    "Prioritize effort over outcome and growth follows.",
    "Your best days come from disciplined mornings.",
    "Keep learning because knowledge compounds faster than money.",
    "You grow stronger with every small effort given.",
    "Stay patient because great stories require time.",
    "A determined mind solves problems creatively.",
    "Your journey matters even when progress is invisible.",
    "Meaningful change starts with consistent tiny actions.",
    "Stay disciplined because effort pays off unexpectedly.",
    "Keep going because you have not reached your peak.",
    "The right step today creates tomorrow’s opportunities.",
    "Be consistent because motivation fades but habits stay.",
    "You grow most when life becomes challenging.",
    "Do not rush; steady improvement builds stronger foundations.",
    "Try again because persistence beats temporary failure.",
    "Your future depends on what you practice now.",
    "Every day brings another chance to improve something.",
    "You create momentum the moment you begin.",
    "Progress arrives quickly once excuses disappear.",
    "One decision can completely redirect your life.",
    "Curiosity fuels lifelong learning and improvement.",
    "Success grows slowly through honest and consistent work.",
    "Believe in progress because small steps change everything."
    };
    string targetText;
    string typedText;

    
    int cursorIndex = 0;
    int correctChars = 0;
    int totalCharsTyped = 0;
    float timeRemaining = GAME_DURATION_SECONDS;
    float wpm = 0.0f;
    float accuracy = 0.0f;

    // --- Private Methods ---

    void ResetGame() {
        int quoteIndex = GetRandomValue(0, quotes.size() - 1);
        targetText = quotes[quoteIndex];

        typedText.clear();
        cursorIndex = 0;
        correctChars = 0;
        totalCharsTyped = 0;
        timeRemaining = GAME_DURATION_SECONDS;
        wpm = 0.0f;
        accuracy = 0.0f;
    }

    void Update() {

        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();

        switch (currentScreen) {
            case GameScreen::MENU: UpdateMenu(); break;
            case GameScreen::PLAYING: UpdatePlaying(); break;
            case GameScreen::GAME_OVER: UpdateGameOver(); break;
            default: break;
        }
    }

    void UpdateMenu() {
        if (IsKeyPressed(KEY_S)) {
            ResetGame();
            currentScreen = GameScreen::PLAYING;
        } else if (IsKeyPressed(KEY_E)) {
            currentScreen = GameScreen::EXITING;
        }
    }

    void UpdatePlaying() {
        if (timeRemaining <= 0.0f || cursorIndex >= (int)targetText.length()) {
            currentScreen = GameScreen::GAME_OVER;
            return;
        }

        timeRemaining -= GetFrameTime();
        // 60 second 
        // 60 - 59 -58 
        // todo : make it support 10s and 20s and 30s 

        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 126) && (cursorIndex < (int)targetText.length())) {
                typedText += (char)key;
                cursorIndex++;
                totalCharsTyped++;
            }
            key = GetCharPressed();
        }


        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (cursorIndex > 0) {
                cursorIndex--;
                typedText.pop_back(); 
            }
        }


        correctChars = 0;
        for (int i = 0; i < cursorIndex; i++) {
            if (typedText[i] == targetText[i]) {
                correctChars++;
            }
        }

        float timeElapsed = GAME_DURATION_SECONDS - timeRemaining;
        if (timeElapsed > 0.0f) {
            wpm = (float)(correctChars / 5.0f) / (timeElapsed / 60.0f);
        }

        if (totalCharsTyped > 0) {
            accuracy = (float)correctChars / totalCharsTyped * 100.0f;
        }
    }

    void UpdateGameOver() {
    if (IsKeyPressed(KEY_R)) {
        ResetGame();
        currentScreen = GameScreen::PLAYING;
    } 
    else if (IsKeyPressed(KEY_M)) {
        currentScreen = GameScreen::MENU;
    }
}

    void Draw() {
        BeginDrawing();
            ClearBackground(COLOR_BACKGROUND);

            switch (currentScreen) {
                case GameScreen::MENU: DrawMenu(); break;
                case GameScreen::PLAYING: DrawPlaying(); break;
                case GameScreen::GAME_OVER: DrawGameOver(); break;
                default: break;
            }

            DrawFPS(10, 10);
        EndDrawing();
    }

    void DrawMenu() {
        int titleSize = screenHeight / 10;
        int menuSize = screenHeight / 25;

        DrawText(" --- Moha's Type ---", screenWidth / 2 - MeasureText("--- Moha's Type ---", titleSize) / 2, screenHeight / 4, titleSize, COLOR_DEFAULT);
        
        DrawText("[S] START TEST", screenWidth / 2 - MeasureText("[S] START TEST", menuSize) / 2, screenHeight / 2, menuSize, COLOR_CORRECT);
        DrawText("[E] EXIT GAME", screenWidth / 2 - MeasureText("[E] EXIT GAME", menuSize) / 2, screenHeight / 2 + menuSize + 20, menuSize, COLOR_INCORRECT);
    }

    void DrawPlaying() {
        int scoreTextSize = screenHeight / 15;
        
        // WPM
        DrawText(TextFormat("WPM: %.0f", wpm), 50, 50, scoreTextSize, COLOR_CORRECT);

        //cout<<"TIME Remaining : "<<timeRemaining<<endl;
        
        string timeStr = "Time: " + to_string(timeRemaining > 0 ? (int)timeRemaining : 0) + "s";
        DrawText(timeStr.c_str(), screenWidth - MeasureText(timeStr.c_str(), scoreTextSize) - 50, 50, scoreTextSize, COLOR_INCORRECT);
        
        DrawTextLayout();
    }

    void DrawTextLayout() {
    int textSize = FONT_SIZE_BASE + (screenHeight / 100); 
    int paddingX = screenWidth / 10;
    int paddingY = screenHeight / 3;
    int x = paddingX;
    int y = paddingY;
    int targetLength = targetText.length();
    
    for (int i = 0; i < targetLength; i++) {
        Color charColor = COLOR_DEFAULT;
        if (i < cursorIndex) {
            if (typedText[i] == targetText[i]) {
                charColor = COLOR_CORRECT;
            } else {
                charColor = COLOR_INCORRECT;
            }
        }
        
        char charBuffer[2] = { targetText[i], '\0' };
        int charWidth = MeasureText(charBuffer, textSize);
        if (x + charWidth + LETTER_SPACING_PIXELS > screenWidth - paddingX) { // Check space needed
            x = paddingX;
            y += textSize + 10;
        }

        DrawText(charBuffer, x, y, textSize, charColor);

        if (i == cursorIndex) {
             DrawRectangle(x, y + textSize + 2, charWidth + LETTER_SPACING_PIXELS, 5, COLOR_CURSOR);
        }
        x += charWidth + LETTER_SPACING_PIXELS; 
    }
    
    if (cursorIndex == targetLength) {
        DrawRectangle(x, y + textSize + 2, 10, 5, COLOR_CURSOR);
    }
}

    void DrawGameOver() {
        int titleSize = screenHeight / 10;
        int scoreSize = screenHeight / 18;
        int menuSize = screenHeight / 25;

        DrawText("TEST COMPLETE!", screenWidth / 2 - MeasureText("TEST COMPLETE!", titleSize) / 2, screenHeight / 4, titleSize, COLOR_CORRECT);

        
        DrawText(TextFormat("WPM: %.0f", wpm), screenWidth / 2 - MeasureText(TextFormat("WPM: %.0f", wpm), scoreSize) / 2, screenHeight / 2 - scoreSize, scoreSize, RAYWHITE);
        DrawText(TextFormat("ACCURACY: %.1f%%", accuracy), screenWidth / 2 - MeasureText(TextFormat("ACCURACY: %.1f%%", accuracy), scoreSize) / 2, screenHeight / 2, scoreSize, RAYWHITE);

        
        DrawText("[R] RETRY", screenWidth / 2 - MeasureText("[R] RETRY", menuSize) / 2, screenHeight * 3 / 4, menuSize, COLOR_CORRECT);
        //DrawText("[M] MENU", screenWidth / 2 - MeasureText("[M] MENU", menuSize) / 2, screenHeight * 3 / 4 + menuSize + 20, menuSize, COLOR_DEFAULT);
    }
};


int main() {
    int height =  GetScreenHeight();
    int width  = GetScreenWidth();
    RayTypeGame game(height, width, "Moha's TYPE");
    game.Run();
    return 0;
}
