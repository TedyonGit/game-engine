#pragma once
#include <iostream>
#include <Object.h>
#include <unordered_map>
#include <Interface.h>

class RenderClass
{
    public:
        void Update();
        void Init();
        void Add(std::string Key, ObjectClass* value);
        std::unordered_map<std::string, ObjectClass*> mapObjects;
};

extern RenderClass Render;