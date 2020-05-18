package org.Justin.Engine;

import org.lwjgl.opengl.*;
import org.lwjgl.glfw.*;

import org.lwjgl.Version;
import static org.lwjgl.glfw.Callbacks.*;

import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.system.MemoryUtil.*;

public class Window {
    private long window;
    private String name;
    private int width, height;
    private boolean setResized, VSync;

    Window(String title, int width, int height, boolean Vsync){
        this.width = width;
        this.height = height;
        this.name = title;
        this.setResized = false;
        this.VSync = Vsync;
    }

    public void init(){
        GLFWErrorCallback.createPrint(System.err).set();

        // Initialize GLFW. Most GLFW functions will not work before doing this.
        if (!glfwInit()) {
            throw new IllegalStateException("Unable to initialize GLFW");
        }

        // Configure our window
        glfwDefaultWindowHints(); // optional, the current window hints are already the default
        glfwWindowHint(GLFW_VISIBLE, GL_FALSE); // the window will stay hidden after creation
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); // the window will be resizable
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        // Create the window
        window = glfwCreateWindow(width, height, name, NULL, NULL);
        if (window == NULL) {
            throw new RuntimeException("Failed to create the GLFW window");
        }

        glfwSetFramebufferSizeCallback(window, (window, width, height) ->{
            this.width = width;
            this.height = height;
            this.setResized = true;
        });

        // Setup a key callback. It will be called every time a key is pressed, repeated or released.
        glfwSetKeyCallback(window, (window, key, scancode, action, mods) -> {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
                glfwSetWindowShouldClose(window, true); // We will detect this in the rendering loop
            }
        });

        // Get the resolution of the primary monitor
        GLFWVidMode vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        // Center our window
        glfwSetWindowPos(
                window,
                (vidmode.width() - width) / 2,
                (vidmode.height() - height) / 2
        );

        // Make the OpenGL context current
        glfwMakeContextCurrent(window);
        // Enable v-sync
        if (VSync) {
            glfwSwapInterval(1);
        }

        // Make the window visible
        glfwShowWindow(window);
    }

    public boolean isResized(){
        return setResized;
    }

    public boolean isVSync(){
        return VSync;
    }

    public void setResized(boolean bool){
        setResized = bool;
    }

    public void setClearColor(float r, float g, float b, float a){
        glClearColor(r, g, b, a);
    }

    public void update(){
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    public void SetWidth(int width){
        this.width = width;
    }

    public void SetHeight(int height){
        this.height = height;
    }

    public int GetWidth(){
        return width;
    }

    public int GetHeight(){
        return height;
    }

    public boolean isKeyPressed(int keycode){
        return glfwGetKey(window, keycode) == GLFW_PRESS;
    }

    public void setName(String name){
        this.name = name;
    }

    public void setWidth(int Width){
        this.width = width;
    }

    public void setHeight(int Height){
        this.height = height;
    }

    public long getWindow(){
        return window;
    }

    public String getName(){
        return name;
    }

    public int getWidth(){
        return width;
    }

    public int getHeight(){
        return height;
    }

    public void cleanup(){
        glfwFreeCallbacks(window);
        glfwDestroyWindow(window);
    }
}
