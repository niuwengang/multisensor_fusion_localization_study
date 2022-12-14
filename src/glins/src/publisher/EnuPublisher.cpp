/*
 * @Description: publisher ENU origin
 * @Function:
 * @Author: niu_wengang@163.com
 * @Version : v1.0
 * @Date: 2022-11-22
 * @Note:
 */


//relevent
#include "../../include/publisher/EnuPublisher.hpp"

namespace glins
{
    /**
     * @brief  config topic for publishing
     * @note
     * @todo
     **/
    EnuPublisher::EnuPublisher(ros::NodeHandle &nh, const std::string topic_name, const size_t queue_size, std::string frame_id) : nh_(nh)
    {
        publisher_ = nh_.advertise<sensor_msgs::NavSatFix>(topic_name, queue_size);
    }

    /**
     * @brief  publish origin point to rviz_satellite
     * @note
     * @todo
     **/
    void EnuPublisher::Publish(GnssFixDataType &enu_input)
    {
        origin_.header.frame_id = frame_id_;
        origin_.latitude = enu_input.latitude;
        origin_.longitude = enu_input.longtitude;
        origin_.altitude = enu_input.status;
        origin_.status.service = enu_input.service;

        publisher_.publish(origin_);
    }

    /**
     * @brief  if has been subscribered
     * @note
     * @todo
     **/
    bool EnuPublisher::HasSubscribered()
    {
        return publisher_.getNumSubscribers() != 0;
    }

} // namespace glins