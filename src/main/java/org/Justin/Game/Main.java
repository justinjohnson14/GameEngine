package org.Justin.Game;

import org.Justin.Engine.Engine;
import org.Justin.Engine.GameLogic;
import org.lwjgl.opengl.*;
import org.lwjgl.glfw.*;

import org.lwjgl.Version;
import static org.lwjgl.glfw.Callbacks.*;

import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.system.MemoryUtil.*;

public class Main {

    //Main should call a new instance of Engine which will run the whole time
    public static void main(String[] args) {
        try {
            boolean vSync = true;
            GameLogic gameLogic = new Game();
            Engine engine = new Engine("Game", 1280, 720, vSync, gameLogic);
            engine.run();
        } catch (Exception e){
            e.printStackTrace();
            System.exit(-1);
        }

    }
}
