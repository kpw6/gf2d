#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"

#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "crops.h"

#include "tileset.h"
#include "tilemap.h"

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite *sprite;
    tileMap* map;
    
    int mx,my;
    float mf = 0;
    Entity* mouse, * other, * crop;
    Vector4D mouseColor = {255,100,255,200};
    
    /*program initializtion*/
    init_logger("gf2d.log");

    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
    tileSet_manager_init(16);
    gf2d_sprite_init(1024);
    entity_system_init(1024);
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/
    //sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png");
    other = enemy_new();
    mouse = player_new();
    //map = tileMap_load("levels/testlevel.json");
    crop = crops_new("config/crops.json", CROP_SQUIRTLE, vector2d(200, 100));
    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        //mf+=0.1;
        //if (mf >= 16.0)mf = 0;
        
        
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            //gf2d_sprite_draw_image(sprite,vector2d(0,0));
            //tileMap_draw(map);
            
            entity_think_all();
            entity_update_all();
            entity_draw_all();
            entity_collision_tests();

        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
        
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
