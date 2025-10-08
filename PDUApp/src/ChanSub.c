#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <errno.h>
#include "cadef.h"
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

//#define IPADDR "10.4.24.120"
//#define PORT 5000
#define BUFFER_SIZE 1024

void byteArrayToFloatArray(const uint8_t *byteArray, float *floatArray, size_t floatCount) {
    for (size_t i = 0; i < floatCount; i++) {
        // Assuming the byte array is in little-endian format
        uint32_t temp = (byteArray[i * 4]) |
                        (byteArray[i * 4 + 1] << 8) |
                        (byteArray[i * 4 + 2] << 16) |
                        (byteArray[i * 4 + 3] << 24);
        floatArray[i] = *((float *)&temp);
    }
}

float* UDPcommand(const char *command, const char *IPset){
    char IP2[50];
    strcpy(IP2,IPset);
//    printf("Status Top: IP=%s  ...\n",IP2);
    char *IPADDR = strtok(IP2,":");
    int PORT = atoi(strtok(NULL,":"));
    int sockfd;
    unsigned char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);
//    printf("Status 1...\n");
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        return(NULL);
//        exit(EXIT_FAILURE);
    }
    struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        perror("setsockopt failed");
        close(sockfd);
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0) {
        perror("setsockopt send timeout failed");
        close(sockfd);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, IPADDR, &server_addr.sin_addr) <= 0) {
        perror("invalid address/ address not supported");
        close(sockfd);
        return(NULL);
//        exit(EXIT_FAILURE);
    }
//    printf("Status 2...\n");
    ssize_t bytes_sent = sendto(sockfd, command, strlen(command), 0, (const struct sockaddr *) &server_addr, sizeof(server_addr));
    if(bytes_sent < 0) {
        perror("sendto failed");
        close(sockfd);
//        exit(EXIT_FAILURE);
        return(NULL);
    }
    if(strcmp(command,"Status")==0){
//        printf("Status 3...\n");
        float* statusArray = (float*)malloc(20*sizeof(float));
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &server_addr, &len);
//        printf("buflen=%d\n",n);
        buffer[n] = '\0';
//        printf("Status 4...\n");
        if(n<0){
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                printf("UDP receive timed out!\n");
            } else {
                perror("sendto failed");
            }
            close(sockfd);
            return(NULL);
        }
        byteArrayToFloatArray(buffer, statusArray, 20);
        close(sockfd);
        return(statusArray);
    }
    close(sockfd);
    return(NULL);
}

static int ChanSub(aSubRecord *precord) {
    int chsp1,chrb1,chsp2,chrb2,chsp3,chrb3,chsp4,chrb4,allONsp,allOFFsp;
    char *IPset = (char *)precord->k;

    chsp1 = *(int *)precord->a;
    chrb1 = *(int *)precord->b;
    chsp2 = *(int *)precord->c;
    chrb2 = *(int *)precord->d;
    chsp3 = *(int *)precord->e;
    chrb3 = *(int *)precord->f;
    chsp4 = *(int *)precord->g;
    chrb4 = *(int *)precord->h;
    allONsp = *(int *)precord->i;
    allOFFsp = *(int *)precord->j;
 //   printf("1...\n");
    if(chsp1!=chrb1){
        *(int *)precord->vala = chsp1;
        *(int *)precord->valb = chsp1;
        if(chsp1==1){
            UDPcommand("CH1-ON",IPset);
        }else{
            UDPcommand("CH1-OFF",IPset);
        }
        usleep(300000);
    }
 //   printf("2...\n");
    if(chsp2!=chrb2){
        *(int *)precord->valc = chsp2;
        *(int *)precord->vald = chsp2;
        if(chsp2==1){
            UDPcommand("CH2-ON",IPset);
        }else{
            UDPcommand("CH2-OFF",IPset);
        }
        usleep(300000);
    }
//    printf("3...\n");
    if(chsp3!=chrb3){
        *(int *)precord->vale = chsp3;
        *(int *)precord->valf = chsp3;
        if(chsp3==1){
            UDPcommand("CH3-ON",IPset);
        }else{
            UDPcommand("CH3-OFF",IPset);
        }
        usleep(300000);
    }
//    printf("4...\n");
    if(chsp4!=chrb4){
        *(int *)precord->valg = chsp4;
        *(int *)precord->valh = chsp4;
        if(chsp4==1){
            UDPcommand("CH4-ON",IPset);
        }else{
            UDPcommand("CH4-OFF",IPset);
        }
        usleep(300000);
    }
 //   printf("5...\n");
    if(allONsp==1){
        *(int *)precord->vala = 1;
        *(int *)precord->valb = 1;
        *(int *)precord->valc = 1;
        *(int *)precord->vald = 1;
        *(int *)precord->vale = 1;
        *(int *)precord->valf = 1;
        *(int *)precord->valg = 1;
        *(int *)precord->valh = 1;
        *(int *)precord->vali = 0;
        UDPcommand("ALL-ON",IPset);
        usleep(300000);
    }
 //   printf("6...\n");
    if(allOFFsp==1){
        *(int *)precord->vala = 0;
        *(int *)precord->valb = 0;
        *(int *)precord->valc = 0;
        *(int *)precord->vald = 0;
        *(int *)precord->vale = 0;
        *(int *)precord->valf = 0;
        *(int *)precord->valg = 0;
        *(int *)precord->valh = 0;
        *(int *)precord->valj = 0;
        UDPcommand("ALL-OFF",IPset);
        usleep(300000);
    }
 //   printf("7...\n");
//    printf("7:IPset=%s\n",IPset);
    float *data = UDPcommand("Status",IPset);
    if(data != NULL){
 //       printf("8...\n");
        memcpy((float *)precord->valk,data,20*sizeof(*data));
 //       printf("9...\n");
        free(data);
    }else{
 //       printf("Array is NULL\n");
    }
    return(0);
}
// Note the function must be registered at the end!
epicsRegisterFunction(ChanSub);
