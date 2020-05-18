package org.Justin.Game;

import org.Justin.Engine.*;
import org.joml.Vector3f;

import static org.lwjgl.glfw.GLFW.*;

//This is where to write game specific logic anything to "low level" should not go in here
public class Game implements GameLogic {
    Renderer renderer;
    private int displxInc = 0;

    private int displyInc = 0;

    private int displzInc = 0;

    private int scaleInc = 0;
    private float color;
    Mesh mesh;
    Mesh mesh2;
    VertexArray vao;
    Shader shader;
    GameObject[] gameObjects;
    GameObject gameObject;
    GameObject gameObject2;

    public Game(){
        renderer = new Renderer();
    }

    @Override
    public void init(Window window)throws Exception{
        renderer.init(window);

        float[] vertices = new float[]{
                0.0f, 0.5f, 0.5f,
                -0.5f, -0.5f, 0.5f,
                0.5f, -0.5f, 0.5f
        };

        float[] square = new float[]{
                -0.5f, -0.5f, -1.5f,
                0.5f, -0.5f, -1.5f,
                0.5f, 0.5f, -1.5f,
                -0.5f, 0.5f, -1.5f
        };

        float[] colors = new float[]{
                0.5f, 0.0f, 0.0f,
                0.0f, 0.5f, 0.0f,
                0.0f, 0.0f, 0.5f,
                0.0f, 0.5f, 0.5f
        };

        int[] indices = new int[]{0, 1, 2, 2, 3, 0};
        int[] indices2 = new int[]{0, 1, 2};

        mesh = new Mesh(square, indices);
        //mesh2 = new Mesh(vertices, colors, indices2);

        gameObject = new GameObject(mesh);
        gameObject.setPosition(0,0,-2);
        //gameObject2 = new GameObject(mesh);
        //gameObject2.setPosition(2, 2, -4);
        gameObjects = new GameObject[] {gameObject};
    }

    @Override
    public void input(Window window){
        displyInc = 0;
        displxInc = 0;
        displzInc = 0;
        scaleInc = 0;
        if (window.isKeyPressed(GLFW_KEY_W)) {
            displyInc = 1;
        } else if (window.isKeyPressed(GLFW_KEY_S)) {
            displyInc = -1;
        } else if (window.isKeyPressed(GLFW_KEY_A)) {
            displxInc = -1;
        } else if (window.isKeyPressed(GLFW_KEY_D)) {
            displxInc = 1;
        } else if (window.isKeyPressed(GLFW_KEY_E)) {
            displzInc = -1;
        } else if (window.isKeyPressed(GLFW_KEY_Q)) {
            displzInc = 1;
        } else if (window.isKeyPressed(GLFW_KEY_Z)) {
            scaleInc = -1;
        } else if (window.isKeyPressed(GLFW_KEY_X)) {
            scaleInc = 1;
        }
    }

    @Override
    public void update(float interval){
        for (GameObject GameObject : gameObjects) {
            // Update position
            Vector3f itemPos = gameObject.getPosition();
            float posx = itemPos.x + displxInc * 0.05f;
            float posy = itemPos.y + displyInc * 0.05f;
            float posz = itemPos.z + displzInc * 0.05f;
            gameObject.setPosition(posx, posy, posz);

            // Update scale
            float scale = gameObject.getScale();
            scale += scaleInc * 0.05f;
            if ( scale < 0 ) {
                scale = 0;
            }
            gameObject.setScale(scale);

            // Update rotation angle
            float rotation = gameObject.getRotation().z + 1.5f;
            if ( rotation > 360 ) {
                rotation = 0;
            }
            gameObject.setRotation(0, 0, rotation);
        }
    }

    @Override
    public void render(Window window){
        renderer.render(window, gameObjects);
    }

    @Override
    public void cleanup(){
        renderer.cleanup();
        mesh.cleanup();
    }
}
