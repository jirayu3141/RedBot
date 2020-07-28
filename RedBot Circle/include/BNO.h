/*
 * BNO.h
 *
 * Created: 04-May-19 4:32:06 PM
 *  Author: BTone
 */ 


#ifndef BNO_H_
#define BNO_H_
#include <stdint.h>

typedef struct {
	double x_acc;
	double y_acc;
	double z_acc;
	uint16_t heading;
	uint16_t roll;
	uint16_t pitch;
	uint16_t ang_x;
	uint16_t ang_y;
	uint16_t ang_z;
} BNO_DATA;

uint8_t BNO_Probe();
void BNO_SetIMU(void);
void BNO_PrintMode(void);
void BNO_PrintData(BNO_DATA* input);
void BNO_GetData(BNO_DATA* output);
void BNO_PrintCalibrationStatus(void);
void BNO_SetConfigMode(void);
double BNO_GetHeading();
void BNO_CalibrateEuler();
#endif /* BNO_H_ */