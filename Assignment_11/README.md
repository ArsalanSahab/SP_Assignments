
### Usage


Client > ./tcpClient <num_threads> <filename/filepath>

Server > ./tcpServer <num_threads> 



NOTE : <num_threads> must be same for Both Client and Server



##### Errors


If any errors occur while compilation, compile using :

*gcc -pthread -std=c99 -o <file_out> <file_in>


or 

*gcc -lpthread -o <file_out> <file_in>

