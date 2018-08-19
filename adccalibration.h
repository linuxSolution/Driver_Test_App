#ifndef ADCCALIBRATION_H
#define ADCCALIBRATION_H

extern float an1_offset,an2_offset,an3_offset,an3_offset2,an4_offset,an4_offset2;
extern float an5_offset,an6_offset,an7_offset,an8_offset;

extern float an1_gain,an2_gain,an3_gain,an4_gain;
extern float an5_gain,an6_gain,an7_gain,an8_gain;

void get_calibration_values();

#endif // ADCCALIBRATION_H
