#include "helper.h"

Helper::Helper()
{

}

void Helper::readAlbumData()
{
    if (!file->open(QIODevice::ReadOnly))
        return;

    if (!albumData.setContent(file)) {
        file->close();
        return;
    }
    file->close();
}
