/*
 * @Description: 多关键帧发布
 * @Function:
 * @Author: Robotic Gang (modified from Ren Qian)
 * @Version : v1.0
 * @Date: 2022-10-16
 */

// relevent
#include "../../include/publisher/key_frames_publisher.hpp"
// ros
#include <nav_msgs/Path.h>
// eigen
#include <Eigen/Dense>

namespace multisensor_localization
{
    /**
     * @brief 多关键帧发布器初始化
     * @note
     * @todo
     **/
    KeyFramesPublisher::KeyFramesPublisher(ros::NodeHandle &nh,
                                           std::string topic_name,
                                           std::string frame_id,
                                           int buff_size)
        : nh_(nh), frame_id_(frame_id)
    {
        publisher_ = nh_.advertise<nav_msgs::Path>(topic_name, buff_size);
    }

    /**
     * @brief 多关键帧发布
     * @note 以path方式发布
     * @todo
     **/
    void KeyFramesPublisher::Publish(const std::deque<KeyFrame> &key_frames)
    {
        nav_msgs::Path path;
        path.header.stamp = ros::Time::now();
        path.header.frame_id = frame_id_;

        for (size_t i = 0; i < key_frames.size(); ++i)
        {
            KeyFrame key_frame = key_frames.at(i);

            geometry_msgs::PoseStamped pose_stamped;
            ros::Time ros_time((float)key_frame.time_stamp_);
            pose_stamped.header.stamp = ros_time;
            pose_stamped.header.frame_id = frame_id_;

            pose_stamped.header.seq = key_frame.index_;

            pose_stamped.pose.position.x = key_frame.pose_(0, 3);
            pose_stamped.pose.position.y = key_frame.pose_(1, 3);
            pose_stamped.pose.position.z = key_frame.pose_(2, 3);

            Eigen::Quaternionf q = key_frame.GetQuaternion();
            pose_stamped.pose.orientation.x = q.x();
            pose_stamped.pose.orientation.y = q.y();
            pose_stamped.pose.orientation.z = q.z();
            pose_stamped.pose.orientation.w = q.w();

            path.poses.push_back(pose_stamped);
        }

        publisher_.publish(path);
    }

    /**
     * @brief 发布器是否被订阅
     * @note
     * @todo
     **/
    bool KeyFramesPublisher::HasSubscribers()
    {
        return publisher_.getNumSubscribers() != 0;
    }
}