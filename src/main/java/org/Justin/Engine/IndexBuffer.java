package org.Justin.Engine;

import org.lwjgl.system.MemoryUtil;

import java.nio.IntBuffer;

import static org.lwjgl.opengl.GL11.GL_FLOAT;
import static org.lwjgl.opengl.GL11.glClearColor;
import static org.lwjgl.opengl.GL15.*;
import static org.lwjgl.opengl.GL15.GL_ARRAY_BUFFER;
import static org.lwjgl.opengl.GL20.glEnableVertexAttribArray;
import static org.lwjgl.opengl.GL20.glVertexAttribPointer;
import static org.lwjgl.opengl.GL30.glBindVertexArray;
import static org.lwjgl.opengl.GL30.glGenVertexArrays;
import static org.lwjgl.system.MemoryUtil.memFree;

public class IndexBuffer {

    public int ID;
    IntBuffer indicesBuffer;

    public IndexBuffer(int[] indices){
        //Index Buffer
        indicesBuffer = MemoryUtil.memAllocInt(indices.length);
        indicesBuffer.put(indices).flip();
        ID = glGenBuffers();
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer, GL_STATIC_DRAW);
        unbind();
        ;
        memFree(indicesBuffer);

        if (indicesBuffer != null){
            MemoryUtil.memFree(indicesBuffer);
        }
    }

    public void bind(){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    }

    public void unbind(){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    public void cleanup() {
        if (indicesBuffer != null) {
            MemoryUtil.memFree(indicesBuffer);
        }
        unbind();
        glDeleteBuffers(ID);
    }
}
