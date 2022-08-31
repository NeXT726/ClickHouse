#include <brpc/server.h>
#include "hello_brpc.protoc.pb.h"
#include "common.h"

namespace example
{
    class HelloServiceImpl : public HelloService
    {
    public:
        HelloServiceImpl(){};

        virtual ~HelloServiceImpl(){};

        virtual void Hello(google::protobuf::RpcController *cntl_base,
                           const example::HelloRequest *request,
                           example::HelloResponse *response,
                           google::protobuf::Closure *done)
        {
            // This object helps you to call done->Run() in RAII style. If you need
            // to process the request asynchronously, pass done_guard.release().
            brpc::ClosureGuard done_guard(done);
            brpc::Controller *cntl =
                static_cast<brpc::Controller *>(cntl_base);

            // The purpose of following logs is to help you to understand
            // how clients interact with servers more intuitively. You should
            // remove these logs in performance-sensitive servers.
            std::cout << "Received request[log_id=" << cntl->log_id()
                      << "] from " << cntl->remote_side()
                      << " to " << cntl->local_side()
                      << ": " << request->message().size() << std::endl;

            // Fill response.
            response->set_message("response");

            // You can compress the response by setting Controller, but be aware
            // that compression may be costly, evaluate before turning on.
            // cntl->set_response_compress_type(brpc::COMPRESS_TYPE_GZIP);

            // Set attachment which is wired to network directly instead of
            // being serialized into protobuf messages.
            cntl->response_attachment().append(cntl->request_attachment());
        }
    };
} // namespace example

void brpcserver()
{
    brpc::Server server;
    example::HelloServiceImpl hello_impl;
    if (server.AddService(&hello_impl, brpc::SERVER_DOESNT_OWN_SERVICE) != 0)
    {
        return ;
    }

    butil::EndPoint point;
    point = butil::EndPoint(butil::IP_ANY, 14768);

    // Start the server.
    brpc::ServerOptions options;
    options.idle_timeout_sec = -1;
    /// options.protocol = brpc::PROTOCOL_BAIDU_STD;
    if (server.Start(point, &options) != 0)
    {
        return ;
    }

    // Wait until Ctrl-C is pressed, then Stop() and Join() the server.
    server.RunUntilAskedToQuit();
}