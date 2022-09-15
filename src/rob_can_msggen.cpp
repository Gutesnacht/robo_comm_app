#include "include/rob_can_msggen.hpp"


namespace robot::serial {

RobotSerial::RobotSerial(){

    m_request.push_back("req_move");
    m_request.push_back("req_state");

}

void RobotSerial::create_msg(){
    std::vector<robot_request> request;
    robot_request dummy {};
    request.push_back(dummy);
    request.push_back(dummy);

    build_msg(request);
}

MSGG_E_T RobotSerial::build_msg(const std::vector<robot_request> & request)
{
    // take a n-sized vector to get message queue to sent those to robot.
    // first - check the request and see what we have
    for (std::size_t var {0}; var < request.size(); ++var) {
        auto it=std::find(m_request.begin(), m_request.end(), request.at(var).request);
        if(it != m_request.end())
        {
            QByteArray msg;
            msg.resize(request.size());
            std::cout<<"size: " << msg.size() << std::endl;
            // we got a match - build the request
        }
        else
        {
            return MSGG_E_T::MSGG_UNKNOWN;
        }

    }

    return MSGG_E_T::MSGG_OK;
}


MSGG_E_T RobotSerial::decode_msg(robot_response & response)
{

    return MSGG_E_T::MSGG_OK;
}

}
