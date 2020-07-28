/*
 * BNO.h
 *
 * Created: 04-May-19 4:30:00 PM
 *  Author: BTone
 */
#include <stdint.h> 
#include <stdio.h>
#include "i2c_master.h"
#include "BNO.h"
#include <math.h>

#define BNO_ADDRESS 0b01010010

static uint8_t wr_data = 0;
static uint8_t status = 0;

uint8_t BNO_Probe() {
	puts("Probing sensor...");
	status = i2c_readReg(BNO_ADDRESS, 0, &wr_data, 1);
	if (status) {
		puts("Sensor not found!");
	} else {
		puts("Sensor found!");
		printf("Device ID: 0x%X\n", wr_data);
	}
	return status;
}

void BNO_SetIMU(void) {
	wr_data = 8;
	i2c_writeReg(BNO_ADDRESS, 0x3D, &wr_data, 1);
}

void BNO_SetConfigMode(void) {
	wr_data = 0;
	i2c_writeReg(BNO_ADDRESS, 0x3D, &wr_data, 1);
}

void BNO_GetData(BNO_DATA* output) {
	static uint8_t data[6];
	/* Acc Data */
	//i2c_readReg(BNO_ADDRESS, 0x28, data, 6);
	//output->x_acc = data[0] | (data[1] << 8);
	//output->y_acc = data[2] | (data[3] << 8);
	//output->z_acc = data[4] | (data[5] << 8);
	/* Euler */
	i2c_readReg(BNO_ADDRESS, 0x1A, data, 6);
	output->heading = data[0] | (data[1] << 8);
	output->roll	= data[2] | (data[3] << 8);
	output->pitch	= data[4] | (data[5] << 8);
	/* Ang */
	i2c_readReg(BNO_ADDRESS, 0x14, data, 6);
	output->ang_x = data[0] | (data[1] << 8);
	output->ang_y	= data[2] | (data[3] << 8);
	output->ang_z	= data[4] | (data[5] << 8);
}

void BNO_PrintData(BNO_DATA* input) {
		//printf("/* BNO Acc Data */\n"
		//	"X Acc: %f\n"
		//	"Z Acc: %f\n"
		//	"Abs: %f\n\n", input->x_acc, input->z_acc, a_abs);
		printf("/* Euler Angles */\n"
				"Heading: %f\n"
				"Roll: %f\n"
				"Pitch: %f\n"
				"Ang X: %f\n"
				"Ang Y: %f\n"
				"Ang Z: %f\n\n", input->heading / 16.0, input->roll / 16.0, input->pitch / 16.0, input->ang_x / 16.0, input->ang_y / 16.0, input->ang_z / 16.0);
}

void BNO_CalibrateEuler() {
	/* Read Current Data */
	static uint8_t data[6];
	i2c_readReg(BNO_ADDRESS, 0x14, data, 6);
	
	/* Write back as offsets */
	//BNO_SetIMU()
	i2c_writeReg(BNO_ADDRESS, 0x61, data, 6);
}

double BNO_GetHeading() {
	static uint8_t data[2];
	i2c_readReg(BNO_ADDRESS, 0x1A, data, 2);
	int16_t temp = data[0] | (data[1] << 8);
	return temp / 16.0;
}

void BNO_PrintMode(void) {
	i2c_readReg(BNO_ADDRESS, 0x3D, &wr_data, 1);
	printf("BNO OPR: 0x%X\n", wr_data);
}

void BNO_PrintCalibrationStatus(void) {
	i2c_readReg(BNO_ADDRESS, 0x35, &wr_data, 1);
	uint8_t mag_sta = wr_data & 0b11;
	uint8_t acc_sta = (wr_data >> 2) & 0b11;
	uint8_t gyr_sta = (wr_data >> 4) & 0b11;
	uint8_t sys_sta = (wr_data >> 6) & 0b11;
	printf("/* Calibration Status */\n"
	"Mag Status: 0x%X\n"
	"Acc Status: 0x%X\n"
	"Gyr Status: 0x%X\n"
	"Sys Status: 0x%X\n\n", mag_sta, acc_sta, gyr_sta, sys_sta);
}

void BNO_PrintCalibrationData(void) {
	static uint8_t data[6];
	i2c_readReg(BNO_ADDRESS, 0x55, data, 6);
	uint16_t acc_x = data[0] | (data[1] << 8);
	uint16_t acc_y = data[2] | (data[3] << 8);
	uint16_t acc_z = data[4] | (data[5] << 8);
	static uint8_t radius_raw[2];
	i2c_readReg(BNO_ADDRESS, 0x67, radius_raw, 2);
	uint16_t radius = 0;
}