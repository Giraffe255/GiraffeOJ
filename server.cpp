#include <iostream>
#include "compile.hpp"
#include "httplib.h"

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
               // 如何从 req 中获取到 json 请求，json 如何和 http 协议结合，
               // json 如何进行解析和构造？
               // 在这里调用 CompileAndRun
               std::string req_json; // 从 req 对象中获取
               std::string resp_json; // resp_json 放到响应中
               Compiler::CompileAndRun(req_json , &resp_json);
               resp.set_content(resp_json , "test/plain");
               });
    server.listen("0.0.0.0" , 9092);
    return 0;
}
