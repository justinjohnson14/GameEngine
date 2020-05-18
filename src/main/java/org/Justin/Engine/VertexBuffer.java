package org.Justin.Engine;

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

public class VertexBuffer {

    public int ID;
    FloatBuffer verticesBuffer;

    public VertexBuffer(float[] vertices) {
        verticesBuffer = MemoryUtil.memAllocFloat(vertices.length);
        verticesBuffer.put(vertices).flip();
        ID = glGenBuffers();
        bind();
        glBufferData(GL_ARRAY_BUFFER, verticesBuffer, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
        unbind();

        cleanup();
    }

    public void bind(){
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }

    public void unbind(){
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    public void cleanup(){
        if (verticesBuffer != null){
            MemoryUtil.memFree(verticesBuffer);
        }
        unbind();
        glDeleteBuffers(ID);
    }

}
