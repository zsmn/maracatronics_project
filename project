#include<bits/stdc++.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<termios.h>
#include<thread>
#include<chrono>
using namespace std;

// g++ project.cpp -o project -pthread

// defines
#define PORT 8889
#define IP "127.0.0.1"
#define delta 5

// some vars
struct sockaddr_in address;
vector<int> joints(40, 0);	
int new_socket, valread, addrlen = sizeof(address), opt = 1;
char buffer[1024] = {0}, param[1024] = {0};

// termios getch
int getch(){
	struct termios oldt, newt;
	int ch;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return ch;
}

// thread function
void getch_thread(){
	int ch;
	while ((ch = getch()) != 27){
		// first joint
		if(ch == 'q') joints[0] = (joints[0] + delta)%360;
		if(ch == 'a') joints[0] = (joints[0] - delta)%360;
		// second joint
		if(ch == 'w') joints[1] = (joints[1] + delta)%360;
		if(ch == 's') joints[1] = (joints[1] - delta)%360;
		// third joint
		if(ch == 'e') joints[2] = (joints[2] + delta)%360;
		if(ch == 'd') joints[2] = (joints[2] - delta)%360;
		// fourth joint
		if(ch == 'r') joints[3] = (joints[3] + delta)%360;
		if(ch == 'f') joints[3] = (joints[3] - delta)%360;
		// fifth joint
		if(ch == 't') joints[4] = (joints[4] + delta)%360;
		if(ch == 'g') joints[4] = (joints[4] - delta)%360;
		// sixth joint
		if(ch == 'y') joints[5] = (joints[5] + delta)%360;
		if(ch == 'h') joints[5] = (joints[5] - delta)%360;
		
		// extra functions =)
		if(ch == 92){ // when press '\'
			cout << "Started a 360 degrees rotating! AmAzInG!" << endl;
			for(int x = 0; x < 360; x++){
				joints[0] = (joints[0] + 1)%360;
				this_thread::sleep_for(chrono::milliseconds(10));
			}
		}
		if(ch == ','){
			cout << "Reseting!" << endl;
			for(int x = 0; x < 6; x++){
				while(true){
					if(joints[x] == 0) break;
					joints[x] = (joints[x] + 1)%360;
					this_thread::sleep_for(chrono::milliseconds(5));
				}
			}
		}
		if(ch == '.'){
			cout << "There are the angles of the joints:" << endl;
			for(int x = 0; x < 6; x++){
				cout << "Joint " << x+1 << " : " << joints[x] << endl;
			}
		}
	}
	
	exit(1); // when press 'ESC', exit the program
}

int main(){
	// starting thread and detaching (parallel work)
	thread first(getch_thread);
	first.detach();

	// starting the socket
	// AF_INET = IPv4 protocol
	// SOCK_STREAM = TCP connection
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == 0){
		cout << "Socket failed" << endl;
		return 0;
	}
	
	// prioriting the connection with setsockopt
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
		cout << "Error in setsockopt" << endl; 
		return 0;
	}
    
	// seting parameters in the struct address
	// connecting at port 8889, ip 127.0.0.1 (check defines)
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = inet_addr(IP);
	address.sin_port = htons(PORT); 
	
	// socket bind
	if(bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0){
		cout << "Bind failed" << endl;
		return 0;
	}
	
	// waiting for connections
	while(true){
		if(listen(socket_fd, 3) >= 0){ // if reached, accept the coonection
			if(((new_socket = accept(socket_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) >= 0)){
				cout << "Connection stabilished" << endl; // when enter in the if case, it means that the client and server are connected 
				valread = read(new_socket, buffer, 1024);
				while(valread){
					/* using std::find to find the string */
					string ax;
					size_t found;
					for(int x = 0; x < sizeof(buffer)/sizeof(char); x++){
						ax += buffer[x];
					}
					/* first transforming the string received in buffer and writing it
					on a string-type (c++), after that searching for some requests from
					client and processing them */
					found = ax.find("CONNECTION_OPEN");
					if(found != string::npos){
						sprintf(param, "CONNECTION_OPEN;;");
						send(new_socket, param, strlen(param), 0); 
					}
					found = ax.find("GET_NUM_ARMS");
					if(found != string::npos){
						strcpy(param, "GET_NUM_ARMS;1;");
						send(new_socket, param, strlen(param), 0); 
					}
					found = ax.find("GET_ARM_CODNAME");
					if(found != string::npos){
						strcpy(param, "GET_ARM_CODNAME;1;NS_00101");
						send(new_socket, param, strlen(param), 0); 
					}
					found = ax.find("GET_ARM_AXES;1");
					if(found != string::npos){
						strcpy(param, "GET_ARM_AXES;1;111111----");
						send(new_socket, param, strlen(param), 0); 
					}
					found = ax.find("GET_ARM_AUX;1");
					if(found != string::npos){
						strcpy(param, "GET_ARM_AUX;1;----------;");
						send(new_socket, param, strlen(param), 0); 
					}
					found = ax.find("GET_ARM_BASE;1");
					if(found != string::npos){
						strcpy(param, "GET_ARM_BASE;1;0;0;0;0;0;0");
						send(new_socket, param, strlen(param), 0); 
					}
					found = ax.find("GET_TOOL_RMT;1");
					if(found != string::npos){
						strcpy(param, "GET_TOOL_RMT;1;False");
						send(new_socket, param, strlen(param), 0); 
					}
					found = ax.find("GET_ARM_ALL_FRAMES;1");
					if(found != string::npos){
						strcpy(param, "GET_ARM_ALL_FRAMES;1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0");
						send(new_socket, param, strlen(param), 0); 
					}
					found = ax.find("GET_AUX_BASE;1");
					if(found != string::npos){
						strcpy(param, "GET_AUX_BASE;1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0");
						send(new_socket, param, strlen(param), 0); 
					}
					found = ax.find("GET_ALL_JNT");
					if(found != string::npos){
						strcpy(param, "GET_ALL_JNT");
						for(int x = 0; x < 40; x++){
							char aux[3];
							sprintf(aux, ";%d", joints[x]);
							strcat(param, aux);
						}
						send(new_socket, param, strlen(param), 0); 
					}
					found = ax.find("GET_IR_TYPES");
					if(found != string::npos){
						strcpy(param, "GET_IR_TYPES;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0");
						send(new_socket, param, strlen(param), 0); 
					}
					valread = read(new_socket, buffer, 1024); // reading new messages =)
				}
				cout << "Client disconnected" << endl;
			}
		}
	}
}
