#ifndef HELPER_H
#define HELPER_H

#include<QDomDocument>
#include<QFile>

class Helper
{
   // Q_OBJECT
public:
    Helper();
    void readAlbumData();

    QDomDocument albumData;
    QFile *file;
};

#endif // HELPER_H
