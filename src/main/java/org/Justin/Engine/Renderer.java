package org.Justin.Engine;

import org.joml.Matrix3f;
import org.joml.Matrix4f;
import org.lwjgl.opengl.GL;
import org.lwjgl.system.CallbackI;
import org.lwjgl.system.MemoryUtil;

import java.nio.FloatBuffer;

import static org.lwjgl.opengl.GL11.GL_FLOAT;
import static org.lwjgl.opengl.GL11.glClearColor;
import static org.lwjgl.opengl.GL15.*;
import static org.lwjgl.opengl.GL15.GL_ARRAY_BUFFER;
import static org.lwjgl.opengl.GL20.glEnableVertexAttribArray;
import static org.lwjgl.opengl.GL20.glVertexAttribPointer;
import static org.lwjgl.opengl.GL30.glBindVertexArray;
import static org.lwjgl.opengl.GL30.glGenVertexArrays;
import static org.lwjgl.system.MemoryUtil.memFree;

public class Renderer {

    Shader shader;

    Mesh mesh;
    Mesh squareMesh;

    Window window;

    static final float FOV = (float) Math.toRadians(60.0f);
    static final float ZNEAR = 0.01f;
    static final float ZFAR = 1000.0f;
    Matrix4f projectionMatrix;
    Transformation transformation;

    GameObject[] gameObjects;

    public Renderer(){
        transformation = new Transformation();
    }

    public void init(Window window) throws Exception{
        //check for events
        //update game state
        //draw the game

        //This line is criticall opengl detects the current context creates
        //the capabilites instance and makes the opengl bindings available for use
        GL.createCapabilities();

        //shader = new Shader();
        //shader.CreateVertexShader(Utils.ReadFile("/shaders/vertex.vs"));
        //shader.CreateFragmentShader(Utils.ReadFile("/shaders/fragment.fs"));
        shader = new Shader("/shaders/basic.glsl");
        shader.link();
        shader.createUniform("u_ProjectionMatrix");
        shader.createUniform("u_WorldMatrix");

        this.window = window;
    }

    public void render(Window window, GameObject[] gameObjects){
        clear();

        if(window.isResized()){
            glViewport(0,0,window.GetWidth(), window.GetHeight());
            window.setResized(false);
        }

        //Bind what i want to render
        //TODO: change this to be able to call mesh.bind();

        shader.bind();

        Matrix4f projection = transformation.getProjectionMatrix(FOV, window.getWidth(), window.getHeight(), ZNEAR, ZFAR);
        shader.setUniform("u_ProjectionMatrix", projection);

        for(GameObject gameObject : gameObjects) {
            // Set world matrix for this item
            Matrix4f worldMatrix =
                    transformation.getWorldMatrix(
                            gameObject.getPosition(),
                            gameObject.getRotation(),
                            gameObject.getScale());
            shader.setUniform("u_WorldMatrix", worldMatrix);
            // Render the mes for this game item
            gameObject.getMesh().render();
        }
        shader.unbind();
    }

    public void clear(){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    public void cleanup(){
        if(shader != null){
            shader.cleanup();
        }
    }
}
