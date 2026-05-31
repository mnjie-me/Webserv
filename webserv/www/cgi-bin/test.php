<?php
echo "Content-Type: text/html\r\n\r\n";
echo "<h1>CGI PHP Test</h1>";
echo "<p>METHOD: " . $_SERVER['REQUEST_METHOD'] . "</p>";
echo "<p>QUERY: " . $_SERVER['QUERY_STRING'] . "</p>";
echo "<p>BODY: " . file_get_contents('php://input') . "</p>";
echo "<p>POST vars: " . print_r($_POST, true) . "</p>";