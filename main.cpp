#include <raylib.h>
#include <iostream>
#include <string>
#include <vector>
#include <raymath.h>
/////////////////////////////// Textures
Texture2D bg_sp_sheet;
Texture2D play_button_sheet;
Texture2D quit_button_sheet;
/////////////////////////////// COLORS
const Color TRANSPARENT_WHITE = {1, 1, 1, 25};
///////////////////////////////
Rectangle next_frame(Texture2D sheet, int frames){
    return {(float)sheet.width / frames, 0, sheet.width / frames, sheet.height};
}
///////////////////////////////
enum Gamestate{
    main_menu,
};
Gamestate gameState;
Rectangle anim(Texture2D sheet, int frames, float anim_speed){
    static int currentframe = 0;
    static float elapsed = 0;
    static Texture2D frame = sheet;
    float ft = GetFrameTime();
    static float frame_width = (float)sheet.width / frames;
    elapsed += ft;
    if(elapsed >= anim_speed) {
        currentframe++;
        if (currentframe > frames - 1) currentframe = 0;
        
        elapsed = 0;
    }
    return {currentframe * frame_width  , 0.0f, frame_width, sheet.height};
}

int main(int argc, char* argv[]){
    ////////////////////////////VARIABLES////////////////////////////////////
    
    gameState = main_menu;
    int width = 960; int height = 540; std::string window_name = "AntKnight";
    SetExitKey(KEY_F2);
    InitWindow(width, height, window_name.c_str());

    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    bg_sp_sheet = LoadTexture("Assets/Texture/gui/bg_texture.png");
    play_button_sheet = LoadTexture("Assets/Texture/gui/resume_button.png");
    quit_button_sheet = LoadTexture("Assets/Texture/gui/quit_button.png");

    Rectangle play_button_rect = {400, 400, 64, 64};
    Rectangle quit_button_rect = {450, 250, 64, 64};
    //////////////////////////////MAIN LOOP//////////////////////////////////
    while(!WindowShouldClose()){
        ////////////////////////// Repeating variables
        Vector2 mouse_pos = GetMousePosition();
        float ft = GetFrameTime();
        //////////////////////////
        BeginDrawing();
        //////////////////////////
        switch(gameState){
            case main_menu: {
                ClearBackground(BLACK);
                DrawTexturePro(bg_sp_sheet, anim(bg_sp_sheet, 2, 0.6), {0, 0, width, height}, {0, 0}, 0, WHITE);
                DrawTexturePro(play_button_sheet, CheckCollisionPointRec(mouse_pos, play_button_rect) ? next_frame(play_button_sheet, 2) : (Rectangle){0, 0, 32, 32}, play_button_rect, {0, 0}, 0, WHITE);
                DrawTexturePro(quit_button_sheet, CheckCollisionPointRec(mouse_pos, quit_button_rect) ? next_frame(quit_button_sheet, 2) : (Rectangle){0, 0, 32, 32}, quit_button_rect, {0, 0}, 0, WHITE);
            }
        }
        if(IsCursorOnScreen())DrawCircle(mouse_pos.x, mouse_pos.y, 30, TRANSPARENT_WHITE);
        //////////////////////////
        EndDrawing();
        
    }
    //////////////////////////////End Of Loop////////////////////////////////
    UnloadTexture(quit_button_sheet);
    UnloadTexture(play_button_sheet);
    UnloadTexture(bg_sp_sheet);
    CloseWindow();
}