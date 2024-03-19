#pragma once
class Observable;

class Observer {
public:
    virtual void HandleEvent(Observable* observable) = 0;
};