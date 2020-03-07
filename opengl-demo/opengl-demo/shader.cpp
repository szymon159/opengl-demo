#include "shader.hpp"

// Public methods
//
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    if (!readShaders(vertexPath, fragmentPath)
        || !compileShaders()
        || !linkShaderProgram())
        return;

    IsDefined = true;
}

void Shader::use()
{
    glUseProgram(ID);
}

bool Shader::setBool(const std::string& name, bool value) const
{
    int uniformLocation = getUnifromLocation(name);
    if (uniformLocation == - 1)
        return FAILURE;

    glUniform1i(uniformLocation, (int)value);
    return SUCCESS;
}
bool Shader::setInt(const std::string& name, int value) const
{
    int uniformLocation = getUnifromLocation(name);
    if (uniformLocation == -1)
        return FAILURE;

    glUniform1i(uniformLocation, value);
    return SUCCESS;
}
bool Shader::setFloat(const std::string& name, float value) const
{
    int uniformLocation = getUnifromLocation(name);
    if (uniformLocation == -1)
        return FAILURE;

    glUniform1f(uniformLocation, value);
    return SUCCESS;
}
//


// Private methods
//
bool Shader::readShaders(const char* vertexPath, const char* fragmentPath)
{
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // Ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // Open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // Close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // Convert stream into string
        vShaderCode = vShaderStream.str();
        fShaderCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        printf("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n");
        return FAILURE;
    }

    return SUCCESS;
}

bool Shader::compileShaders()
{
    // VETREX SHADER
    //
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (!vertexShader)
        return FAILURE;
    const char* vertexShaderCode = vShaderCode.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    if (!checkCompileErrors(vertexShader, "VERTEX"))
        return FAILURE;
    //

    // FRAGMENT SHADER
    //
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!fragmentShader)
        return FAILURE;
    const char* fragmentShaderCode = fShaderCode.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    if (!checkCompileErrors(fragmentShader, "FRAGMENT"))
        return FAILURE;
    //

    return SUCCESS;
}

bool Shader::linkShaderProgram()
{
    ID = glCreateProgram();
    if (!ID)
        return FAILURE;

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    if (!checkCompileErrors(ID, "PROGRAM"))
        return FAILURE;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return SUCCESS;
}

int Shader::getUnifromLocation(const std::string& name) const
{
    int uniformLocation = glGetUniformLocation(ID, name.c_str());
    if (uniformLocation == -1)
    {
        printf("Unable to find uniform: intensityFactor\n");
    }

    return uniformLocation;
}

bool Shader::checkCompileErrors(uint shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            printf("ERROR::SHADER_COMPILATION_ERROR of type: %s\n", type.c_str());
            printf(infoLog);
            printf("\n -- --------------------------------------------------- -- \n");
            return FAILURE;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            printf("ERROR::PROGRAM_LINKING_ERROR of type: %s\n", type.c_str());
            printf(infoLog);
            printf("\n -- --------------------------------------------------- -- \n");
            return FAILURE;
        }
    }

    return SUCCESS;
}
//