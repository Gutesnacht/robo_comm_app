# robo_comm_app
Application to communicate with refurbished Schunk arm - creating CAN msg via UART

This application will feature a small GUI for the start to send basic motion to the Arm via some dedictated 
UART to CAN Message transcription. The transcription happens will be part of a dedicated UART-to-CAN
Library that encodes the motion desired - e.g. Joint ID | CMD | SUB_CMD| (payload) Direction | Joint Position | Joint Velocity
1/0 (right/left - rotation) | (Angle (integer) + Angle (floating point) | Desired Velocity
