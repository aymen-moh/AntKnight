#include <raylib.h>
#include <iostream>
#include <string>
#include <vector>
#include <raymath.h>

/////////////////////////////// COLORS
const Color TRANSPARENT_LIGHT_GRAY = {50, 50, 50, 200};
///////////////////////////////
Texture2D anim(Texture2D sheet, int frames, float anim_speed){
    static int currentframe = 0;
    static float elapsed = 0;
    float ft = GetFrameTime();
    elapsed += ft;
    if(elapsed >= anim_speed) {
        currentframe++;
        elapsed = 0;
        return 
    }
}

int main(int argc, char* argv[]){
    ////////////////////////////VARIABLES////////////////////////////////////
    int width = 960; int height = 540; std::string window_name = "AntKnight";
    SetExitKey(KEY_F2);
    InitWindow(width, height, window_name.c_str());

    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    Texture2D bg_sp_sheet = LoadTexture("Assets/Texture/gui/bg_texture.png");
    //////////////////////////////MAIN LOOP//////////////////////////////////
    while(!WindowShouldClose()){
        ////////////////////////// Repeating variables
        Vector2 mouse_pos = GetMousePosition();
        float ft = GetFrameTime();
        //////////////////////////
        BeginDrawing();
        //////////////////////////
        ClearBackground(BLACK);
        
        if(IsCursorOnScreen)DrawCircle(mouse_pos.x, mouse_pos.y, 30, TRANSPARENT_LIGHT_GRAY);
        //////////////////////////
        EndDrawing();
    }
    //////////////////////////////End Of Loop////////////////////////////////
    CloseWindow();
}