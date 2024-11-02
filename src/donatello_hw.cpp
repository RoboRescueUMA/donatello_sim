#include <ros/ros.h>
#include <controller_manager/controller_manager.h>
#include <donatello_sim/donatello_hw.hpp>

Donatello::Donatello() : RobotHW(){

    // connect and register the joint state interface
    hardware_interface::JointStateHandle state_handle_a("back_left_wheel_joint", &pos[0], &vel[0], &eff[0]);
    jnt_state_interface.registerHandle(state_handle_a);

    hardware_interface::JointStateHandle state_handle_b("center_left_wheel_joint", &pos[1], &vel[1], &eff[1]);
    jnt_state_interface.registerHandle(state_handle_b);

    hardware_interface::JointStateHandle state_handle_c("front_left_wheel_joint", &pos[2], &vel[2], &eff[2]);
    jnt_state_interface.registerHandle(state_handle_c);

    hardware_interface::JointStateHandle state_handle_d("back_right_wheel_joint", &pos[3], &vel[3], &eff[3]);
    jnt_state_interface.registerHandle(state_handle_d);

    hardware_interface::JointStateHandle state_handle_e("center_right_wheel_joint", &pos[4], &vel[4], &eff[4]);
    jnt_state_interface.registerHandle(state_handle_e);

    hardware_interface::JointStateHandle state_handle_f("front_right_wheel_joint", &pos[5], &vel[5], &eff[5]);
    jnt_state_interface.registerHandle(state_handle_f);

    registerInterface(&jnt_state_interface);


    // connect and register the joint velocity interface
    hardware_interface::JointHandle vel_handle_a(jnt_state_interface.getHandle("back_left_wheel_joint"), &cmd[0]);
    jnt_vel_interface.registerHandle(vel_handle_a);

    hardware_interface::JointHandle vel_handle_b(jnt_state_interface.getHandle("center_left_wheel_joint"), &cmd[1]);
    jnt_vel_interface.registerHandle(vel_handle_b);

    hardware_interface::JointHandle vel_handle_c(jnt_state_interface.getHandle("front_left_wheel_joint"), &cmd[2]);
    jnt_vel_interface.registerHandle(vel_handle_c);

    hardware_interface::JointHandle vel_handle_d(jnt_state_interface.getHandle("back_right_wheel_joint"), &cmd[3]);
    jnt_vel_interface.registerHandle(vel_handle_d);

    hardware_interface::JointHandle vel_handle_e(jnt_state_interface.getHandle("center_right_wheel_joint"), &cmd[4]);
    jnt_vel_interface.registerHandle(vel_handle_e);

    hardware_interface::JointHandle vel_handle_f(jnt_state_interface.getHandle("front_right_wheel_joint"), &cmd[5]);
    jnt_vel_interface.registerHandle(vel_handle_f);


    registerInterface(&jnt_vel_interface);
}

Donatello::~Donatello(){}

void Donatello::read(){

}

void Donatello::write(){
    
}


int main(int argc, char* argv[]){

    // Setup
    ros::init(argc, argv, "donatello");

    Donatello robot;
    controller_manager::ControllerManager cm(&robot);

    ros::AsyncSpinner spinner(1);
    spinner.start();

    // Control loop
    ros::Time prev_time = ros::Time::now();
    ros::Rate rate(10.0);

    while(ros::ok()){
        const ros::Time time = ros::Time::now();
        const ros::Duration period = time - prev_time;

        robot.read();
        cm.update(time, period);
        robot.write();

        rate.sleep();
    }


    return 0;
}