#include <stdio.h>
#include "robocup_ssl_client.h"
#include "timer.h"

#include "messages_robocup_ssl_detection.pb.h"
#include "messages_robocup_ssl_geometry.pb.h"
#include "messages_robocup_ssl_wrapper.pb.h"

void printRobotInfo(SSL_DetectionRobot robot) {
    printf("ID: %d  ",robot.robot_id());
    printf("Altura : %6.2f | Posicao: <%9.2f,%9.2f> |", robot.height(),robot.x(),robot.y());
    if (robot.has_orientation()) {
        printf("Angulo: %6.3f |", robot.orientation());
    } else {
        printf("Angulo: N/A    ");
    }
    printf("Raw: <%8.2f,%8.2f>\n", robot.pixel_x(),robot.pixel_y());
}

void printBallsInfo(SSL_DetectionFrame detection, int qt_balls){
    for(int x = 0; x < qt_balls; x++){
        SSL_DetectionBall ball = detection.balls(x);
        printf("Bola %d: <%9.2f, %9.2f, ", x+1, ball.x(), ball.y());
        if(ball.has_z()) printf(" %9.2f>", ball.z());
        else printf(" N/A>");
        printf("\t Raw: <%9.2f, %9.2f>\n", ball.pixel_x(), ball.pixel_y());
    }
}

void printTeamsInfo(SSL_DetectionFrame detection, string team, int qt_robots){
    if(team == "blue"){
        for(int x = 0; x < qt_robots; x++){
            SSL_DetectionRobot robot = detection.robots_blue(x);
            printf("-Robot(B) (%2d/%2d): ",x+1, qt_robots);
            printRobotInfo(robot);
        }
    }else if(team == "yellow"){
        for(int x = 0; x < qt_robots; x++){
            SSL_DetectionRobot robot = detection.robots_yellow(x);
            printf("-Robot(Y) (%2d/%2d): ",x+1, qt_robots);
            printRobotInfo(robot);
        }
    }
}

int main(){
    RoboCupSSLClient client;
    client.open(true);
    SSL_WrapperPacket packet;

    while(true){
        if(client.receive(packet)){
            if(packet.has_detection()){
                SSL_DetectionFrame detection = packet.detection();
                unsigned int qt_bolas = detection.balls_size();
                unsigned int qt_robosBlue = detection.robots_blue_size();
                unsigned int qt_robosYellow = detection.robots_yellow_size();
                cout << "Quantidade de bolas detectadas: " << qt_bolas << endl;
                printBallsInfo(detection, qt_bolas);
                printTeamsInfo(detection, "blue", qt_robosBlue);
                printTeamsInfo(detection, "yellow", qt_robosYellow);
            }
        }
    }
}
