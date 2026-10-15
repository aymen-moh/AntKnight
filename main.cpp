#include <raylib.h>
#include <iostream>
#include <string>
#include <vector>
#include <raymath.h>
/////////////////////////////// Textures
Texture2D bg_sp_sheet;
Texture2D play_button;
Texture2D play_button_h;
Texture2D quit_button;
Texture2D quit_button_h;

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
    Texture2D frame = sheet;
    float ft = GetFrameTime();
    float frame_width = (float)sheet.width / frames;
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
    play_button = LoadTexture("Assets/Texture/gui/play_button.png");
    play_button_h = LoadTexture("Assets/Texture/gui/play_button_h.png");
    quit_button = LoadTexture("Assets/Texture/gui/quit_button.png");
    quit_button_h = LoadTexture("Assets/Texture/gui/quit_button_h.png");

    Rectangle play_button_rect = {500, 250, 64, 64};
    Rectangle quit_button_rect = {350, 250, 64, 64};
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
                Texture2D current_quit = CheckCollisionPointRec(mouse_pos, quit_button_rect) ? current_quit = quit_button_h : current_quit = quit_button;                
                Texture2D current_quit = CheckCollisionPointRec(mouse_pos, play_button_rect) ? play_button_h :play_button;                
                DrawTexturePro(bg_sp_sheet, anim(bg_sp_sheet, 2, 1.2), {0, 0, width, height}, {0, 0}, 0, WHITE);
                DrawTexturePro(CheckCollisionPointRec(mouse_pos, play_button_rect) ? play_button_h : play_button, {0, 0, 16, 16}, play_button_rect, {0, 0}, 0, WHITE);
                
                DrawTexturePro(CheckCollisionPointRec(mouse_pos, quit_button_rect) ? quit_button_h : quit_button, anim(current_quit, 2, 1.2), quit_button_rect, {0, 0}, 0, WHITE);
            }
        }
        if(IsCursorOnScreen())DrawCircle(mouse_pos.x, mouse_pos.y, 30, TRANSPARENT_WHITE);
        //////////////////////////
        EndDrawing();
        
    }
    //////////////////////////////End Of Loop////////////////////////////////
    UnloadTexture(quit_button);
    UnloadTexture(quit_button_h);
    UnloadTexture(play_button);
    UnloadTexture(play_button_h);
    UnloadTexture(bg_sp_sheet);
    CloseWindow();
}