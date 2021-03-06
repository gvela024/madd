#include "madd.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gameobject.h"
#include "renderer.h"
#include "camera.h"
#include "eventhandler.h"
Madd::Madd(int width, int height, const char *title):mainCamera(NULL),
                                                    close(false),
                                                     width(width),
                                                     height(height),
                                                     timeScale(1.0f),
                                                     lastFrame(Clock::now()){
    render = new Renderer(this, width, height, title);
    event = new EventHandler(this);
    std::vector<unsigned int> keys = {KEY_ESCAPE,KEY_SPACE};
    event->RegisterMultipleKeyCB(BIND(Madd::ProcessInput),keys);
}

Madd::~Madd() { 
    for(GameObject* obj : objs){
        delete obj;
    }
    delete render;
    delete event;
}

void Madd::AddObject(GameObject* obj){
    objs.push_back(obj);
}

void Madd::Tick(){
    event->Update();
    render->Start();
    for(GameObject* obj : objs){
        obj->Update();
        obj->Render();
    }
    render->Finish();
    UpdateDeltaTime();
}

void Madd::ReloadShader() {
    for(GameObject* obj : objs)
        if(!obj->ReloadShaders())
            return;
}
#include <iostream>
void Madd::ProcessInput(int key, int action){
    if (key == KEY_ESCAPE)
        Close();
    if (key == KEY_SPACE && action == KEY_PRESS)
        ReloadShader();
}

void Madd::UpdateDeltaTime(){
    dTime = Clock::now() - lastFrame;
    lastFrame = Clock::now();
}

Camera* Madd::GetMainCamera(){return mainCamera;}
void Madd::SetMainCamera(Camera* cameraObj){mainCamera=cameraObj;}
EventHandler* Madd::GetEventHandler(){return event;}
int Madd::GetWidth(){return render->GetWidth();}
int Madd::GetHeight(){return render->GetHeight();}
GLFWwindow* Madd::GetWindow(){return render->GetWindow();}
float Madd::GetTime(){return glfwGetTime();}
float Madd::GetDeltaTime(){return dTime.count() * timeScale;}