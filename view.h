#ifndef VIEW_H
#define VIEW_H
typedef struct
{
    char title[100];
    char artist[100];
    char album[100];
    char year[10];
    char contenttype[100];
    char downloadfrom[100];
}tag;
void view(char*filename);


#endif