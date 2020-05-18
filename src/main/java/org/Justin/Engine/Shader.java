package org.Justin.Engine;

import jdk.jshell.execution.Util;
import org.joml.Matrix4f;
import org.lwjgl.system.MemoryStack;

import javax.swing.tree.ExpandVetoException;

import java.util.HashMap;
import java.util.Map;

import static org.lwjgl.opengl.GL20.*;

public class Shader {
    private int program;
    private int fragmentShader, vertexShader;
    private final Map<String, Integer> uniforms;

    public Shader(String src) throws Exception{
        program = glCreateProgram();
        uniforms = new HashMap<>();

        if (program == 0){
            throw new Exception("COuld not create shader");
        }

        String str  = Utils.ReadFile(src);
        String[] tokens = str.split("#shader");

        CreateVertexShader(tokens[1].substring(tokens[1].indexOf("#")+1).trim());
        CreateFragmentShader(tokens[2].substring(tokens[2].indexOf("#")+1).trim());
    }

    public Shader() throws Exception{
        program = glCreateProgram();
        uniforms = new HashMap<>();

        if (program == 0) {
            throw new Exception("Could not create shader!");
        }
    }

    public void CreateVertexShader(String src) throws Exception{
        vertexShader = createShader(src, GL_VERTEX_SHADER);
    }

    public void CreateFragmentShader(String src) throws Exception{
        fragmentShader = createShader(src, GL_FRAGMENT_SHADER);
    }

    protected int createShader(String src, int shaderType) throws Exception {
        int id = glCreateShader(shaderType);
        if (id == 0){
            throw new Exception("Error creating " + (shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment" ) + "shader");
        }

        glShaderSource(id, src);
        glCompileShader(id);

        if(glGetShaderi(id, GL_COMPILE_STATUS) == 0){
            throw new Exception("Error compiling shader: " + glGetShaderInfoLog(id, 1024));
        }

        glAttachShader(program, id);

        return id;
    }

    public void link() throws Exception{
        glLinkProgram(program);

        if(glGetProgrami(program, GL_LINK_STATUS) == 0){
            throw new Exception("Errror linking shader code: " + glGetProgramInfoLog(program, 1024));
        }

        if (vertexShader != 0) {
            glDetachShader(program, vertexShader);
        }
        if (fragmentShader != 0) {
            glDetachShader(program, fragmentShader);
        }

        glValidateProgram(program);
        if (glGetProgrami(program, GL_VALIDATE_STATUS) == 0) {
            System.err.println("Warning validating Shader code: " + glGetProgramInfoLog(program, 1024));
        }
    }

    public void bind(){
        glUseProgram(program);
    }

    public void unbind(){
        glUseProgram(0);
    }

    public void createUniform(String uniform) throws Exception{
        int location = glGetUniformLocation(program, uniform);

        if (location < 0){
            throw new Exception("Could not find uniform: " + uniform);
        }
        uniforms.put(uniform, location);
    }

    public void setUniform(String uniform, Matrix4f value){
        try (MemoryStack stack = MemoryStack.stackPush()) {
            glUniformMatrix4fv(uniforms.get(uniform), false, value.get(stack.mallocFloat(16)));
        }
    }

    public void cleanup(){
        unbind();
        if (program != 0){
            glDeleteProgram(program);
        }
    }
}
