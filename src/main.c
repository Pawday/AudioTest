#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>




unsigned char* getData(void);


typedef struct
{
	unsigned long long sample_num;
	unsigned char* data;
} AudioData;

#define SAMPLE_RATE (44100)

void exit_error(char* str);


static int sound_callback
(
	const    void*                     input_buffer    ,
	         void*                     output_buffer   ,
	unsigned long                      framesPerBuffer ,
	const PaStreamCallbackTimeInfo*    timeInfo        ,
	PaStreamCallbackFlags              statusFlags     ,
	         void*                     userData
) 
{
	AudioData* data = (AudioData*) userData;
	short* out = (int*) output_buffer;

	unsigned long iter;

	//sample1 int16_t [ch1,ch2,ch3,ch4] 
	//sample2 int16_t [ch5,ch6,ch7,ch8]

	for (iter = 0; iter < framesPerBuffer; iter++) 
	{
		*out = *((short*)(data->data) + data->sample_num);
		out++;
		*out = *((short*)(data->data) + 1 + data->sample_num);
		out++;
		data->sample_num += 2;
	}

	return paContinue;
}

int main()
{
	PaStreamParameters outputParameters;
	PaStream* stream;
	PaError err;

	AudioData audio;

	audio.sample_num = 0;


	

	audio.data = getData();

	err = Pa_Initialize();

	if (err != paNoError) exit_error("ERR1");
	outputParameters.device = Pa_GetDefaultOutputDevice();
	if (outputParameters.device == paNoDevice) exit_error("NO DEVICE");

	outputParameters.channelCount = 2;
	outputParameters.sampleFormat = paInt16;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;

	err = Pa_OpenStream
	(
		&stream,
		NULL,
		&outputParameters,
		SAMPLE_RATE,
		100,
		paClipOff,
		sound_callback,
		&audio
	);

	if (err != paNoError) exit_error("ERR CREATE STREAM");

	Pa_StartStream(stream);

	system("chcp 1251");

	printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");

	printf("Я драм н бас продюсер\n");



	Pa_Sleep(3140);
	printf("Саня\n");

	Pa_Sleep((3762 - 3140));
	printf("\t\tХуй\n");

	Pa_Sleep((4098 - 3762));
	printf("Соси\n");


	Pa_Sleep(5039 - 4098);
	printf("\tСаня\n");

	Pa_Sleep((5538 - 5039));
	printf("\t\t\tХуй\n");

	Pa_Sleep((5909 - 5538));
	printf("\tСоси\n");


	Pa_Sleep((6978 - 5909));
	printf("Са\n");

	Pa_Sleep((7488 - 6978));
	printf("\tня\n");

	Pa_Sleep((7906 - 7488));
	printf("\t\tХуй\n");


	Pa_Sleep((8371 - 7906));
	printf("\t\t\tСо\n");

	Pa_Sleep((8789 - 8371));
	printf("\t\t\t\tси\n");


	Pa_Sleep((9300 - 8789));
	printf("\tХуй\n");

	Pa_Sleep((9729 - 9300));
	printf("\t\tСа\n");


	Pa_Sleep((10147 - 9729));
	printf("\tня\n");



	Pa_Sleep((10623 - 10147));
	printf("Саня\n");

	Pa_Sleep((10623 - 10147));
	printf("\tХуй\n");

	Pa_Sleep((4098 - 3762));
	printf("\t\tСоси\n");


	Pa_Sleep(5039 - 4098);
	printf("\t\t\tСаня\n");

	Pa_Sleep((5538 - 5039));
	printf("\tХуй\n");

	Pa_Sleep((5909 - 5538));
	printf("\t\tСоси\n");


	Pa_Sleep(1000);
	Pa_StopStream(stream);

	Pa_CloseStream(stream);

	Pa_Terminate();
}



void exit_error(char* str) 
{
	Pa_Terminate();
	printf(str);
	exit(-1);
}