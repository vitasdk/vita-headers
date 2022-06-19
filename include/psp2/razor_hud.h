/**
 * \usergroup{SceRazorHud}
 * \usage{psp2/razor_hud.h,SceRazorHud_stub,SCE_SYSMODULE_RAZOR_HUD}
 */
 
#ifndef _PSP2_RAZOR_HUD_H_
#define _PSP2_RAZOR_HUD_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Enumeration for the gpu live metrics groups */
typedef enum SceRazorGpuLiveMetricsGroup {
	SCE_RAZOR_GPU_LIVE_METRICS_GROUP_PBUFFER_USAGE,
	SCE_RAZOR_GPU_LIVE_METRICS_GROUP_OVERVIEW_1,
	SCE_RAZOR_GPU_LIVE_METRICS_GROUP_OVERVIEW_2,
	SCE_RAZOR_GPU_LIVE_METRICS_GROUP_OVERVIEW_3
} SceRazorGpuLiveMetricsGroup;

/** Enumeration for the gpu live results entry types */
typedef enum SceRazorLiveTraceMetricEntryType {
	SCE_RAZOR_LIVE_TRACE_METRIC_ENTRY_TYPE_JOB,
	SCE_RAZOR_LIVE_TRACE_METRIC_ENTRY_TYPE_PARAMETER_BUFFER,
	SCE_RAZOR_LIVE_TRACE_METRIC_ENTRY_TYPE_FRAME
} SceRazorLiveTraceMetricEntryType;

/** Enumeration for the gpu live results job types */
typedef enum SceRazorLiveTraceMetricJobType {
	SCE_RAZOR_LIVE_TRACE_METRIC_JOB_TYPE_FIRMWARE,
	SCE_RAZOR_LIVE_TRACE_METRIC_JOB_TYPE_VERTEX1,
	SCE_RAZOR_LIVE_TRACE_METRIC_JOB_TYPE_FRAGMENT1,
	SCE_RAZOR_LIVE_TRACE_METRIC_JOB_TYPE_VERTEX2,
	SCE_RAZOR_LIVE_TRACE_METRIC_JOB_TYPE_FRAGMENT2,
	SCE_RAZOR_LIVE_TRACE_METRIC_JOB_TYPE_VERTEX3,
	SCE_RAZOR_LIVE_TRACE_METRIC_JOB_TYPE_FRAGMENT3,
	SCE_RAZOR_LIVE_TRACE_METRIC_JOB_TYPE_VERTEX0,
	SCE_RAZOR_LIVE_TRACE_METRIC_JOB_TYPE_FRAGMENT0
} SceRazorLiveTraceMetricJobType;

typedef struct SceRazorGpuLiveResultInfo {
	void *result_data;      //!< Pointer to the raw data results entries.
	SceSize entry_count;    //!< Number of elements stored in the results buffer
	SceSize overflow_count; //|< Number of results elements not included in the results buffer due to buffer overflow
	SceSize buffer_size;    //!< Size of the results buffer in bytes
	uint64_t start_time;    //!< Start time of the results collection in microseconds
	uint64_t end_time;      //!< End time of the results collection in microseconds
	uint32_t metric_group;  //!< Metrics group used for the results
	int reserved;           //!< Reserved data
} SceRazorGpuLiveResultInfo;

typedef struct SceRazorGpuLiveEntryHeader {
	uint16_t entry_size;  //!< Entry size in bytes
	uint16_t entry_type;  //!< Entry type (One of ::SceRazorLiveTraceMetricEntryType)
	int reserved;         //!< Reserved data
} SceRazorGpuLiveEntryHeader;

typedef struct SceRazorGpuLiveEntryJobVertexValues1 {
	float usse_vertex_processing_percent; //!< USSE vertex processing percentage
} SceRazorGpuLiveEntryJobVertexValues1;

typedef struct SceRazorGpuLiveEntryJobFragmentValues1 {
	float usse_fragment_processing_percent;         //!< USSE fragment processing percentage
	float usse_dependent_texture_reads_percent;     //!< USSE dependant texture reads requests percentage
	float usse_non_dependent_texture_reads_percent; //!< USSE non-dependant texture reads requests percentage
} SceRazorGpuLiveEntryJobFragmentValues1;

typedef struct SceRazorGpuLiveEntryJobVertexValues2 {
	uint32_t vdm_primitives_input_num;  //!< VDM input primitives  number
	uint32_t mte_primitives_output_num; //!< MTE output primitives number
	uint32_t vdm_vertices_input_num;    //!< VDM input vertices number
	uint32_t mte_vertices_output_num;   //!< MTE output vertices number
} SceRazorGpuLiveEntryJobVertexValues2;

typedef struct SceRazorGpuLiveEntryJobFragmentValues2 {
	uint32_t rasterized_pixels_before_hsr_num; //!< Number of rasterized pixels before Hidden Surface Removal
	uint32_t rasterized_output_pixels_num;     //!< Number of rasterized pixels
	uint32_t rasterized_output_samples_num;    //!< Number of rasterized samples
} SceRazorGpuLiveEntryJobFragmentValues2;

typedef struct SceRazorGpuLiveEntryJobVertexValues3 {
	uint32_t tiling_accelerated_mem_writes; //!< Amount of tiling accelerated memory writes in bytes
} SceRazorGpuLiveEntryJobVertexValues3;

typedef struct SceRazorGpuLiveEntryJobFragmentValues3 {
	uint32_t isp_parameter_fetches_mem_reads; //!< Amount of ISP parameter fetches memory reads in bytes
} SceRazorGpuLiveEntryJobFragmentValues3;

typedef struct SceRazorGpuLiveEntryJobValues {
	SceRazorGpuLiveEntryJobVertexValues1 vertex_values_type1;     //!< Values for a job of SCE_RAZOR_LIVE_TRACE_METRIC_JOB_TYPE_VERTEX1 type
	SceRazorGpuLiveEntryJobFragmentValues1 fragment_values_type1; //!< Values for a job of SCE_RAZOR_LIVE_TRACE_METRIC_JOB_TYPE_FRAGMENT1 type
	SceRazorGpuLiveEntryJobVertexValues2 vertex_values_type2;     //!< Values for a job of SCE_RAZOR_LIVE_TRACE_METRIC_JOB_TYPE_VERTEX2 type
	SceRazorGpuLiveEntryJobFragmentValues2 fragment_values_type2; //!< Values for a job of SCE_RAZOR_LIVE_TRACE_METRIC_JOB_TYPE_FRAGMENT2 type
	SceRazorGpuLiveEntryJobVertexValues3 vertex_values_type3;     //!< Values for a job of SCE_RAZOR_LIVE_TRACE_METRIC_JOB_TYPE_VERTEX3 type
	SceRazorGpuLiveEntryJobFragmentValues3 fragment_values_type3; //!< Values for a job of SCE_RAZOR_LIVE_TRACE_METRIC_JOB_TYPE_FRAGMENT3 type
	int reserved[8];                                              //!< Reserved data
} SceRazorGpuLiveEntryJobValues;

typedef struct SceRazorGpuLiveEntryJob {
	SceRazorGpuLiveEntryHeader header;        //!< Distinguishing header for the entry
	uint64_t start_time;                      //!< Start time of the entry in microseconds
	uint64_t end_time;                        //!< End time of the entry in microseconds
	uint8_t type;                             //!< The type of the job (One of ::SceRazorLiveTraceMetricJobType)
	int8_t core;                              //!< Core number on which the job got executed
	uint16_t scene_index;                     //!< Index of the scene in which the job got executed
	uint32_t frame_number;                    //!< Frame number in which the job got executed
	SceRazorGpuLiveEntryJobValues job_values; //!< Reported values by the job
	uint32_t process_id;                      //!< ID of the process which executed the job
	int unk;                                  //!< Unknown data
} SceRazorGpuLiveEntryJob;

typedef struct SceRazorGpuLiveEntryParameterBuffer {
	SceRazorGpuLiveEntryHeader header;       //!< Distinguishing header for the entry
	uint64_t peak_usage_timestamp;           //!< Time of param buffer peak usage in microseconds
	uint32_t peak_usage_value;               //!< Memory peak usage of the param buffer in bytes
	uint8_t partial_render;                  //!< Flag indicating wether a partial render occurred or not
	uint8_t vertex_job_paused;               //!< Flag indicating wether a vertex job had been paused or not
} SceRazorGpuLiveEntryParameterBuffer;

typedef struct SceRazorGpuLiveEntryFrame {
	SceRazorGpuLiveEntryHeader header;       //!< Distinguishing header for the entry
	uint64_t start_time;                     //!< Start time of the entry in microseconds
	uint32_t duration;                       //!< Duration of the frame in microseconds
	uint32_t frame_number;                   //!< Number of the frame
	uint32_t gpu_activity_duration_time;     //!< Duration of GPU activity for the frame in microseconds
	int reserved;                            //!< Reserved data
} SceRazorGpuLiveEntryFrame;

/**
 * Sets a metrics group to use for gpu live debugging
 *
 * @param[in] metrics - The metrics group to use (One of ::SceRazorGpuLiveMetricsGroup)
 *
 * @return 0, <0 on error.
*/
int sceRazorGpuLiveSetMetricsGroup(uint32_t metrics);

/**
 * Sets the buffer in which to store gpu live debugging results for the current frame
 *
 * @param[in] buffer - The buffer to use
 * @param[in] buf_size - The buffer size in bytes
 * @param[out] results - The debugging results of the previous frame
 *
 * @return 0, <0 on error.
*/
int sceRazorGpuLiveSetBuffer(void *buffer, SceSize buf_size, SceRazorGpuLiveResultInfo *results);

/**
 * Starts gpu live debugging
 *
 * @return 0, <0 on error.
*/
int sceRazorGpuLiveStart();

/**
 * Stops gpu live debugging
 *
 * @return 0, <0 on error.
*/
int sceRazorGpuLiveStop();

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_RAZOR_HUD_H_ */
