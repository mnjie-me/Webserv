/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 12:25:10 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/05/04 13:08:33 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Method.hpp"

Response Method::handleCGI(const Request& request, const Router& router)
{
    Response response;
    int fd[2];

    if (pipe(fd) == -1)
    {
        response.setStatusCode(500);
        response.setBody(defaultErrorPage(500));
        return (response);
    }
    pid_t pid = fork();
    if (pid == -1)
    {
        response.setStatusCode(500);
        response.setBody(defaultErrorPage(500));
        return (response);
    }
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        std::vector<std::string> env;

        env.push_back("REQUEST_METHOD=" + request.getMethod());
        env.push_back("SCRIPT_FILENAME=" + router.getCgiPath()); 
        env.push_back("SERVER_PROTOCOL=HTTP/1.1");
        env.push_back("QUERY_STRING=" + router.getQuery());
        if (!request.getBody().empty())
        {
            std::stringstream ss;
            ss << request.getBody().size();
            env.push_back("CONTENT_LENGTH=" + ss.str());
        }        
        else
            env.push_back("CONTENT_LENGTH=0");

        char** envp = vecToCharArray(env);
        std::string script = router.getCgiPath();
        std::string interpreter = getInterpreter(router);
        if (interpreter.empty())
        {
            response.setStatusCode(500);
            response.setBody(defaultErrorPage(500));
            exit (1);
        }        
        char* argv[] = {
            (char*)interpreter.c_str(),
            (char*)script.c_str(),
            NULL
        };
        execve(argv[0], argv, envp);
        size_t i = 0;
        while (envp[i])
        {
            delete(envp[i]);
            i++;
        }
        delete(envp);
        exit(1);
    }
    response = readCgiOutput(fd, response, pid);
    return (response);
}

Response Method::readCgiOutput(int* fd, Response& response, pid_t pid)
{
    close(fd[1]);

    std::string output;
    char buf[4096];
    ssize_t bytesRead;
    
    while ((bytesRead = read(fd[0], buf, sizeof(buf))) > 0)
        output.append(buf, bytesRead);
    close(fd[0]);
    
    int status;
    
    waitpid(pid, &status, 0);
    //std::cerr << "output: " << output << std::endl;
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
    {
        response.setStatusCode(500);
        response.setBody(defaultErrorPage(500));
        return response;
    }
    
    size_t pos = output.find("\r\n\r\n");
    if (pos == std::string::npos)
        pos = output.find("\n\n");
    if (pos != std::string::npos)
    {
        std::string cgiHeaders = output.substr(0, pos);
        size_t offset = 0;
        
        if (output.compare(pos, 4, "\r\n\r\n") == 0)
            offset = 4;
        else
            offset = 2;
        body = output.substr(pos + offset);
    }
    else
        body = output;
    response.setStatusCode(200);
    response.setBody(body);
    response.setHeader("Content-Type", "text/html");
    return (response);
}

char** Method::vecToCharArray(const std::vector<std::string>& env)
{
    char** result = new char*[env.size() + 1];
    size_t i = 0;

    while (i < env.size())
    {
        result[i] = new char[env[i].size() + 1];
        size_t j = 0;
        while (j < env[i].size())
        {
            result[i][j] = env[i][j];
            j++;
        }
        result[i][j] = '\0';
        i++;
    }
    result[env.size()] = NULL;
    return (result);
}

std::string Method::getInterpreter(const Router& router)
{
    std::string ext = router.getCgiPass();
    std::string interpreter;
    
    if (ext == ".py")
        interpreter = "/usr/bin/python3";
    else if (ext == ".php")
        interpreter = "/usr/bin/php-cgi";
    else
        return ("");
    return (interpreter);
}