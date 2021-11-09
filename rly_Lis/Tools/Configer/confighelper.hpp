#ifndef CONFIGHELPER_H
#define CONFIGHELPER_H
#include <QString>
#include <QHash>
#include <QSettings>
#include <QTextCodec>
#include "windows.h"
#include <QDir>
#include <QDebug>

#define configPathC "./protocol.ini"

class configHelper
{
public:
    //解析qss文件,乘以比例系数
    static bool writeInit(QHash<QString,QString> Hvalue,QString user_config)
    {
        if(Hvalue.isEmpty())
        {
            return false;
        }
        else
        {
            //创建配置文件操作对象
            QSettings *config = new QSettings(configPathC, QSettings::IniFormat);
            config->setIniCodec(QTextCodec::codecForName("UTF-8"));
            //将信息写入配置文件
            config->beginGroup(user_config);
            QHash<QString,QString>::const_iterator i = Hvalue.constBegin();
            while(i != Hvalue.constEnd())
            {
                config->setValue(i.key(),i.value());
                ++i;
            }
            config->endGroup();
            delete config;
            return true;
        }
    }

    static bool DeleteInitConfig(QString user_config)
    {
        QString path=configPathC;
        const QChar* sz_path = path.unicode();
        const QChar* sz_user_config = user_config.unicode();
        WritePrivateProfileString((LPCWSTR)sz_user_config,NULL,NULL,(LPCWSTR)sz_path);
        return true;
    }

    static QString readInit( QString user_key,QString user_config)
    {
        QString user_value = "";
        user_config +="/";
        if(!user_key.isEmpty())
        {
            QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
            //创建配置文件操作对象
//            qDebug() << QDir::currentPath();
            QSettings *config = new QSettings(configPathC, QSettings::IniFormat);
            config->setIniCodec(QTextCodec::codecForName("UTF-8"));
            //读取用户配置信息
            user_value = config->value(user_config + user_key).toString();
            delete config;
        }

        return user_value;
    }
};

#endif // CONFIGHELPER_H
