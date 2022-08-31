#include <brpc/channel.h>
#include "hello_brpc.protoc.pb.h"
#include "common.h"

void brpcclient()
{
    int bytes = 8;

    // A Channel represents a communication line to a Server. Notice that
    // Channel is thread-safe and can be shared by all threads in your program.
    brpc::Channel channel;

    // Initialize the channel, NULL means using default options.
    brpc::ChannelOptions options;
    options.protocol = brpc::PROTOCOL_BAIDU_STD;
    options.timeout_ms = -1;
    options.max_retry = 3;
    if (channel.Init("127.0.0.1:14768", "", &options) != 0)
    {
        return ;
    }

    example::HelloService_Stub stub(&channel);
    int count = 1000;
    uint64_t cost = 0;

    for (int i = 0; i < count; i++)
    {
        example::HelloRequest request;
        example::HelloResponse response;
        brpc::Controller cntl;
        std::string data(bytes, 'a');
        request.set_message(data);
        cntl.set_request_compress_type(brpc::COMPRESS_TYPE_NONE);

        // Because `done'(last parameter) is NULL, this function waits until
        // the response comes back or error occurs(including timedout).
        stub.Hello(&cntl, &request, &response, NULL);

        if (!cntl.Failed())
        {
            std::cout << "Received response from " << cntl.remote_side()
                      << " to " << cntl.local_side()
                      << ": " << response.message().size()
                      << " latency=" << cntl.latency_us() << "us" << std::endl;
            cost += cntl.latency_us();
        }
        else
        {
            std::cout << "wrong";
        }
    }
    printf("avg_latency:%.2fus\n", 1.0 * cost / count);
}