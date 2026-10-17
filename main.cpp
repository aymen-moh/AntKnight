#include <raylib.h>
#include <iostream>
#include <string>
#include <vector>
#include <raymath.h>
#include "reasings.h"

/////////////////////////////// Textures
Texture2D bg_sp_sheet;
Texture2D play_button;
Texture2D bg_lvl;
Texture2D play_button_h;
Texture2D quit_button;
Texture2D quit_button_h;
Texture2D menu_button;
Texture2D menu_button_h;
Texture2D lvlbg_texture;
Texture2D logo;

Texture2D player_idle;
Texture2D player_running;
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

struct anima{
    int frames;
    float speed;
    float elapsed = 0;
    float current_anim;

    Rectangle anim(Texture2D sheet){
    
    Texture2D frame = sheet;
    float ft = GetFrameTime();
    float frame_width = (float)sheet.width / frames;
    elapsed += ft;
    if(elapsed >= speed) {
        current_anim++;
        if (current_anim > frames - 1) current_anim = 0;
        
        elapsed = 0;
    }
    return {current_anim * frame_width  , 0.0f, frame_width, sheet.height};
}
    
};

struct Player{
    Rectangle player;
    float speed = 180;
    float y_vel; 
};
Player player;
///////////////////////////////
enum PlayerState{
    idle,
    running
};
PlayerState player_state;
enum Gamestate{
    main_menu,
    game
};
Gamestate gameState;

Rectangle next_frame(Texture2D sheet, int frames){
    return {(float)sheet.width / frames, 0, sheet.width / frames, sheet.height};
}


bool hovered(Vector2 mouse, Rectangle rect){
    if (CheckCollisionPointRec(mouse, rect)) return true;
    else return false;
}

void move_player(){
    static anima player_idle_anima = {2, 0.5};
    static anima player_running_anima = {3, 0.33};
    float ft = GetFrameTime();
    if(IsKeyDown(KEY_D)) {player.player.x += player.speed * ft; player_state = running;}
    if(IsKeyDown(KEY_A)) {player.player.x -= player.speed * ft; player_state = running;}
    if(IsKeyUp(KEY_A) and IsKeyUp(KEY_D) or IsKeyDown(KEY_A) and IsKeyDown(KEY_D)) player_state = idle;
    switch(player_state){
        case idle: {
            DrawTexturePro(player_idle, player_idle_anima.anim(player_idle), player.player, {0, 0}, 0, WHITE);
            break;
        }
        case running: {
            DrawTexturePro(player_running, player_running_anima.anim(player_running), player.player, {0, 0}, 0, WHITE);
        }
    }
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
    bg_lvl = LoadTexture("Assets/Texture/textures/lvl_bg.png");

    player_idle = LoadTexture("Assets/Texture/entities/player/player_idle.png");
    player_running = LoadTexture("Assets/Texture/entities/player/player_running.png");

    Rectangle play_button_rect = {500, 250, 64, 64};
    Rectangle quit_button_rect = {350, 250, 64, 64};
    Rectangle menu_button_rect = {425, 250, 64, 64};
    Rectangle logor = {100, 60, 760, 150};

    player.player = {width / 2, height / 2, 64, 64};

    move play_button_move = {1060, 500, 1.5};
    move quit_button_move = {-100, 350, 1.5};
    move menu_button_move = {600, 250, 1.5};
    move mm_logo = {-100, 50, 1};

    anima x2f_1_1 = {2, 0.5};
    anima x2f_1_2 = {2, 0.5};
    anima x2f_1_3 = {2, 0.5};
    anima x2f_1_4 = {2, 0.5};
    
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
                
                DrawTexturePro(bg_sp_sheet, x2f_1_1.anim(bg_sp_sheet), {0, 0, width, height}, {0, 0}, 0, WHITE);
                DrawTexturePro(current_play, x2f_1_2.anim(current_play), play_button_rect, {0, 0}, 0, WHITE);
                if(hovered(mouse_pos, play_button_rect) and left_click) gameState = game;
                DrawTexturePro(current_menu, x2f_1_3.anim(current_menu), menu_button_rect, {0, 0}, 0, WHITE);
                DrawTexturePro(hovered(mouse_pos, quit_button_rect) ? quit_button_h : quit_button, x2f_1_4.anim(current_quit), quit_button_rect, {0, 0}, 0, WHITE);
                if(hovered(mouse_pos, quit_button_rect) and left_click) quit = true;
                DrawTexturePro(logo, {0, 0, 256, 64}, logor, {0, 0}, 0, WHITE);
                break;
            }
            case game: {
                DrawTexturePro(bg_lvl, {0, 0, 160, 90}, {0, 0, 960, 540}, {0, 0}, 0, WHITE);
                move_player();
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
    UnloadTexture(logo);        CloseWindow();
}