#include <raylib.h>
#include <iostream>
#include <string>
#include <vector>
#include <raymath.h>
#include "reasings.h"

/////////////////////////////// Textures
Texture2D bg_sp_sheet;
Texture2D play_button;
Texture2D play_button_h;
Texture2D quit_button;
Texture2D quit_button_h;
Texture2D menu_button;
Texture2D menu_button_h;
Texture2D lvlbg_texture;
Texture2D logo;
/////////////////////////////// COLORS
const Color TRANSPARENT_WHITE = {255, 255, 255, 25};
/////////////////////////////// Booleans
bool quit = false;



////////////////////////////////
struct move {
    float start, end, time;
    float elapsed = 0;
    bool playing = true;
    
    float update(){
        if(playing){
            elapsed += GetFrameTime();
            elapsed = Clamp(elapsed, 0, time);
            
        }
        float t = elapsed / time;
        return EaseCubicInOut(elapsed, start, end - start, time);
    }
};
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
Rectangle next_frame(Texture2D sheet, int frames){
    return {(float)sheet.width / frames, 0, sheet.width / frames, sheet.height};
}


bool hovered(Vector2 mouse, Rectangle rect){
    if (CheckCollisionPointRec(mouse, rect)) return true;
    else return false;
}

int main(int argc, char* argv[]){
    ////////////////////////////VARIABLES////////////////////////////////////
    
    gameState = main_menu;
    int width = 960; int height = 540; std::string window_name = "AntKnight";
    SetExitKey(KEY_F2);
    InitWindow(width, height, window_name.c_str());

    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    bg_sp_sheet = LoadTexture("Assets/Texture/gui/bg_texture.png");
    lvlbg_texture = LoadTexture("Assets/Texture/gui/lvlbg_texture.png");
    play_button = LoadTexture("Assets/Texture/gui/play_button.png");
    play_button_h = LoadTexture("Assets/Texture/gui/play_button_h.png");
    quit_button = LoadTexture("Assets/Texture/gui/quit_button.png");
    quit_button_h = LoadTexture("Assets/Texture/gui/quit_button_h.png");
    menu_button = LoadTexture("Assets/Texture/gui/menu_button.png");
    menu_button_h = LoadTexture("Assets/Texture/gui/menu_button_h.png");
    logo = LoadTexture("Assets/Texture/gui/logo.png");

    Rectangle play_button_rect = {500, 250, 64, 64};
    Rectangle quit_button_rect = {350, 250, 64, 64};
    Rectangle menu_button_rect = {425, 250, 64, 64};
    Rectangle logor = {100, 60, 760, 128};

    move play_button_move = {1060, 500, 1.5};
    move quit_button_move = {-100, 350, 1.5};
    move menu_button_move = {600, 250, 1.5};
    move mm_logo = {-100, 50, 1};
    //////////////////////////////MAIN LOOP//////////////////////////////////
    while(!WindowShouldClose() and !quit){
        ////////////////////////// Repeating variables
        Vector2 mouse_pos = GetMousePosition();
        float ft = GetFrameTime();
        bool left_click = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        //////////////////////////
        BeginDrawing();
        //////////////////////////
        switch(gameState){
            
            case main_menu: {
                ClearBackground(BLACK);
                Texture2D current_quit = hovered(mouse_pos, quit_button_rect) ? quit_button_h : quit_button;
                Texture2D current_play = hovered(mouse_pos, play_button_rect) ? play_button_h : play_button;
                Texture2D current_menu = hovered(mouse_pos, menu_button_rect) ? menu_button_h : menu_button;
                
                quit_button_rect.x = quit_button_move.update();
                play_button_rect.x = play_button_move.update();
                menu_button_rect.y = menu_button_move.update();
                logor.y = mm_logo.update();

                DrawTexturePro(bg_sp_sheet, anim(bg_sp_sheet, 2, 2.4), {0, 0, width, height}, {0, 0}, 0, WHITE);
                DrawTexturePro(current_play, anim(current_play, 2, 2.4), play_button_rect, {0, 0}, 0, WHITE);
                DrawTexturePro(current_menu, anim(current_menu, 2, 2.4), menu_button_rect, {0, 0}, 0, WHITE);
                DrawTexturePro(hovered(mouse_pos, quit_button_rect) ? quit_button_h : quit_button, anim(current_quit, 2, 2.4), quit_button_rect, {0, 0}, 0, WHITE);
                if(hovered(mouse_pos, quit_button_rect) and left_click) quit = true;
                DrawTexturePro(logo, {0, 0, 256, 64}, logor, {0, 0}, 0, WHITE);
                break;
            }
        };
        if(IsCursorOnScreen())DrawCircle(mouse_pos.x, mouse_pos.y, 30, TRANSPARENT_WHITE);
        //////////////////////////
        std::string mx = std::to_string((int)GetMousePosition().x);
        std::string my = std::to_string((int)GetMousePosition().y);
        DrawText(mx.c_str(), 50, 50, 28, BLACK);
        DrawText(my.c_str(), 120, 50, 28, BLACK);
        EndDrawing();
        
    }
    //////////////////////////////End Of Loop////////////////////////////////
    UnloadTexture(quit_button);
    UnloadTexture(quit_button_h);
    UnloadTexture(play_button);
    UnloadTexture(play_button_h);
    UnloadTexture(bg_sp_sheet);
    UnloadTexture(play_button);
    UnloadTexture(play_button_h);
    UnloadTexture(menu_button);
    UnloadTexture(menu_button_h);
    UnloadTexture(logo);
    CloseWindow();
}