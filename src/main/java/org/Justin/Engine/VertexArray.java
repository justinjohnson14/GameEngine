package org.Justin.Engine;

import static org.lwjgl.opengl.GL15.*;
import static org.lwjgl.opengl.GL20.glEnableVertexAttribArray;
import static org.lwjgl.opengl.GL30.glBindVertexArray;
import static org.lwjgl.opengl.GL30.glGenVertexArrays;

public class VertexArray {
    int ID;

    public VertexArray() {
        ID = glGenVertexArrays();
    }

    public void bind(){
        glBindVertexArray(ID);
    }

    public void unbind(){
        glBindVertexArray(0);
    }

    public void selectVertexAttribArray(int index){
        glEnableVertexAttribArray(index);
    }

    public void cleanup(){
        unbind();
        glDeleteBuffers(ID);
    }
}
