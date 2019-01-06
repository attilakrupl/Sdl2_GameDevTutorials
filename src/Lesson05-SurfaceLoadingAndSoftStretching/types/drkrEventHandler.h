#pragma once

union SDL_Event;
class drkrWindow;

class drkrEventHandler
{
public:
    drkrEventHandler(drkrWindow* aWindow);
    ~drkrEventHandler() = default;

    void runEventLoop();

private:
    drkrWindow* m_pWindow;

    void handleEvent( const SDL_Event* aEvent, bool& aShouldQuit );
};

