#pragma once
#include "GameObject.hpp"

enum class DoorType
{
    playerOneDoor,
    playerTwoDoor
};

class Door : public GameObject
{
public:
    Door(float x, float y, float width, float height, DoorType type);

    DoorType getType();
    void setOpen(bool state);

private:
    DoorType type;
    bool opened = false;
};