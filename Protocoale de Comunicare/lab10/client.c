#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

int main(int argc, char *argv[])
{
    char *message;
    char *response;
    int sockfd;

        
    // Ex 1.1: GET dummy from main server
    sockfd = open_connection("3.8.116.10", 8080, AF_INET, SOCK_STREAM, 0);
    message = compute_get_request("3.8.116.10", "/api/v1/dummy", NULL, NULL, 0);
    puts(message);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    puts(response);


    // Ex 1.2: POST dummy and print response from main server
    char* body[1];
    body[0] = "mesaj=dummy";
    char* content = "application/x-www-form-urlencoded";
    message = compute_post_request("3.8.116.10", "/api/v1/dummy", content, body, 1, NULL, 0);
    puts(message);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    puts(response);


    // Ex 2: Login into main server
    char* login[2];
    login[0] = "username=student";
    login[1] = "password=student";
    content = "application/x-www-form-urlencoded";
    message = compute_post_request("3.8.116.10", "/api/v1/auth/login", content, login, 2, NULL, 0);
    puts(message);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    puts(response);
    

    // Ex 3: GET weather key from main server
    char* cookies[1];
    cookies[0] = "connect.sid=s%3AsTO0tH1TbLw3fzi6nRogjLnIh09yquIG.e4IbvuI%2Btk3KSgt2KW1QZgGmTiw8ldSLVQWDBbnNmBE";
    message = compute_get_request("3.8.116.10", "/api/v1/weather/key", NULL, cookies, 1);
    puts(message);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    puts(response);
    

    // Ex 4: GET weather data from OpenWeather API
    int w_sockfd = open_connection("37.139.1.159", 80, AF_INET, SOCK_STREAM, 0);
    char* params = "lat=12&lon=12&appid=b912dd495585fbf756dc6d8f415a7649";
    message = compute_get_request("37.139.1.159", "/data/2.5/weather", params, NULL, 0);
    puts(message);
    send_to_server(w_sockfd, message);
    response = receive_from_server(w_sockfd);
    puts(response);
    

    // Ex 5: POST weather data for verification to main server
    content = "application/json";
    char* data[1];
    data[0] = basic_extract_json_response(message);
    message = compute_post_request("3.8.116.10", "/api/v1/weather/12/12", content, data, 1, NULL, 0);
    puts(message);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    puts(response);
    

    // Ex 6: Logout from main server
    
    // BONUS: make the main server return "Already logged in!"

    // free the allocated data at the end!

    return 0;
}
