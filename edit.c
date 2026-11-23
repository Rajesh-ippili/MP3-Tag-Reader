#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "edit.h"

void edit(char *filename,char *changetext,char *tagname)
{
    FILE *temp=fopen("temp.mp3","wb");
    FILE *fptr=fopen(filename,"rb");

    if(temp == NULL)
    {
        printf("Unable to create temp file\n");
        return;
    }

    if(fptr == NULL)
    {
        printf("----------------------------------------------------------------\n");
        printf("|             Enter file is doesn't exit                        |\n");
        printf("----------------------------------------------------------------\n");
        fclose(temp);
        exit(EXIT_SUCCESS);
    }

    char header[10];

    if(fread(header,1,sizeof(header),fptr) != sizeof(header))
    {
        fclose(fptr);
        fclose(temp);
        return;
    }

    if(header[0]=='I' && header[1]=='D' && header[2]=='3')
    {
        printf("-------------------ID3 Tag Successfully Found-------------------\n");
    }
    else
    {
        fclose(fptr);
        fclose(temp);
        return;
    }

    unsigned int tag_size =
        ((unsigned char)header[6] << 21) |
        ((unsigned char)header[7] << 14) |
        ((unsigned char)header[8] << 7) |
        (unsigned char)header[9];

    unsigned int processed=0;

    fwrite(header,1,10,temp);

    while(processed<tag_size)
    {
        char frame_id[5];

        if(fread(frame_id,1,4,fptr)!=4)
            break;

        frame_id[4]='\0';

        /*
         * ID3 padding
         */
        if(frame_id[0]==0)
        {
            fwrite(frame_id,1,4,temp);
            processed+=4;
            break;
        }

        char size[4];

        if(fread(size,1,4,fptr)!=4)
            break;

        unsigned int old_size =
            ((unsigned char)size[0] << 24) |
            ((unsigned char)size[1] << 16) |
            ((unsigned char)size[2] << 8) |
            (unsigned char)size[3];

        char flags[2];

        if(fread(flags,1,2,fptr)!=2)
            break;

        /*
         * Find which frame has to be edited
         */
        int found=0;

        if(strcmp(tagname,"-t")==0 && strcmp(frame_id,"TIT2")==0)
            found=1;

        else if(strcmp(tagname,"-a")==0 && strcmp(frame_id,"TPE1")==0)
            found=1;

        else if(strcmp(tagname,"-A")==0 && strcmp(frame_id,"TALB")==0)
            found=1;

        else if(strcmp(tagname,"-y")==0 && strcmp(frame_id,"TYER")==0)
            found=1;

        else if(strcmp(tagname,"-m")==0 && strcmp(frame_id,"TCON")==0)
            found=1;

        else if(strcmp(tagname,"-c")==0 && strcmp(frame_id,"COMM")==0)
            found=1;


        fwrite(frame_id,1,4,temp);

        if(found)
        {
            unsigned int value=strlen(changetext)+1;

            if(value<=old_size)
            {
                char size1[4];

                size1[0]=(old_size >> 24) & 0xFF;
                size1[1]=(old_size >> 16) & 0xFF;
                size1[2]=(old_size >> 8) & 0xFF;
                size1[3]=old_size & 0xFF;

                fwrite(size1,1,4,temp);
                fwrite(flags,1,2,temp);

                /*
                 * Encoding byte
                 */
                char nul;

                if(fread(&nul,1,1,fptr)!=1)
                    break;

                fwrite(&nul,1,1,temp);

                /*
                 * New text
                 */
                fwrite(changetext,1,strlen(changetext),temp);

                /*
                 * Fill remaining bytes with zero
                 */
                char zero=0;

                for(unsigned int i=strlen(changetext)+1;
                    i<old_size;
                    i++)
                {
                    fwrite(&zero,1,1,temp);
                }

                /*
                 * We already read encoding byte.
                 * Skip remaining old data.
                 */
                if(old_size>0)
                    fseek(fptr,old_size-1,SEEK_CUR);
            }
            else
            {
                /*
                 * New text is bigger than old frame.
                 * Keep original frame.
                 */
                fwrite(size,1,4,temp);
                fwrite(flags,1,2,temp);

                if(old_size>0)
                {
                    char *data=malloc(old_size);

                    if(data==NULL)
                    {
                        printf("Memory allocation failed\n");
                        fclose(fptr);
                        fclose(temp);
                        return;
                    }

                    fread(data,1,old_size,fptr);
                    fwrite(data,1,old_size,temp);

                    free(data);
                }
            }

            processed+=10+old_size;
        }
        else
        {
            /*
             * Copy frame without changing it
             */
            fwrite(size,1,4,temp);
            fwrite(flags,1,2,temp);

            if(old_size>0)
            {
                char *data=malloc(old_size);

                if(data==NULL)
                {
                    printf("Memory allocation failed\n");
                    fclose(fptr);
                    fclose(temp);
                    return;
                }

                fread(data,1,old_size,fptr);
                fwrite(data,1,old_size,temp);

                free(data);
            }

            processed+=10+old_size;
        }
    }

    /*
     * VERY IMPORTANT:
     * Copy remaining ID3 padding / MP3 AUDIO DATA.
     */
    char ch;

    while(fread(&ch,1,1,fptr)==1)
    {
        fwrite(&ch,1,1,temp);
    }

    fclose(fptr);
    fclose(temp);

    remove(filename);
    rename("temp.mp3",filename);
}