/*
 * RealityAI_sound_classifier.h
 *
 *  Created on: May 17, 2019
 *      Author: matlab
 */

#ifndef REALITYAI_SOUND_CLASSIFIER_H_
#define REALITYAI_SOUND_CLASSIFIER_H_

/*Classifier Definitions*/
#define PREDICTION_BUFFER_LENGTH 8192
#define PREDICTION_BUFFER_LENGTH_memorex 8192
#define WINDOW_LENGTH 4096 //Length of the fft window
#define FFT_SIZE WINDOW_LENGTH //length of the fft window
#define STEP_SIZE WINDOW_LENGTH/2 //step size originally 2

/*Classifier 1 Definitions*/
#define NUM_CLASSES_c1 2
#define NUM_LEARNERS_c1 1
#define FEATURE_LENGTH_c1 2048

/*Classifier 2 Definitions*/
#define NUM_CLASSES_c2 2
#define NUM_LEARNERS_c2 1
#define FEATURE_LENGTH_c2 2048

/*Memorex Classifier Definitions*/
#define NUM_CLASSES_memorex 3
#define NUM_LEARNERS_memorex 1
#define FEATURE_LENGTH_memorex 2048

/*VOICEID Classifier Definitions*/
#define NUM_CLASSES_voiceid 5
#define NUM_LEARNERS_voiceid 5
#define FEATURE_LENGTH_voiceid 2048

/*RAI Classifier Definitions*/
/*List of possible classes returned by the classifier*/
typedef enum {noise,
	glass_breaking,
	car_horn,
	crying_baby,
	dog,
	foot_steps,
	siren,
	toilet_flush,
	vacuum_cleaner}NXP_classes;

typedef enum{memorex,
		live,
		memorex2}Memorex_classes;

typedef enum{xavier,
		ryan,
		nate,
		kirk,
		jeff
}VoiceID_classes;

typedef struct classifier_struct {
	const float* Beta;
	const float* Bias;
	const float* Mu;
	const float* Sigma;
	const float* coding_matrix;
	float* learner_scores;
	float* class_scores;
	int num_classes;
	int num_learners;
	int feature_length;
} classifier_struct, *classifier_struct_ptr;

typedef struct output_buffers {
	int out_buff[4];
	int num_results;
} output_buffers, *output_buffers_ptr;

typedef struct output_buffers_reg {
	float out_buff[4];
	int num_results;
} output_buffers_reg, *output_buffers_reg_ptr;

//const static char *result_str[8] = {"Car Horn\0","Crying Baby\0","Dog\0","Foot Steps\0","Glass Breaking\0","Siren\0","Toilet Flush\0","Vacuum Cleaner\0"};

/** @brief Performs classification on the E2C5 feature vector calculated on Sound
 *   the input classification parameters, and returns an enumerated class.
 *
 *   This function may be used to classify a single instance of data vectors of fixed window
 *   length into on output class, with the customer providing sampling and data handling.
 *
 *   Alternatively, we can provide data handling in which the customer passes streaming samples to
 *   a circular input buffer on which our classifier operates to detect and classify on-going events.
 *
 *  @param X(data vector, clasiifier_struct_prt, cls_defs_ptr), classifier parameter structure
 *  @return int.
 */

//memorex Classifies a window of WINDOW_LENGTH
NXP_classes RealityAI_memorex_classify(float *input_vector);

//glassbreak Classifies a window of WINDOW_LENGTH
NXP_classes RealityAI_glass_break_classify(float *input_vector);

//updated the floating point audio buffer (full_buff) with num_samples data samples from the input_buff
int update_audio_buffer(float* full_buff, int16_t* input_buff, int num_samples);

//shift and pad the smoothing buffers
void shift_and_pad_smoothing_buffers();



#endif /* REALITYAI_SOUND_CLASSIFIER_H_ */
