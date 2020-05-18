package org.Justin.Engine;

import jdk.jshell.execution.Util;
import org.lwjgl.opengl.*;
import org.lwjgl.glfw.*;

import org.lwjgl.Version;
import org.lwjgl.system.MemoryUtil;

import java.nio.FloatBuffer;

import static org.lwjgl.glfw.Callbacks.*;

import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL20.glEnableVertexAttribArray;
import static org.lwjgl.opengl.GL20.glVertexAttribPointer;
import static org.lwjgl.system.MemoryUtil.*;
import static org.lwjgl.opengl.GL11.GL_COLOR_BUFFER_BIT;
import static org.lwjgl.opengl.GL11.GL_DEPTH_BUFFER_BIT;
import static org.lwjgl.opengl.GL11.GL_FLOAT;
import static org.lwjgl.opengl.GL11.GL_TRIANGLES;
import static org.lwjgl.opengl.GL11.glClear;
import static org.lwjgl.opengl.GL11.glDrawArrays;
import static org.lwjgl.opengl.GL11.glViewport;
import static org.lwjgl.opengl.GL15.GL_ARRAY_BUFFER;
import static org.lwjgl.opengl.GL15.GL_STATIC_DRAW;
import static org.lwjgl.opengl.GL15.glBindBuffer;
import static org.lwjgl.opengl.GL15.glBufferData;
import static org.lwjgl.opengl.GL15.glDeleteBuffers;
import static org.lwjgl.opengl.GL15.glGenBuffers;
import static org.lwjgl.opengl.GL20.glDisableVertexAttribArray;
import static org.lwjgl.opengl.GL20.glEnableVertexAttribArray;
import static org.lwjgl.opengl.GL20.glVertexAttribPointer;
import static org.lwjgl.opengl.GL30.glBindVertexArray;
import static org.lwjgl.opengl.GL30.glDeleteVertexArrays;
import static org.lwjgl.opengl.GL30.glGenVertexArrays;

public class Engine implements Runnable{

    Window window;
    GameLogic gameLogic;
    Renderer renderer;

    Timer timer;

    public static final int TARGET_FPS = 30;
    public static final int TARGET_UPS = 30;

    public Engine(String title, int width, int height, boolean VSync, GameLogic gameLogic)throws Exception{
        window = new Window(title, width, height, VSync);
        this.gameLogic = gameLogic;
        timer = new Timer();
    }

    @Override
    public void run(){
        System.out.println("Running Engine");

        try {
            init();
            loop();
        } catch(Exception e){
            e.printStackTrace();
        }
        finally {
            cleanup();
            glfwTerminate();
            glfwSetErrorCallback(null).free();
        }
    }

    public void init() throws Exception{
        window.init();
        timer.init();
        gameLogic.init(window);
    }

    public void loop(){
        float elapsedTime;
        float accum = 0.0f;
        float interval = 1f / TARGET_UPS;

        boolean running = true;
        while(running && !glfwWindowShouldClose(window.getWindow())) {
            elapsedTime = timer.getElapsedTime();
            accum += elapsedTime;

            input();

            while (accum >= interval) {
                update(interval);
                accum -= interval;
            }

            render();

            if ( !window.isVSync()) {
                sync();
            }
        }
    }

    private void sync() {
        float loopSlot = 1f / TARGET_FPS;
        double endTime = timer.getLastLoopTime() + loopSlot;
        while (timer.getTime() < endTime) {
            try {
                Thread.sleep(1);
            } catch (InterruptedException ie) {
            }
        }
    }

    protected void input(){
        gameLogic.input(window);
    }

    protected void update(float interval){
        gameLogic.update(interval);
    }

    protected void render(){
        gameLogic.render(window);
        window.update();
    }

    public void cleanup(){
        gameLogic.cleanup();
    }
}
