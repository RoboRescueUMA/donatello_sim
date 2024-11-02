#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/robot_hw.h>

class Donatello : public hardware_interface::RobotHW{
    public:

        Donatello();
        ~Donatello();

        void read();
        void write();

    private: 

        hardware_interface::JointStateInterface jnt_state_interface;
        hardware_interface::VelocityJointInterface jnt_vel_interface;

        double cmd[6];

        double pos[6];
        double vel[6];
        double eff[6];
};