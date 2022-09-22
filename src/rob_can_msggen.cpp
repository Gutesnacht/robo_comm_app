#include "include/rob_can_msggen.hpp"

// use innomaker usb-to-can library from github to send out messages!
// move developement to linux os to have easy access to cansocket (windows is a bit tricky though)
// if on windows - we need to use usbtocan from innomaker (maybe integrate that here and send out messages)
// https://github.com/INNO-MAKER/usb2can/tree/master/For%20Windows/InnoMakerUsb2Can-v.1.2.3
// should start developement on linux and switch back to windwos when we are finished though.

namespace robot::serial {

requests resolveOption(std::string input) {
   static const std::map<std::string, requests> request_map {
       { "err", INVALID },
       { "move_joint", MOVE_JOINT },
       { "move_multiple", MOVE_MULTIPLE },
       { "get_state", GET_STATUS },
       { "toggle_break", TOGGLE_BREAK },
       //...
   };

   auto itr = request_map.find(input);
   if( itr != request_map.end() ) {
       return itr->second;
   }
   return INVALID;
}


RobotSerial::RobotSerial(){

    m_request.push_back("move_joint");
    m_request.push_back("move_multiple");
    m_request.push_back("get_state");
    m_request.push_back("toggle_break");

    m_sender = new communication::SenderThread;


}

void RobotSerial::create_msg(){
    std::vector<robot_request> request;
    robot_request dummy {};
    dummy.request="move_joint";
    dummy.req_args.joint_id=3;
    dummy.req_args.joint_name="Elbow";
    dummy.req_args.angle=90;
    dummy.req_args.dir=1;
    dummy.req_args.speed=13;
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
            msg.push_back(0xFF);
            const msg_sizes sizes;
            requests req=resolveOption(*it);
            switch (req) {
            case INVALID:
            {
                std::cout<<"Invalid option - aborting"<<std::endl;
                return MSGG_E_T::MSGG_MISSING;
            }
                break;
            case MOVE_JOINT:
            {
                std::cout<<"Building Joint Angle message" <<std::endl;

                msg.push_back(request.at(var).req_args.joint_id);
                msg.push_back(req);
                msg.push_back(request.at(var).req_args.dir);
                msg.push_back(request.at(var).req_args.angle);
                msg.push_back(request.at(var).req_args.speed);
                std::cout<<"Send request" << msg.size()<< std::endl;
                // check if message has same size
                if(msg.size()==(sizes.SINGLE_MSG_SIZE-1)) // we do miss the EOF here
                    std::cout<<"Message has correct size"<<std::endl;
            }
                break;
            case MOVE_MULTIPLE:
            {

            }
                break;
             case TOGGLE_BREAK:
            {
                // This does not have a request field - we just send the signal and ask what state we are in
                //msg.push_back()

            }
                break;

            default:
                break;
            }

            msg.push_back(0xFF);
            // call communication layer to get out message
            // get angle and convert to hex
            // in so nem Feld - FF (SOF) | joint | CMD | DIR | ANGLE | SPEED | EOF (FF)

            // we got a match - build the request
        }
        else
        {
            std::cout<<"No match"<<std::endl;
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
