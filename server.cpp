#include <iostream>
#include "httplib.h"
#include "compile.hpp"
#include <jsoncpp/json/json.h>

int main() {
    using namespace httplib;
    Server server;

    // Get 给 server 注册一个回调函数，这个函数的调用时机，
    // 处理 Get 方法的时候
    // lambda 表达式？  匿名函数(一次性函数)
    // 路由
    server.Get("/comepile" , [](const Request& req , Response& resp){
               // 根据具体问题场景，根据请求，计算出响应结果
        (void)req;
        // TODO 如何从 req 中获取到 json 请求，json 如何和 http 协议结合，
        // json 如何进行解析和构造 ？json 的第三方库?
        // 在这里调用 CompileAndRun
        Json::Value req_json; // 从 req 对象中获取
        Json::Value resp_json; // resp_json 放到响应中
        Compiler::CompileAndRun(req_json , &resp_json);
        // 需要把 Json::Value 对象序列化成一个字符串，才能返回
        Json::FastWriter writer;
        resp.set_content(writer.write(resp_json) , "test/plain");
    });
    server.listen("0.0.0.0" , 9092);
    return 0;
}
