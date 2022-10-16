/*
 * @Description: 畸变矫正
 * @Function:
 * @Author: Robotic Gang (modified from Ren Qian)
 * @Version : v1.0
 * @Date: 2022-10-16
 */

// relevent
#include "../../../include/models/scan_adjust/distortion_adjust.hpp"
// pcl
#include <pcl/common/transforms.h>

namespace multisensor_localization
{
    /**
     * @brief 设置运动参数
     * @note
     * @todo
     **/
    void DistortionAdjust::SetMotionParam(float scan_period, VelocityData velocity_data)
    {
        scan_period_ = scan_period;
        linear_velocity_ << velocity_data.linear_velocity_.x, velocity_data.linear_velocity_.y, velocity_data.linear_velocity_.z;
        angular_velocity_ << velocity_data.angular_velocity_.x, velocity_data.angular_velocity_.y, velocity_data.angular_velocity_.z;
    }

    /**
     * @brief
     * @note
     * @todo
     **/
    bool DistortionAdjust::AdjustCloud(CloudData::CLOUD_PTR &input_cloud_ptr, CloudData::CLOUD_PTR &output_cloud_ptr)
    {
        CloudData::CLOUD_PTR origin_cloud_ptr(new CloudData::CLOUD(*input_cloud_ptr));
        output_cloud_ptr.reset(new CloudData::CLOUD());
        /*圈参数*/
        const float orientation_space = 2.0 * M_PI;
        const float orientation_delete = 0; //暂时设置为无盲区
        const double orientation_start = atan2(origin_cloud_ptr->points[0].y, origin_cloud_ptr->points[0].x);
        /*将点云旋转到0位置*/
        Eigen::AngleAxisf t_V(orientation_start, Eigen::Vector3f::UnitZ());
        Eigen::Matrix3f rotate_matrix = t_V.matrix();
        Eigen::Matrix4f transform_matrix = Eigen::Matrix4f::Identity();
        transform_matrix.block<3, 3>(0, 0) = rotate_matrix.inverse();
        pcl::transformPointCloud(*origin_cloud_ptr, *origin_cloud_ptr, transform_matrix);
        /*速度转换*/
        linear_velocity_ = rotate_matrix.inverse() * linear_velocity_;
        angular_velocity_ = angular_velocity_.inverse() * angular_velocity_;
        /*遍历点云并转换*/
        for (size_t point_index = 1; point_index < origin_cloud_ptr->points.size(); point_index++)
        {
            /*计算当前角度*/
            float orientation_current = atan2(origin_cloud_ptr->points[point_index].y, origin_cloud_ptr->points[point_index].x);
            /*过圈处理*/
            orientation_current += orientation_current < 0.0 ? 2.0 * M_PI : orientation_current;
            /*盲区处理*/
            if(orientation_current<orientation_delete||(2.0*M_PI-orientation_delete)<orientation_delete)
            {
                continue;
            }
             /*计算圈内的比例系数*/
             // 针对kitti数据集 比例为1的一圈
            float time_rotation=fabs(orientation_current)/orientation_space*scan_period_-scan_period_/2.0;
            //time_rotation   
        }
        return true;
    }

} // namespace multisensor_localization