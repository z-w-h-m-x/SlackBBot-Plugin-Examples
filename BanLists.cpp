#include "SlackBot/Plugin_Base.h"

Plugin_Extern const char * PluginName()
{
    return "Ban";
}
Plugin_Extern void Init()
{
    SubmitFunction("Filter_AfterReceiveMessage");
}

Plugin_Extern bool Filter_AfterReceiveMessage(MessageContent content)
{
    if (content.sendID.userID == 114514) // 如果userID为114514就过滤
        return false;
    return true;
}
