#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"view.h"
tag mp3; 
void view(char *filename)
{
   
    FILE *fptr=fopen(filename,"rb");
    if(fptr == NULL)
    {
        printf("----------------------------------------------------------------\n");
        printf("|             Enter file is doesn't exit                        |\n");
        printf("----------------------------------------------------------------\n");
        exit(EXIT_SUCCESS);
    }
    char header[10];
    fread(header,1,sizeof(header),fptr);
    if (header[0] == 'I' && header[1] == 'D' && header[2] == '3')
    {
        printf("-------------------ID3 Tag Successfully Found--------------------\n");
    }
    else
    {
        return;
    }

    unsigned int version = (unsigned char)header[3];
    unsigned int revision = (unsigned char)header[4];

    printf("------------------- Version : %d   Revision: %d -------------------\n", version, revision);
    int count = 6;
    while(count--)
    {
        char frame_id[5];
        fread(frame_id,1,sizeof(frame_id)-1,fptr);
        frame_id[4]='\0';
        char size[4];
        fread(size,1,sizeof(size),fptr);
        unsigned int value;
        value=(((unsigned char)size[0]<<24)|((unsigned char)size[1]<<16)|((unsigned char)size[2]<<8)|((unsigned char)size[3]));
        char flag[2];
        fread(flag,1,sizeof(flag),fptr);
        fseek(fptr,1,SEEK_CUR);

        if(strcmp(frame_id,"TIT2")==0)
        {
            fread(mp3.title,1,value-1,fptr);
            mp3.title[value-1]='\0';
        }
        else if(strcmp(frame_id,"TPE1")==0)
        {
            fread(mp3.artist,1,value-1,fptr);
            mp3.artist[value-1]='\0';

        }
        else if(strcmp(frame_id,"TALB")==0)
        {
            fread(mp3.album,1,value-1,fptr);
            mp3.album[value-1]='\0';
        }
        else if(strcmp(frame_id,"TYER")==0)
        {
            fread(mp3.year,1,value-1,fptr);
            mp3.year[value-1]='\0';
        }
        else if(strcmp(frame_id,"TCON")==0)
        {
            fread(mp3.contenttype,1,value-1,fptr);
            mp3.contenttype[value-1]='\0';
        }
        else if(strcmp(frame_id,"COMM")==0)
        {
            fread(mp3.downloadfrom,1,value-1,fptr);
            mp3.downloadfrom[value-1]='\0';
        }
        
    }
    printf("--------------------- SELECTED VIEW DETAILS ---------------------\n");
    printf("-----------------------------------------------------------------\n");
    printf("|           MP3 TAG READER AND EDITOR FOR ID3.v2                |\n");
    printf("-----------------------------------------------------------------\n");
    printf("    TITLE   :   %s\n",mp3.title);
    printf("    ARTIST  :   %s\n",mp3.artist);
    printf("    ALBUM   :   %s\n",mp3.album);
    printf("    YEAR    :   %s\n",mp3.year);
    printf("    MUSIC   :   %s\n",mp3.contenttype);
    printf("    COMMENT :   %s\n",mp3.downloadfrom);
    printf("-----------------------------------------------------------------\n");
    printf("----------------- DETAILS DISPLAYED SUCCESSFULLY ----------------\n");

    return;
}
