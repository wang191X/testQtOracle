#ifndef GLOABEPARAMS_H
#define GLOABEPARAMS_H

#include <QString>
#include <QTextCodec>

#define G2U(s) (QTextCodec::codecForName("GBK")->toUnicode(s))

const QString g_ip= "127.0.0.1";
const QString g_dbName= "orcl";
const QString g_usr="eightyg";
const QString g_passwd="123456";

extern QString g_clientUsr;
extern int g_clientId;
extern int g_ParentId;
extern QString g_clientPasswd;
extern int g_privilege;
extern int g_minACLID;
extern int g_maxACLID;
extern int g_minXACLID;
extern int g_maxXACLID;
extern int g_minPLID;
extern int g_maxPLID;

#endif //

