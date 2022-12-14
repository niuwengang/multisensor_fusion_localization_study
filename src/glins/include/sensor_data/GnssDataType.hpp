/*
 * @Description: gnss data type define
 * @Function: Using the WGS 84 reference ellipsoid
 * @Author: niu_wengang@163.com
 * @Version : v1.0
 * @Date: 2022-11-18
 * @Todo:add defination about gnss raw data
 */

#ifndef GNSS_DATA_TYPE_HPP_
#define GNSS_DATA_TYPE_HPP_

// c++ lib
#include <deque>
// thirdpart lib
#include <GeographicLib/LocalCartesian.hpp>

namespace glins
{
    class GnssFixDataType
    {
    public:
        double time_stamp = 0.0; // unix time
        double longtitude = 0.0, latitude = 0.0, altitude = 0.0;
        int status = 0; // fix is valid when status >= STATUS_FIX.
        int service = 0;
        double local_east = 0.0, local_north = 0.0, local_up = 0.0; // ENU coordinates
    private:
        static bool flag_origin_fixed;
        static GeographicLib::LocalCartesian geo_converter; // convert WGS84 to ENU

    public:
        void FixOrigin();
        void UpdateGnssOdom();
        static bool TimeSync(std::deque<GnssFixDataType> &unsynced_data_deque,
                             std::deque<GnssFixDataType> &synced_data_buff,
                             const double refer_time);
    }; // class GnssFixDataType

} // namespace glins

#endif