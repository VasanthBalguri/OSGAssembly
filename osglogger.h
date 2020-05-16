#ifndef OSGLOGGER_H
#define OSGLOGGER_H
#define BOOST_CHRONO_VERSION 2
#include <osgDB/ReadFile>
#include <fstream>
#include <boost/chrono.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <boost/chrono/io/timezone.hpp>

class OsgLogger : public osg::NotifyHandler{
public:
    OsgLogger(const std::string& file_path)
    {
        path = file_path;
    }

    virtual ~OsgLogger(){_log.close();}

    virtual void notify(osg::NotifySeverity severity,const char* msg);

protected:
    std::ofstream _log;
    std::string path;
};
#endif // OSGLOGGER_H
