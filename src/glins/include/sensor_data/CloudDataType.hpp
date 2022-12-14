/*
 * @Description: cloud data type define
 * @Function:
 * @Author: niu_wengang@163.com
 * @Version : v1.0
 * @Date: 2022-11-30
 * @Todo: add defination about colorful point cloud
 */

#ifndef CLOUD_DATA_TYPE_HPP_
#define CLOUD_DATA_TYPE_HPP_

// thirdpart lib
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

namespace glins
{

    class CloudDataType
    {
    public:
        using POINT = pcl::PointXYZ;
        using CLOUD = pcl::PointCloud<POINT>;
        using CLOUD_PTR = pcl::PointCloud<pcl::PointXYZ>::Ptr;

    public:
        CloudDataType();

    public:
        double time_stamp = 0.0;
        CLOUD_PTR cloud_ptr;
    }; // class cloud data type
} // namespace glins

#endif