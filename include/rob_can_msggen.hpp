#ifndef ROB_CAN_MSGGEN_HPP
#define ROB_CAN_MSGGEN_HPP

// build messages to be used by communication layers

#include<string>
#include<vector>
#include<stdexcept>
#include<iostream>
#include<QByteArray>
#include<QObject>
#include<QtQml>
#include<QtSerialBus/QCanBusDevice>
#include<QtSerialBus/QCanBus>

// private
#include "include/communication.hpp"


namespace robot::serial {

struct msg_sizes
{
   const size_t SINGLE_MSG_SIZE = 7;
   const size_t MULTIPLE_MSGS_SIZE = 14;
   const size_t GET_MSG_SIZE = 5;
};

enum requests {
    INVALID=-1,
    MOVE_MULTIPLE,
    GET_STATUS,
    MOVE_JOINT, //2
    TOGGLE_BREAK,
    //others...
};

enum struct MSGG_E_T: int
{
    MSGG_MISSING,
    MSGG_UNKNOWN,
    MSGG_ERR,
    MSGG_OK=0,
};

struct robot_arg_type{
    std::string joint_name = {""};
    int joint_id = {0};
    int dir = {0};
    int speed = {0};
    int angle ={0};
    int break_state = {0};
};

struct robot_request{
    std::string request = {""};
    robot_arg_type req_args={};
};

struct robot_response{
    std::string response ={""};
    robot_arg_type res_args={};
};


class RobotSerial : public QObject
{
    Q_OBJECT

public slots:
    void create_msg();

public:
    RobotSerial();
    MSGG_E_T build_msg(const std::vector<robot_request> & request);
    MSGG_E_T decode_msg(robot_response & response);

private:
    std::vector<std::string> m_request;
    communication::SenderThread * m_sender;


};


}

#endif // ROB_CAN_MSGGEN_HPP
