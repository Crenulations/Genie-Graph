
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <utility>
#include <cstdlib> 
#include <ctime>
#include <time.h> 
#include <thread>

#include "ColonyManager.h"

#include "graphics/NodeViewer.h"


int main(void){

    srand(time(0)); // Seeding random function
    RuntimeVars settings;


    NodeViewer viewer = NodeViewer(&settings);

    ColonyManager colony_manager = ColonyManager(5000, 5000);


    viewer.SetColonyManager(&colony_manager);


    unsigned int counter = 0;
    time_t last_time = time(0);
    unsigned int fps_counter = 0;
    while (!settings.window_close) {
        
        fps_counter++;

        if (last_time != time(0)) {
            last_time = time(0);
            settings.fps = fps_counter;
            fps_counter = 0;
        }

        viewer.Draw();

        if (settings.active) {

            for (int i = 0; i < 6; i++) {
                if (counter % settings.speed == 0)
                    colony_manager.colonies[i]->Update();

                colony_manager.colonies[i]->UpdateEdges();
                colony_manager.colonies[i]->UpdateNodes();

            }
        }
        if (settings.restart) {
            settings.restart = false;
            colony_manager.colonies[settings.focused_colony]->InitializeColony();
        }
        counter++;
    }
    glfwTerminate();
    
}

 /*  TODO
 
 ==#&* GUI *&#==
 - Add glDebugMessageCallback for error handling
 https://stackoverflow.com/questions/44687061/how-to-draw-points-efficiently/44687171
 */