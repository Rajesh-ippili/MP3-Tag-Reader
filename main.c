/*
Name                : Ippili Rajesh
Class               : 26015C
Start Date          : 01/09/2026
End Date            : __/__/2026
Project Name        : MP3 Tag Reader & Editor

Project Description :
 The MP3 Tag Reader & Editor is a simple application designed to
.   read and manage information stored in an MP3 file.
 .      It allows users to view and edit details such as title, artist,
  .         album, year, genre, and comment easily.
   .            The updated information can be saved into a new MP3 file,
    .               making it convenient to manage and organize music files.

FEATURES

1. View MP3 Tags
   Displays the title, artist, album, year, genre, and comment of an MP3 file.

2. Edit Title
   Allows users to change the title of an MP3 file.

3. Edit Artist
   Allows users to change the artist information of an MP3 file.

4. Edit Album
   Allows users to change the album name of an MP3 file.

5. Edit Year
   Allows users to update the release year of an MP3 file.

6. Edit Genre
   Allows users to change the genre of an MP3 file.

7. Edit Comment
   Allows users to update the comment stored in an MP3 file.

8. Save Edited File
   Saves the updated MP3 tag information into a new output file.
*/
#include<stdio.h>
#include<string.h>
#include "view.h"
#include "edit.h"
int main(int argc,char **argv)
{
    if(argc==1)
    {
        printf("---------------------------------------------------------------\n");
        printf("Error: ./a.out : INVALID ARGUMENTS\n");
        printf("USAGE :\n");
        printf("To view please pass like : ./a.out -v mp3file_name\n");
        printf("To edit please pass like : ./a.out -e changing_text mp3file_name\n");
        printf("To get help pass like : ./a.out --help\n");
        printf("---------------------------------------------------------------\n");
    }
    else
    {
        if(argc==2 && (strcmp(argv[1],"--help")==0))
        {
            printf("--help\n");
            printf("-------------------------HELP MENU---------------------------\n");
            printf("1. -v -> To view mp3 file contents.\n");
            printf("2. -e -> To edit mp3 file contents.\n");
            printf("    2.1. -t -> To edit song title.\n");
            printf("    2.2. -a -> To edit artist name.\n");
            printf("    2.3. -A -> To edit album name.\n");
            printf("    2.4. -y -> To edit year.\n");
            printf("    2.5. -m -> To edit content.\n");
            printf("    2.6. -c -> To edit comment.\n");
            printf("-------------------------------------------------------------\n");
        }
        // char *ext = strrchr(argv[2], '.');
        else if(argc==3 && (strcmp(argv[1],"-v")==0))
        {
            char *ext1 = strrchr(argv[2], '.');
            if((strcmp(ext1,".mp3"))==0)
            {
               view(argv[2]);
               
               //printf("view\n");
            }
            else
            {
                printf("-----------------------------------------------------------------\n");
                printf("Error: ./a.out -v INVALID ARGUMENTS\n");
                printf("USAGE :\n");
                printf("To view please pass like : ./a.out -v mp3file_name\n");
                printf("To edit please pass like : ./a.out -e changing_text mp3file_name\n");
                printf("To get help pass like : ./a.out --help\n");
                printf("-----------------------------------------------------------------\n");       
            }
        }
        else if(argc==5 && (strcmp(argv[1],"-e")==0))
        {
            
            char *ext2 = strrchr(argv[4], '.');
            if((strcmp(argv[2],"-t") || strcmp(argv[2],"-a") || strcmp(argv[2],"-A") || strcmp(argv[2],"-m") ||strcmp(argv[2],"-y") || strcmp(argv[2],"-c"))&&(strcmp(ext2,".mp3")==0))
            {
                printf("-------------------- SELECTED EDIT OPTION ----------------------\n");
                edit(argv[4],argv[3],argv[2]);

                if(strcmp(argv[2],"-t")==0)
                {
                    printf("------------------ TITLE CHANGED SUCCESSFULLY ------------------\n");
                    printf("               \n");
                    printf("    TITLE   :   %s\n",argv[3]);
                    printf("           \n");


                }
                else if(strcmp(argv[2],"-a")==0)
                {
                    printf("----------------- ARTIST CHANGED SUCCESSFULLY ------------------\n");
                    printf("               \n");
                    printf("    ARTIST   :   %s\n",argv[3]);
                    printf("           \n");
                }
                else if(strcmp(argv[2],"-A")==0)
                {
                    printf("------------------ ALBUM CHANGED SUCCESSFULLY ------------------\n");
                    printf("               \n");
                    printf("    ALBUM   :   %s\n",argv[3]);
                    printf("           \n");

                }
                else if(strcmp(argv[2],"-y")==0)
                {
                    printf("------------------ YEAR CHANGED SUCCESSFULLY -------------------\n");
                    printf("               \n");
                    printf("    YEAR   :   %s\n",argv[3]);
                    printf("           \n");

                }
                else if(strcmp(argv[2],"-m")==0)
                {
                    printf("------------------- MUSIC CHANGED SUCCESSFULLY -----------------\n");
                    printf("               \n");
                    printf("    MUSIC   :   %s\n",argv[3]);
                    printf("           \n");

                }
                else if(strcmp(argv[2],"-c")==0)
                {
                    printf("----------------- COMMENT CHANGED SUCCESSFULLY -----------------\n");
                    printf("               \n");
                    printf("    COMMENT   :   %s\n",argv[3]);
                    printf("           \n");

                }
                
                printf("----------------------------------------------------------------\n");
                printf("|                 EDIT SUCCESSFULLY COMPLETED                  |\n");
                printf("----------------------------------------------------------------\n");
            }
            else
            {
                printf("-------------------------------------------------------------\n");
                printf("Error: ./a.out -e INVALID ARGUMENTS\n");
                printf("USAGE :\n");
                printf("To view please pass like : ./a.out -v mp3file_name\n");
                printf("To edit please pass like : ./a.out -e changing_text mp3file_name\n");
                printf("To get help pass like : ./a.out --help\n");
                printf("-------------------------------------------------------------\n");
            }
            
        }
        else
        {
            printf("--help\n");
            printf("------------------------HELP MENU--------------------------\n");
            printf("1. -v -> To view mp3 file contents.\n");
            printf("2. -e -> To edit mp3 file contents.\n");
            printf("    2.1. -t -> To edit song title.\n");
            printf("    2.2. -a -> To edit artist name.\n");
            printf("    2.3. -A -> To edit album name.\n");
            printf("    2.4. -y -> To edit year.\n");
            printf("    2.5. -m -> To edit content.\n");
            printf("    2.6. -c -> To edit comment.\n");
            printf("-------------------------------------------------------------\n");
        }

    }
    return 0;
}