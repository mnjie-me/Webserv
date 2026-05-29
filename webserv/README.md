*This proyect was created as part of the 42 curriculum by mnjie-me and iranieri.*

<h1>Webserv</h1>

<h2>Description</h2>
<p>Webserv is a simplified HTTP server inspired by NGINX, developed in C++98 as part of the 42 curriculum. Concepts that we have learned and implemented are:</p>
<ol>
	<li>TCP sockets communcation</li>
	<li>HTTP request parsing</li>
	<li>Static file serving</li>
	<li>CGI execution</li>
	<li>Multiple client handling</li>
	<li>Configuration file parsing</li>
	<li>HTTP response generation</li>
</ol>

<h2>Instructions</h2>
<p>Instalation</p>
<li>Clone the repository</li>
```
git clone https:/...
```
<p>Compilation</p>
<li>Enter the repository and compile writing</li>
```
make
```
<p>Run<p>
<li>./Webserv config.conf</li>
<p>Test</p>
<li>Open a different terminal</li>
<li>Write nc localhost 8080<li>
	<li>or curl -v http://localhost:8080</li>
<li>Write the request (first two lines are mandatory):</li>
<li>Line 1: Method of choice | route to file of choice | HTTP version"</li>
<li>Line 2: Host: "Host's name"</li>


