#include "HoroscopeToday.h"

#include <sstream>
#include <string>
#include <ctime>
#include <map>
#include <random>

struct UserData
{
    long long id = -1 ;
    long long lasterDate = -1;
    int scope;
};

std::map<int,UserData> UserDatas;

Plugin_Extern const char * PluginName()
{
    return "今日运势";
}

Plugin_Extern void Init()
{
    SubmitSpecialFunction(Message_Normal,"TriggerAt",0);//作为非触发器
}

Plugin_Extern bool TriggerAt(MessageContent message)
{
    std::istringstream str(message.content);
    std::string parm;
    str>>parm;// 空格切分字符串 | Split string

    // 判断第一个值
    // Determine the first value
    if (parm == "今日运势")
        HoroscopeToday(message);

    return true;
}

void HoroscopeToday(MessageContent message)
{
    time_t nowtime;
    time(&nowtime);
    tm * p = localtime(&nowtime);

    long long date = (p->tm_year+1900)*10000 + (p->tm_mon+1)*100 + p->tm_mday;// 获取日期 | Get the date

    UserData ud;

    if (UserDatas.find(message.sendID.userID) != UserDatas.end())
    {
        ud = UserDatas[message.sendID.userID];
    }
    else
    {
        ud.id = message.sendID.userID;
    }

    std::stringstream ss;

    ss << "\n";

    if (ud.lasterDate >= date)//今日有
    {
        ss<<"缓存中显示今天已经测过了！\n";// The cache shows that it has been tested today!
    }
    else
    {
        ud.scope = RandARumber100();
        ud.lasterDate = date;
    }

    ss<<"今日指数："<<ud.scope;

    message.content = ss.str().c_str();

    message.sendID.messageType = at;
/*
    message为传入的消息，其中有user的ID、群聊还是私聊、群联ID(如果是群聊)
    这里作为普通类型，要at对方，所以将类型设置为at

    message is the incoming message, which contains the user ID, group or private chat, and group ID(if group chat).
    Here, as a normal type, we want to be at each other, so we set the type to at
*/

    UserDatas[message.sendID.userID] = ud;

    BotSendMessage(message);
}

int RandARumber100()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1,100);

    return dist(gen);
}