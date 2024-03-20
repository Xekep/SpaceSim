#pragma once
class Observable;

class Observer {
public:
    virtual void HandleEvent(const Observable& observable) = 0;
};