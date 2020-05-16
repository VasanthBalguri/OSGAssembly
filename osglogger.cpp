#include "osglogger.h"

void OsgLogger::notify(osg::NotifySeverity severity,const char* msg)
{
    _log.open(path.c_str());
    _log<<boost::chrono::time_fmt(boost::chrono::timezone::local, "[%H:%M:%S]") <<boost::chrono::system_clock::now();
    _log<<msg;
    _log.close();
}
