package org.Justin.Engine;

public interface GameLogic {
    void init(Window window)throws Exception;
    void input(Window window);
    void update(float interval);
    void render(Window window);
    void cleanup();
}
