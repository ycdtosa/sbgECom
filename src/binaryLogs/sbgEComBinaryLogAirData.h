/*!
 * \file			sbgEComBinaryLogAirData.h
 * \author			SBG Systems
 * \date			20 February 2019
 *
 * \brief			Parse received air data measurement logs such as barometer data.
 *
 * Air Data logs are used to inject / return barometric altitude
 * as well as true air speed.
 *
 * \copyright		Copyright (C) 2022, SBG Systems SAS. All rights reserved.
 * \beginlicense	The MIT license
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * \endlicense
 */

#ifndef SBG_ECOM_BINARY_LOG_AIR_DATA_H
#define SBG_ECOM_BINARY_LOG_AIR_DATA_H

// sbgCommonLib headers
#include <sbgCommon.h>
#include <streamBuffer/sbgStreamBuffer.h>

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------//
//- Log Air Data status definitions                                    -//
//----------------------------------------------------------------------//

/*!
 * Air Data sensor status mask definitions
 */
#define SBG_ECOM_AIR_DATA_TIME_IS_DELAY				(0x0001u << 0)		/*!< Set to 1 if the time stamp field represents a delay instead of an absolute time stamp. */
#define SBG_ECOM_AIR_DATA_PRESSURE_ABS_VALID		(0x0001u << 1)		/*!< Set to 1 if the pressure field is filled and valid. */
#define SBG_ECOM_AIR_DATA_ALTITUDE_VALID			(0x0001u << 2)		/*!< Set to 1 if the barometric altitude field is filled and valid. */
#define SBG_ECOM_AIR_DATA_PRESSURE_DIFF_VALID		(0x0001u << 3)		/*!< Set to 1 if the differential pressure field is filled and valid. */
#define SBG_ECOM_AIR_DATA_AIRSPEED_VALID			(0x0001u << 4)		/*!< Set to 1 if the true airspeed field is filled and valid. */
#define SBG_ECOM_AIR_DATA_AIRPSEED_VALID			(0x0001u << 4)		/*!< Typo. Keep for compatibility. */
#define SBG_ECOM_AIR_DATA_TEMPERATURE_VALID			(0x0001u << 5)		/*!< Set to 1 if the output air temperature field is filled and valid. */

//----------------------------------------------------------------------//
//- Log structure definitions                                          -//
//----------------------------------------------------------------------//

/*!
 * Log structure for AirData.
 */
typedef struct _SbgLogAirData
{
	uint32_t	timeStamp;						/*!< Time in us since the sensor power up OR measurement delay in us. */
	uint16_t	status;							/*!< Airdata sensor status bitmask. */
	float		pressureAbs;					/*!< Raw absolute pressure measured by the barometer sensor in Pascals. */
	float		altitude;						/*!< Altitude computed from barometric altimeter in meters and positive upward. */
	float		pressureDiff;					/*!< Raw differential pressure measured by the pitot tube in Pascal. */
	float		trueAirspeed;					/*!< True airspeed measured by a pitot tube in m.s^-1 and positive forward. */
	float		airTemperature;					/*!< Outside air temperature in °C that could be used to compute true airspeed from differential pressure. */
} SbgLogAirData;

//----------------------------------------------------------------------//
//- Public methods                                                     -//
//----------------------------------------------------------------------//

/*!
 * Parse data for the SBG_ECOM_LOG_AIR_DATA message and fill the corresponding structure.
 *
 * \param[in]	pInputStream				Input stream buffer to read the payload from.
 * \param[out]	pOutputData					Pointer on the output structure that stores parsed data.
 * \return									SBG_NO_ERROR if the payload has been parsed.
 */
SbgErrorCode sbgEComBinaryLogParseAirData(SbgStreamBuffer *pInputStream, SbgLogAirData *pOutputData);

/*!
 * Write data for the SBG_ECOM_LOG_AIR_DATA message to the output stream buffer from the provided structure.
 *
 * \param[out]	pOutputStream				Output stream buffer to write the payload to.
 * \param[in]	pInputData					Pointer on the input structure that stores data to write.
 * \return									SBG_NO_ERROR if the message has been generated in the provided buffer.
 */
SbgErrorCode sbgEComBinaryLogWriteAirData(SbgStreamBuffer *pOutputStream, const SbgLogAirData *pInputData);

#ifdef __cplusplus
}
#endif

#endif // SBG_ECOM_BINARY_LOG_AIR_DATA_H
