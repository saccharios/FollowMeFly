#include "pi_controller.h"
#include "math/functions.h"

double PI_Controller::Update(double error)
{
    auto proportional_part = error * _gain_proportional;
    auto gain_integral_scaled = _sampling_time * _time_constant_inverse;
    _integral_part += gain_integral_scaled * error + _anti_windup * _gain_correction;
    auto output_unlimited = _integral_part + proportional_part + _feed_fwd;

    auto output_limited = Limit(output_unlimited, _limit_lower, _limit_upper);
    _anti_windup = output_limited - output_unlimited;
    return output_limited;
}

void PI_Controller::Reset()
{
    _integral_part = 0;
    _anti_windup = 0;
}